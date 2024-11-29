#ifndef MAP_BLOCK_GUI_H
#define MAP_BLOCK_GUI_H

#include <algorithm>
#include <string>
#include <vector>

#include "common/Transform.h"
#include "multimedia/2d/MapBlock2D.h"
#include "multimedia/Camera.h"
#include "multimedia/cache/SheetDataCache.h"

#include "GraphicUI.h"

using std::map;
using std::string;
using std::vector;
using namespace SDL2pp;  // NOLINT

class MapBlockGUI: public GraphicUI {
    MapBlockRenderData renderData;

public:
    MapBlockGUI(const string& imageFilename, const string& sheetDataFilename,
                const RectTransform& rectTransform, float tileSize, int layerOrder = 0);

    ~MapBlockGUI();

    void SetBorders(bool left, bool right, bool top, bool bottom);

    void Draw(Camera& cam) override;
};

#endif
