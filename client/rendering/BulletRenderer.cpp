#include "BulletRenderer.h"

BulletRenderer::BulletRenderer(TypeProjectile type, Vector2D origin, Vector2D end, float speed):
        origin(origin), end(end), speed(speed), alive(true) {
    renderData = bulletsDataMap.contains(type) ? bulletsDataMap.at(type) :
                                                 bulletsDataMap.at(TypeProjectile::BULLET);
    SetFileName(renderData.imageFile);
    SetSourceRect(renderData.GetSourceRect());
    SetTransform(Transform(origin, renderData.size, renderData.angle));
    GetTransform().LookAt(end, Vector2D::Right(), renderData.angle);
}
BulletRenderer::~BulletRenderer() = default;

void BulletRenderer::Update(float deltaTime) {
    Vector2D dir = (end - origin).Normalized();
    GetTransform().Move(dir * speed * deltaTime);
    if (Vector2D::Distance(GetTransform().GetPos(), origin) >= (end - origin).GetMagnitude()) {
        alive = false;
        SetVisible(false);
    }
}

bool BulletRenderer::IsAlive() { return alive; }
