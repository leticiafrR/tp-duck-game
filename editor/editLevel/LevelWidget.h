#ifndef LEVEL_WIDGET_H
#define LEVEL_WIDGET_H
#include <string>

#include "editor/constantsEditor.h"
#include "multimedia/ColorExtension.h"
#include "multimedia/Definitions.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"
using std::string;

class LevelWidget {
private:
public:
    string levelName;
    Image lvlConentImage;
    Text lvlNameText;
    Button selectLevelButton;
    Text selectLevelText;
    CallbackParam<string> onSelectClicked;

    explicit LevelWidget(const string& ownerName, CallbackParam<string> onSelect);

    ~LevelWidget() = default;

    void MoveContent(Vector2D movement);
};

#endif
