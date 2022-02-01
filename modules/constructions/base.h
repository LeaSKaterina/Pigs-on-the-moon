#pragma once

#include "construction.h"

class Base : public Construction {
public:
    explicit Base(std::vector<Hex *> &basis) : Construction(basis) {}

    void Play(Vehicle *v) override;
};


