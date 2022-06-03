#pragma once

#include "MapView.h"
#include "gameClient.h"
#include "gui/screen.h"
#include "gui/shapes/VehicleLogo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

class Controller;

class View {
public:
    // Console controller
    View(Controller &controller, const Game *game, sf::Mutex &gameMutex, bool mute_music = true);

    // Menu controller
    View(Controller &controller, const Game *game, sf::Mutex &gameMutex,
         std::shared_ptr<sf::RenderWindow> &renderWindow, bool mute_music);

    // Basic
    View(Controller &controller, const Game *game, sf::Mutex &gameMutex, bool mute_music, bool basic);

    void Show();

private:
    // elements
    std::shared_ptr<sf::RenderWindow> window;
    MapView mapViewModel;
    Controller &controller;
    const Game* game;

    // resources
    const std::string music_file_path = "resources/music/Intro.ogg";
    const std::string config_view_file_path = "resources/config/view.json";
    const std::string background_file_path = "resources/image/view_background.jpg";

    // controls
    bool play_music;

    void PlayStartMusic(sf::Music &music);
};
