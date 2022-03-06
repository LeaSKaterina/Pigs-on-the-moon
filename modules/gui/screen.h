#pragma once

#include <SFML/Graphics.hpp>

struct Screen {
    unsigned int width;
    unsigned int height;

    Screen() {}

    Screen(unsigned int width, unsigned int height) : width(width), height(height) {}
};

struct Point2D {
    float x;
    float y;

    Point2D operator-(const Point2D &right) const {
        return {this->x - right.x, this->y - right.y};
    }

    Point2D operator/(int right) const {
        return {this->x / right, this->y / right};
    }
};