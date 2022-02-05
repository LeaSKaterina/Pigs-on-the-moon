#pragma once

//#include <tuple>
#include "../map/hex.h"
#include "../map/map.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

class ActionController {
private:
    static void ModuleDecrement(int &n);

    static void ModuleIncrement(int &n);

    static void ReduceModule(int &n, int amount);

    static void IncreaseModule(int &n, int amount);


public:
    static Point GetTargetForMove(Point coordinates, Map *map);

    static Point GetNextOnAxis(Point coordinates, Map *map);

    static Point GetTargetForShoot(Point coordinates, std::vector<std::vector<int>> attackMatrix,
                                   std::vector<std::vector<Vehicle *>> vehicles, int playerId);

    static std::vector<int> GetPotentialDamage(const std::vector<Vehicle*>& vehicles, const std::vector<Point>& enemyPoints);

    static std::vector<Point> GetPointsForShoot(const std::vector<std::vector<int>>& attackMatrix,
                                                std::vector<std::vector<Vehicle *>> vehicles, int playerId);

    static std::unordered_map<Vehicle*, std::vector<Vehicle*>> GetPointsForShoot
            (const std::vector<std::vector<int>>& attackMatrix,
             const std::vector<std::vector<Vehicle *>>& vehicles,
             int playerId, int playersNum = 3, int playerVehiclesNum = 5);
};
