#ifndef EDITORSCREEN_H
#define EDITORSCREEN_H

#include <list>
#include <set>
#include <string>
#include <vector>

#include "client/tweening/TransformTween.h"
#include "client/tweening/TweenManager.h"
#include "multimedia/Camera.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/KeyboardExtension.h"
#include "multimedia/audio/AudioManager.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/ButtonsManager.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "PlatformOptionWidget.h"
#include "mapEditor.h"
// se debe poder agregar una plataforma (obtiene tamanos y aristas), y escribe en la posicion que
// se indica

using std::vector;
class EditorScreen {
private:
    Camera& cam;
    MapEditor& writer;
    vector<PlatformOptionWidget> basicsPlatform;
    GroundDto loadPlatforms(const YAML::Node& config, const std::string& platformName);
    vector<GroundDto> ReadBasicPlataforms();
    bool running = true;
    Button saveButton;
    Text saveButtonText;
    vector<string> edgesSelected;

public:
    explicit EditorScreen(Camera& cam, MapEditor& writer);
    bool Render();
};
#endif
