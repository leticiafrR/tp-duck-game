#include "Rate.h"

Rate::Rate(int target): target(target) { Init(); }
Rate::~Rate() = default;

int Rate::GetTargetMiliseconds() const { return 1000.0f / target; }
float Rate::GetTargetDeltaTime() const { return 1.0f / target; }

void Rate::Init() { lastTick = SDL_GetTicks(); }

float Rate::GetDeltaTime() const {
    std::cout << deltaTime << "\n";
    return deltaTime;
}

// Drop & rest
void Rate::Delay() {
    int now = SDL_GetTicks();
    int rate = GetTargetMiliseconds();
    int rest = rate - (now - lastTick);

    deltaTime = 0;

    if (rest < 0) {
        int behind = -rest;
        rest = rate - behind % rate;
        int lost = behind + rest;
        lastTick += lost;
        deltaTime += (lost / rate) * GetTargetDeltaTime();
    }

    SDL_Delay(rest);

    lastTick += rate;
    deltaTime += GetTargetDeltaTime();
}
