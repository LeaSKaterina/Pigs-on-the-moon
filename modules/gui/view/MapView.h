#pragma once

#include "enums/types.h"
#include "gameClient.h"
#include "gui/screen.h"
#include "gui/shapes/VehicleLogo.h"
#include <SFML/Graphics.hpp>

class MapView {
public:
    MapView(const Game *game, sf::Mutex &gameMutex, const Point2D &leftTopPoint, const Point2D &rightBottomPoint);

    void Draw(sf::RenderWindow &window);

    void Resize(const sf::Vector2<unsigned int> &windowSize);


private:
    //window border. Relative coordinates
    Point2D leftTopPointRelative;
    Point2D rightBottomPointRelative;

    int size;
    Point2D center;

    //drawable models
    sf::CircleShape hex = sf::CircleShape(0, 6);
    VehicleLogo vehicleLogo = VehicleLogo(0);
    sf::Texture catapultTexture;
    sf::Texture lightRepairTexture;
    sf::Texture hardRepairTexture;

    //game info
    const Game *game;
    sf::Mutex &gameMutex;
    //ToDo: thread problem chance.
    std::vector<std::vector<Vehicle *>> vehiclesVectors = game->GetVehicles();
    const Map *map = game->GetMap();

    //health
    sf::Font font;
    sf::Text text;

    sf::Sprite GetSprite(const sf::Texture &texture, int x, int y) const;

    void DrawGrid(sf::RenderWindow &window);

    void DrawVehicles(sf::RenderWindow &window);
};
