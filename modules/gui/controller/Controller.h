#pragma once

#include "gui/model/Bot.h"
#include "gui/view/View.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Controller {
private:
    std::string game = "game";
    Bot bot1;
    Bot bot2;
    Bot bot3;
    Bot observer;
    sf::Thread thread1;
    sf::Thread thread2;
    sf::Thread thread3;
    sf::Thread observerThread;
    sf::Mutex observerMutex;
    View view;


    void ObserverThread() {
        observer.gc.InitIds();
        while (!observer.gc.GameIsFinished()) {
            sf::Lock lock(observerMutex);
            observer.gc.UpdateGameState();
            observerMutex.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(9));
            observer.gc.SendTurn();
        }
    }

public:
    Controller() : bot1("Den-Pig1", "", game, 0, 3),
                   bot2("Den-Pig2", "", game, 0, 3),
                   bot3("Den-Pig3", "", game, 0, 3),
                   observer("Den-obs", "", game, 0, 3, true),
                   thread1(&Bot::StartAI, &bot1),
                   thread2(&Bot::StartAI, &bot2),
                   thread3(&Bot::StartAI, &bot3),
                   observerThread(&Controller::ObserverThread, this),
                   view(observer.gc.GetGame(), observerMutex) {
        thread1.launch();
        thread2.launch();
        thread3.launch();

        observerThread.launch();


        view.Show();
    }

};

