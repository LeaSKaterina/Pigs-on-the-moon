#pragma once

#include "MenuButton.h"
#include "gui/controller/Controller.h"
#include "gui/screen.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>


class Menu {
public:
    Menu();

    void Run();

private:
    // view elements
    const Screen screen;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<MenuButton> battle_but;

    // consts
    const std::string config_view_file_path = "resources/config/view.json";
    const std::string background_file_path = "resources/image/menu_background.jpg";
    const std::string battle_but_file_path = "resources/image/battle_button.jpg";
    const int waitTime = 0;
    const int numTurns = 45;

    //resources
    const int numTextures = 2;
    enum Texture {
        MAIN_BACKGROUND,
        BATTLE_BUTTON,
    };

    std::vector<sf::Texture> textures;
    sf::Sprite background;

    // control variables
    unsigned int width;
    unsigned int height;

    bool muteMusic;
    int numPlayers;
    std::string gameName;

    // methods

    // RunMethods
    void RunGame();

    // Render
    void Render();
    void RenderButtons();

    // Update
    void UpdateButtons(sf::Vector2f mousePosition);

    // Init methods

    void InitVariables();
    void InitTextures();
    void InitWindow();
    void InitButtons();
};
