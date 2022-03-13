#include "Controller.h"

Controller::Controller(const std::string &gameName, int waitTime) : bot1(*this, "Den-Pig1", "", game, 0, 3),
                                                                    bot2(*this, "Den-Pig2", "", game, 0, 3),
                                                                    bot3(*this, "Den-Pig3", "", game, 0, 3),
                                                                    observer(*this, "Den-obs", "", game, 0, 3, true),
                                                                    thread1(&Bot::StartAI, &bot1),
                                                                    thread2(&Bot::StartAI, &bot2),
                                                                    thread3(&Bot::StartAI, &bot3),
                                                                    observerThread(&Controller::ObserverThread, this),
                                                                    view(*this, observer.gc->GetGame(), observerMutex),
                                                                    waitTime(waitTime), game(gameName) {
    thread1.launch();
    thread2.launch();
    thread3.launch();

    observerThread.launch();

    view.Show();
}

Controller::~Controller() {
    thread1.wait();
    thread2.wait();
    thread3.wait();
    observerThread.wait();
}

void Controller::ObserverThread() {
    observer.gc->ConnectPlayer();
    while (!observer.gc->GameIsFinished() && !GetIsWindowClose()) {
        sf::Lock lock(observerMutex);
        observer.gc->UpdateGameState();
        observerMutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(this->waitTime));
        observer.gc->SendTurn();
    }
}
