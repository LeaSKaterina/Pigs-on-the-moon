#pragma once
#include <SFML/Graphics.hpp>

struct Screen{
    unsigned int width;
    unsigned int height;
    Screen() {}
    Screen(unsigned int width, unsigned int height) : width(width), height(height) {}

};