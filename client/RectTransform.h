#ifndef RECT_TRANSFORM_H
#define RECT_TRANSFORM_H

#include <SDL2pp/SDL2pp.hh>

#include "common/Transform.h"

using SDL2pp::Rect;

class RectTransform {
private:
    Transform t;
    Vector2D anchor;
    Vector2D pivot;

public:
    RectTransform(): t(Transform()), anchor(Vector2D(0.5f, 0.5f)), pivot(Vector2D(0.5f, 0.5f)) {}

    explicit RectTransform(const Transform& t, Vector2D anchor = Vector2D(0.5f, 0.5f),
                           Vector2D pivot = Vector2D(0.5f, 0.5f)):
            t(t), anchor(anchor), pivot(pivot) {}

    explicit RectTransform(Vector2D pos, Vector2D size, Vector2D anchor = Vector2D(0.5f, 0.5f),
                           Vector2D pivot = Vector2D(0.5f, 0.5f)):
            t(Transform(pos, size)), anchor(anchor), pivot(pivot) {}

    Transform& GetTransform() { return t; }
    void SetSize(Vector2D size) { t.SetSize(size); }
    Vector2D GetSize() { return t.GetSize(); }
    Vector2D GetPivot() { return pivot; }
    Vector2D GetAnchor() { return anchor; }

    void Move(Vector2D add) { t.Move(add); }
    float GetAngle() { return t.GetAngle(); }
    void SetAngle(float angle) { t.SetAngle(angle); }

    ~RectTransform() = default;
};

#endif
