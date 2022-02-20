#include "enums/types.h"
#include <SFML/Graphics.hpp>
#include <cmath>

class VehicleLogo {
private:
    std::vector<sf::CircleShape> logos;
    std::map<VehiclesTypes::Type, sf::RectangleShape *> details;
    float r;

    sf::CircleShape CreateFigure(int pointCount, float rotation, int separatorCount);
    sf::RectangleShape *CreateDetail(int separatorCount) const;

    void SetColor(const sf::Color &color);

public:
    VehicleLogo(float radius);

    std::tuple<sf::CircleShape, sf::RectangleShape *> GetLogoByType(VehiclesTypes::Type type);

    //    static sf::CircleShape *GetLogoOfType(VehiclesTypes::Type type, float rotation);

    void ChangeColorById(int playerId);
};
