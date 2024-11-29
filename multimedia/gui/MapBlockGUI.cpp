#include "MapBlockGUI.h"

MapBlockGUI::MapBlockGUI(const string& imageFilename, const string& sheetDataFilename,
                         const RectTransform& rectTransform, float tileSize, int layerOrder):
        GraphicUI(rectTransform, ColorExtension::White(), layerOrder),
        renderData(imageFilename, sheetDataFilename, tileSize) {}

MapBlockGUI::~MapBlockGUI() = default;

void MapBlockGUI::SetBorders(bool left, bool right, bool top, bool bottom) {
    renderData.SetBorders(left, right, top, bottom);
}

void MapBlockGUI::Draw(Camera& cam) {

    int n = GetSize().x / renderData.tileSize;
    int k = GetSize().y / renderData.tileSize;

    float startXPos = GetPos().x - (GetSize().x / 2) + (renderData.tileSize / 2);
    float startYPos = GetPos().y + (GetSize().y / 2) - (renderData.tileSize / 2);

    // Top
    cam.DrawImageGUI(renderData.imageFilename,
                     RectTransform(Vector2D(startXPos, startYPos),
                                   Vector2D(renderData.tileSize, renderData.tileSize),
                                   rect.GetAnchor(), rect.GetPivot()),
                     renderData.mapBlockData[renderData.borderTop ? "ground_top" : "ground_center"]
                                            [renderData.borderLeft ? 0 : 1],
                     Color(255, 255, 255, 255), false);

    for (int i = 1; i < n - 1; i++) {
        cam.DrawImageGUI(
                renderData.imageFilename,
                RectTransform(Vector2D(startXPos + i * renderData.tileSize, startYPos),
                              Vector2D(renderData.tileSize, renderData.tileSize), rect.GetAnchor(),
                              rect.GetPivot()),
                renderData.mapBlockData[renderData.borderTop ? "ground_top" : "ground_center"][1],
                Color(255, 255, 255, 255), false);
    }

    cam.DrawImageGUI(renderData.imageFilename,
                     RectTransform(Vector2D(startXPos + (n - 1) * renderData.tileSize, startYPos),
                                   Vector2D(renderData.tileSize, renderData.tileSize),
                                   rect.GetAnchor(), rect.GetPivot()),
                     renderData.mapBlockData[renderData.borderTop ? "ground_top" : "ground_center"]
                                            [renderData.borderRight ? 2 : 1],
                     Color(255, 255, 255, 255), false);

    // Center
    for (int j = 1; j < k - 1; j++) {
        cam.DrawImageGUI(renderData.imageFilename,
                         RectTransform(Vector2D(startXPos, startYPos - j * renderData.tileSize),
                                       Vector2D(renderData.tileSize, renderData.tileSize),
                                       rect.GetAnchor(), rect.GetPivot()),
                         renderData.mapBlockData["ground_center"][renderData.borderLeft ? 0 : 1],
                         Color(255, 255, 255, 255), false);

        for (int i = 1; i < n - 1; i++) {
            cam.DrawImageGUI(renderData.imageFilename,
                             RectTransform(Vector2D(startXPos + i * renderData.tileSize,
                                                    startYPos - j * renderData.tileSize),
                                           Vector2D(renderData.tileSize, renderData.tileSize),
                                           rect.GetAnchor(), rect.GetPivot()),
                             renderData.mapBlockData["ground_center"][1], Color(255, 255, 255, 255),
                             false);
        }

        cam.DrawImageGUI(renderData.imageFilename,
                         RectTransform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
                                                startYPos - j * renderData.tileSize),
                                       Vector2D(renderData.tileSize, renderData.tileSize),
                                       rect.GetAnchor(), rect.GetPivot()),
                         renderData.mapBlockData["ground_center"][renderData.borderRight ? 2 : 1],
                         Color(255, 255, 255, 255), false);
    }

    // Bottom
    cam.DrawImageGUI(
            renderData.imageFilename,
            RectTransform(Vector2D(startXPos, startYPos - (k - 1) * renderData.tileSize),
                          Vector2D(renderData.tileSize, renderData.tileSize), rect.GetAnchor(),
                          rect.GetPivot()),
            renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" : "ground_center"]
                                   [renderData.borderLeft ? 0 : 1],
            Color(255, 255, 255, 255), false);

    for (int i = 1; i < n - 1; i++) {
        cam.DrawImageGUI(renderData.imageFilename,
                         RectTransform(Vector2D(startXPos + i * renderData.tileSize,
                                                startYPos - (k - 1) * renderData.tileSize),
                                       Vector2D(renderData.tileSize, renderData.tileSize),
                                       rect.GetAnchor(), rect.GetPivot()),
                         renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" :
                                                                           "ground_center"][1],
                         Color(255, 255, 255, 255), false);
    }

    cam.DrawImageGUI(
            renderData.imageFilename,
            RectTransform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
                                   startYPos - (k - 1) * renderData.tileSize),
                          Vector2D(renderData.tileSize, renderData.tileSize), rect.GetAnchor(),
                          rect.GetPivot()),
            renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" : "ground_center"]
                                   [renderData.borderRight ? 2 : 1],
            Color(255, 255, 255, 255), false);
}
