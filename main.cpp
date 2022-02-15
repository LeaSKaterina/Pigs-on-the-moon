#include "gameClient.h"
#include "gui/screen.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

double xPosition = 0.2;
double yPosition = 0.2;
double width = 0.5;
double height = 0.6;
int size = 15;
Screen center;

int main() {
    Screen screen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    sf::RenderWindow window(sf::VideoMode(screen.width * width, screen.height * height), "WoT_strategy_Pigs-on-the-moon");

    window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window.setFramerateLimit(30);
    center = {window.getSize().x / 2, window.getSize().y / 2};

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

    sf::CircleShape hex(size - 3, 6);
    hex.setOutlineThickness(1.f);
    hex.setFillColor(sf::Color::Transparent);
    hex.setOutlineColor(sf::Color(100, 250, 50));
    hex.setRotation(30.f);


    while (window.isOpen()) {
        window.draw(sprite);
        auto grid = gc.GetGame()->GetMap()->GetGrid();
        for (auto point : grid) {
            int x = size * 3. / 2 * point.first.points[0] + center.width;
            int y = size * (sqrt(3) / 2 * point.first.points[0] + std::sqrt(3) * point.first.points[1]) + center.height;
            hex.setPosition(x, y);
            window.draw(hex);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }


        window.display();
    }

    return 0;
}