#ifndef TIME_MANAGER_
#define TIME_MANAGER_

#include <chrono>
#include <iostream>
#include <thread>

class TimeManager {
private:
    // objetivo de frames (updtes que se pasen a los clientes) por segundo
    int targetFPS;

    // Càlculo del tiempo que debrìa durar cada tick del gameLoop
    std::chrono::duration<double, std::milli> frameTime;

    // tiempo de inicio del tick
    std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime =
            std::chrono::steady_clock::now();

protected:
    virtual void handleOverflowOfTimeInTick() = 0;


public:
    explicit TimeManager(int targetFPS):
            targetFPS(targetFPS), frameTime(std::chrono::milliseconds(1000 / targetFPS)) {}

    void synchronizeTick() {
        auto currentTime = std::chrono::steady_clock::now();
        auto timeRemaining = frameTime - (currentTime - lastUpdateTime);
        if (timeRemaining > frameTime.zero()) {
            std::this_thread::sleep_for(timeRemaining);
        } else {
            handleOverflowOfTimeInTick();
        }

        lastUpdateTime = currentTime;
    }
};

#endif
