#include "enums/types.h"
#include <SFML/Graphics.hpp>


class VehicleLogo {
private:
    std::vector<sf::CircleShape> logos;
    float r;

    sf::CircleShape CreateFigure(int pointCount, float rotation, int separatorCount);

    void SetColor(const sf::Color &color);

public:

    VehicleLogo(float radius);

    sf::CircleShape *GetLogoByType(VehiclesTypes::Type type){ return &logos[type]; }

//    static sf::CircleShape *GetLogoOfType(VehiclesTypes::Type type, float rotation);

    void ChangeColorById(int playerId);
};
