#pragma once

#include <cstdlib>
#include <tuple>

struct Hex {

private:
    std::tuple<int, int, int> coordinates;
    bool isEmpty = true;
    int ownerId = -1;

public:
    Hex(int x, int y, int z) { coordinates = std::make_tuple(x, y, z); }

    [[nodiscard]] bool IsEmpty() const { return isEmpty; }

    [[nodiscard]] bool IsSpecial() const { return ownerId == -1; }

    [[nodiscard]] const std::tuple<int, int, int> &GetCoordinates() const { return coordinates; }

    bool Occupy();

    void Free() { isEmpty = true; }

    static int GetDistance(Hex &f, Hex &s);

    void SetOwnerId(int id) { ownerId = id; }

    bool operator<(const Hex &rhs) const { return coordinates < rhs.coordinates; }

    bool operator==(const Hex &rhs) const { return coordinates == rhs.coordinates; }
};
