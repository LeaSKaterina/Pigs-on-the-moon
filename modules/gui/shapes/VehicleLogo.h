#include "enums/types.h"
#include <SFML/Graphics.hpp>


class VehicleLogo {

    static bool isCreated;
    static std::vector<sf::CircleShape> logos;
    static float r;

    static sf::CircleShape InitLogo(int pointCount, float rotation, int separatorCount);

    explicit VehicleLogo();

public:
    static sf::CircleShape *GetVehicleLogo(VehiclesTypes::Type type, const sf::Color &color);

    static std::vector<sf::CircleShape> *GetLogos(const sf::Color &color);

    static std::vector<sf::CircleShape> *GetLogos(float newR, const sf::Color &color);

    static void SetRadius(float newR);
};
