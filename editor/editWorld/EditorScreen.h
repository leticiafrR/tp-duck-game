#ifndef EDITORSCREEN_H
#define EDITORSCREEN_H

#include <list>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "client/tweening/TransformTween.h"
#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/KeyboardExtension.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"
#include "multimedia/resource/ResourceManager.h"

#include "PlatformOptionWidget.h"
#include "SpawnPointWidget.h"
#include "mapEditor.h"

using std::list;
using std::optional;
using std::vector;

class EditorScreen: public BaseScreen {
private:
    MapEditor& writer;
    list<PlatformOptionWidget> basicsPlatform;
    GroundDto loadPlatforms(const YAML::Node& config, const std::string& platformName);
    vector<GroundDto> ReadBasicPlataforms();
    Button* saveButton;
    Text* saveButtonText;
    Object2D mapBg;
    vector<MapBlock2D> mapBlocks;
    vector<Object2D> boxes;
    optional<MapBlock2D> selected;
    optional<Object2D> spawnPoint;
    optional<int> typeSpawnPoint;
    SpawnPointWidget playersPoint;
    SpawnPointWidget collectablesPoint;
    SpawnPointWidget boxPoint;
    void UpdateWidgetListPosition(Vector2D movement);
    float currentY = 0;
    float scrollSize = 0;


    void DrawGameWorld();
    void DrawOptions();
    void InitMap(GameSceneDto mapData);
    void TakeInput();
    void HandleMouseClick(const SDL_MouseButtonEvent& eventButton);
    void TakeAPlatform();
    void UpdateWorld();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    explicit EditorScreen(Camera& cam, MapEditor& writer, ResourceManager& resourceManager,
                          bool& wasClosed);
    ~EditorScreen();
    bool Render();
};
#endif
