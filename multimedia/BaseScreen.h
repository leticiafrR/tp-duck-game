#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/GUIManager.h"

class BaseScreen {
protected:
    Camera& cam;
    ResourceManager& resource;

    GUIManager guiManager;
    AudioManager audioPlayer;

    bool& wasClosed;
    bool running;

public:
    explicit BaseScreen(Camera& cam, ResourceManager& resource, bool& wasClosed);
    virtual ~BaseScreen();

    virtual void InitRun() = 0;

    virtual void TakeInput(SDL_Event event) = 0;

    virtual void Update(float deltaTime) = 0;

    void Run();
};

#endif
