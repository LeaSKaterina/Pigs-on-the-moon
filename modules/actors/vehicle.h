#pragma once

#include "../map/hex.h"

class Vehicle {
public:

    enum Type {
        MEDIUM_TANK, LIGHT_TANK, HEAVY_TANK, AT_SPG, SPG
    };

    Vehicle(Type type, int playerId);

    bool Move(Hex *newPos);

    int Shoot(Vehicle *v);

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int health, Hex *newPos, int capture);

    int GetPlayerId() const { return playerId; }

    [[nodiscard]] const std::tuple<int, int, int> &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const std::tuple<int, int, int> &
    GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    void InitSpawn(Hex *p);

    void Respawn();

private:

    int playerId;
    int health;
    int destructionPoints;    // Очки за уничтожение
    int speedPoints;
    int damage = 1;
    int capturePoints = 0;
    Hex *spawnPosition = nullptr;
    Hex *currentPosition = nullptr;
    Type type;

    int GetHit(int damage = 1);

    bool IsEnemy(Vehicle *v) const { return this->playerId != v->playerId; }
};


