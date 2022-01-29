#include <iostream>
//#include "modules/client/Client.h"
//#include "modules/game.h"
#include "modules/game_client.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

//void test_json() {
//    // create a JSON object with different entry types
//    json j =
//    {
//            {"integer", 1},
//            {"boolean", false},
//            {"string", "Welcome to CppSecrets!!!"},
//            {"object", {{"one", 1}, {"two", 2}}},
//            {"array", {1, 2, 3}}
//    };
//
//    // accessing existing values in the above given Json.
//    int integer_value = j.value("integer", 0);
//    bool boolean_value = j.value("boolean", false);
//    std::cout << integer_value <<endl;
//    std::cout << boolean_value<<endl;
//
//    // accessing non existing values. As they are non existing
//    // they give us the default values provided in the second parameter.
//    std::string string_value = j.value("Strings", "oops");
//    std::cout<<string_value<<endl;
//}

//void parse() {
//    char* msg = "{\"result\" : 0, \"answer\" : \"\" }";
//
//    char text[] = R"(
//     {
//         "colors": {
//	                "color": "black",
//		        "category": "hue",
//		        "type": "primary",
//	                       "code": {
//			        "rgba": [255,255,255,1],
//			        "hex": "#000"
//			      }
//		     }
//     }
//     )";
//
//    char* emptyMsg = "";
//
//    json b = json::parse(text);
////    nlohmann::json a = json::parse(msg);
//    json a(msg);
////    auto c = json::parse(emptyMsg); // error
////    int x = a.value("fi", -1);
////    if (x == -1)
////        cout << "fail";
////    else
////        cout << "ok";
//    cout << a << endl;
//    for (auto& x : a.items())
//        std::cout << "key is : " << x.key()
//                  << ", value is : " << x.value() << '\n';
//
//}

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

int main() {

//    test_json();

//    parse();

//    parse_map_info();

//    Client client;
//    std::cout << client.Login("test18722") << '\n';
//    std::cout << client.Map() << '\n';
//    cout << client.GameActions();
//    cout << client.GameState();
//    cout << client.Turn();
//    cout << client.Move(1, -1, 2, 3);
//    cout << client.GameActions();
//    cout << client.GameState();
//    cout << client.Turn();
//    std::cout << client.Logout() << '\n';

//    Game game;
//    game.InitMap(11);
//
//    return 0;
    GameClient gc;
    gc.initGame("test14");
    cout << "Success";
}