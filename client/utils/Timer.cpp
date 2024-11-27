#include "Timer.h"

Timer::Timer(): duration(0), timer(0), running(false) {}

Timer::Timer(float duration, Callback onTime):
        duration(duration), onTime(onTime), timer(duration), running(false) {}

Timer::~Timer() = default;

void Timer::Start() { running = true; }

void Timer::Stop() { running = false; }

void Timer::Update(float deltaTime) {
    if (!running)
        return;
    timer -= deltaTime;
    if (timer <= 0) {
        onTime();
        running = false;
    }
}
