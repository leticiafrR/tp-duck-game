#ifndef LEVELSSCREEN_H
#define LEVELSSCREEN_H
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "multimedia/Button.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Text.h"

#include "LevelWidget.h"
#include "constants.h"
#include "constantsEditor.h"

using std::list;


class LevelsScreen {
private:
    Camera& cam;
    list<LevelWidget> widgets;

    void OnSelectLevelPressed(const std::string& name);

    void ReadAvaiableLevels();

public:
    explicit LevelsScreen(Camera& cam);

    std::string Render(const string& text = "", bool lockerOnly = false);
};

#endif
