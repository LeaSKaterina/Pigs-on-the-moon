#pragma once

#include <vector>
#include "../actors/vehicle.h"
#include "../map/hex.h"

class Construction {
private:
    static int counter;
    int id;

public:
    virtual void Play(Vehicle *) = 0;

    virtual ~Construction() = default;

    explicit Construction(std::vector<Hex *> &basis);
};

