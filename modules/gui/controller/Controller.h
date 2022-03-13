#pragma once

#include "gui/model/Bot.h"
#include "gui/view/View.h"

//#include "AIBehaviorTree/aiBehaviorTree.h"

class Controller {
public:
    Controller(const std::string &gameName, int waitTime);

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
    Bot bot1;
    Bot bot2;
    Bot bot3;
    Bot observer;
    sf::Thread thread1;
    sf::Thread thread2;
    sf::Thread thread3;
    sf::Thread observerThread;
    View view;
    sf::Mutex observerMutex;
    bool isWindowClose = false;
    sf::Mutex closeMutex;


    void ObserverThread();
};
