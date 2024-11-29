#ifndef PLATFORMOPTIONWIDGET_H
#define PLATFORMOPTIONWIDGET_H
#include <string>
#include <vector>

#include "data/gameScene.h"
#include "multimedia/2d/MapBlock2D.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Text.h"

#include "constantsEditor.h"
using std::string;
using std::vector;
class PlatformOptionWidget {
private:
public:
    MapBlock2D obj;
    Button btn;
    vector<string> edges;
    Text selectLevelText;
    CallbackParam<vector<string>> onSelectClicked;

    PlatformOptionWidget();

    explicit PlatformOptionWidget(GroundDto& info, CallbackParam<vector<string>> onSelect);

    ~PlatformOptionWidget() = default;
    void DrawOption(Camera& cam);
    void MoveContent(Vector2D movement, Vector2D movObj);
};
#endif
