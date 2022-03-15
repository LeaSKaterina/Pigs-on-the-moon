#include "gui/controller/Controller.h"

int main(int argc, char **argv) {

    std::string name = "team";
    std::string password;
    std::string gameName;
    int numberTurns = 45;
    int numberPlayers = 1;
    bool observer = false;

    //parsing arguments
    for (int i = 1; i < argc; i += 2) {
        std::string key(argv[i]);
        char *value = argv[i + 1];

        if(key == "-n"){
            name = value;
        }else if(key == "-pa"){
            password = value;
        }else if(key == "-g"){
            gameName = value;
        }else if(key == "-t"){
            numberTurns = std::stoi(value);
        }else if(key == "-pl"){
            numberPlayers = std::stoi(value);
        }else if(key == "-o"){
            observer = std::stoi(value);
        }
    }


    AIClient bot(name, password, gameName, numberTurns, numberPlayers, observer);
    sf::Thread thread(&AIClient::StartAI, &bot);
    thread.launch();
//    bot.StartAI();

//    Gui with 3 our bots
    Controller controller(gameName, 0, numberPlayers);
    thread.wait();

    return 0;
}
