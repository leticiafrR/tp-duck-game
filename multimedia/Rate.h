#ifndef RATE_H
#define RATE_H

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

class Rate {
private:
    int target;

    int lastTick;

    float deltaTime;

    float GetTargetDeltaTime() const;
    int GetTargetMiliseconds() const;

public:
    explicit Rate(int target);
    ~Rate();

    void Init();

    float GetDeltaTime() const;

    void Delay();
};

#endif
