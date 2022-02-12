#include "gameClient.h"
#include "gui/screen.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

double xPosition = 0.2;
double yPosition = 0.2;
double width = 0.4;
double height = 0.4;

int main()
{
    Screen screen (sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    sf::RenderWindow window(sf::VideoMode(screen.width * width, screen.height * height), "WoT_strategy_Pigs-on-the-moon");
    window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window.setFramerateLimit(30);

    sf::Music music;
    if (!music.openFromFile("resources/music/Intro.ogg"))
        return -1; // error
    music.play();
//    GameClient gc;
//    gc.InitGame("Den-Pig");
//    gc.InitIds();
//    gc.



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
       {
            if (event.type == sf::Event::Closed)
                window.close();
       }

       sf::CircleShape hex(50.f, 6);
       hex.setFillColor(sf::Color(100, 250, 50));
       hex.rotate(30.f);
       window.draw(hex);

//       window.clear(sf::Color(250,220,100,0));
       window.display();
    }

    return 0;
}