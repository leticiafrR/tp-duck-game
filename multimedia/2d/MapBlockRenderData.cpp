
#include "MapBlockRenderData.h"

MapBlockRenderData::MapBlockRenderData(MapThemeData& mapThemeData):
        tileFile(mapThemeData.tileSetFile), tileRects(&mapThemeData.tileRects) {}

MapBlockRenderData::~MapBlockRenderData() = default;

void MapBlockRenderData::SetBorders(bool left, bool right, bool top, bool bottom) {
    borderLeft = left;
    borderRight = right;
    borderTop = top;
    borderBottom = bottom;
}

string MapBlockRenderData::GetTileFile() { return tileFile; }

// Top
Rect MapBlockRenderData::GetTopLeftRect() {
    return (*tileRects)[borderTop ? TOP_RECTS : CENTER_RECTS][borderLeft ? 0 : 1];
}

Rect MapBlockRenderData::GetTopCenterRect() {
    return (*tileRects)[borderTop ? TOP_RECTS : CENTER_RECTS][1];
}

Rect MapBlockRenderData::GetTopRightRect() {
    return (*tileRects)[borderTop ? TOP_RECTS : CENTER_RECTS][borderRight ? 2 : 1];
}

// Center
Rect MapBlockRenderData::GetCenterLeftRect() {
    return (*tileRects)[CENTER_RECTS][borderLeft ? 0 : 1];
}

Rect MapBlockRenderData::GetCenterCenterRect() { return (*tileRects)[CENTER_RECTS][1]; }

Rect MapBlockRenderData::GetCenterRightRect() {
    return (*tileRects)[CENTER_RECTS][borderRight ? 2 : 1];
}

// Bottom
Rect MapBlockRenderData::GetBottomLeftRect() {
    return (*tileRects)[borderBottom ? BOTTOM_RECTS : CENTER_RECTS][borderLeft ? 0 : 1];
}
Rect MapBlockRenderData::GetBottomCenterRect() {
    return (*tileRects)[borderBottom ? BOTTOM_RECTS : CENTER_RECTS][1];
}
Rect MapBlockRenderData::GetBottomRightRect() {
    return (*tileRects)[borderBottom ? BOTTOM_RECTS : CENTER_RECTS][borderRight ? 2 : 1];
}
