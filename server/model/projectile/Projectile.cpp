#include "Projectile.h"

Projectile::Projectile(TypeProjectile type): type(type), isDead(false) {}
void Projectile::MarkAsDead() { isDead = true; }
bool Projectile::IsDead() { return isDead; }
