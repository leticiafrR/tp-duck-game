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
    RectTransform();

    explicit RectTransform(const Transform& t, Vector2D anchor = Vector2D(0.5f, 0.5f),
                           Vector2D pivot = Vector2D(0.5f, 0.5f));

    explicit RectTransform(Vector2D pos, Vector2D size, Vector2D anchor = Vector2D(0.5f, 0.5f),
                           Vector2D pivot = Vector2D(0.5f, 0.5f));

    ~RectTransform();

    Transform& GetTransform();
    void SetSize(Vector2D size);
    Vector2D GetSize();
    Vector2D GetPivot();
    Vector2D GetAnchor();

    void Move(Vector2D add);
    float GetAngle();
    void SetAngle(float angle);
};

#endif
