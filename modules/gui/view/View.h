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

class Controller;

class View {
public:
    View(Controller &controller, Game *game, sf::Mutex &gameMutex) : controller(controller),
                                                                     screen(sf::VideoMode::getDesktopMode().width,
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

    void Show();

private:
    const Screen screen;
    sf::RenderWindow window;
    MapView mapView;
    Controller &controller;

    void PlayStartMusic(sf::Music &music) {
        if (!music.openFromFile("resources/music/Intro.ogg"))
            std::cerr << "can't load Intro music" << '\n';
        music.play();
    }

};
