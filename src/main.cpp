#include <SFML/Graphics.hpp>
#include "defines.h"
#include "util.h"
#include "SimulatedDisk.h"
#include "Controller.h"
#include "PolicyNetwork.h"

#include <unistd.h>
#include <time.h>
#include <cfloat>




int main(int argc, char **argv)
{

    // SIMULATION PART

    // construct SimulatedDisk objects
    double disk_pos_x = rand_double(diskRadius, WINSIZEX-diskRadius);
    SimulatedDisk disk1(diskRadius, disk_pos_x, diskRadius);
    disk1.setVelocity(rand_double(5.0,10.0),rand_double(5.0, 10.0));

    // construct Controller object
    double controller_x_pos = WINSIZEX/2;
    double controller_y_pos = WINSIZEY - controller_height/2;

    Controller controller(controller_length, controller_height, controller_x_pos, controller_y_pos);

    // sf shape primitives
    sf::CircleShape drawDisk1(diskRadius);
    sf::RectangleShape drawController(sf::Vector2f(controller_length,controller_height));

    // set the origin of the drawDisk
    drawDisk1.setOrigin(diskRadius, diskRadius);
    drawDisk1.setFillColor(sf::Color::White);

    // set the origin of the controllerDisk
    drawController.setOrigin(controller_length/2, controller_height/2);
    drawController.setFillColor(sf::Color::White);

    // create RenderWindow object
    sf::RenderWindow window(sf::VideoMode(WINSIZEX, WINSIZEY), "Project 0 Simulator");



    // POLICYNETWORK PART

    PolicyNetwork pn;
    pn.initialize();

    int D = 50*50;
    int H = pn.nHidden;


    Eigen::VectorXd prev_x = Eigen::VectorXd::Zero(D); // used in computing the difference frame
    std::vector<Eigen::VectorXd> xs,hs;
    std::vector<double> dlogps,drs;

    double running_reward = 0.0;
    double reward_sum = 0.0;
    int episode_number = 0;
    int counter = 1;

    // Simulation loop
    while (true)
    {
        // POLICYNETWORK part
        clock_t t_start,t_end;
        t_start=clock();


        //   cur_x = prepro()
        Eigen::VectorXd cur_x = prepro(window);

        // x = cur_x - prev_x if prev_x is not None else np.zeros(D)
        Eigen::VectorXd x = cur_x - prev_x;

        // update prev_x
        prev_x = cur_x;

        // aprob, h = policy_forward(x)
        auto aprob_and_h = pn.policy_forward(x);

        double aprob = aprob_and_h.first;
        Eigen::VectorXd h = aprob_and_h.second;

        // action = 2 if np.random.uniform() < aprob else 3 # roll the dice!
        float rand_float = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
        int action = 2;
        if (rand_float < aprob)
        {
            action = 1;
        }

        //  xs.append(x) # observation
        xs.push_back(x);
        //  hs.append(h) # hidden state
        hs.push_back(h);
        //  y = 1 if action == 2 else 0 # a "fake label"
        int y;
        if (action == 1)
        {
            y = 1;
        } else
        {
            y = 0;
        }

        //  dlogps.append(y - aprob) # grad that encourages the action that was taken to be taken (see http://cs231n.github.io/neural-networks-2/#losses if confused)
        dlogps.push_back(y - aprob);

        //  step the environment and get new measurements
        //  observation, reward, done = step(action,counter)


        if (action == 1)
        {
            controller.move(1);
        }
        else if (action == 2)
        {
            controller.move(2);
        }

        // update disk positions according to gravity and user input
        bool disk1_oob = disk1.updatePosition();

        controller.updatePosition();

        // detect collisions between disks and controller
        bool touched = collisionDetect(disk1, controller, diskRadius);

        double reward = -1.0; // TODO: reward okay like that?
        if(touched) reward = 10.0; // if controller touched ball: give reward!

        // set new positions of both disks
        drawDisk1.setPosition(disk1.getPositionX(), disk1.getPositionY());
        drawController.setPosition(controller.getPositionX(), controller.getPositionY());


        // draw and display disks
        if(episode_number % 100 == 0 && episode_number != 0)
        {
            window.clear();
            window.draw(drawDisk1);
            window.draw(drawController);
            window.display();
            usleep(20000);
        }



        reward_sum += reward;
        //  drs.append(reward) # record reward (has to be done after we call step() to get reward for previous action)
        drs.push_back(reward);

        if(disk1_oob) // episode finished
        {
            episode_number += 1;

            // stack together all inputs, hidden states, action gradients, and rewards for this episode
            // epx = np.vstack(xs)
            Eigen::MatrixXd epx = stack(xs);

            // eph = np.vstack(hs)
            Eigen::MatrixXd eph = stack(hs);

            // epdlogp = np.vstack(dlogps)
            Eigen::VectorXd epdlogp = stack_vector(dlogps);

            // epr = np.vstack(drs)
            Eigen::VectorXd epr = stack_vector(drs);

            // xs,hs,dlogps,drs = [],[],[],[] # reset array memory
            xs.clear();
            hs.clear();
            dlogps.clear();
            drs.clear();

            // # compute the discounted reward backwards through time
            Eigen::VectorXd discounted_epr = pn.discount_rewards(epr);

            // # standardize the rewards to be unit normal (helps control the gradient estimator variance)
            // discounted_epr -= np.mean(discounted_epr)
            // discounted_epr /= np.std(discounted_epr)
            double mean = discounted_epr.mean();
            double stddev = std_dev(discounted_epr, mean);

//            Eigen::VectorXd discounted_epr_mean = discounted_epr.array() - mean;
//            Eigen::VectorXd discounted_epr_mean_stddev = discounted_epr_mean.array() / stddev;
            auto discounted_epr_mean_stddev = discounted_epr;

            // TODO: add also standard deviation normalization

            // epdlogp *= discounted_epr # modulate the gradient with advantage (PG magic happens right here.)
            Eigen::VectorXd epdlogp_discounted = epdlogp.array() * discounted_epr_mean_stddev.array();


            // grad = policy_backward(eph, epdlogp)
            auto grad = pn.policy_backward(eph,epdlogp_discounted,epx);

            // for k in model: grad_buffer[k] += grad[k] # accumulate grad over batch
            pn.grad_buffer_W1 = grad.first;
            pn.grad_buffer_W2 = grad.second;

            if(std::isnan(pn.grad_buffer_W2(0)))
            {
                printf("Program terminated due to NANs\n");
                EXIT_FAILURE;
            }


            // perform rmsprop parameter update every batch_size episodes
            if (episode_number % pn.batch_size == 0)
            {
            //   for k,v in model.iteritems():
            //     g = grad_buffer[k] # gradient
            //     rmsprop_cache[k] = decay_rate * rmsprop_cache[k] + (1 - decay_rate) * g**2
            //     model[k] += learning_rate * g / (np.sqrt(rmsprop_cache[k]) + 1e-5)
            //     grad_buffer[k] = np.zeros_like(v) # reset batch gradient buffer

                // W1:
                auto g_W1 = pn.grad_buffer_W1;
                pn.rmsprop_cache_W1 = pn.decay_rate * pn.rmsprop_cache_W1 + (1.0-pn.decay_rate)* g_W1.cwiseProduct(g_W1);
                pn.W1 = pn.learning_rate * g_W1.array() / (pn.rmsprop_cache_W1.array().sqrt() + 1e-5);
                pn.grad_buffer_W1 = Eigen::MatrixXd::Zero(H,D); // reset W1 buffer

                // // W2:
                auto g_W2 = pn.grad_buffer_W2;
                pn.rmsprop_cache_W2 = pn.decay_rate * pn.rmsprop_cache_W2 + (1.0-pn.decay_rate)* g_W2.cwiseProduct(g_W2);
                pn.W2 = pn.learning_rate * g_W2.array() / (pn.rmsprop_cache_W2.array().sqrt() + 1e-5);
                pn.grad_buffer_W2 = Eigen::VectorXd::Zero(H); // reset W2 buffer

                t_end = clock();
                float diff = ((float)t_end-(float)t_start) / CLOCKS_PER_SEC;
                t_start = clock();
                printf("      time per batch = %f.\n", diff);

            }


            // boring book-keeping
            // running_reward = reward_sum if running_reward is None else running_reward * 0.99 + reward_sum * 0.01
            if(running_reward == 0.0)
            {
                running_reward = reward_sum;
            }
            else
            {
                running_reward = running_reward * 0.99 + reward_sum * 0.01;
            }
            printf("Resetting env. Episode reward total was %f. Running mean: %f\n", reward_sum, running_reward);
            reward_sum = 0.0;

            // prev_x = None
            prev_x = Eigen::VectorXd::Zero(D);


            disk1.setPosition(rand_double(diskRadius, WINSIZEX-diskRadius) , diskRadius); // reset disk position
            disk1.setVelocity(rand_double(-10.0, 10.0),rand_double(-10.0, 10.0)); // reset disk speed

            controller.setPosition(controller_x_pos,controller_y_pos); // reset controller position

            printf("episode %i finished.\n", episode_number);


        }
        counter += 1;

    }

}