#include "VehicleLogo.h"

#include "enums/types.h"
#include <SFML/Graphics.hpp>

bool VehicleLogo::isCreated = false;
float VehicleLogo::r;
std::vector<sf::CircleShape*> VehicleLogo::logos;

sf::CircleShape* VehicleLogo::InitLogo(int pointCount, float rotation, int separatorCount) {
    auto *instance = new sf::CircleShape(r, pointCount);
    instance->setOrigin(instance->getLocalBounds().width/2, instance->getLocalBounds().height/2);
    instance->setOutlineThickness(2.f);
    instance->setOutlineColor(sf::Color::Black);
    instance->setFillColor(sf::Color::Transparent);
    if (rotation != 0.f) { instance->setRotation(rotation); }
    if (separatorCount != 0) {
        // for Medium separatorCount = 1, for Heavy separatorCount = 2
    }
    return instance;
}

VehicleLogo::VehicleLogo(){
    r = 5;
    logos.push_back(InitLogo(3, -30.f, 0));
    logos.push_back(InitLogo(4, 0.f, 1));
    logos.push_back(InitLogo(4, 0.f, 2));
    logos.push_back(InitLogo(4, 0.f, 0));
    logos.push_back(InitLogo(4, 45.f, 0));
    isCreated = true;
}

sf::CircleShape* VehicleLogo::GetLogoOfType(VehiclesTypes::Type type) {
    if (!isCreated) VehicleLogo();
    return logos[type];
}

void VehicleLogo::SetColor(const sf::Color &color) {
//    if (!isCreated) VehicleLogo();
    for (auto logo : logos) {
        logo->setOutlineColor(color);
    }
}

void VehicleLogo::GenerateLogos(float radius, int playerId) {
    if (!isCreated) VehicleLogo();
    SetRadius(radius);
    for (auto logo : logos) {
        logo->rotate(120*(float) playerId);
    }
    switch(playerId) {
        case 0:{
            SetColor(sf::Color::Blue);
            break;
        }
        case 1:{
            SetColor(sf::Color::White);
            break;
        }
        case 2:{
            SetColor(sf::Color::Yellow);
            break;
        }
        default:{
            SetColor(sf::Color::Black);
        }
    }
}

void VehicleLogo::SetRadius(float newR) {
    r = newR;
}

void VehicleLogo::DestructLogos() {
    for (auto logo : logos){
        delete[] logo;
    }
}
