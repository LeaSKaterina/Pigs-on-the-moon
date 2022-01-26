#include "player.h"

int Player::GetId() const {
    return id;
}

Player::Player(int id, std::string name, std::string pass) {
    this->id = id;
    this->name = name;
    this->password = pass;
    this->capture = 0;
    this->kill = 0;
}
