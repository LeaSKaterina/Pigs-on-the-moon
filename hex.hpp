#pragma once
#include <cstdlib>
#include <tuple>

struct Hex {
public: 

  Hex(int x, int y, int z) {
    coordinates = std::make_tuple(x, y, z);
  }

  // void init(int x, int y, int z) {
  //   this->x = x;
  //   this->y = y;
  //   this->z = z;
  // }
  
  bool isEmpty() const {
    return isEmpty_;
  }

  bool isSpecial() const {
    return owner_id == -1;
  }

  const std::tuple<int, int, int>& get_coordinates() const {
    return coordinates;
  }

  bool occupy() {
    if (!isEmpty_)
      return false;
    
    isEmpty_ = false;
    return true;
  }

  void free() {
    isEmpty_ = true;
  }

  static int GetDistance (Hex& f, Hex& s) {
    auto& [x1, y1, z1] = f.coordinates;
    auto& [x2, y2, z2] = s.coordinates;
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
  }

  void set_owner_id(int id) {
    owner_id = id;
  }

  bool operator<(const Hex& rhs) const {
    return coordinates < rhs.coordinates;
  }

  bool operator==(const Hex& rhs) const {
    return coordinates == rhs.coordinates;
  }

private:
  
  std::tuple<int, int, int> coordinates;

  bool isEmpty_ = true;

  int owner_id = -1;
};