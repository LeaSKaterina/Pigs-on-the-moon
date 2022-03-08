#include "View.h"
#include "gui/controller/Controller.h"

void View::Show() {
    sf::Music music;
    this->PlayStartMusic(music);

    sf::Texture texture;
    if (!texture.loadFromFile("resources/image/background.jpg")) {
        std::cerr << "can't load texture" << '\n';
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::View view = window.getDefaultView();

    while (window.isOpen()) {
        window.clear();
        window.draw(sprite);

        mapViewModel.Draw(window);

        sf::Event event;
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
