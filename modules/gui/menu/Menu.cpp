
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
    std::cout << "|=============GAME NAME=============|\t" << gameName << std::endl;
    AIClient bot(playerName, password, gameName, numTurns, numPlayers);
    sf::Thread thread(&AIClient::StartAI, &bot);
    thread.launch();

    Controller controller(gameName, waitTime, numPlayers, window, muteMusic);
    controller.Run();
    thread.wait();
}

// Init Methods

void Menu::InitVariables() {
    muteMusic = true;
    numPlayers = 1;
}

void Menu::InitTextures() {
    textures.resize(numTextures + numOtherButtons * 2);

    if (!textures[Texture::MAIN_BACKGROUND].loadFromFile(background_file_path))
        std::cerr << "ERROR::MENU:TEXTURE:" << background_file_path << std::endl;
    background.setTexture(textures[Texture::MAIN_BACKGROUND]);

    if (!textures[Texture::BATTLE_BUTTON].loadFromFile(battle_but_file_path))
        std::cerr << "ERROR::MENU:TEXTURE:" << battle_but_file_path << std::endl;

    for (int i = 0, j = OTHER_BUTTONS; i < numOtherButtons; i++, j+=2) {
        std::string source_on = number_but_on_template + std::to_string(i + 1) + number_but_file_template;
        std::string source_off = number_but_off_template + std::to_string(i + 1) + number_but_file_template;
        if (!textures[j].loadFromFile(source_on))
            std::cerr << "ERROR::MENU:TEXTURE:" << source_on << std::endl;
        if (!textures[j + 1].loadFromFile(source_off))
            std::cerr << "ERROR::MENU:TEXTURE:" << source_off << std::endl;
    }
}

void Menu::InitWindow() {
    // get config
    std::ifstream config(config_view_file_path);
    std::string str((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
    config.close();
    nlohmann::json json = nlohmann::json::parse(str);

    // size
    float scaleWidth = json["sizeScale"]["width"];
    float scaleHeight = json["sizeScale"]["height"];
    width = screen.width * scaleWidth;
    height = screen.height * scaleHeight;

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

    auto w = window->getSize();
    float x_pos = w.x - 20 - 84 * numOtherButtons;
    float y_pos = w.y - 84;

    for (int i = 0, j = OTHER_BUTTONS; i < numOtherButtons; i++, j+=2) {
        number_buttons.push_back(std::make_unique<MenuButton>(textures[j], textures[j + 1], i + 1));
        number_buttons[i]->SetPosition(x_pos, y_pos);
        x_pos += 84;
    }

    // default numValue = 1
    number_buttons[0]->Click();
}

// Render

void Menu::Render() {
    window->clear();
    window->draw(background);
    RenderButtons();
}

void Menu::RenderButtons() {
    battle_but->Draw(*window);
    for(auto& but : number_buttons)
        but->Draw(*window);
}

// Update

void Menu::UpdateButtons(sf::Vector2f mousePosition) {
    if (battle_but->GetBoundingRect().contains(mousePosition))
        RunGame();

    for (auto& but: number_buttons) {
        but->Click(false);
        if (but->GetBoundingRect().contains(mousePosition)) {
            but->Click(true);
            numPlayers = but->Value();
        }
    }
}

std::string Menu::GenerateName(std::string&& prefix) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<double> dist(1., 1000.);

    double generated_value = dist(mt);
    size_t value = generated_value * 1000000.;
    return prefix + std::to_string(value);
}
