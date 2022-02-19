#include "enums/types.h"
#include <SFML/Graphics.hpp>


class VehicleLogo {

    static bool isCreated;
    static std::vector<sf::CircleShape*> logos;
    static std::map<VehiclesTypes::Type, sf::RectangleShape*> details;
    static float r;

    static sf::CircleShape*CreateLogo(int pointCount, float rotation, int separatorCount);

    static sf::RectangleShape* CreateDetail(int separatorCount);

    explicit VehicleLogo();

    static void SetColor(const sf::Color &color);

public:
    static std::tuple<sf::CircleShape*, sf::RectangleShape*> GetLogoOfType(VehiclesTypes::Type type);

    static void GenerateLogos(float radius, int playerId);

    static void DestructLogos();

    static void SetRadius(float radius);
};
