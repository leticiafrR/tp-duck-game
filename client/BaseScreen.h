#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "client/Framework.h"

class BaseScreen {
protected:
    GameKit& gameKit;
    Camera& cam;
    MenuData menuData;

    bool& wasClosed;
    bool running;

public:
    explicit BaseScreen(GameKit& gameKit, bool& wasClosed);
    virtual ~BaseScreen();

    virtual void InitRun() = 0;

    virtual void TakeInput(SDL_Event event) = 0;

    virtual void Update(float deltaTime) = 0;

    void Run();
};

#endif
