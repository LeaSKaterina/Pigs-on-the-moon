#include "hex.h"


Hex::Hex(int x, int y, int z) {
    coordinates = std::make_tuple(x, y, z);
}

bool Hex::IsEmpty() const {
    return isEmpty;
}

bool Hex::IsSpecial() const {
    return ownerId == -1;
}

const std::tuple<int, int, int> &Hex::GetCoordinates() const {
    return coordinates;
}

bool Hex::Occupy() {
    if (!isEmpty)
        return false;

    isEmpty = false;
    return true;
}

void Hex::Free() {
    isEmpty = true;
}

int Hex::GetDistance(Hex &f, Hex &s) {
    auto&[x1, y1, z1] = f.coordinates;
    auto&[x2, y2, z2] = s.coordinates;
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

void Hex::SetOwnerId(int id) {
    ownerId = id;
}

bool Hex::operator<(const Hex &rhs) const {
    return coordinates < rhs.coordinates;
}

bool Hex::operator==(const Hex &rhs) const {
    return coordinates == rhs.coordinates;
}

