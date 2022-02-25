#include "gameClient.h"
#include "gui/screen.h"
#include "gui/shapes/VehicleLogo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

double xPosition = 0.2;
double yPosition = 0.2;
double width = 0.5;
double height = 0.6;
int size = 17;
Screen center;


void ClientThreadFunction(GameClient *gc) {
    gc->StartAI();
}

int main() {
    Screen screen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    sf::RenderWindow window(sf::VideoMode(screen.width * width, screen.height * height), "Pigs-on-the-moon_GUI");

    window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    center = {window.getSize().x / 2, window.getSize().y / 2};

    sf::Music music;
    if (!music.openFromFile("resources/music/Intro.ogg"))
        std::cerr << "can't load Intro music" << '\n';
    music.play();

    std::string game = "game3";
    GameClient gc;
    GameClient gc2;
    GameClient gc3;
    gc.InitGame("Den-Pig", "", game, 0, 3);
    gc2.InitGame("Den-Pig2", "", game, 0, 3);
    gc3.InitGame("Den-Pig3", "", game, 0, 3);
    sf::Thread thread(ClientThreadFunction, &gc);
    sf::Thread thread2(ClientThreadFunction, &gc2);
    sf::Thread thread3(ClientThreadFunction, &gc3);
    thread.launch();
    thread2.launch();
    thread3.launch();

    sf::Texture texture;
    if (!texture.loadFromFile("resources/image/background.jpg")) {
        std::cerr << "can't load texture" << '\n';
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::CircleShape hex(size * 0.8, 6);
    hex.setOutlineThickness(1.f);
    hex.setFillColor(sf::Color::Transparent);
    hex.setOrigin(hex.getLocalBounds().width / 2, hex.getLocalBounds().height / 2);
    hex.setRotation(30.f);

    VehicleLogo vehicleLogo(size * 0.4);

    GameClient guiClient;
    guiClient.InitGame("Den-Pig", "", game, 0, 3);
    guiClient.InitIds();
    guiClient.UpdateGameState();

    const auto &vehiclesVectors = guiClient.GetGame()->GetVehicles();
    auto map = guiClient.GetGame()->GetMap();

    sf::Font font;
    if (!font.loadFromFile("resources/font/nimbusMono.ttf")) {
        std::cerr << "Error! Font isn't loaded!" << '\n';
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(size * 0.6);
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

    while (window.isOpen()) {
        window.draw(sprite);
        //draw grid
        guiClient.UpdateGameState();
        for (const auto point : map->GetGrid()) {
            hex.setOutlineColor(sf::Color::Green);
            hex.setFillColor(sf::Color::Transparent);
            if (map->GetType(*point.second) == ConstructionsTypes::BASE) hex.setOutlineColor(sf::Color::Blue);
            if (map->GetType(*point.second) == ConstructionsTypes::OBSTACLE) {
                hex.setOutlineColor(sf::Color::Red);
                hex.setFillColor(sf::Color(255, 20, 20, 70));
            }
            int x = size * 3. / 2 * point.first.x + center.width;
            int y = size * (sqrt(3) / 2 * point.first.x + std::sqrt(3) * point.first.y) + center.height;
            hex.setPosition(x, y);
            window.draw(hex);
        }


        for (int i = 0; i < vehiclesVectors.size(); i++) {
            vehicleLogo.ChangeColorById(i);
            for (int j = 0; j < vehiclesVectors[i].size(); j++) {
                auto logo = vehicleLogo.GetLogoByType(VehiclesTypes::Type(j));
                auto point = vehiclesVectors[i][j]->GetCurrentPosition();
                int x = size * 3. / 2 * point.x + center.width;
                int y = size * (sqrt(3) / 2 * point.x + std::sqrt(3) * point.y) + center.height - 2;
                std::get<0>(logo).setPosition(x, y);
                window.draw(std::get<0>(logo));
                if (std::get<1>(logo)) {
                    std::get<1>(logo)->setPosition(x, y);
                    window.draw(*std::get<1>(logo));
                }

                text.setString(std::to_string(vehiclesVectors[i][j]->GetHp()));
                text.setFillColor(std::get<0>(logo).getOutlineColor());
                text.setPosition(x, y + 4);
                window.draw(text);
            }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                thread.terminate();
                thread2.terminate();
                thread3.terminate();
                window.close();
            }
        }


        guiClient.SendTurn();
        window.display();
   }

    return 0;
}