#include "VehicleLogo.h"

#include "enums/types.h"
#include <SFML/Graphics.hpp>
#include <cmath>

bool VehicleLogo::isCreated = false;
float VehicleLogo::r = 8;
std::vector<sf::CircleShape*> VehicleLogo::logos;
std::map<VehiclesTypes::Type, sf::RectangleShape*> VehicleLogo::details;

sf::CircleShape* VehicleLogo::CreateLogo(int pointCount, float rotation, int separatorCount) {
    auto *instance = new sf::CircleShape(r, pointCount);
    instance->setOrigin(instance->getLocalBounds().width/2, instance->getLocalBounds().height/2);
    instance->setFillColor(sf::Color::Black);
    if (rotation != 0.f) { instance->setRotation(rotation); }
    if (separatorCount != 0) {
        VehiclesTypes::Type type;
        if (separatorCount == 1)
            type = VehiclesTypes::MEDIUM_TANK;
        else
            type = VehiclesTypes::HEAVY_TANK;
        details.insert(std::make_pair(type, CreateDetail(separatorCount)));
    }
    return instance;
}

VehicleLogo::VehicleLogo(){
    logos.push_back(CreateLogo(3, -30.f, 0)); //AtSpg
    logos.push_back(CreateLogo(4, 0.f, 1)); //MediumTank
    logos.push_back(CreateLogo(4, 0.f, 2)); //HeavyTank
    logos.push_back(CreateLogo(4, 0.f, 0)); //LightTank
    logos.push_back(CreateLogo(4, 45.f, 0)); //Spg
    isCreated = true;
}

void VehicleLogo::SetColor(const sf::Color &color) {
//    if (!isCreated) VehicleLogo();
    for (auto logo : logos) {
        logo->setFillColor(color);
    }
    for (auto detail: details){
        detail.second->setFillColor(color);
    }
}

void VehicleLogo::GenerateLogos(float radius, int playerId) {
    if (!isCreated) VehicleLogo();
    if (r != radius) SetRadius(radius);
    for (auto logo : logos) {
        logo->rotate(120*(float) playerId);
    }
    for (auto detail: details){
        detail.second->rotate(120*(float) playerId);
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

void VehicleLogo::DestructLogos() {
    for (auto logo : logos){
        delete[] logo;
    }
    for (auto detail : details){
        delete[] detail.second;
    }
}

sf::RectangleShape *VehicleLogo::CreateDetail(int separatorCount) {
    auto *detail = new sf::RectangleShape(sf::Vector2f(2*r/std::sqrt(2.f), r*0.15*(separatorCount - 1)));
    detail->setOutlineThickness(2.f);
    detail->setOutlineColor(sf::Color::Black);
    detail->setFillColor(sf::Color::Transparent);
    detail->setOrigin(detail->getSize().x/2, detail->getSize().y/2);
    detail->setRotation(45);
    return detail;
}

std::tuple<sf::CircleShape *, sf::RectangleShape *> VehicleLogo::GetLogoOfType(VehiclesTypes::Type type) {
    if (!isCreated) VehicleLogo();
    return std::make_tuple(logos[type], details.find(type)->second);
}

void VehicleLogo::SetRadius(float radius) {
    r = radius;
    for (auto logo : logos){
        logo->setRadius(radius);
        logo->setOrigin(logo->getLocalBounds().width/2, logo->getLocalBounds().height/2);
    }
    for (auto detail : details){
        detail.second->setSize(sf::Vector2(2*r/std::sqrt(2.f),2*detail.second->getSize().y));
        detail.second->setOrigin(detail.second->getSize().x/2, detail.second->getSize().y/2);
    }
}
