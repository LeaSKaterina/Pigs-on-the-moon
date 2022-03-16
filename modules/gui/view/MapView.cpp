#include "MapView.h"

MapView::MapView(const Game *game, sf::Mutex &gameMutex, const Point2D &leftTopPoint, const Point2D &rightBottomPoint) : game(game), gameMutex(gameMutex),
                                                                                                                         leftTopPointRelative(leftTopPoint),
                                                                                                                         rightBottomPointRelative(rightBottomPoint) {
    hex.setOutlineThickness(1.f);
    hex.setOrigin(hex.getLocalBounds().width / 2, hex.getLocalBounds().height / 2);
    hex.setRotation(30.f);


    //load texture
    if (!font.loadFromFile("resources/font/nimbusMono.ttf")) {
        std::cerr << "Error! Font isn't loaded!" << '\n';
    }
    if (!catapultTexture.loadFromFile("resources/image/catapult.png") ||
        !lightRepairTexture.loadFromFile("resources/image/light_repair.png") ||
        !hardRepairTexture.loadFromFile("resources/image/hard_repair.png")) {
        std::cerr << "can't load texture" << '\n';
    }

    text.setFont(font);
}

void MapView::DrawGrid(sf::RenderWindow &window) {
    for (const auto& point : map->GetGrid()) {
        int x = size * 3. / 2 * point.first.x + center.x;
        int y = size * (sqrt(3) / 2 * point.first.x + std::sqrt(3) * point.first.z) + center.y;

        if (point.second->GetType() == ConstructionsTypes::EMPTY) {
            hex.setOutlineColor(sf::Color::Green);
            hex.setFillColor(sf::Color::Transparent);
        } else if (point.second->GetType() == ConstructionsTypes::BASE) {
            hex.setOutlineColor(sf::Color::Blue);
            hex.setFillColor(sf::Color::Transparent);
        } else if (point.second->GetType() == ConstructionsTypes::OBSTACLE) {
            hex.setOutlineColor(sf::Color::Red);
            hex.setFillColor(sf::Color(255, 20, 20, 70));
        } else {
            const sf::Texture *texture = &catapultTexture;
            if (point.second->GetType() == ConstructionsTypes::LIGHT_REPAIR) texture = &lightRepairTexture;
            else if (point.second->GetType() == ConstructionsTypes::HARD_REPAIR)
                texture = &hardRepairTexture;
            sf::Sprite sprite = GetSprite(*texture, x, y);
            if (!point.second->IsEmpty()) {
                sf::Color color = sprite.getColor();
                sprite.setColor(sf::Color(color.r, color.g, color.b, 60));
            }
            window.draw(sprite);
        }
        hex.setPosition(x, y);
        window.draw(hex);
    }
}

void MapView::DrawVehicles(sf::RenderWindow &window) {
    const auto & vehiclesVectors = game->GetVehicles();
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
            //Draw health
            text.setString(std::to_string(vehicle->GetHp()));
            text.setFillColor(std::get<0>(logo).getOutlineColor());
            text.setPosition(x, y + 4);
            window.draw(text);
        }
    }
}

sf::Sprite MapView::GetSprite(const sf::Texture &texture, int x, int y) const {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale((float) (size + 2) / (float) (texture.getSize().x), (float) (size + 2) / (float) (texture.getSize().y));
    sprite.setPosition(x, y);
    return sprite;
}

void MapView::Resize(const sf::Vector2<unsigned int> &windowSize) {
    Point2D diagPoint = rightBottomPointRelative - leftTopPointRelative;
    diagPoint.x *= windowSize.x;
    diagPoint.y *= windowSize.y;

    size = std::min(diagPoint.x, diagPoint.y) / 40;
    center = (rightBottomPointRelative - leftTopPointRelative) / 2;
    center.x *= windowSize.x;
    center.y *= windowSize.y;

    text.setCharacterSize(size * 0.6);

    hex.setRadius(size * 0.85);
    hex.setOrigin(hex.getLocalBounds().width / 2, hex.getLocalBounds().height / 2);

    vehicleLogo.SetRadius(size * 0.4);
}

void MapView::Draw(sf::RenderWindow &window) {
    sf::Lock lock(gameMutex);

    this->DrawGrid(window);
    this->DrawVehicles(window);
}
