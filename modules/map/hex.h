#pragma once

#include <cstdlib>
#include <tuple>

typedef std::tuple<int, int, int> Point;

struct Hex {

private:
    Point coordinates;
    bool isEmpty = true;
    int ownerId = -1;

public:
    Hex(int x, int y, int z) { coordinates = std::make_tuple(x, y, z); }

    [[nodiscard]] bool IsEmpty() const { return isEmpty; }

    [[nodiscard]] bool IsSpecial() const { return ownerId == -1; }

    [[nodiscard]] const Point &GetCoordinates() const { return coordinates; }

    bool Occupy();

    void Free() { isEmpty = true; }

    static int GetDistance(const Point &f, const Point &s);

    void SetOwnerId(int id) { ownerId = id; }

    bool operator<(const Hex &rhs) const { return coordinates < rhs.coordinates; }

    bool operator==(const Hex &rhs) const { return coordinates == rhs.coordinates; }
};
