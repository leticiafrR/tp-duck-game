#ifndef THEME_WIDGET_H
#define THEME_WIDGET_H
#include <string>

#include "editor/constantsEditor.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/GUIManager.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"
using std::string;

class ThemeWidget {
private:
public:
    string levelName;
    Image* lvlConentImage;
    Text* lvlNameText;
    Button* selectThemeButton;
    Text* selectThemeText;
    CallbackParam<string> onSelectClicked;

    explicit ThemeWidget(GUIManager& guiManager, const string& ownerName,
                         CallbackParam<string> onSelect);

    ~ThemeWidget() = default;

    void MoveContent(Vector2D movement);
};

#endif
