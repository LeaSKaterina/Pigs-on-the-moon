#ifndef PIGS_ON_THE_MOON_CONSTRUCTIONS_CONSTRUCTION_H
#define PIGS_ON_THE_MOON_CONSTRUCTIONS_CONSTRUCTION_H

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



#endif // PIGS_ON_THE_MOON_CONSTRUCTIONS_CONSTRUCTION_H