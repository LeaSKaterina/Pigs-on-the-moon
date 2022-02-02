#ifndef PIGS_ON_THE_MOON_ACTORS_VEHICLE_H
#define PIGS_ON_THE_MOON_ACTORS_VEHICLE_H

#include "../map/hex.h"
#include "../enums/vehicle_types.h"

class Vehicle {
public:

//    enum Type {
//        MediumTank, LightTank, HeavyTank, AtSpg, Spg
//    };

    Vehicle(VehiclesTypes::Type type, int playerId);

    bool Move(Hex *newPos);

    int Shoot(Vehicle *v);

    void IncCapture();

    void DropCapture();

    void Update(int health, Hex *newPos, int capture);

    int GetPlayerId() const;

    [[nodiscard]] const std::tuple<int, int, int> &GetSpawn() const;

    [[nodiscard]] const std::tuple<int, int, int> &GetCurrentPosition() const;

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
    VehiclesTypes::Type type;

    int GetHit(int damage = 1);

    bool IsEnemy(Vehicle *v) const;
};



#endif //PIGS_ON_THE_MOON_ACTORS_VEHICLE_H
