#include "ThrowableCreator.h"

#include "server/model/Duck.h"

ThrowableCreator::ThrowableCreator(const Transform& initialSpace): Collectable(initialSpace) {}


bool ThrowableCreator::Use(Duck* thrower) {
    std::shared_ptr<Throwable> throwable = GetThrowable();
    thrower->PrepareToThrow(throwable);
    return true;
}

void ThrowableCreator::Update(float /*deltaTime*/) {}
