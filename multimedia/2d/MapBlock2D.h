#ifndef MAP_BLOCK_2D_H
#define MAP_BLOCK_2D_H

#include <algorithm>
#include <string>
#include <vector>

#include "common/Transform.h"
#include "data/gameScene.h"
#include "multimedia/Camera.h"
#include "multimedia/resource/ResourceData.h"

#include "MapBlockRenderData.h"

using std::map;
using std::string;
using std::vector;
using namespace SDL2pp;  // NOLINT

class MapBlock2D {
protected:
    MapBlockRenderData renderData;
    Transform transform;
    vector<string> edges;

    void DrawTop(Camera& cam, int hCount, int startXPos, int startYPos);
    void DrawCenter(Camera& cam, int hCount, int vCount, int startXPos, int startYPos);
    void DrawBottom(Camera& cam, int hCount, int vCount, int startXPos, int startYPos);

public:
    MapBlock2D(MapThemeData& mapThemeData, const Transform& transform);

    ~MapBlock2D();

    Transform& GetTransform();

    void SetBorders(bool left, bool right, bool top, bool bottom);

    vector<string> GetEdges();

    void Draw(Camera& cam);
};

#endif
