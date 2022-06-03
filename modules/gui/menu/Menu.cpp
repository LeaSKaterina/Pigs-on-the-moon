
#include "Menu.h"

Menu::Menu()
    : screen(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),
      playerName(GenerateName("Player")) {
    InitVariables();
    InitTextures();
    InitWindow();
    InitButtons();
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
                sf::FloatRect visibleArea(
                        0, 0,
                        (float) event.size.width,
                        (float) event.size.height);
                window->setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                auto mousePos = sf::Mouse::getPosition(*window);
                UpdateButtons(sf::Vector2f(mousePos.x, mousePos.y));
            }
        }

        window->display();
    }
}

void Menu::RunGame() {
    gameName = GenerateName();
    AIClient bot(playerName, password, gameName, numTurns, numPlayers);
    sf::Thread thread(&AIClient::StartAI, &bot);
    thread.launch();

    Controller controller(gameName, waitTime, numPlayers, window, muteMusic);
    thread.wait();
}

// Init Methods

void Menu::InitVariables() {
    muteMusic = true;
    numPlayers = 1;
}

void Menu::InitTextures() {
    textures.resize(numTextures);

    if (!textures[Texture::MAIN_BACKGROUND].loadFromFile(background_file_path))
        std::cerr << "ERROR::MENU:TEXTURE:" << background_file_path << std::endl;
    background.setTexture(textures[Texture::MAIN_BACKGROUND]);

    if (!textures[Texture::BATTLE_BUTTON].loadFromFile(battle_but_file_path))
        std::cerr << "ERROR::MENU:TEXTURE:" << battle_but_file_path << std::endl;
}

void Menu::InitWindow() {
    // get config
    std::ifstream config(config_view_file_path);
    std::string str((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
    config.close();
    nlohmann::json json = nlohmann::json::parse(str);

    // size
    float scale_width = json["sizeScale"]["width"];
    float scale_height = json["sizeScale"]["height"];
    width = screen.width * scale_width;
    height = screen.height * scale_height;

    // init window
    window = std::make_shared<sf::RenderWindow>(
            sf::VideoMode(width, height), "Best Course Work");
    // position
    float xPosition = json["position"]["x"];
    float yPosition = json["position"]["y"];

    window->setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window->setFramerateLimit(30);
    window->setVerticalSyncEnabled(true);
}

void Menu::InitButtons() {
    battle_but = std::make_unique<MenuButton>(textures[Texture::BATTLE_BUTTON]);
    battle_but->SetPosition(20., 20.);
}

// Render

void Menu::Render() {
    window->clear();
    window->draw(background);
    RenderButtons();
}

void Menu::RenderButtons() {
    battle_but->Draw(*window);
}

// Update

void Menu::UpdateButtons(sf::Vector2f mousePosition) {
    if (battle_but->GetBoundingRect().contains(mousePosition))
        RunGame();
}

std::string Menu::GenerateName(std::string&& prefix) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(1., 1000.);

    double generated_value = dist(mt);
    size_t value = generated_value * 1000000.;
    return prefix + std::to_string(value);
}
