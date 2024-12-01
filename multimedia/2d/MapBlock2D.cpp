#include "MapBlock2D.h"

#include "constants.h"
MapBlock2D::MapBlock2D(const string& imageFilename, const string& sheetDataFilename,
                       const Transform& transform, float tileSize):
        transform(transform), renderData(imageFilename, sheetDataFilename, tileSize) {}

MapBlock2D::~MapBlock2D() = default;

void MapBlock2D::SetBorders(bool left, bool right, bool top, bool bottom) {
    renderData.SetBorders(left, right, top, bottom);
    vector<string> newEdges;
    if (left) {
        newEdges.emplace_back(LEFT_STR);
    }

    if (right) {
        newEdges.emplace_back(RIGHT_STR);
    }

    if (top) {
        newEdges.emplace_back(TOP_STR);
    }

    if (bottom) {
        newEdges.emplace_back(BOTTOM_STR);
    }
    edges = newEdges;
}

vector<string> MapBlock2D::GetEdges() { return edges; }

Transform& MapBlock2D::GetTransform() { return transform; }

void MapBlock2D::Draw(Camera& cam) {

    int n = transform.GetSize().x / renderData.tileSize;
    int k = transform.GetSize().y / renderData.tileSize;

    float startXPos =
            transform.GetPos().x - (transform.GetSize().x / 2) + (renderData.tileSize / 2);
    float startYPos =
            transform.GetPos().y + (transform.GetSize().y / 2) - (renderData.tileSize / 2);

    // Top
    cam.DrawTexture(renderData.imageFilename,
                    renderData.mapBlockData[renderData.borderTop ? "ground_top" : "ground_center"]
                                           [renderData.borderLeft ? 0 : 1],
                    Color(255, 255, 255, 255),
                    Transform(Vector2D(startXPos, startYPos),
                              Vector2D(renderData.tileSize, renderData.tileSize)),
                    SDL_FLIP_NONE);

    for (int i = 1; i < n - 1; i++) {
        cam.DrawTexture(
                renderData.imageFilename,
                renderData.mapBlockData[renderData.borderTop ? "ground_top" : "ground_center"][1],
                Color(255, 255, 255, 255),
                Transform(Vector2D(startXPos + i * renderData.tileSize, startYPos),
                          Vector2D(renderData.tileSize, renderData.tileSize)),
                SDL_FLIP_NONE);
    }

    cam.DrawTexture(renderData.imageFilename,
                    renderData.mapBlockData[renderData.borderTop ? "ground_top" : "ground_center"]
                                           [renderData.borderRight ? 2 : 1],
                    Color(255, 255, 255, 255),
                    Transform(Vector2D(startXPos + (n - 1) * renderData.tileSize, startYPos),
                              Vector2D(renderData.tileSize, renderData.tileSize)),
                    SDL_FLIP_NONE);

    // Center
    for (int j = 1; j < k - 1; j++) {
        cam.DrawTexture(renderData.imageFilename,
                        renderData.mapBlockData["ground_center"][renderData.borderLeft ? 0 : 1],
                        Color(255, 255, 255, 255),
                        Transform(Vector2D(startXPos, startYPos - j * renderData.tileSize),
                                  Vector2D(renderData.tileSize, renderData.tileSize)),
                        SDL_FLIP_NONE);

        for (int i = 1; i < n - 1; i++) {
            cam.DrawTexture(renderData.imageFilename, renderData.mapBlockData["ground_center"][1],
                            Color(255, 255, 255, 255),
                            Transform(Vector2D(startXPos + i * renderData.tileSize,
                                               startYPos - j * renderData.tileSize),
                                      Vector2D(renderData.tileSize, renderData.tileSize)),
                            SDL_FLIP_NONE);
        }

        cam.DrawTexture(renderData.imageFilename,
                        renderData.mapBlockData["ground_center"][renderData.borderRight ? 2 : 1],
                        Color(255, 255, 255, 255),
                        Transform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
                                           startYPos - j * renderData.tileSize),
                                  Vector2D(renderData.tileSize, renderData.tileSize)),
                        SDL_FLIP_NONE);
    }

    // Bottom
    cam.DrawTexture(
            renderData.imageFilename,
            renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" : "ground_center"]
                                   [renderData.borderLeft ? 0 : 1],
            Color(255, 255, 255, 255),
            Transform(Vector2D(startXPos, startYPos - (k - 1) * renderData.tileSize),
                      Vector2D(renderData.tileSize, renderData.tileSize)),
            SDL_FLIP_NONE);

    for (int i = 1; i < n - 1; i++) {
        cam.DrawTexture(renderData.imageFilename,
                        renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" :
                                                                          "ground_center"][1],
                        Color(255, 255, 255, 255),
                        Transform(Vector2D(startXPos + i * renderData.tileSize,
                                           startYPos - (k - 1) * renderData.tileSize),
                                  Vector2D(renderData.tileSize, renderData.tileSize)),
                        SDL_FLIP_NONE);
    }

    cam.DrawTexture(
            renderData.imageFilename,
            renderData.mapBlockData[renderData.borderBottom ? "ground_bottom" : "ground_center"]
                                   [renderData.borderRight ? 2 : 1],
            Color(255, 255, 255, 255),
            Transform(Vector2D(startXPos + (n - 1) * renderData.tileSize,
                               startYPos - (k - 1) * renderData.tileSize),
                      Vector2D(renderData.tileSize, renderData.tileSize)),
            SDL_FLIP_NONE);
}
