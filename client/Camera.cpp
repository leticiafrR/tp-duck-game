#include "Camera.h"

Camera::Camera(Renderer render, float size):
        render(std::move(render)), textureCache(this->render), size(size) {}

void Camera::DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
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


void Camera::DrawGUI(Rect rect, Color color) {
    Color tmpColor = render.GetDrawColor();
    render.SetDrawColor(color);
    render.FillRect(rect);
    render.SetDrawColor(tmpColor);  // Restore color
}

void Camera::DrawText(const string& text, SDL2pp::Font& font, SDL2pp::Point point, Color color) {
    Texture text_sprite(render, font.RenderText_Blended(text, color));

    render.Copy(text_sprite, SDL2pp::NullOpt,
                Rect(point.x, point.y, text_sprite.GetWidth(), text_sprite.GetHeight()));
}


void Camera::Render() { render.Present(); }

Camera::~Camera() {}
