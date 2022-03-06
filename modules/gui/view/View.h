#pragma once

#include "gui/screen.h"
#include "gameClient.h"
#include "gui/shapes/VehicleLogo.h"
#include "gui/model/Bot.h"
#include "MapView.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>


class View {
public:
    View(Game *game, sf::Mutex &gameMutex) : screen(sf::VideoMode::getDesktopMode().width,
                                                    sf::VideoMode::getDesktopMode().height),
                                             mapView(game, gameMutex) {
        std::ifstream config("resources/config/view.json");
        std::string str((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
        config.close();
        nlohmann::json json = nlohmann::json::parse(str);
        float width = json["sizeScale"]["width"];
        float height = json["sizeScale"]["height"];

        window.create(sf::VideoMode(int(screen.width * width), int(screen.height * height)), "jdsa");

        float xPosition = json["position"]["x"];
        float yPosition = json["position"]["y"];
        window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
        window.setFramerateLimit(30);
        window.setVerticalSyncEnabled(true);

        mapView.SetBorder({0, 0}, {1, 1});
    }

    void Show() {
        sf::Music music;
        this->PlayStartMusic(music);

        sf::Texture texture;
        if (!texture.loadFromFile("resources/image/background.jpg")) {
            std::cerr << "can't load texture" << '\n';
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);

        sf::View view = window.getDefaultView();

        while (window.isOpen()) {
            window.clear();
            window.draw(sprite);

            mapView.Draw(window);

            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::Resized) {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }
            }

            window.display();
        }

    }

private:
    const Screen screen;
    sf::RenderWindow window;
    MapView mapView;

    void PlayStartMusic(sf::Music &music) {
        if (!music.openFromFile("resources/music/Intro.ogg"))
            std::cerr << "can't load Intro music" << '\n';
//        music.play();
    }

};
