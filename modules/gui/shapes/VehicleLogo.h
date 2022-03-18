#pragma once

#include "enums/types.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>

class VehicleLogo {
public:
    explicit VehicleLogo(float radius);

    std::tuple<sf::CircleShape, sf::RectangleShape *> GetLogoByType(VehiclesTypes::Type type);

    void SetRadius(float radius);

    void ChangeColorById(int playerId);

    virtual ~VehicleLogo() = default;

private:
    std::vector<sf::CircleShape> logos;
    std::map<VehiclesTypes::Type, std::unique_ptr<sf::RectangleShape>> details;
    float r;

    sf::CircleShape CreateFigure(int pointCount, float rotation, int separatorCount);

    [[nodiscard]] std::unique_ptr<sf::RectangleShape> CreateDetail(int separatorCount) const;

    void SetColor(const sf::Color &color);
};
