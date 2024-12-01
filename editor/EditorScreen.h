#ifndef EDITORSCREEN_H
#define EDITORSCREEN_H

#include <list>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "client/tweening/TransformTween.h"
#include "client/tweening/TweenManager.h"
#include "editWorld/GameWorld.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/KeyboardExtension.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "PlatformOptionWidget.h"
#include "SpawnPointWidget.h"
#include "mapEditor.h"
// se debe poder agregar una plataforma (obtiene aristas), y escribe en la posicion que
// se indica el boton del tablero

using std::list;
using std::optional;
using std::vector;
class EditorScreen {
private:
    Camera& cam;
    MapEditor& writer;
    list<PlatformOptionWidget> basicsPlatform;
    GroundDto loadPlatforms(const YAML::Node& config, const std::string& platformName);
    vector<GroundDto> ReadBasicPlataforms();
    bool running = true;
    Button saveButton;
    Text saveButtonText;
    Object2D mapBg;
    vector<MapBlock2D> mapBlocks;
    optional<MapBlock2D> selected;
    optional<Object2D> spawnPoint;
    optional<int> typeSpawnPoint;
    SpawnPointWidget playersPoint;
    SpawnPointWidget collectablesPoint;
    void UpdateWidgetListPosition(Vector2D movement);
    float currentY = 0;
    float scrollSize = 0;


    void DrawGameWorld();
    void DrawOptions();
    void InitMap(GameSceneDto mapData);
    void TakeInput();
    void HandleMouseClick(const SDL_MouseButtonEvent& eventButton);

public:
    explicit EditorScreen(Camera& cam, MapEditor& writer);
    ~EditorScreen() = default;
    bool Render();
};
#endif
