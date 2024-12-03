#include "ThrowableCollectable.h"

ThrowableCollectable::ThrowableCollectable(const Transform& initialSpace):
        Collectable(initialSpace) {}

void ThrowableCollectable::StopUse(Duck* /*user*/) {}
void ThrowableCollectable::Update(float /*deltaTime*/) {}
