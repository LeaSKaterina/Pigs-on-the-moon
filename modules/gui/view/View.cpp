#include "View.h"
#include "gui/controller/Controller.h"

View::View(Controller &controller, const Game *game, sf::Mutex &gameMutex, bool mute_music)
    : View(controller, game, gameMutex, mute_music, true) {

    const Screen screen(sf::VideoMode::getDesktopMode().width,
                        sf::VideoMode::getDesktopMode().height);

    std::ifstream config(config_view_file_path);
    std::string str((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
    config.close();
    nlohmann::json json = nlohmann::json::parse(str);
    float width = json["sizeScale"]["width"];
    float height = json["sizeScale"]["height"];

    window = std::make_shared<sf::RenderWindow>();

    window->create(sf::VideoMode(
                           (unsigned int) (screen.width * width),
                           (unsigned int) (screen.height * height)),
                   "Best Course Work");

    float xPosition = json["position"]["x"];
    float yPosition = json["position"]["y"];
    window->setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window->setFramerateLimit(30);
    window->setVerticalSyncEnabled(true);

    mapViewModel.Resize(window->getSize());
}

View::View(Controller &controller, const Game *game, sf::Mutex &gameMutex,
           std::shared_ptr<sf::RenderWindow> &renderWindow, bool muteMusic)
    : View(controller, game, gameMutex, muteMusic, true) {
    window = renderWindow;
    mapViewModel.Resize(window->getSize());
}

View::View(Controller &controller, const Game *game, sf::Mutex &gameMutex, bool mute_music, bool)
    : controller(controller),
      mapViewModel(game, gameMutex, {0, 0}, {1, 1}),
      play_music(!mute_music),
      game(game) {
    InitTextures();
    InitSprites();
}


void View::Wait() {
    window->clear();
    window->draw(waiting_background);
}


void View::Show() {
    sf::Music music;
    this->PlayStartMusic(music);

    sf::View view = window->getDefaultView();

    while (window->isOpen() && !game->IsFinished()) {
        window->clear();
        window->draw(background);

        mapViewModel.Draw(*window);

        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                controller.CloseGame();
                window->close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
                mapViewModel.Resize(window->getSize());
            }
        }

        window->display();
    }
}


void View::PlayStartMusic(sf::Music &music) {
    if (!play_music)
        return;
    if (!music.openFromFile(music_file_path))
        std::cerr << "can't load Intro music" << '\n';
    music.play();
}

// Init

void View::InitTextures() {
    if (!background_texture.loadFromFile(background_file_path))
        std::cerr << "ERROR::VIEW:TEXTURE:" << background_file_path << std::endl;
    if (!waiting_texture.loadFromFile(wait_image_file_path))
        std::cerr << "ERROR::VIEW:TEXTURE:" << wait_image_file_path << std::endl;
}

void View::InitSprites() {
    background.setTexture(background_texture);
    waiting_background.setTexture(waiting_texture);
}
