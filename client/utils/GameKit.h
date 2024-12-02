#ifndef GAME_KIT_H
#define GAME_KIT_H

#include "client/FrameworkUI.h"
#include "client/tweening/TweenManager.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/resource/ResourceManager.h"

class GameKit {
private:
    Camera& cam;
    GUIManager& guiManager;
    AudioManager audioManager;
    TweenManager& tweenManager;
    ResourceManager resourceManager;

public:
    explicit GameKit(Camera& cam);
    ~GameKit();

    Camera& GetCamera();
    GUIManager& GetGUIManager();
    AudioManager& GetAudioManager();
    TweenManager& GetTweenManager();
    ResourceManager& GetResourceManager();

    void PlayButtonSFX();
};

#endif
