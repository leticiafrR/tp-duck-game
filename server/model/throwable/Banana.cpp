#include "Banana.h"

#include "common/Collision.h"
#include "server/model/Duck.h"

#define MASS_BANANA 4
#define INTENSITY_SLIDE_DUCK(y) (y * 54)
#define INTENSITY_SLIDE(x) (x * 14)

Banana::Banana(): Throwable(MASS_BANANA), beenStepped(false) {}

void Banana::BeStepped(Duck* duck) {
    body.ApplyForce(INTENSITY_SLIDE(duck->GetLookVector(true)));
    duck->Slide(INTENSITY_SLIDE_DUCK(duck->GetLookVector(true)));
    beenStepped = true;
}

TypeCollectable Banana::GetTypeCollectable() { return TypeCollectable::BANANA; }

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
