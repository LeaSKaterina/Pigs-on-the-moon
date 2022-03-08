#pragma once

#include "enums/types.h"
#include "map/Point3D.h"
#include <cstdlib>
#include <tuple>
#include <vector>

struct Hex {
public:
    Hex(int x, int y, int z) : coordinates(x, y, z) {}

    [[nodiscard]] bool IsEmpty() const { return isEmpty; }

    [[nodiscard]] bool IsSpecial() const { return ownerId != -1; }

    [[nodiscard]] const Point3D &GetCoordinates() const { return coordinates; }

    [[nodiscard]] ConstructionsTypes::Type GetType() const;

    bool Occupy();

    void Free() { isEmpty = true; }

    void SetOwnerId(int id) { ownerId = id; }

    bool operator<(const Hex &rhs) const { return coordinates < rhs.coordinates; }

    bool operator==(const Hex &rhs) const { return coordinates == rhs.coordinates; }

    static std::vector<Point3D> GetRing(Point3D center, int r);

    static Point3D GetDiagonalVector(const Point3D &from, const Point3D &to, int radius);// Point array : int[3]

private:
    Point3D coordinates;
    bool isEmpty = true;
    int ownerId = -1;
};
