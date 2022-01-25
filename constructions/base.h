#ifndef PIGS_ON_THE_MOON_BASE_H
#define PIGS_ON_THE_MOON_BASE_H

//#pragma once
#include "construction.h"

class Base : public Construction {
public: 
    Base(std::vector<Hex*>& basis) : Construction(basis) {}
    void Play(Vehicle* v) override;
};