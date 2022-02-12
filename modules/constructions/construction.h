#pragma once

#include "actors/vehicles/vehicle.h"
#include "map/hex.h"
#include "enums/types.h"

#include <vector>

class Construction {
private:
    static int counter;
    int id;
    ConstructionsTypes::Type type;

public:

    ~Construction() = default;

    [[nodiscard]] ConstructionsTypes::Type GetType() const {
        return type;
    }

    Construction(ConstructionsTypes::Type type, std::vector<Hex *> &basis);
};
