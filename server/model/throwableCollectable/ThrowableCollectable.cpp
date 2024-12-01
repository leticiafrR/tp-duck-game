#include "ThrowableCollectable.h"

#include "server/model/Duck.h"

ThrowableCollectable::ThrowableCollectable(const Transform& initialSpace):
        Collectable(initialSpace) {}


bool ThrowableCollectable::Use(Duck* thrower) {
    std::shared_ptr<Throwable> throwable = GetThrowable();
    thrower->PrepareToThrow(throwable);
    return true;
}

void ThrowableCollectable::Update(float /*deltaTime*/) {}
