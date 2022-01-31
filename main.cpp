#include <iostream>
//#include "modules/client/Client.h"
//#include "modules/game.h"
#include "modules/gameClient.h"

#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;

//void parse_map_info() {
//    char map_txt[] = R"(
//    {
//        "Map":
//              {
//                "content":
//                {
//                  "base":
//                  [
//                    {"x":-1,"y":0,"z":1},
//                    {"x":-1,"y":1,"z":0},
//                    {"x":0,"y":-1,"z":1},
//                    {"x":0,"y":0,"z":0},
//                    {"x":0,"y":1,"z":-1},
//                    {"x":1,"y":-1,"z":0},
//                    {"x":1,"y":0,"z":-1}
//                  ],
//                  "catapult":[],
//                  "hard_repair":[],
//                  "light_repair":[],
//                  "obstacle":[]
//                },
//                "name":"map01",
//                "size":11,
//                "spawn_points":
//                [
//                  {
//                    "medium_tank":
//                    [
//                      {"x":-7,"y":-3,"z":10},
//                      {"x":-6,"y":-4,"z":10},
//                      {"x":-5,"y":-5,"z":10},
//                      {"x":-4,"y":-6,"z":10},
//                      {"x":-3,"y":-7,"z":10}
//                    ]
//                  },
//                  {
//                    "medium_tank":
//                    [
//                      {"x":-7,"y":10,"z":-3},
//                      {"x": -6,"y":10,"z":-4},
//                      {"x":-5,"y":10,"z":-5},
//                      {"x":-4,"y":10,"z":-6},
//                      {"x":-3,"y":10,"z":-7}
//                    ]
//                  },
//                  {
//                    "medium_tank":
//                    [
//                      {"x":10,"y":-7,"z":-3},
//                      {"x":10,"y":-6,"z":-4},
//                      {"x":10,"y":-5,"z":-5},
//                      {"x":10,"y":-4,"z":-6},
//                      {"x":10,"y":-3,"z":-7}
//                    ]
//                  }
//                ]
//              }
//    }
//    )";
//    json map = json::parse(map_txt);
//    auto map_in = map.value("Map", json(""));
//    auto spawn_info = map_in.value("spawn_points", nlohmann::json(""));
//    auto base_info = map_in.value("content", json("")).value("base", json(""));
//    for (auto& x : map_in.items()) {
////        cout << x.value("x", -1) << endl;
//        std::cout << "key is : " << x.key()
//                  << ", value is : " << x.value() << '\n';
////        auto inx = x.value().value("medium_tank", nlohmann::json(""));
////        cout << "\tin\n";
////        for (auto& i : inx)
////            cout << "next\t" << i.value("x", -1) << endl;
//    }
////    cout << map_in.value("content", json("not_fount"));
//}

//void parse_am() {
//    char matrix_txt[] = R"(
//         {
//            "win_points":
//            {
//              "406":
//              {
//                "capture":0,
//                "kill":0
//              },
//                 "1239":
//              {
//                "capture":0,
//                "kill":0
//              }
//            }
//         }
//    )";
//    json am = json::parse(matrix_txt);
//    auto am_in = am.value("win_points", json(""));
//    for(auto& pm : am_in.items()) {
//        string key = pm.key();
//        int k_ = stoi(key);
//        cout << "|" << k_ << "|" << pm.value() << "|" << endl;
//        cout << "size: " << pm.value().size() << endl;
//        for(int i : pm.value())
//            cout << "nex v: " << i << ' ';
//        cout << endl;
//    }
//}

int main() {
    bool debug = true;

///////////////////////////////////////////////////////////////////////////////variables for debugging
    std::string game = "test3";// the name of the game we are connecting to
    int numbersCount = 2; // number of players. Values from [1, 2, 3]
    int numbersTurn = 100; // numbers of turns. Values from [0 ... 100]
    int ourOrder = 1; // our connection number. Values from [1, 2, 3] // may be mare than numberCount
///////////////////////////////////////////////////////////////////////////////

    if(ourOrder > numbersCount) // simple check max value
        ourOrder = numbersCount;

    Client* clients = new Client[numbersCount - 1]; // bots for extras
    GameClient gc(debug); // our overmind

    int clientIndex = 0;
    for (int i = 0; i < numbersCount; ++i) {// Login
        if(i == ourOrder - 1) {
            gc.initGame("test14", "", game, numbersTurn, numbersCount);
            continue;
        }
        clients[clientIndex].Login("bot" + std::to_string(clientIndex), "", game, numbersTurn, numbersCount);
        ++clientIndex;
    }


    while(gc.SendTurn() != true);
    gc.InitPlayersId();
    while(gc.GameIsFinished() != true){
        gc.CheckGameState();
        if(gc.isOurTurn())
            gc.SendAction();
//        std::cout << gc.getClient()->GameState();
        if(debug)
            std::cerr << "\n---------------------------------------\n";
        gc.SendTurn();
    }
    std::cout << "Game is finished : " << std::boolalpha << gc.GameIsFinished() << '\n';
//    parse_am();
}

