#include <SFML/Graphics.hpp>
#include "defines.h"
#include "geometry.h"
#include "SimulatedDisk.h"
#include "Controller.h"
#include "PolicyNetwork.h"




Eigen::MatrixXd step()
{
    Eigen::VectorXd observation = Eigen::VectorXd::Zero(80*80);
    return observation;
}


Eigen::MatrixXd stack( std::vector<Eigen::VectorXd> xs)
{
    // stacks elements of std::vector<Eigen::VectorXd> to MatrixXd

    double* ptr = &xs[0];
    int nEntries = xs.size();
    int entries_per_vector = xs[0].rows();
    Eigen::Map<Eigen::MatrixXd> result(ptr, nEntries*entries_per_vector);

    // test MatrixXd content
    for(int i = 0; i < result.rows(); i++)
    {
        for(int i = 0; i < result.rows(); i++)
        {
            printf("matrix entry = %s", result(i,j));
        }
    }

    return result;
}


int main(int argc, char **argv)
{

    // SIMULATION PART

    // construct SimulatedDisk objects
    SimulatedDisk disk1(diskRadius, diskRadius, diskRadius, 50.);
    SimulatedDisk disk2(diskRadius, diskRadius, diskRadius, 10.);

    // construct Controller object
    Controller controller(controller_length, controller_height, WINSIZEX/2, WINSIZEY - controller_height/2);

    // sf shape primitives
    sf::CircleShape drawDisk1(diskRadius);
    sf::CircleShape drawDisk2(diskRadius);
    sf::RectangleShape drawController(sf::Vector2f(controller_length,controller_height));

    // set the origin of the drawDisk
    drawDisk1.setOrigin(diskRadius, diskRadius);
    drawDisk1.setFillColor(sf::Color::Red);
    drawDisk2.setOrigin(diskRadius, diskRadius);
    drawDisk2.setFillColor(sf::Color::Red);

    // set the origin of the controllerDisk
    drawController.setOrigin(controller_length/2, controller_height/2);
    drawController.setFillColor(sf::Color::White);

    // create RenderWindow object
    sf::RenderWindow window(sf::VideoMode(WINSIZEX, WINSIZEY), "Project 0 Simulator");


    // POLICYNETWORK PART

    PolicyNetwork pn;
    pn.initialize();

    int D = 20*20;

    Eigen::VectorXd prev_x = Eigen::VectorXd::Zero(D); // used in computing the difference frame
    std::vector<Eigen::VectorXd> xs,hs;
    std::vector<int> dlogps,drs;

    int running_reward = 0;
    int reward_sum = 0;
    int episode_number = 0;
    int counter = 0;

    // Simulation loop
    while (window.isOpen())
    {

        // SIMULATION part


        // check for keyboard events

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            controller.move(1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            controller.move(2);
        }

        // update disk positions according to gravity and user input
        disk1.updatePosition();
        disk2.updatePosition();
        controller.updatePosition();


        // detect collisions between disks and controller
        collisionDetect(disk1, controller, diskRadius);
        collisionDetect(disk2, controller, diskRadius);


        // set new positions of both disks
        drawDisk1.setPosition(disk1.getPositionX(), disk1.getPositionY());
        drawDisk2.setPosition(disk2.getPositionX(), disk2.getPositionY());
        drawController.setPosition(controller.getPositionX(), controller.getPositionY());

        // draw and display disks
        window.clear();
        window.draw(drawDisk1);
        window.draw(drawDisk2);
        window.draw(drawController);
        window.display();

        auto image = window.capture();
        auto image_ptr = image.getPixelsPtr();


        // POLICYNETWORK part

        int D = 80*80;
        int H = 200;

        //   cur_x = prepro()
        auto cur_x = pn.prepro();

        // x = cur_x - prev_x if prev_x is not None else np.zeros(D)
        auto x = cur_x - prev_x;

        // update prev_x
        prev_x = cur_x;

        // aprob, h = policy_forward(x)
        auto aprob_and_h = pn.policy_forward(x);

        auto aprob = aprob_and_h.first;
        auto h = aprob_and_h.second;
        
        // action = 2 if np.random.uniform() < aprob else 3 # roll the dice!
        int action = 2; // TODO: replace

        //  record various intermediates (needed later for backprop)

        //  xs.append(x) # observation
        xs.push_back(x);
        //  hs.append(h) # hidden state
        hs.push_back(h);
        //  y = 1 if action == 2 else 0 # a "fake label"
        int y;
        if (action == 2)
        {
            y = 2;
        } else
        {
            y = 0;
        }
        
        //  dlogps.append(y - aprob) # grad that encourages the action that was taken to be taken (see http://cs231n.github.io/neural-networks-2/#losses if confused)
        dlogps.push_back(y - aprob);
        //  step the environment and get new measurements
        //  observation, reward, done = step(action,counter)
        Eigen::MatrixXd observarion = step(action,counter);
        
        done = counter % 10 == 0;
        float reward = 1.0;
        //  reward_sum += reward

        reward_sum += reward;
        //  drs.append(reward) # record reward (has to be done after we call step() to get reward for previous action)
        drs.push_back(reward);

        if(done) // episode finished
        {
            episode_number += 1;

            // stack together all inputs, hidden states, action gradients, and rewards for this episode
            // epx = np.vstack(xs)
            Eigen::MatrixXd epx = stack(xs);

            // eph = np.vstack(hs)
            Eigen::MatrixXd eph = np.stack(hs);

            // epdlogp = np.vstack(dlogps)
            Eigen::MatrixXd epdlogp = np.stack(dlogps);

            // epr = np.vstack(drs)
            Eigen::MatrixXd epr = np.stack(drs);

            // xs,hs,dlogps,drs = [],[],[],[] # reset array memory
            xs.clear();
            hs.celar();
            dlogps.clear();
            drs.clear();

            // # compute the discounted reward backwards through time
            Eigen::MatrixXd discounted_epr = discount_rewards(epr);
            
            // # standardize the rewards to be unit normal (helps control the gradient estimator variance)
            // discounted_epr -= np.mean(discounted_epr)
            // discounted_epr /= np.std(discounted_epr)
            discounted_epr -= discounted_epr.mean();
            // TODO: add also standard deviation normalization

            // epdlogp *= discounted_epr # modulate the gradient with advantage (PG magic happens right here.)
            epdlogp *= discounted_epr;

            // grad = policy_backward(eph, epdlogp)
            auto grad = pn.policy_backward(eph,epdlogp);

            // for k in model: grad_buffer[k] += grad[k] # accumulate grad over batch
            grad_buffer_W1 = grad.first;
            grad_buffer_W2 = grad.second;


            // perform rmsprop parameter update every batch_size episodes
            if (episode_number % batch_size == 0)
            {
            //   for k,v in model.iteritems():
            //     g = grad_buffer[k] # gradient
            //     rmsprop_cache[k] = decay_rate * rmsprop_cache[k] + (1 - decay_rate) * g**2
            //     model[k] += learning_rate * g / (np.sqrt(rmsprop_cache[k]) + 1e-5)
            //     grad_buffer[k] = np.zeros_like(v) # reset batch gradient buffer

                // W1:
                auto g_W1 = grad_buffer_W1;
                rmsprop_cache_W1 = pn.decay_rate * rmsprop_cache_W1 + (1.0-pn.decay_rate)* g_W1.cwiseProduct(g_W1);
                pn.W1 = learning_rate * g_W1 / (rmsprop_cache_W1.sqrt() + 1e-5);
                grad_buffer_W1 = Eigen::VectorXd::Zero(H,D);

                // W2:
                auto g_W2 = grad_buffer_W2;
                rmsprop_cache_W2 = pn.decay_rate * rmsprop_cache_W2 + (1.0-pn.decay_rate)* g_W2.cwiseProduct(g_W2);
                pn.W2 = learning_rate * g_W2 / (rmsprop_cache_W2.sqrt() + 1e-5);
                grad_buffer_W2 = Eigen::VectorXd::Zero(H);
            }


            // boring book-keeping
            // running_reward = reward_sum if running_reward is None else running_reward * 0.99 + reward_sum * 0.01
            if(running_reward == 0)
            {
                running_reward = reward_sum;
            }
            else
            {
                running_reward = running_reward * 0.99 + reward_sum * 0.01;
            }
            printf("resetting env. Episode reward total was %f. Running mean: %f\n", reward_sum, running_reward);
            reward_sum = 0;

            // prev_x = None
            prev_x = Eigen::VectorXd::Zero(D);
        }
    }

    return 0;
}