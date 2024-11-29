#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "client/Framework.h"

class BaseScreen {
protected:
    Camera& cam;
    bool wasClosed;
    bool running;

public:
    explicit BaseScreen(Camera& cam);
    virtual ~BaseScreen();

    bool WasClosed();

    virtual void InitRun() = 0;

    virtual void TakeInput(SDL_Event event) = 0;

    virtual void Update(float deltaTime) = 0;

    void Run();
};

#endif
