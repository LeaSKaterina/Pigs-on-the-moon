#pragma once

//#include <tuple>
#include "../map/hex.h"
#include "../map/map.h"
#include <cstdlib>
#include <iostream>


class ActionController {
private:
    static void ModuleDecrement(int &n);

    static void ModuleIncrement(int &n);

    static void ReduceModule(int &n, int amount);

    static void IncreaseModule(int &n, int amount);


public:
    static std::tuple<int, int, int> GetTargetForMove(std::tuple<int, int, int> coordinates, Map *map);

    static std::tuple<int, int, int> GetNextOnAxis(std::tuple<int, int, int> coordinates, Map *map);

    static std::tuple<int, int, int>
    GetTargetForShoot(std::tuple<int, int, int> coordinates, vector<vector<int>> attackMatrix,
                      vector<vector<Vehicle *>> vehicles, int playerId);
};
