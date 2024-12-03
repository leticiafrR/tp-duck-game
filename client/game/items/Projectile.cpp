#include "Projectile.h"

Projectile::Projectile(ProjectileData data, Vector2D origin, Vector2D end):
        origin(origin), end(end), speed(data.speed), alive(true) {

    SetFileName(data.file);
    SetSourceRect(data.rect);
    SetTransform(Transform(origin, data.size));
    GetTransform().LookAt(end, Vector2D::Right());
}

Projectile::~Projectile() = default;

void Projectile::Update(float deltaTime) {
    Vector2D dir = (end - origin).Normalized();
    GetTransform().Move(dir * speed * deltaTime);
    if (Vector2D::Distance(GetTransform().GetPos(), origin) >= (end - origin).GetMagnitude()) {
        alive = false;
        SetVisible(false);
    }
}

bool Projectile::IsAlive() { return alive; }
