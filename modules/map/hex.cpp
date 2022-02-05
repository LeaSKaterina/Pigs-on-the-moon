#include "hex.h"

bool Hex::Occupy() {
    if (!isEmpty)
        return false;

    isEmpty = false;
    return true;
}

int Hex::GetDistance(Hex &f, Hex &s) {
    auto &[x1, y1, z1] = f.coordinates;
    auto &[x2, y2, z2] = s.coordinates;
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

