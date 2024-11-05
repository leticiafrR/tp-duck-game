#ifndef CAMERA_H
#define CAMERA_H

#include <algorithm>
#include <list>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "common/Vector2D.h"

#include "TextureCache.h"

using SDL2pp::Color;
using SDL2pp::Rect;
using SDL2pp::Renderer;
using SDL2pp::Texture;
using std::string;

class Camera {
private:
    Renderer render;
    TextureCache textureCache;
    Vector2D position;

    float size;

public:
    Camera(Renderer render, float size);
    void Clean() { render.Clear(); }
    void Render();
    void SetPos(Vector2D position) { this->position = position; }
    Vector2D GetPos() { return position; }
    void SetSize(float size) { this->size = size; }
    float GetSize() { return this->size; }
    ~Camera();

    void DrawTexture(string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
                     const Transform& transform, int flip);
};

Camera::Camera(Renderer render, float size):
        render(std::move(render)), textureCache(this->render), size(size) {}

void Camera::DrawTexture(string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
                         const Transform& transform, int flip) {
    Vector2D sprSize = transform.GetSize();
    float angle = transform.GetAngle();

    int screenWidth = render.GetOutputWidth();
    int screenHeight = render.GetOutputHeight();

    // float screenScale = Vector2D(screenWidth, screenHeight).GetMagnitude() / size;

    // Mantiene completamente la relación de aspecto
    float screenScale = std::min(static_cast<float>(screenWidth) / size,
                                 static_cast<float>(screenHeight) / size);

    int screenX = (screenWidth / 2) + (transform.GetPos().x - position.x) * screenScale;
    int screenY = (screenHeight / 2) - (transform.GetPos().y - position.y) * screenScale;

    Texture& tex = textureCache.GetTexture(filename);

    tex.SetColorAndAlphaMod(color);
    render.Copy(textureCache.GetTexture(filename), sourceRect,
                Rect(screenX - ((sprSize.x) * screenScale) / 2,
                     screenY - ((sprSize.y) * screenScale) / 2,
                     ((sprSize.x) * screenScale) + 1,  // +1 to avoid lost of pixels
                     ((sprSize.y) * screenScale) + 1),
                angle, SDL2pp::NullOpt, flip);
    tex.SetColorAndAlphaMod(Color(255, 255, 255, 255));  // Return texture color to normal
}


void Camera::Render() { render.Present(); }

Camera::~Camera() {}

#endif
