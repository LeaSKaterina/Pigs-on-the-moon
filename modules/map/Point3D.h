#pragma once

#include <iostream>
#include <vector>

struct Point3D {
public:
    int x;
    int y;
    int z;

    Point3D() = default;

    Point3D(int x, int y, int z) : x(x), y(y), z(z) {}

    Point3D operator+(const Point3D &other) const {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    bool operator==(const Point3D &other) const {
        return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
    }

    bool operator!=(const Point3D &other) const {
        return (this->x != other.x) || (this->y != other.y) || (this->z != other.z);
    }

    bool operator<(const Point3D &other) const {
        if (this->x != other.x) return this->x < other.x;
        if (this->y != other.y) return this->y < other.y;
        if (this->z != other.z) return this->z < other.z;
        return false;
    }

    int operator[](int index) const {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return x;
        }
    }

    int &operator[](int index) {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return x;
        }
    }

    int Distance(const Point3D &other) const {
        return (abs(this->x - other.x) + abs(this->y - other.y) + abs(this->z - other.z)) / 2;
    }

    static std::vector<Point3D> GetNeighborDirections() {
        return {Point3D(+1, -1, 0), Point3D(+1, 0, -1), Point3D(0, +1, -1),
                Point3D(-1, +1, 0), Point3D(-1, 0, +1), Point3D(0, -1, +1)};
    }


    [[nodiscard]] std::string ToString() const {
        return std::to_string(x) + std::to_string(y) + std::to_string(z);
    }
};

template<>
struct std::hash<Point3D> {
    size_t operator()(const Point3D point) const {
        return point.x + 31 * point.y + 997 * point.z;
    }
};