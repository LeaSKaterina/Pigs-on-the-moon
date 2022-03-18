#include "gui/controller/Controller.h"
#include "AI/AIClient.h"

int main(int argc, char **argv) {

    std::string name = "Pigs-on-the-Moon";
    std::string password;
    std::string gameName;
    int numberTurns = 45;
    int numberPlayers = 3;
    bool isObserver = false;
    bool isGui = false;

    //parsing arguments
    for (int i = 1; i < argc; i += 2) {
        std::string key(argv[i]);
        char *value = argv[i + 1];

        if (key == "-n") {
            name = value;
        } else if (key == "-pa") {
            password = value;
        } else if (key == "-g") {
            gameName = value;
        } else if (key == "-t") {
            numberTurns = std::stoi(value);
        } else if (key == "-pl") {
            numberPlayers = std::stoi(value);
        } else if (key == "-o") {
            isObserver = std::stoi(value);
        }else if (key == "--gui") {
            isGui = std::stoi(value);
        }else if (key == "-h") {
            std::cout << "-h keys info" << '\n';
            std::cout << "-n name default: Pigs-on-the-Moon" << '\n';
            std::cout << "-pa password" << '\n';
            std::cout << "-g gameName" << '\n';
            std::cout << "-t  numberTurns default: 45" << '\n';
            std::cout << "-pl  numberPlayers default: 3" << '\n';
            std::cout << "-o isObserver 0 (false) 1(true) default: false" << '\n';
            std::cout << "--gui isGui 0 (false) 1(true) default: false" << '\n';
            return 0;
        }
    }


    AIClient bot(name, password, gameName, numberTurns, numberPlayers, isObserver);
    sf::Thread thread(&AIClient::StartAI, &bot);
    thread.launch();

    if(isGui) Controller controller(gameName, 0, numberPlayers);
    thread.wait();

    return 0;
}
