#pragma once


#include "gui/view/View.h"
#include "AI/AIClient.h"


class Controller {
public:
    Controller(std::string gameName, int waitTime, int numberPlayers = 3);

    virtual ~Controller();

    bool GetIsWindowClose() {
        sf::Lock lock(closeMutex);
        return isWindowClose;
    };

    void CloseGame() {
        sf::Lock lock(closeMutex);
        isWindowClose = true;
    }


private:
    std::string game;
    const int waitTime;
    AIClient observer;
    sf::Thread observerThread;
    View view;
    sf::Mutex observerMutex;
    bool isWindowClose = false;
    sf::Mutex closeMutex;


    void ObserverThread();
};
