#pragma once

#include "gui/screen.h"
#include "enums/types.h"
#include "gui/shapes/VehicleLogo.h"
#include "gameClient.h"
#include <SFML/Graphics.hpp>

class MapView {
public:
    MapView(Game *game, sf::Mutex &gameMutex) : game(game), gameMutex(gameMutex) {
        hex.setOutlineThickness(1.f);
        hex.setFillColor(sf::Color::Transparent);
        hex.setOrigin(hex.getLocalBounds().width / 2, hex.getLocalBounds().height / 2);
        hex.setRotation(30.f);


        if (!font.loadFromFile("resources/font/nimbusMono.ttf")) {
            std::cerr << "Error! Font isn't loaded!" << '\n';
        }
        text.setFont(font);
        text.setCharacterSize(size * 0.6);
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

    }

    void Draw(sf::RenderWindow &window) {
        sf::Lock lock(gameMutex);

        vehiclesVectors = game->GetVehicles();

        Point2D center = (rightBottomPoint - leftTopPoint) / 2;
//        size = 10;
        hex.setRadius(size);
        center.x *= window.getSize().x;
        center.y *= window.getSize().y;
        std::cout << center.x << " " << center.y << '\n';
        //draw grid
        for (const auto point: map->GetGrid()) {
            hex.setOutlineColor(sf::Color::Green);
            hex.setFillColor(sf::Color::Transparent);
            if (map->GetType(*point.second) == ConstructionsTypes::BASE) hex.setOutlineColor(sf::Color::Blue);
            if (map->GetType(*point.second) == ConstructionsTypes::OBSTACLE) {
                hex.setOutlineColor(sf::Color::Red);
                hex.setFillColor(sf::Color(255, 20, 20, 70));
            }
            int x = size * 3. / 2 * point.first.x + center.x;
            int y = size * (sqrt(3) / 2 * point.first.x + std::sqrt(3) * point.first.z) + center.y;
            hex.setPosition(x, y);
            window.draw(hex);
        }


        for (int i = 0; i < vehiclesVectors.size(); i++) {
            vehicleLogo.ChangeColorById(i);
            for (int j = 0; j < vehiclesVectors[i].size(); j++) {
                auto logo = vehicleLogo.GetLogoByType(VehiclesTypes::Type(j));
                auto point = vehiclesVectors[i][j]->GetCurrentPosition();
                int x = size * 3. / 2 * point.x + center.x;
                int y = size * (sqrt(3) / 2 * point.x + std::sqrt(3) * point.z) + center.y - 2;
                std::get<0>(logo).setPosition(x, y);
                window.draw(std::get<0>(logo));
                if (std::get<1>(logo)) {
                    std::get<1>(logo)->setPosition(x, y);
                    window.draw(*std::get<1>(logo));
                }

                text.setString(std::to_string(vehiclesVectors[i][j]->GetHp()));
                text.setFillColor(std::get<0>(logo).getOutlineColor());
                text.setPosition(x, y + 4);
                window.draw(text);
            }
        }
    }

    void SetBorder(const Point2D &leftTopPoint, const Point2D &rightBottomPoint) {
        this->leftTopPoint = leftTopPoint;
        this->rightBottomPoint = rightBottomPoint;
    }


private:
    Point2D leftTopPoint;
    Point2D rightBottomPoint;

    int size = 17;
    sf::CircleShape hex = sf::CircleShape(size * 0.8, 6);
    VehicleLogo vehicleLogo = VehicleLogo(size * 0.4);

    Game *game;
    sf::Mutex &gameMutex;

    sf::Font font;
    sf::Text text;

    std::vector<std::vector<Vehicle *>> vehiclesVectors = game->GetVehicles();
    Map *map = game->GetMap();
};

