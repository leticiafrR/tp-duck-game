#include "MapBlockGUI.h"

MapBlockGUI::MapBlockGUI(MapThemeData& mapThemeData, const RectTransform& rectTransform,
                         float tileSize, int layerOrder):
        GraphicUI(rectTransform, ColorExtension::White(), layerOrder),
        renderData(mapThemeData),
        tileSize(tileSize) {}

MapBlockGUI::~MapBlockGUI() = default;

void MapBlockGUI::SetBorders(bool left, bool right, bool top, bool bottom) {
    renderData.SetBorders(left, right, top, bottom);
}

RectTransform MapBlockGUI::GetRelative(Vector2D pos) {
    return RectTransform(pos, Vector2D(tileSize, tileSize), rect.GetAnchor(), rect.GetPivot());
}

void MapBlockGUI::DrawTop(Camera& cam, int hCount, int startXPos, int startYPos) {
    string tileSetFile = renderData.GetTileFile();

    cam.DrawImageGUI(tileSetFile, GetRelative(Vector2D(startXPos, startYPos)),
                     renderData.GetTopLeftRect());

    for (int i = 1; i < hCount - 1; i++) {
        cam.DrawImageGUI(tileSetFile, GetRelative(Vector2D(startXPos + i * tileSize, startYPos)),
                         renderData.GetTopCenterRect());
    }

    cam.DrawImageGUI(tileSetFile,
                     GetRelative(Vector2D(startXPos + (hCount - 1) * tileSize, startYPos)),
                     renderData.GetTopRightRect());
}

void MapBlockGUI::DrawCenter(Camera& cam, int hCount, int vCount, int startXPos, int startYPos) {

    string tileSetFile = renderData.GetTileFile();

    for (int j = 1; j < vCount - 1; j++) {

        cam.DrawImageGUI(tileSetFile, GetRelative(Vector2D(startXPos, startYPos - j * tileSize)),
                         renderData.GetCenterLeftRect());

        for (int i = 1; i < hCount - 1; i++) {
            cam.DrawImageGUI(
                    tileSetFile,
                    GetRelative(Vector2D(startXPos + i * tileSize, startYPos - j * tileSize)),
                    renderData.GetCenterCenterRect());
        }

        cam.DrawImageGUI(tileSetFile,
                         GetRelative(Vector2D(startXPos + (hCount - 1) * tileSize,
                                              startYPos - j * tileSize)),
                         renderData.GetCenterRightRect());
    }
}

void MapBlockGUI::DrawBottom(Camera& cam, int hCount, int vCount, int startXPos, int startYPos) {

    string tileSetFile = renderData.GetTileFile();

    cam.DrawImageGUI(tileSetFile,
                     GetRelative(Vector2D(startXPos, startYPos - (vCount - 1) * tileSize)),
                     renderData.GetBottomLeftRect());

    for (int i = 1; i < hCount - 1; i++) {
        cam.DrawImageGUI(tileSetFile,
                         GetRelative(Vector2D(startXPos + i * tileSize,
                                              startYPos - (vCount - 1) * tileSize)),
                         renderData.GetBottomCenterRect());
    }

    cam.DrawImageGUI(tileSetFile,
                     GetRelative(Vector2D(startXPos + (hCount - 1) * tileSize,
                                          startYPos - (vCount - 1) * tileSize)),
                     renderData.GetBottomRightRect());
}

