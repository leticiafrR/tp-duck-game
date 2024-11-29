#include "RectTransform.h"

RectTransform::RectTransform():
        t(Transform()), anchor(Vector2D(0.5f, 0.5f)), pivot(Vector2D(0.5f, 0.5f)) {}

RectTransform::RectTransform(const Transform& t, Vector2D anchor, Vector2D pivot) {
    this->t = t;
    this->anchor = anchor;
    this->pivot = pivot;
}

RectTransform::RectTransform(Vector2D pos, Vector2D size, Vector2D anchor, Vector2D pivot):
        t(Transform(pos, size)) {
    this->anchor = anchor;
    this->pivot = pivot;
}

RectTransform::~RectTransform() = default;

Transform& RectTransform::GetTransform() { return t; }
void RectTransform::SetSize(Vector2D size) { t.SetSize(size); }
Vector2D RectTransform::GetSize() { return t.GetSize(); }
Vector2D RectTransform::GetPos() { return t.GetPos(); }
Vector2D RectTransform::GetPivot() { return pivot; }
Vector2D RectTransform::GetAnchor() { return anchor; }

void RectTransform::Move(Vector2D add) { t.Move(add); }
float RectTransform::GetAngle() { return t.GetAngle(); }
void RectTransform::SetAngle(float angle) { t.SetAngle(angle); }
