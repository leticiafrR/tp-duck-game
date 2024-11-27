#include "Object2D.h"

Object2D::Object2D() {}

Object2D::Object2D(const std::string& filename, const Transform& transform, Color color):
        filename(filename), sourceRect(SDL2pp::NullOpt), transform(transform), color(color) {}

Object2D::~Object2D() {}

void Object2D::SetColor(Color color) { this->color = color; }
Color Object2D::GetColor() { return color; }

Transform& Object2D::GetTransform() { return this->transform; }
void Object2D::SetTransform(const Transform& transform) { this->transform = transform; }

std::string& Object2D::GetFileName() { return filename; }
void Object2D::SetFileName(const std::string& filename) { this->filename = filename; }

void Object2D::SetSourceRect(const SDL2pp::Optional<Rect>& rect) { this->sourceRect = rect; }
SDL2pp::Optional<Rect> Object2D::GetSourceRect() { return this->sourceRect; }

void Object2D::SetFlip(bool flipH) { this->flipH = flipH; }
bool Object2D::GetFlip() { return flipH; }

int Object2D::GetFlipSDL() { return flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE; }

void Object2D::Draw(Camera& cam) {
    if (!visible)
        return;
    if (filename.empty())
        return;
    cam.DrawTexture(filename, sourceRect, color, transform, GetFlipSDL());
}

void Object2D::SetVisible(bool visible) { this->visible = visible; }
