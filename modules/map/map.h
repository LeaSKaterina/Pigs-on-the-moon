#pragma once

#include "constructions/construction.h"
#include "enums/types.h"
#include "hex.h"
#include <map>
#include <tuple>

class Map {
private:
    int size;
    std::vector<Construction *> content;
    std::map<Point3D, Hex *> grid;

    void InitGrid();

public:
    explicit Map(int size) : size(size) { InitGrid(); }

    void AddConstruction(ConstructionsTypes::Type type, std::vector<Point3D> &points);


    [[nodiscard]] Hex *Get(const Point3D &p) const { return grid.at(p); }

    [[nodiscard]] bool IsBasePoint(const Hex *point) const;

    [[nodiscard]] bool IsBasePoint(const Point3D &point) const;
    ConstructionsTypes::Type GetType(const Hex &hex) const;

    ~Map();

    const std::map<Point3D, Hex *> &GetGrid() const{ return grid; }

    const std::vector<Construction *> &GetContent() const { return content; }
};
