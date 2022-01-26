#ifndef PIGS_ON_THE_MOON_CONSTRUCTION_H
#define PIGS_ON_THE_MOON_CONSTRUCTION_H


#pragma once

#include <vector>
#include "..\map\hex.h"
#include "..\actors\vehicle.h"

class Construction {
private:
    // std::vector<Hex*> basis;
    static int counter;
    int id;

public:
    virtual void Play(Vehicle *);

    explicit Construction(std::vector<Hex *> &basis);
};

#endif //PIGS_ON_THE_MOON_CONSTRUCTION_H
