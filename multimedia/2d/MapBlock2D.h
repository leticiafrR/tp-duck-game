#ifndef MAP_BLOCK_2D_H
#define MAP_BLOCK_2D_H

#include <algorithm>
#include <string>
#include <vector>

#include "common/Transform.h"
#include "multimedia/Camera.h"
#include "multimedia/cache/SheetDataCache.h"

using std::map;
using std::string;
using std::vector;
using namespace SDL2pp;  // NOLINT

class MapBlock2D {
private:
    bool borderTop = false;
    bool borderBottom = false;
    bool borderLeft = false;
    bool borderRight = false;

    string imageFilename;
    Transform transform;
    float tileSize;
    map<string, vector<Rect>> mapBlockData;

public:
    MapBlock2D(const string& imageFilename, const string& sheetDataFilename,
               const Transform& transform, float tileSize);

    ~MapBlock2D();

    void SetTopBorder(bool value);
    void SetBottomBorder(bool value);
    void SetLeftBorder(bool value);
    void SetRightBorder(bool value);
    Transform& GetTransform();

    void SetBorders(bool left, bool right, bool top, bool bottom);

    void Draw(Camera& cam);
};

#endif
