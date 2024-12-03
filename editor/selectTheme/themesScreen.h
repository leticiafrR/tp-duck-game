#ifndef THEMESSCREEN_H
#define THEMESSCREEN_H
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <yaml-cpp/yaml.h>

#include "editor/constantsEditor.h"
#include "multimedia/BaseScreen.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Text.h"

#include "constants.h"
#include "themeWidget.h"

using std::list;
using std::string;

class ThemesScreen: public BaseScreen {
private:
    list<ThemeWidget> widgets;

    string selectedTheme;
    float currentY = 0;
    float scrollSize = 0;
    void ReadAvaiableThemes();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    explicit ThemesScreen(Camera& cam, ResourceManager& resource, bool& wasClosed);
    void UpdateWidgetListPosition(Vector2D movement);
    string Render(bool lockerOnly = false);
    ~ThemesScreen();
};

#endif
