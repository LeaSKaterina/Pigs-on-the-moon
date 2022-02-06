#pragma once

#include "actors/vehicles/vehicle.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

class ActionController {
private:
public:
    static std::vector<bool>
    NeutralityRuleCheck(const std::vector<std::vector<bool>> &attackMatrix, int playerId, int playersNum);

    static std::unordered_map<Vehicle *, std::vector<Vehicle *>>
    GetPointsForShoot(const std::vector<std::vector<bool>> &attackMatrix,
                      const std::vector<std::vector<Vehicle *>> &vehicles,
                      int playerId, int playersNum = 3);
};
