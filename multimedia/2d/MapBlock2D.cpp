#include "MapBlock2D.h"

#include "constants.h"

MapBlock2D::MapBlock2D(MapThemeData& mapThemeData, const Transform& transform):
        renderData(mapThemeData), transform(transform) {}

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

void MapBlock2D::DrawTop(Camera& cam, int hCount, int startXPos, int startYPos) {
    string tileSetFile = renderData.GetTileFile();

    cam.DrawTexture(tileSetFile, renderData.GetTopLeftRect(),
                    Transform(Vector2D(startXPos, startYPos), Vector2D(TILE_SIZE, TILE_SIZE)));

    for (int i = 1; i < hCount - 1; i++) {
        cam.DrawTexture(tileSetFile, renderData.GetTopCenterRect(),
                        Transform(Vector2D(startXPos + i * TILE_SIZE, startYPos),
                                  Vector2D(TILE_SIZE, TILE_SIZE)));
    }

    cam.DrawTexture(tileSetFile, renderData.GetTopRightRect(),
                    Transform(Vector2D(startXPos + (hCount - 1) * TILE_SIZE, startYPos),
                              Vector2D(TILE_SIZE, TILE_SIZE)));
}

void MapBlock2D::DrawCenter(Camera& cam, int hCount, int vCount, int startXPos, int startYPos) {

    string tileSetFile = renderData.GetTileFile();

    for (int j = 1; j < vCount - 1; j++) {
        cam.DrawTexture(tileSetFile, renderData.GetCenterLeftRect(),
                        Transform(Vector2D(startXPos, startYPos - j * TILE_SIZE),
                                  Vector2D(TILE_SIZE, TILE_SIZE)));

        for (int i = 1; i < hCount - 1; i++) {
            cam.DrawTexture(
                    tileSetFile, renderData.GetCenterCenterRect(),
                    Transform(Vector2D(startXPos + i * TILE_SIZE, startYPos - j * TILE_SIZE),
                              Vector2D(TILE_SIZE, TILE_SIZE)));
        }

        cam.DrawTexture(
                tileSetFile, renderData.GetCenterRightRect(),
                Transform(Vector2D(startXPos + (hCount - 1) * TILE_SIZE, startYPos - j * TILE_SIZE),
                          Vector2D(TILE_SIZE, TILE_SIZE)));
    }
}

void MapBlock2D::DrawBottom(Camera& cam, int hCount, int vCount, int startXPos, int startYPos) {

    string tileSetFile = renderData.GetTileFile();

    cam.DrawTexture(tileSetFile, renderData.GetBottomLeftRect(),
                    Transform(Vector2D(startXPos, startYPos - (vCount - 1) * TILE_SIZE),
                              Vector2D(TILE_SIZE, TILE_SIZE)));

    for (int i = 1; i < hCount - 1; i++) {
        cam.DrawTexture(
                tileSetFile, renderData.GetBottomCenterRect(),
                Transform(Vector2D(startXPos + i * TILE_SIZE, startYPos - (vCount - 1) * TILE_SIZE),
                          Vector2D(TILE_SIZE, TILE_SIZE)));
    }

    cam.DrawTexture(tileSetFile, renderData.GetBottomRightRect(),
                    Transform(Vector2D(startXPos + (hCount - 1) * TILE_SIZE,
                                       startYPos - (vCount - 1) * TILE_SIZE),
                              Vector2D(TILE_SIZE, TILE_SIZE)));
}

void MapBlock2D::Draw(Camera& cam) {
    int hCount = transform.GetSize().x / TILE_SIZE;
    int vCount = transform.GetSize().y / TILE_SIZE;

    float startXPos = transform.GetPos().x - (transform.GetSize().x / 2) + (TILE_SIZE / 2);
    float startYPos = transform.GetPos().y + (transform.GetSize().y / 2) - (TILE_SIZE / 2);

    DrawTop(cam, hCount, startXPos, startYPos);
    DrawCenter(cam, hCount, vCount, startXPos, startYPos);
    DrawBottom(cam, hCount, vCount, startXPos, startYPos);
}
