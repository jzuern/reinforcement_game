#include <SFML/Graphics.hpp>
#include "defines.h"
#include "geometry.h"

#include "SimulatedDisk.h"
#include "Controller.h"

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

    Eigen::VectorXd prev_x = Eigen::VectorXd::Zeros(D); // used in computing the difference frame
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

        //   cur_x = prepro()
        auto cur_x = pn.prepro();

        // x = cur_x - prev_x if prev_x is not None else np.zeros(D)
        auto x = cur_x - prev_x;

        prev_x = cur_x;

        // aprob, h = policy_forward(x)
        auto p_and_h = pn.policy_forward(x);


    }

    return 0;
}