#ifndef TIME_MANAGER_
#define TIME_MANAGER_

#include <chrono>
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

public:
    explicit TimeManager(int targetFPS):
            targetFPS(targetFPS),
            frameTime(std::chrono::duration<double, std::milli>(1000.0 / targetFPS)) {}

    std::chrono::duration<double, std::milli> synchronizeTick() {
        auto currentTime = std::chrono::steady_clock::now();

        auto deltaTime = frameTime - (currentTime - lastUpdateTime);
        if (deltaTime > std::chrono::duration<double, std::milli>(0)) {
            std::this_thread::sleep_for(deltaTime);
        }
        lastUpdateTime = currentTime;
        return deltaTime;
    }
};

#endif
