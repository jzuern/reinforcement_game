#include <SFML/Graphics.hpp>
#include "defines.h"

#include "SimulatedDisk.h"


int main(int argc, char **argv)
{


    sf::RenderWindow window(sf::VideoMode(WINSIZEX, WINSIZEY), "Project 0 Simulator");


    float diskRadius = 100.0;
    float diskMass = 10.0;

    SimulatedDisk simDisk(diskMass,diskRadius);

    sf::CircleShape drawDisk(diskRadius);

    // set the origin of the drawDisk
    drawDisk.setOrigin(diskRadius, diskRadius);

    drawDisk.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            simDisk.setPosition(100.,100.);
        }

        
        simDisk.updatePosition();


        drawDisk.setPosition(simDisk.getPositionX(), simDisk.getPositionY());

        window.clear();
        window.draw(drawDisk);
        window.display();
    }

    return 0;
}