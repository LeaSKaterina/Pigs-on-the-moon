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
//        vehicleLogo.SetRadius(5);
        hex.setRadius(size);
        center.x *= window.getSize().x;
        center.y *= window.getSize().y;

        //draw grid
        for (const auto point: map->GetGrid()) {
            int x = size * 3. / 2 * point.first.x + center.x;
            int y = size * (sqrt(3) / 2 * point.first.x + std::sqrt(3) * point.first.z) + center.y;

            switch (map->GetType(*point.second)) {
                case ConstructionsTypes::EMPTY: {
                    hex.setOutlineColor(sf::Color::Green);
                    hex.setFillColor(sf::Color::Transparent);
                    break;
                }
                case ConstructionsTypes::BASE:{
                    hex.setOutlineColor(sf::Color::Blue);
                    hex.setFillColor(sf::Color::Transparent);
                    break;
                }
                case ConstructionsTypes::OBSTACLE:{
                    hex.setOutlineColor(sf::Color::Red);
                    hex.setFillColor(sf::Color(255, 20, 20, 70));
                    break;
                }
                case ConstructionsTypes::CATAPULT:{
                    sf::Texture texture;
                    if (!texture.loadFromFile("resources/image/catapult.png"))
                    {
                        std::cerr << "can't load catapult texture" << '\n';
                    }
                    window.draw(GetSprite(texture,x,y));
                    break;
                }
                case ConstructionsTypes::LIGHT_REPAIR:{
                    sf::Texture texture;
                    if (!texture.loadFromFile("resources/image/light_repair.png"))
                    {
                        std::cerr << "can't load light repair texture" << '\n';
                    }
                    window.draw(GetSprite(texture,x,y));
                    break;
                }
                case ConstructionsTypes::HARD_REPAIR:{
                    sf::Texture texture;
                    if (!texture.loadFromFile("resources/image/hard_repair.png"))
                    {
                        std::cerr << "can't load hard repair texture" << '\n';
                    }
                    window.draw(GetSprite(texture,x,y));
                    break;
                }

            }
            hex.setPosition(x, y);
            window.draw(hex);
        }

        for (int i = 0; i < vehiclesVectors.size(); i++) {
            vehicleLogo.ChangeColorById(i);
            for (auto &vehicle : vehiclesVectors[i]) {
                auto logo = vehicleLogo.GetLogoByType(vehicle->GetType());
                auto point = vehicle->GetCurrentPosition();
                int x = size * 3. / 2 * point.x + center.x;
                int y = size * (sqrt(3) / 2 * point.x + std::sqrt(3) * point.z) + center.y - 2;
                std::get<0>(logo).setPosition(x, y);
                window.draw(std::get<0>(logo));
                if (std::get<1>(logo)) {
                    std::get<1>(logo)->setPosition(x, y);
                    window.draw(*std::get<1>(logo));
                }

                text.setString(std::to_string(vehicle->GetHp()));
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
    sf::Sprite GetSprite(sf::Texture &texture, int x, int y) const{
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale((float)(size + 2)/(float)(texture.getSize().x), (float)(size + 2)/(float)(texture.getSize().y));
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(x+0.2*size,y+0.2*size);
        return sprite;
    }
};

