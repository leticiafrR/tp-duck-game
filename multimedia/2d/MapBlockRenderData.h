#ifndef MAP_BLOCK_RENDER_DATA
#define MAP_BLOCK_RENDER_DATA

#include <map>
#include <string>
#include <vector>

#include "multimedia/cache/SheetDataCache.h"

using std::map;
using std::string;
using std::vector;

class MapBlockRenderData {
private:
public:
    string imageFilename;
    float tileSize;

    bool borderTop = false;
    bool borderBottom = false;
    bool borderLeft = false;
    bool borderRight = false;

    map<string, vector<Rect>> mapBlockData;

    MapBlockRenderData(const string& imageFilename, const string& sheetDataFilename,
                       float tileSize);

    ~MapBlockRenderData();

    void SetBorders(bool left, bool right, bool top, bool bottom);
};

#endif
