#pragma once
#include "construction.hpp"

class Base : public Construction {
public: 
    Base(std::vector<Hex*>& basis) : Construction(basis) {}

    void play(Vehicle* v) override {
        v->inc_capture();
    }
private:
};