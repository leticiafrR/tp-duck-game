#ifndef MAP_BLOCK_2D_H
#define MAP_BLOCK_2D_H

#include <algorithm>
#include <string>
#include <vector>

#include "common/Transform.h"
#include "data/gameScene.h"
#include "multimedia/Camera.h"
#include "multimedia/cache/SheetDataCache.h"

#include "MapBlockRenderData.h"

using std::map;
using std::string;
using std::vector;
using namespace SDL2pp;  // NOLINT

class MapBlock2D {
protected:
    Transform transform;
    MapBlockRenderData renderData;
    vector<string> edges;

public:
    MapBlock2D(const string& imageFilename, const string& sheetDataFilename,
               const Transform& transform, float tileSize);

    ~MapBlock2D();

    Transform& GetTransform();

    void SetBorders(bool left, bool right, bool top, bool bottom);

    vector<string> GetEdges();

    void Draw(Camera& cam);
};

#endif
