
#include "Menu.h"

Menu::Menu()
    : screen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height) {
    InitVariables();
    InitTextures();
    InitWindow();
}

void Menu::Run() {
    sf::View view = window->getDefaultView();
    while (window->isOpen()) {
        Render();

        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, (float) event.size.width, (float) event.size.height);
                window->setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                // upd buttons
            }
        }

        window->display();
    }
}

void Menu::RunGame() {

}

// Init Methods

void Menu::InitVariables() {
    muteMusic = true;
    numPlayers = 3;
}

void Menu::InitTextures() {
    if (!main_background_texture.loadFromFile(background_file_path))
        std::cerr << "ERROR::MENU:TEXTURE" << background_file_path << std::endl;
    background.setTexture(main_background_texture);
}

void Menu::InitWindow() {
    // get config
    std::ifstream config(config_view_file_path);
    std::string str((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
    config.close();
    nlohmann::json json = nlohmann::json::parse(str);
    float width = json["sizeScale"]["width"];
    float height = json["sizeScale"]["height"];

    // init window
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(
                                                        (unsigned int) (screen.width * width),
                                                        (unsigned int) (screen.height * height)),
                                                "Best Course Work");

    // position
    float xPosition = json["position"]["x"];
    float yPosition = json["position"]["y"];

    window->setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window->setFramerateLimit(30);
    window->setVerticalSyncEnabled(true);
}

// Render

void Menu::Render() {
    window->clear();
    window->draw(background);
    RenderButtons();
}

void Menu::RenderButtons() {
    // TODO!
}
