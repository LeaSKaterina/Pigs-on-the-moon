#pragma once

#include <SFML/Graphics.hpp>

class MenuButton {
public:
    MenuButton(const sf::Texture &onTexture, const sf::Texture &offTexture, int value = -1)
        : isTwoStable(true), isActive(false), value(value) {
        on.setTexture(onTexture);
        off.setTexture(offTexture);
        currentState = &off;
    }

    explicit MenuButton(const sf::Texture &texture)
        : MenuButton(texture, texture) { isTwoStable = false; }

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

    void Click(bool isOn) {
        isActive = isOn;
        Update();
    }

    sf::Rect<float> GetBoundingRect() const {
        return currentState->getGlobalBounds();
    }

    bool IsActive() const {
        return isTwoStable && isActive;
    }

    int Value() const {
        return value;
    }

private:
    sf::Sprite *currentState;
    bool isTwoStable;
    bool isActive;
    int value;

    // states
    sf::Sprite on;
    sf::Sprite off;

    void Update() {
        currentState = isActive ? &on : &off;
    }
};
