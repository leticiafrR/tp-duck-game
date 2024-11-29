#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "client/Framework.h"

class BaseScreen {
protected:
    Camera& cam;
    bool running;

public:
    explicit BaseScreen(Camera& cam);
    virtual ~BaseScreen();

    virtual void InitRun() = 0;

    virtual void TakeInput(SDL_Event event) = 0;

    virtual void Update(float deltaTime) = 0;

    void Run(bool& wasClosed);
};

#endif
