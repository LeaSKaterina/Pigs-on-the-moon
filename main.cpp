#include "gameClient.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
       {
            if (event.type == sf::Event::Closed)
                window.close();
       }
       window.clear(sf::Color(250,220,100,0));
        window.display();
    }

    return 0;
}