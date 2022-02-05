#ifndef PIGS_ON_THE_MOON_VEHICLE_H
#define PIGS_ON_THE_MOON_VEHICLE_H

#include "../../map/hex.h"
#include <map>
#include <vector>

class Vehicle {
public:
    Vehicle(int playerId, int hp, int speed, int damage = 1);

    bool Move(Hex *newPos);

    std::multimap<int, Point> GetAvailableMovePoints(Point target);

    virtual bool IsAvailableForShoot(Vehicle *enemy) = 0;

    int Shoot(Vehicle *v);

    void IncCapture() { capturePoints++; }

    void DropCapture() { capturePoints = 0; }

    void Update(int health, Hex *newPos, int capture);

    [[nodiscard]] int GetPlayerId() const { return playerId; }

    [[nodiscard]] const Point &GetSpawn() const { return spawnPosition->GetCoordinates(); }

    [[nodiscard]] const Point &GetCurrentPosition() const { return currentPosition->GetCoordinates(); }

    void InitSpawn(Hex *p);

    void Respawn();

private:
    int playerId;
    int health;
    int destructionPoints;
    int speedPoints;
    int damage;
    int capturePoints = 0;
    Hex *spawnPosition = nullptr;
    Hex *currentPosition = nullptr;

    int GetHit(int damage = 1);

    bool IsEnemy(Vehicle *v) const { return this->playerId != v->playerId; }
};


#endif//PIGS_ON_THE_MOON_VEHICLE_H
