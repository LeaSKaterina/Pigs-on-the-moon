#pragma once

#include "gui/controller/Controller.h"
#include "gui/screen.h"
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <memory>
#include <fstream>


class Menu {
public:
    Menu();

    void Run();

private:
    // view elements
    const Screen screen;
    std::unique_ptr<sf::RenderWindow> window;

    // consts
    const std::string background_file_path = "resources/image/menu_background.jpg";
    const std::string config_view_file_path = "resources/config/view.json";
    const int waitTime = 0;
    const int numTurns = 45;

    //resources
    sf::Texture main_background_texture;
    sf::Sprite background;

    // control variables
    bool muteMusic;
    int numPlayers;
    std::string gameName;

    // methods

    // RunMethods
    void RunGame();

    // Render
    void Render();
    void RenderButtons();

    // Init methods

    void InitVariables();
    void InitTextures();
    void InitWindow();
};
