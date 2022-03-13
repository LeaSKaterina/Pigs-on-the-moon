#pragma once

#include "enums/types.h"
#include <SFML/Graphics.hpp>
#include <cmath>

class VehicleLogo {
public:
    VehicleLogo(float radius);

    std::tuple<sf::CircleShape, sf::RectangleShape *> GetLogoByType(VehiclesTypes::Type type);

    void SetRadius(float radius);

    void ChangeColorById(int playerId);

    virtual ~VehicleLogo();

private:
    std::vector<sf::CircleShape> logos;
    std::map<VehiclesTypes::Type, sf::RectangleShape *> details;
    float r;

    sf::CircleShape CreateFigure(int pointCount, float rotation, int separatorCount);

    [[nodiscard]] sf::RectangleShape *CreateDetail(int separatorCount) const;

    void SetColor(const sf::Color &color);
};
