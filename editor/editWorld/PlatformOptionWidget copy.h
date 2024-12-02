#ifndef PLATFORMOPTIONWIDGET_H
#define PLATFORMOPTIONWIDGET_H
#include <string>
#include <vector>

#include "data/gameScene.h"
#include "editor/constantsEditor.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/MapBlockGUI.h"
#include "multimedia/gui/Text.h"
#include "multimedia/resource/ResourceData.h"

using std::string;
using std::vector;
class PlatformOptionWidget {
private:
public:
    Button btn;
    MapBlockGUI obj;
    Text selectLevelText;
    CallbackParam<MapBlock2D> onSelectClicked;
    MapBlock2D gameBlock;

    PlatformOptionWidget();

    explicit PlatformOptionWidget(MapThemeData& mapThemeData, GroundDto& info,
                                  CallbackParam<MapBlock2D> onSelect);

    ~PlatformOptionWidget() = default;
    void DrawOption(Camera& cam);
    void MoveContent(Vector2D movement);
};
#endif
