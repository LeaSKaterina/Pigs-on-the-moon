#include "VehicleLogo.h"

sf::CircleShape VehicleLogo::CreateFigure(int pointCount, float rotation, int separatorCount) {
    sf::CircleShape shape(r, pointCount);
    shape.setOrigin(shape.getLocalBounds().width / 2, shape.getLocalBounds().height / 2);
    shape.setRotation(rotation);

    // for Medium separatorCount = 1, for Heavy separatorCount = 2
    if (separatorCount != 0) {
        VehiclesTypes::Type type;
        if (separatorCount == 1)
            type = VehiclesTypes::MEDIUM_TANK;
        else
            type = VehiclesTypes::HEAVY_TANK;
        details.emplace(type, std::unique_ptr<sf::RectangleShape>(CreateDetail(separatorCount)));
    }
    return shape;
}

VehicleLogo::VehicleLogo(float radius) : r(radius) {
    logos.push_back(CreateFigure(4, 45.f, 0)); //spg
    logos.push_back(CreateFigure(4, 0.f, 0));  //light
    logos.push_back(CreateFigure(4, 0.f, 2));  //hard
    logos.push_back(CreateFigure(4, 0.f, 1));  //medium
    logos.push_back(CreateFigure(3, 180.f, 0));//at_spg
}

void VehicleLogo::SetColor(const sf::Color &color) {
    for (auto &logo : logos) {
        logo.setFillColor(color);
    }
    for (auto& detail : details) {
        detail.second->setFillColor(color);
    }
}

void VehicleLogo::ChangeColorById(int playerId) {
    switch (playerId) {
        case 0: {
            SetColor(sf::Color::Cyan);
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

std::tuple<sf::CircleShape, sf::RectangleShape *> VehicleLogo::GetLogoByType(VehiclesTypes::Type type) {
    if (details.find(type) == details.end()) {
        return std::make_tuple(logos[type], nullptr);
    }
    return std::make_tuple(logos[type], details.find(type)->second.get());
}

std::unique_ptr<sf::RectangleShape> VehicleLogo::CreateDetail(int separatorCount) const {
    auto detail = std::make_unique<sf::RectangleShape>(sf::Vector2f(2 * r / std::sqrt(2.f), r * 0.15 * (separatorCount - 1)));
    detail->setOutlineThickness(2.f);
    detail->setOutlineColor(sf::Color::Black);
    detail->setFillColor(sf::Color::Transparent);
    detail->setOrigin(detail->getSize().x / 2, detail->getSize().y / 2);
    detail->setRotation(45);
    return detail;
}

void VehicleLogo::SetRadius(float radius) {
    r = radius;
    for (auto &logo : logos) {
        logo.setRadius(radius);
        logo.setOrigin(logo.getLocalBounds().width / 2, logo.getLocalBounds().height / 2);
    }
    for (auto& detail : details) {
        detail.second->setSize(sf::Vector2(2 * r / std::sqrt(2.f), 2 * detail.second->getSize().y));
        detail.second->setOrigin(detail.second->getSize().x / 2, detail.second->getSize().y / 2);
    }
}
