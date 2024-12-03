#ifndef MAP_BLOCK_RENDER_DATA
#define MAP_BLOCK_RENDER_DATA

#include <string>
#include <unordered_map>
#include <vector>

#include "multimedia/resource/ResourceData.h"

using std::string;
using std::unordered_map;
using std::vector;

const float TILE_SIZE = 4;

const string TOP_RECTS = "top_rects";
const string CENTER_RECTS = "center_rects";
const string BOTTOM_RECTS = "bottom_rects";

class MapBlockRenderData {
private:
public:
    string tileFile;
    unordered_map<string, vector<Rect>>* tileRects;

    bool borderTop = false;
    bool borderBottom = false;
    bool borderLeft = false;
    bool borderRight = false;

    explicit MapBlockRenderData(MapThemeData& mapThemeData);

    ~MapBlockRenderData();

    void SetBorders(bool left, bool right, bool top, bool bottom);

    Rect GetTopLeftRect();
    Rect GetTopCenterRect();
    Rect GetTopRightRect();


    Rect GetCenterLeftRect();
    Rect GetCenterCenterRect();
    Rect GetCenterRightRect();

    Rect GetBottomLeftRect();
    Rect GetBottomCenterRect();
    Rect GetBottomRightRect();

    string GetTileFile();
};

#endif
