#include "GameKit.h"

GameKit::GameKit(Camera& cam):
        cam(cam),
        guiManager(GUIManager::GetInstance()),
        tweenManager(TweenManager::GetInstance()) {}
GameKit::~GameKit() = default;

Camera& GameKit::GetCamera() { return cam; }

GUIManager& GameKit::GetGUIManager() { return guiManager; }

AudioManager& GameKit::GetAudioManager() { return audioManager; }

TweenManager& GameKit::GetTweenManager() { return tweenManager; }

ResourceManager& GameKit::GetResourceManager() { return resourceManager; }

void GameKit::PlayButtonSFX() { audioManager.PlaySFX(resourceManager.GetMenuData().buttonSfxFile); }
