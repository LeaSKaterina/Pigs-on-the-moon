#pragma once

#include "actors/vehicles/vehicle.h"
#include "map/map.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

class ActionController {
private:
//    const Map &map;

public:
//    ActionController(const Map &map) : map(map) {}

    static std::vector<bool>
    NeutralityRuleCheck(const std::vector<std::vector<bool>> &attackMatrix, int playerId, int playersNum);

    static std::unordered_map<Vehicle *, std::vector<Vehicle *>>
    GetPointsForShoot(const std::vector<std::vector<bool>> &attackMatrix,
                      const std::vector<std::vector<Vehicle *>> &vehicles,
                      int playerId, int playersNum = 3);
};
