#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <string>

#include "client/Framework.h"
#include "client/FrameworkUI.h"

class LoadingScreen: public BaseScreen {
private:
    Function<bool> endFunction;

public:
    LoadingScreen(Camera& cam, ResourceManager& resource, bool& wasClosed,
                  Function<bool> endFunction, const string& text = "", bool lockerOnly = false);

    ~LoadingScreen();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;
};

#endif