void MapBlockGUI::Draw(Camera& cam) {

    int hCount = GetSize().x / tileSize;
    int vCount = GetSize().y / tileSize;

    float startXPos = GetPos().x - (GetSize().x / 2) + (tileSize / 2);
    float startYPos = GetPos().y + (GetSize().y / 2) - (tileSize / 2);

    DrawTop(cam, hCount, startXPos, startYPos);
    DrawCenter(cam, hCount, vCount, startXPos, startYPos);
    DrawBottom(cam, hCount, vCount, startXPos, startYPos);

    // Top
    // cam.DrawImageGUI(renderData.imageFilename,
    //                  RectTransform(Vector2D(startXPos, startYPos),
    //                                Vector2D(renderData.tileSize, renderData.tileSize),
    //                                rect.GetAnchor(), rect.GetPivot()),
    //                  renderData.mapBlockData[renderData.borderTop ? "ground_top" :
    //                  "ground_center"]
    //                                         [renderData.borderLeft ? 0 : 1],
    //                  Color(255, 255, 255, 255), false);

    // for (int i = 1; i < n - 1; i++) {
    //     cam.DrawImageGUI(
    //             renderData.imageFilename,
    //             RectTransform(Vector2D(startXPos + i * renderData.tileSize, startYPos),
    //                           Vector2D(renderData.tileSize, renderData.tileSize),
    //                           rect.GetAnchor(), rect.GetPivot()),
    //             renderData.mapBlockData[renderData.borderTop ? "ground_top" :
    //             "ground_center"][1], Color(255, 255, 255, 255), false);
    // }

    // cam.DrawImageGUI(renderData.imageFilename,
    //                  RectTransform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
    //                  startYPos),
    //                                Vector2D(renderData.tileSize, renderData.tileSize),
    //                                rect.GetAnchor(), rect.GetPivot()),
    //                  renderData.mapBlockData[renderData.borderTop ? "ground_top" :
    //                  "ground_center"]
    //                                         [renderData.borderRight ? 2 : 1],
    //                  Color(255, 255, 255, 255), false);

    // Center
    // for (int j = 1; j < k - 1; j++) {
    //     cam.DrawImageGUI(renderData.imageFilename,
    //                      RectTransform(Vector2D(startXPos, startYPos - j * renderData.tileSize),
    //                                    Vector2D(renderData.tileSize, renderData.tileSize),
    //                                    rect.GetAnchor(), rect.GetPivot()),
    //                      renderData.mapBlockData["ground_center"][renderData.borderLeft ? 0 : 1],
    //                      Color(255, 255, 255, 255), false);

    //     for (int i = 1; i < n - 1; i++) {
    //         cam.DrawImageGUI(renderData.imageFilename,
    //                          RectTransform(Vector2D(startXPos + i * renderData.tileSize,
    //                                                 startYPos - j * renderData.tileSize),
    //                                        Vector2D(renderData.tileSize, renderData.tileSize),
    //                                        rect.GetAnchor(), rect.GetPivot()),
    //                          renderData.mapBlockData["ground_center"][1], Color(255, 255, 255,
    //                          255), false);
    //     }

    //     cam.DrawImageGUI(renderData.imageFilename,
    //                      RectTransform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
    //                                             startYPos - j * renderData.tileSize),
    //                                    Vector2D(renderData.tileSize, renderData.tileSize),
    //                                    rect.GetAnchor(), rect.GetPivot()),
    //                      renderData.mapBlockData["ground_center"][renderData.borderRight ? 2 :
    //                      1], Color(255, 255, 255, 255), false);
    // }

    // // Bottom
    // cam.DrawImageGUI(
    //         renderData.imageFilename,
    //         RectTransform(Vector2D(startXPos, startYPos - (k - 1) * renderData.tileSize),
    //                       Vector2D(renderData.tileSize, renderData.tileSize), rect.GetAnchor(),
    //                       rect.GetPivot()),
    //         renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" : "ground_center"]
    //                                [renderData.borderLeft ? 0 : 1],
    //         Color(255, 255, 255, 255), false);

    // for (int i = 1; i < n - 1; i++) {
    //     cam.DrawImageGUI(renderData.imageFilename,
    //                      RectTransform(Vector2D(startXPos + i * renderData.tileSize,
    //                                             startYPos - (k - 1) * renderData.tileSize),
    //                                    Vector2D(renderData.tileSize, renderData.tileSize),
    //                                    rect.GetAnchor(), rect.GetPivot()),
    //                      renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" :
    //                                                                        "ground_center"][1],
    //                      Color(255, 255, 255, 255), false);
    // }

    // cam.DrawImageGUI(
    //         renderData.imageFilename,
    //         RectTransform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
    //                                startYPos - (k - 1) * renderData.tileSize),
    //                       Vector2D(renderData.tileSize, renderData.tileSize), rect.GetAnchor(),
    //                       rect.GetPivot()),
    //         renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" : "ground_center"]
    //                                [renderData.borderRight ? 2 : 1],
    //         Color(255, 255, 255, 255), false);
}
