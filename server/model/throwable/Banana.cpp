#include "Banana.h"

#include "common/Collision.h"
#include "server/model/Duck.h"

#define MASS_BANANA 4
#define COEFFICIENT_SLIDE_DUCK 8
#define COEFFICIENT_SLIDE_BANANA 1.35
Banana::Banana(): Throwable(MASS_BANANA), beenStepped(false) {}

void Banana::BeStepped(Duck* duck) {
    Vector2D intensity = duck->GetLookVector(true) * COEFFICIENT_SLIDE_DUCK;
    body.ApplyForce(duck->GetLookVector(true) * COEFFICIENT_SLIDE_BANANA);
    duck->Slide(intensity);
    beenStepped = true;
}

TypeCollectable Banana::GetTypeCollectable() { return TypeCollectable::BANANA; }

void Banana::CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& ducks) {
    if (isGrounded && throwingID != NOT_THROWED) {
        for (auto& pair: ducks) {
            Duck* duck = pair.second;
            if (Collision::RectCollision(duck->GetTransform(), mySpace)) {
                BeStepped(duck);
                break;
            }
        }
    }
}

void Banana::Update(const StaticMap& map, float deltaTime) {
    Vector2D initialPos = mySpace.GetPos();
    Throwable::Update(map, deltaTime);
    if (throwingID != NOT_THROWED) {
        if (beenStepped && (mySpace.GetPos().x - initialPos.x) == 0) {
            listener->Despawning(throwingID);
            MarkAsDead();
        } else {
            listener->Moving(throwingID, GetMovingEventDto());
        }
    }
}
