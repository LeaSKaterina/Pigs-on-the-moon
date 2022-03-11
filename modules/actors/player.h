#pragma once

#include <string>
#include <utility>

struct Player {
public:
    Player(int id, std::string name, std::string pass) : id(id),
                                                         name(std::move(name)),
                                                         password(std::move(pass)) {}

    [[nodiscard]] int GetId() const { return id; }

    void SetIdAdapter(std::vector<int> idAdapter) {tanksIdAdapter = std::move(idAdapter);}

    [[nodiscard]] int GetServerId(int index) const {return tanksIdAdapter[index];}

private:
    const std::string name;
    const std::string password;
    int id;

    // save real ids of tanks to interact with the server
    std::vector<int> tanksIdAdapter;
};
