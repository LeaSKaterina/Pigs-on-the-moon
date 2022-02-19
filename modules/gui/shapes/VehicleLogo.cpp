#include "VehicleLogo.h"

sf::CircleShape VehicleLogo::CreateFigure(int pointCount, float rotation, int separatorCount) {
    sf::CircleShape shape(r, pointCount);
    shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::Transparent);
    shape.setRotation(rotation);

    // for Medium separatorCount = 1, for Heavy separatorCount = 2
    if (separatorCount != 0) {
//        shape.
    }
    return shape;
}

//ToDo order????
VehicleLogo::VehicleLogo(float radius) : r(radius) {
    logos.push_back(std::move(CreateFigure(3, 180.f, 0)));//at_spg
    logos.push_back(std::move(CreateFigure(4, 0.f, 1)));  //medium
    logos.push_back(std::move(CreateFigure(4, 0.f, 2)));  //hard
    logos.push_back(std::move(CreateFigure(4, 0.f, 0)));  //light
    logos.push_back(std::move(CreateFigure(4, 45.f, 0))); //spg
}

void VehicleLogo::SetColor(const sf::Color &color) {
    for (auto &logo : logos) {
        logo.setOutlineColor(color);
    }
}

void VehicleLogo::ChangeColorById(int playerId) {
    switch (playerId) {
        case 0: {
            SetColor(sf::Color::Blue);
            break;
        }
        case 1: {
            SetColor(sf::Color::White);
            break;
        }
        case 2: {
            SetColor(sf::Color::Yellow);
            break;
        }
        default: {
            SetColor(sf::Color::Black);
        }
    }
}
