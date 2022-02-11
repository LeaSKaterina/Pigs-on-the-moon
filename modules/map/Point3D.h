#pragma once

#include <iostream>

struct Point3D{
public:
    int points[3];
    int& x = points[0];
    int& y = points[1];
    int& z = points[2];

    Point3D() = default;

    Point3D(int x, int y, int z) : points {x, y, z} {}

    Point3D operator+(const Point3D &other) const {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    bool operator==(const Point3D &other) const{
        return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
    }

    Point3D operator=(const Point3D &other) {
        for (int i = 0; i < 3; ++i) {
            this->points[i] = other.points[i];
        }
        return *this;
    }

    bool operator<(const Point3D &other) const {
        for (int i = 0; i < 3; ++i) {
            if(this->points[i] != other.points[i]) return this->points[i] < other.points[i];
        }
        return false;
    }

    int operator[](int index) const { return points[index];}

    int& operator[](int index) { return points[index];}

    int Distance(const Point3D &other) const {
        return (abs(this->x - other.x) + abs(this->y - other.y) + abs(this->z - other.z)) / 2;
    }
};