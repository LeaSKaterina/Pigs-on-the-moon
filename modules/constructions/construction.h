#pragma once

#include "../actors/vehicles/vehicle.h"
#include "../map/hex.h"

#include <vector>

class Construction {
private:
    static int counter;
    int id;

public:
    virtual void Play(Vehicle *) = 0;

    virtual ~Construction() = default;

    explicit Construction(std::vector<Hex *> &basis);
};
