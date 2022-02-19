#pragma once

#include "map/Point3D.h"
#include "enums/types.h"
#include <cstdlib>
#include <tuple>
#include <vector>

struct Hex {

private:
    Point3D coordinates;
    bool isEmpty = true;
    // TODO! remove. it's useless
    int ownerId = -1;

public:
    Hex(int x, int y, int z) : coordinates(x, y, z) {}

    [[nodiscard]] bool IsEmpty() const { return isEmpty; }

    [[nodiscard]] bool IsSpecial() const { return ownerId != -1; }

    [[nodiscard]] const Point3D &GetCoordinates() const { return coordinates; }

    int GetOwnerId() const;

    bool Occupy();

    void Free() { isEmpty = true; }

    void SetOwnerId(int id) { ownerId = id; }

    bool operator<(const Hex &rhs) const { return coordinates < rhs.coordinates; }

    bool operator==(const Hex &rhs) const { return coordinates == rhs.coordinates; }

    static std::vector<Point3D> GetRing(Point3D center, int r);

//    static Point GetDiagonalVector(const Point& from, const Point& to, int radius);
    static Point3D GetDiagonalVector(const Point3D &from, const Point3D &to, int radius); // Point array : int[3]
};
