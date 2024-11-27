#ifndef TIMER_H
#define TIMER_H

#include <functional>

#include "multimedia/Definitions.h"

class Timer {
private:
    float duration;
    Callback onTime;
    float timer;
    bool running;

public:
    Timer();

    Timer(float duration, Callback onTime);

    ~Timer();

    void Start();

    void Stop();

    void Update(float deltaTime);
};

#endif
