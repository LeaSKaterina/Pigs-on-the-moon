#pragma once

#include <SFML/Graphics.hpp>

class MenuButton {
public:
    MenuButton(const sf::Texture &onTexture, const sf::Texture &offTexture, bool isMutable = true)
        : isTwoStable(isMutable), isActive(false) {
        on.setTexture(onTexture);
        off.setTexture(offTexture);
        currentState = &off;
    }

    explicit MenuButton(const sf::Texture &texture)
        : MenuButton(texture, texture, false) {}

    void Draw(sf::RenderWindow &window) {
        window.draw(*currentState);
    }

    void SetPosition(float x, float y) {
        on.setPosition(x, y);
        off.setPosition(x, y);
    }

    void Click() {
        isActive = !isActive;
        Update();
    }

    sf::Rect<float> GetBoundingRect() const {
        return currentState->getGlobalBounds();
    }

    bool IsActive() const {
        return isTwoStable && isActive;
    }

private:
    sf::Sprite *currentState;
    bool isTwoStable;
    bool isActive;

    // states
    sf::Sprite on;
    sf::Sprite off;

    void Update() {
        currentState = isActive ? &on : &off;
    }
};
