#ifndef SPAWNPOINTNWIDGET_H
#define SPAWNPOINTWIDGET_H
#include <string>
#include <utility>
#include <vector>

#include "data/gameScene.h"
#include "multimedia/2d/Object2D.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/MapBlockGUI.h"
#include "multimedia/gui/Text.h"

#include "constantsEditor.h"
using std::pair;
using std::string;
using std::vector;
class SpawnPointWidget {
private:
public:
    Button btn;
    Text selectLevelText;
    CallbackParam<pair<Object2D, int>> onSelectClicked;
    Image img;
    Object2D point;

    int type;

    SpawnPointWidget();

    explicit SpawnPointWidget(CallbackParam<pair<Object2D, int>> onSelect, int type,
                              const std::string& fileName, Vector2D position,
                              const std::string& text, Vector2D size);

    ~SpawnPointWidget() = default;
    void MoveContent(Vector2D movement);
    void Draw(Camera& cam);
};
#endif
