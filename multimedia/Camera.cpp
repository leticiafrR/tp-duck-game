#include "Camera.h"

#include "Rate.h"

Camera::Camera(Renderer render, float size, Rate rate):
        render(std::move(render)), textureCache(this->render), size(size), rate(rate) {}

Camera::~Camera() { textureCache.Clear(); }

void Camera::Clean() { render.Clear(); }
void Camera::Render() { render.Present(); }

void Camera::SetPos(Vector2D position) { this->position = position; }
Vector2D Camera::GetPos() { return position; }
void Camera::SetSize(float size) { this->size = size; }
float Camera::GetSize() { return this->size; }

void Camera::InitRate() { rate.Init(); }
void Camera::Delay() { rate.Delay(); }
float Camera::GetRateDeltatime() { return rate.GetDeltaTime(); }

void Camera::ClearCacheItem(const string& filename) { textureCache.ClearItem(filename); }

void Camera::DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect,
                         const Transform& transform, Color color, bool flip) {
    DrawTexture(filename, sourceRect, color, transform, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Camera::DrawTexture(const string& filename, SDL2pp::Optional<Rect> sourceRect, Color color,
                         const Transform& transform, int flip) {
    Vector2D sprSize = transform.GetSize();
    float angle = transform.GetAngle();

    int screenWidth = render.GetOutputWidth();
    int screenHeight = render.GetOutputHeight();

    // Keeps aspect ratio
    float screenScale = std::min(static_cast<float>(screenWidth) / size,
                                 static_cast<float>(screenHeight) / size);

    int screenX = (screenWidth / 2) + (transform.GetPos().x - position.x) * screenScale;
    int screenY = (screenHeight / 2) - (transform.GetPos().y - position.y) * screenScale;

    Texture& tex = textureCache.GetTexture(filename);

    tex.SetColorAndAlphaMod(color);
    render.Copy(tex, sourceRect,
                Rect(screenX - ((sprSize.x) * screenScale) / 2,
                     screenY - ((sprSize.y) * screenScale) / 2,
                     ((sprSize.x) * screenScale) + 1,  // +1 to avoid lost of pixels
                     ((sprSize.y) * screenScale) + 1),
                -angle, SDL2pp::NullOpt, flip);
    tex.SetColorAndAlphaMod(Color(255, 255, 255, 255));  // Return texture color to normal
}


void Camera::DrawGUI(RectTransform rect, Color color) {
    Color tmpColor = render.GetDrawColor();
    render.SetDrawColor(color);
    render.FillRect(RectTransformToRenderRect(rect));
    render.SetDrawColor(tmpColor);  // Restore color
}

void Camera::DrawImageGUI(const string& filename, RectTransform rect,
                          SDL2pp::Optional<Rect> srcRect, Color color, bool flip) {
    Texture& tex = textureCache.GetTexture(filename);
    tex.SetColorAndAlphaMod(color);
    render.Copy(tex, srcRect, RectTransformToRenderRect(rect), -rect.GetAngle(), SDL2pp::NullOpt,
                flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    tex.SetColorAndAlphaMod(Color(255, 255, 255, 255));  // Return texture color to normal
}

void Camera::DrawText(const string& text, const string& fontFile, int fontSize,
                      RectTransform rectTransform, Color color) {

    Font& font = fontCache.GetFontData(fontFile, fontSize);
    Texture fontTexture(render, font.RenderText_Blended(text, color));
    float textAspectRatio = static_cast<float>(fontTexture.GetWidth()) / fontTexture.GetHeight();

    Vector2D targetSize = Vector2D(fontTexture.GetWidth(), fontTexture.GetHeight());

    if (targetSize.x > rectTransform.GetSize().x) {
        targetSize.x = rectTransform.GetSize().x;
        targetSize.y = static_cast<int>(rectTransform.GetSize().x / textAspectRatio);
    }

    if (targetSize.y > rectTransform.GetSize().y) {
        targetSize.y = rectTransform.GetSize().y;
        targetSize.x = static_cast<int>(rectTransform.GetSize().y * textAspectRatio);
    }

    rectTransform.SetSize(targetSize);
    Rect rect = RectTransformToRenderRect(rectTransform);
    render.Copy(fontTexture, SDL2pp::NullOpt, rect, -rectTransform.GetAngle());
}

Rect Camera::RectTransformToRenderRect(RectTransform& rectT) {
    Transform transform = rectT.GetTransform();
    Vector2D rectPos = transform.GetPos();
    Vector2D rectSize = transform.GetSize();

    int screenWidth = render.GetOutputWidth();
    int screenHeight = render.GetOutputHeight();

    int screenX = (screenWidth * rectT.GetAnchor().x) + (transform.GetPos().x);
    int screenY = (screenHeight - (screenHeight * rectT.GetAnchor().y)) - (transform.GetPos().y);

    return Rect(screenX - (rectSize.x) * rectT.GetPivot().x,
                screenY - ((rectSize.y) - rectSize.y * rectT.GetPivot().y), rectSize.x, rectSize.y);
}


Vector2D Camera::ScreenToWorldPoint(Vector2D screenPos) {

    int screenWidth = render.GetOutputWidth();
    int screenHeight = render.GetOutputHeight();

    // Keeps aspect ratio
    float screenScale = std::min(static_cast<float>(screenWidth) / size,
                                 static_cast<float>(screenHeight) / size);

    Vector2D worldPos =
            Vector2D(((screenPos.x - (screenWidth / 2)) / screenScale) + position.x,
                     (-((screenPos.y - (screenHeight / 2)) / screenScale) - position.x));

    return worldPos;
}
