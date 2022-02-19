#include "enums/types.h"
#include <SFML/Graphics.hpp>


class VehicleLogo {

    static bool isCreated;
    static std::vector<sf::CircleShape*> logos;
    static std::map<VehiclesTypes::Type, sf::RectangleShape*> details;
//    static sf::RectangleShape* detail;
    static float r;

    static sf::CircleShape*CreateLogo(int pointCount, float rotation, int separatorCount);

    static sf::RectangleShape* CreateDetail(int separatorCount);

    explicit VehicleLogo();

    static void SetColor(const sf::Color &color);

public:
    static sf::CircleShape *GetLogoOfType(VehiclesTypes::Type type);

    static std::tuple<sf::CircleShape*, sf::RectangleShape*> GetLogoWithDetailsOfType(VehiclesTypes::Type type);

//    static sf::CircleShape *GetLogoOfType(VehiclesTypes::Type type, float rotation);

    static void GenerateLogos(float radius, int playerId);

    static void SetRadius(float newR);

    static void DestructLogos();
};
