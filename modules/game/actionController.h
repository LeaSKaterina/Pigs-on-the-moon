#ifndef PIGS_ON_THE_MOON_GAME_ACTIONCONTROLLER_H
#define PIGS_ON_THE_MOON_GAME_ACTIONCONTROLLER_H

//#include <tuple>
#include <cstdlib>
#include <iostream>
#include "../map/hex.h"
#include "../map/map.h"


class ActionController {
private:
    static void ModuleDecrement(int &n);

    static void ModuleIncrement(int &n);

    static void ReduceModule(int &n, int amount);

    static void IncreaseModule(int &n, int amount);


public:
    static std::tuple<int, int, int> getTargetForMove(std::tuple<int, int, int> coordinates, Map *map);

    static std::tuple<int, int, int> getNextOnAxis(std::tuple<int, int, int> coordinates, Map *map);

    static std::tuple<int, int, int>
    getTargetForShoot(std::tuple<int, int, int> coordinates, vector<vector<int>> attackMatrix,
                      vector<vector<Vehicle *>> vehicles, int playerId);


};


#endif //PIGS_ON_THE_MOON_GAME_ACTIONCONTROLLER_H
