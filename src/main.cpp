#include <SFML/Graphics.hpp>
#include "defines.h"
#include "geometry.h"

#include "SimulatedDisk.h"
#include "ControllerDisk.h"

int main(int argc, char **argv)
{


    sf::RenderWindow window(sf::VideoMode(WINSIZEX, WINSIZEY), "Project 0 Simulator");


    float simDiskRadius = 100.0;
    float simDiskMass = 10.0;

    float controllerDiskRadius = 50.0;

    SimulatedDisk simDisk(simDiskMass, simDiskRadius, 100., 100.);
    ControllerDisk controllerDisk(controllerDiskRadius, WINSIZEY-controllerDiskRadius, WINSIZEX/2);

    sf::CircleShape drawDiskSim(simDiskRadius);
    sf::CircleShape drawDiskController(controllerDiskRadius);

    // set the origin of the drawDisk
    drawDiskSim.setOrigin(simDiskRadius, simDiskRadius);
    drawDiskSim.setFillColor(sf::Color::Red);

    // set the origin of the controllerDisk
    drawDiskController.setOrigin(controllerDiskRadius, controllerDiskRadius);
    drawDiskController.setFillColor(sf::Color::Green);


    while (window.isOpen())
    {


        // reset controller Disk speed
        controllerDisk.setVelocity(0.0, 0.0);

        // check for keyboard events

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            controllerDisk.move(1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            controllerDisk.move(2);
        }

        // update disk positions according to gravity and user input
        simDisk.updatePosition();
        controllerDisk.updatePosition();


        // detect collisions between disks
        collisionDetect(simDisk, controllerDisk, controllerDiskRadius, simDiskRadius);


        // set new positions of both disks
        drawDiskSim.setPosition(simDisk.getPositionX(), simDisk.getPositionY());
        drawDiskController.setPosition(controllerDisk.getPositionX(), controllerDisk.getPositionY());

        // draw and display disks
        window.clear();
        window.draw(drawDiskSim);
        window.draw(drawDiskController);
        window.display();
    }

    return 0;
}