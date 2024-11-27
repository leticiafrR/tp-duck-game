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

    // string OnSelectLevelPressed(const std::string& name);
    string selectedLvl;
    bool running = true;
    void ReadAvaiableLevels();

public:
    explicit LevelsScreen(Camera& cam);

    string Render(bool lockerOnly = false);
};

#endif
