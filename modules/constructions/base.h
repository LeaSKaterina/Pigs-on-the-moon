#ifndef PIGS_ON_THE_MOON_CONSTRUCTIONS_BASE_H
#define PIGS_ON_THE_MOON_CONSTRUCTIONS_BASE_H

#include "construction.h"

class Base : public Construction {
public:
    explicit Base(std::vector<Hex *> &basis) : Construction(basis) {}

    void Play(Vehicle *v) override;
};



#endif  //PIGS_ON_THE_MOON_CONSTRUCTIONS_BASE_H