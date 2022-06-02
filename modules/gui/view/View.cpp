#include "View.h"
#include "gui/controller/Controller.h"

View::View(Controller &controller, const Game *game, sf::Mutex &gameMutex, bool unmute_music)
    : controller(controller),
      screen(sf::VideoMode::getDesktopMode().width,
             sf::VideoMode::getDesktopMode().height),
      mapViewModel(game, gameMutex, {0, 0}, {1, 1}),
      play_music(unmute_music) {
    std::ifstream config(config_view_file_path);
    std::string str((std::istreambuf_iterator<char>(config)), std::istreambuf_iterator<char>());
    config.close();
    nlohmann::json json = nlohmann::json::parse(str);
    float width = json["sizeScale"]["width"];
    float height = json["sizeScale"]["height"];

    window.create(sf::VideoMode(
                          (unsigned int) (screen.width * width),
                          (unsigned int) (screen.height * height)),
                  "Best Course Work");

    float xPosition = json["position"]["x"];
    float yPosition = json["position"]["y"];
    window.setPosition(sf::Vector2i(screen.width * xPosition, screen.height * yPosition));
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);

    mapViewModel.Resize(window.getSize());
}


void View::Show() {
    sf::Music music;
    this->PlayStartMusic(music);

    sf::Texture texture;
    if (!texture.loadFromFile(background_file_path)) {
        std::cerr << "can't load texture" << '\n';
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::View view = window.getDefaultView();

    while (window.isOpen()) {
        window.clear();
        window.draw(sprite);

        mapViewModel.Draw(window);

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                controller.CloseGame();
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                mapViewModel.Resize(window.getSize());
            }
        }

        window.display();
    }
}


void View::PlayStartMusic(sf::Music &music) {
    if (!play_music)
        return;
    if (!music.openFromFile(music_file_path))
        std::cerr << "can't load Intro music" << '\n';
    music.play();
}
