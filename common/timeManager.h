#ifndef TIME_MANAGER_
#define TIME_MANAGER_

#include <chrono>
#include <thread>

class TimeManager {
private:
    // objetivo de frames (updtes que se pasen a los clientes) por segundo
    // Càlculo del tiempo que debrìa durar cada tick del gameLoop
    float tickDurationTarget;
    float tickDuration = 0.0f;

    // tiempo de inicio del tick
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTickTime;


public:
    explicit TimeManager(int targetFPS):
            tickDurationTarget(1.0f / targetFPS),
            lastTickTime(std::chrono::high_resolution_clock::now()) {}

    // returns the deltaTime (duration of the last Tick) and sets
    float updateTickTimer() {
        auto now = std::chrono::high_resolution_clock::now();
        tickDuration = std::chrono::duration<float>(now - lastTickTime).count();
        lastTickTime = now;
        return tickDuration;
    }


    float getTickDuration() const { return tickDuration; }

    void sleepIfNeeded() {
        if (tickDuration < tickDurationTarget) {
            std::this_thread::sleep_for(
                    std::chrono::duration<float>(tickDurationTarget - tickDuration));
        }
    }
};

#endif
