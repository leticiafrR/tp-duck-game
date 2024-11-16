#ifndef TIMER_H
#define TIMER_H

#include <functional>

using OnTimerCallback = std::function<void()>;

class Timer {
private:
    float duration;
    OnTimerCallback onTime;
    float timer;
    bool running;

public:
    Timer(): running(false), duration(0), timer(0) {}
    Timer(float duration, OnTimerCallback onTime):
            duration(duration), onTime(onTime), timer(duration), running(false) {}
    ~Timer() = default;

    void Start() { running = true; }

    void Stop() { running = false; }

    void Update(float deltaTime) {
        if (!running)
            return;
        timer -= deltaTime;
        if (timer <= 0) {
            onTime();
            running = false;
        }
    }
};

#endif
