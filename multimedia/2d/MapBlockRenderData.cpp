
#include "MapBlockRenderData.h"

MapBlockRenderData::MapBlockRenderData(const string& imageFilename, const string& sheetDataFilename,
                                       float tileSize):
        imageFilename(imageFilename),
        tileSize(tileSize),
        mapBlockData(SheetDataCache::GetData(sheetDataFilename)) {}

MapBlockRenderData::~MapBlockRenderData() = default;

void MapBlockRenderData::SetBorders(bool left, bool right, bool top, bool bottom) {
    borderLeft = left;
    borderRight = right;
    borderTop = top;
    borderBottom = bottom;
}
