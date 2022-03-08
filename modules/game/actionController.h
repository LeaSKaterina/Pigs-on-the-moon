#pragma once

#include "actors/vehicles/vehicle.h"
#include "map/map.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

class ActionController {
public:
    static std::vector<bool>
    NeutralityRuleCheck(const std::vector<std::vector<bool>> &attackMatrix, int playerId);

    static std::unordered_map<Vehicle *, std::vector<Vehicle *>>
    GetPointsForShoot(const std::vector<std::vector<bool>> &attackMatrix,
                      const std::vector<std::vector<Vehicle *>> &vehicles,
                      const Map *map,
                      int playerId);
};
