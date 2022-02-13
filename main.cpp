#include "gameClient.h"
#include "gui/screen.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

double xPosition = 0.2;
double yPosition = 0.2;
double width = 0.5;
double height = 0.6;

int main() {
    Screen screen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    sf::RenderWindow window(sf::VideoMode(screen.width * width, screen.height * height), "WoT_strategy_Pigs-on-the-moon");
    window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window.setFramerateLimit(30);

    sf::Music music;
    if (!music.openFromFile("resources/music/Intro.ogg"))
        std::cerr << "can't load Intro music" << '\n';
    music.play();

        GameClient gc;
        gc.InitGame("Den-Pig");
        gc.InitIds();

    sf::Texture texture;
    if (!texture.loadFromFile("resources/image/background.jpg")) {
        std::cerr << "can't load texture" << '\n';
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::CircleShape hex(50.f, 6);
        hex.setFillColor(sf::Color(100, 250, 50));
        hex.setRotation(30.f);
        window.draw(sprite);
        window.draw(hex);

        window.display();
    }

    return 0;
}