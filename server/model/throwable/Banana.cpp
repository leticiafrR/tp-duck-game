#include "Banana.h"

#include "../physicsConstants.h"
#include "common/Collision.h"
#include "server/model/Duck.h"

#define MASS_BANANA 4

Banana::Banana(TypeItem type): Throwable(MASS_BANANA, type), beenStepped(false) {}

void Banana::BeStepped(Duck* duck) {
    body.ApplyForce((duck->GetLookVector(true) * INTENSITY_SLIDE_BANANA));
    duck->RetrocessOrSlide(INTENSITY_SLIDE_DUCK, true);
    beenStepped = true;
}

bool Banana::IsReadyToBeStepped() { return isGrounded && beenThrowed; }

void Banana::CheckCollisionWithDucks(std::unordered_map<PlayerID_t, Duck*>& ducks) {
    if (IsReadyToBeStepped() && !beenStepped) {
        for (auto& pair: ducks) {
            if (Collision::RectCollision(pair.second->GetTransform(), mySpace)) {
                BeStepped(pair.second);
                break;
            }
        }
    }
}

void Banana::Update(const StaticMap& map, float deltaTime) {
    Vector2D initialPos = mySpace.GetPos();
    Throwable::Update(map, deltaTime);
    if (beenThrowed) {
        if (beenStepped && (mySpace.GetPos().x - initialPos.x) == 0) {
            MarkAsDead();
        }
    }
}
