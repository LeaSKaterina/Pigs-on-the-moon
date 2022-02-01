#pragma once

#include <cstdlib>
#include <tuple>

struct Hex {

private:

    std::tuple<int, int, int> coordinates;
    bool isEmpty = true;
    int ownerId = -1;

public:

    Hex(int x, int y, int z);

    bool IsEmpty() const;

    bool IsSpecial() const;

    const std::tuple<int, int, int> &GetCoordinates() const;

    bool Occupy();

    void Free();

    static int GetDistance(Hex &f, Hex &s);

    void SetOwnerId(int id);

    bool operator<(const Hex &rhs) const;

    bool operator==(const Hex &rhs) const;
};

