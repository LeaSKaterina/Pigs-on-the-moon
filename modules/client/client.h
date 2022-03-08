#pragma once

#include "enums/action.h"
#include "enums/result.h"
#include <cstring>
#include <iostream>
#include <memory>

#include <SFML/Network.hpp>
#include <nlohmann/json.hpp>


struct Response {
    Result result;
    nlohmann::ordered_json answer;

    friend std::ostream &operator<<(std::ostream &out, const Response &response);
};

class Client {
public:
    Client();

    ~Client() { tcpSocket.disconnect(); }

    Response Login(const std::string &name, const std::string &password = "",
                   const std::string &game = "", int numTurns = 0, int numPlayers = 1,
                   bool isObserver = false);

    Response Logout() {
        this->SendRequest(Action::LOGOUT, "");
        return this->GetAnswer();
    }

    Response Map() {
        this->SendRequest(Action::MAP, "");
        return this->GetAnswer();
    }

    Response GameState() {
        this->SendRequest(Action::GAME_STATE, "");
        return this->GetAnswer();
    }

    Response GameActions() {
        this->SendRequest(Action::GAME_ACTIONS, "");
        return this->GetAnswer();
    }

    Response Turn() {
        this->SendRequest(Action::TURN, "");
        return this->GetAnswer();
    }

    Response Chat(const std::string &msg);

    //send Shoot or Move. This actions has same param
    Response SendTankAction(Action action, int vehicleId, int x, int y, int z);

    static void PrintLogInfo(const std::string &info) { std::cout << info << '\n'; }

private:
    const char address[26] = "wgforge-srv.wargaming.net";
    const int port = 443;
    sf::TcpSocket tcpSocket;
    const int codeSize = 4;// action size in bytes

    //send to server msg
    void SendRequest(Action action, const std::string &msg);

    //receive int from server
    int GetIntFromServer();

    //receive data from server. Guaranteed that all packages are received
    std::vector<char> Receive(size_t size);

    //gets response after request
    Response GetAnswer();

    bool debug;
};
