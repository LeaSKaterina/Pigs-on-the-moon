#pragma once

#include "../map/hex.h"

enum Type {
    MediumTank, LightTank, HeavyTank, AtSpg, Spg
};

class Vehicle {
private:

    int playerId;
    int health;
    int destructionPoints;    // Очки за уничтожение
    int speedPoints;
    int damage = 1;
    int capturePoints;
    Hex *spawnPosition;
    Hex *currentPosition;
    Type type;

    int GetHit(int damage = 1);

    bool IsEnemy(Vehicle *v) const;

public:

    Vehicle(Type type, int playerId);

    bool Move(Hex *newPos);

    int Shoot(Vehicle *v);

    void IncCapture();

    void DropCapture();

    void Update(int health, Hex *newPos, int capture);

    int GetPlayerId() const;

    const std::tuple<int, int, int> &GetSpawn() const;

    void InitSpawn(Hex *p);

    void Respawn();
};
