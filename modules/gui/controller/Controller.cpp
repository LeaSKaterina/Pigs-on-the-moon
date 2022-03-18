#include "Controller.h"

#include <utility>

Controller::Controller(std::string gameName, int waitTime) : bot1("Den-Pig1", "", game, 0, 3),
                                                             bot2("Den-Pig2", "", game, 0, 3),
                                                             bot3("Den-Pig3", "", game, 0, 3),
                                                             observer("Den-obs", "", game, 0, 3, true),
                                                             thread1(&Bot::StartAI, &bot1),
                                                             thread2(&Bot::StartAI, &bot2),
                                                             thread3(&Bot::StartAI, &bot3),
                                                             observerThread(&Controller::ObserverThread, this),
                                                             view(*this, observer.GetClient()->GetGame(), observerMutex),
                                                             waitTime(waitTime), game(std::move(gameName)) {
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

void Controller::ObserverThread() { // TODO:THERE?
    observer.GetClient()->ConnectPlayer();
    while (!observer.GetClient()->GameIsFinished() && !GetIsWindowClose()) {
        sf::Lock lock(observerMutex);
        observer.GetClient()->UpdateGameState();
        observerMutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(this->waitTime));
        observer.GetClient()->SendTurn();
    }
}
