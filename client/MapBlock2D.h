#ifndef MAP_BLOCK_2D_H
#define MAP_BLOCK_2D_H

#include <algorithm>
#include <string>
#include <vector>

#include "common/Transform.h"

#include "Camera.h"
#include "SheetDataCache.h"

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

public:
    string imageFilename;
    Transform transform;
    float tileSize;
    map<string, vector<Rect>> mapBlockData;
    MapBlock2D(const string& imageFilename, const string& sheetDataFilename,
               const Transform& transform, float tileSize):
            imageFilename(imageFilename),
            transform(transform),
            tileSize(tileSize),
            mapBlockData(SheetDataParser::GetData(sheetDataFilename)) {}

    void SetTopBorder(bool value) { borderTop = value; }
    void SetBottomBorder(bool value) { borderBottom = value; }
    void SetLeftBorder(bool value) { borderLeft = value; }
    void SetRightBorder(bool value) { borderRight = value; }

    void SetBorders(bool left, bool right, bool top, bool bottom) {
        borderLeft = left;
        borderRight = right;
        borderTop = top;
        borderBottom = bottom;
    }

    void Draw(Camera& cam) {

        int n = transform.GetSize().x / tileSize;
        int k = transform.GetSize().y / tileSize;

        float startXPos = transform.GetPos().x - (transform.GetSize().x / 2) + (tileSize / 2);
        float startYPos = transform.GetPos().y + (transform.GetSize().y / 2) - (tileSize / 2);

        // Top
        cam.DrawTexture(
                imageFilename,
                mapBlockData[borderTop ? "ground_top" : "ground_center"][borderLeft ? 0 : 1],
                Color(255, 255, 255, 255),
                Transform(Vector2D(startXPos, startYPos), Vector2D(tileSize, tileSize)),
                SDL_FLIP_NONE);

        for (int i = 1; i < n - 1; i++) {
            cam.DrawTexture(imageFilename,
                            mapBlockData[borderTop ? "ground_top" : "ground_center"][1],
                            Color(255, 255, 255, 255),
                            Transform(Vector2D(startXPos + i * tileSize, startYPos),
                                      Vector2D(tileSize, tileSize)),
                            SDL_FLIP_NONE);
        }

        cam.DrawTexture(
                imageFilename,
                mapBlockData[borderTop ? "ground_top" : "ground_center"][borderRight ? 2 : 1],
                Color(255, 255, 255, 255),
                Transform(Vector2D(startXPos + (n - 1) * tileSize, startYPos),
                          Vector2D(tileSize, tileSize)),
                SDL_FLIP_NONE);

        // Center
        for (int j = 1; j < k - 1; j++) {
            cam.DrawTexture(imageFilename, mapBlockData["ground_center"][borderLeft ? 0 : 1],
                            Color(255, 255, 255, 255),
                            Transform(Vector2D(startXPos, startYPos - j * tileSize),
                                      Vector2D(tileSize, tileSize)),
                            SDL_FLIP_NONE);

            for (int i = 1; i < n - 1; i++) {
                cam.DrawTexture(
                        imageFilename, mapBlockData["ground_center"][1], Color(255, 255, 255, 255),
                        Transform(Vector2D(startXPos + i * tileSize, startYPos - j * tileSize),
                                  Vector2D(tileSize, tileSize)),
                        SDL_FLIP_NONE);
            }

            cam.DrawTexture(
                    imageFilename, mapBlockData["ground_center"][borderRight ? 2 : 1],
                    Color(255, 255, 255, 255),
                    Transform(Vector2D(startXPos + (n - 1) * tileSize, startYPos - j * tileSize),
                              Vector2D(tileSize, tileSize)),
                    SDL_FLIP_NONE);
        }

        // Bottom
        cam.DrawTexture(
                imageFilename,
                mapBlockData[borderBottom ? "ground_bottom" : "ground_center"][borderLeft ? 0 : 1],
                Color(255, 255, 255, 255),
                Transform(Vector2D(startXPos, startYPos - (k - 1) * tileSize),
                          Vector2D(tileSize, tileSize)),
                SDL_FLIP_NONE);

        for (int i = 1; i < n - 1; i++) {
            cam.DrawTexture(
                    imageFilename,
                    mapBlockData[borderBottom ? "ground_bottom" : "ground_center"][1],
                    Color(255, 255, 255, 255),
                    Transform(Vector2D(startXPos + i * tileSize, startYPos - (k - 1) * tileSize),
                              Vector2D(tileSize, tileSize)),
                    SDL_FLIP_NONE);
        }

        cam.DrawTexture(
                imageFilename,
                mapBlockData[borderBottom ? "ground_bottom" : "ground_center"][borderRight ? 2 : 1],
                Color(255, 255, 255, 255),
                Transform(Vector2D(startXPos + (n - 1) * tileSize, startYPos - (k - 1) * tileSize),
                          Vector2D(tileSize, tileSize)),
                SDL_FLIP_NONE);
    }

    ~MapBlock2D() = default;
};

#endif
