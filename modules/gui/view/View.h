#pragma once

#include "MapView.h"
#include "gameClient.h"
#include "gui/screen.h"
#include "gui/shapes/VehicleLogo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

class Controller;

class View {
public:
    View(Controller &controller, const Game *game, sf::Mutex &gameMutex, bool unmute_music = false);

    void Show();

private:
    const Screen screen;
    sf::RenderWindow window;
    MapView mapViewModel;
    Controller &controller;
    const std::string music_file_path = "resources/music/Intro.ogg";
    const std::string config_view_file_path = "resources/config/view.json";
    const std::string background_file_path = "resources/image/background.jpg";
    bool play_music;

    void PlayStartMusic(sf::Music &music);
};
