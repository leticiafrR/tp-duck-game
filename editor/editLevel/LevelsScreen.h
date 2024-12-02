#ifndef LEVELSSCREEN_H
#define LEVELSSCREEN_H
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "editor/constantsEditor.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "LevelWidget.h"
#include "constants.h"

using std::list;
using std::string;

class LevelsScreen {
private:
    Camera& cam;
    list<LevelWidget> widgets;

    string selectedLvl;
    bool running = true;
    float currentY = 0;
    float scrollSize = 0;
    void ReadAvaiableLevels();

public:
    explicit LevelsScreen(Camera& cam);
    void UpdateWidgetListPosition(Vector2D movement);
    string Render(bool lockerOnly = false);
    ~LevelsScreen();
};

#endif
