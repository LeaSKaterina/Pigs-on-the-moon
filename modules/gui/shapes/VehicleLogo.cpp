#include "VehicleLogo.h"

#include "enums/types.h"
#include <SFML/Graphics.hpp>

bool VehicleLogo::isCreated = false;
float VehicleLogo::r;
std::vector<sf::CircleShape> VehicleLogo::logos;

sf::CircleShape VehicleLogo::InitLogo(int pointCount, float rotation, int separatorCount) {
    sf::CircleShape instance(r, pointCount);
    instance.setFillColor(sf::Color::Transparent);
    if (rotation != 0.f) { instance.setRotation(rotation); }
    if (separatorCount != 0) {
        // for Medium separatorCount = 1, for Heavy separatorCount = 2
    }
    return instance;
};

VehicleLogo::VehicleLogo(){
    r = 10;
    logos.push_back(std::move(InitLogo(4, 180.f, 0)));
    logos.push_back(std::move(InitLogo(4, 0.f, 0)));
    logos.push_back(std::move(InitLogo(4, 0.f, 2)));
    logos.push_back(std::move(InitLogo(4, 0.f, 1)));
    logos.push_back(std::move(InitLogo(3, 180.f, 0)));
    isCreated = true;
}

sf::CircleShape* VehicleLogo::GetVehicleLogo(VehiclesTypes::Type type, const sf::Color &color) {
    if (!isCreated) VehicleLogo();
    logos[type].setOutlineColor(color);
    return &logos[type];
}

std::vector<sf::CircleShape>* VehicleLogo::GetLogos(const sf::Color &color) {
    if (!isCreated) VehicleLogo();
    for (auto logo : logos) {
        logo.setOutlineColor(color);
    }
    return &logos;
}

std::vector<sf::CircleShape>* VehicleLogo::GetLogos(float newR, const sf::Color &color) {
    if (!isCreated) VehicleLogo();
    SetRadius(newR);
    return GetLogos(color);
}

void VehicleLogo::SetRadius(float newR) {
    r = newR;
}
