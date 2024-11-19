#include "Duck.h"

#include "common/Collision.h"
#include "map/staticMap.h"
#include "projectile/ProjectilesController.h"
#include "weapon/instant/PistolaCowboy.h"

#include "types.h"
/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/
Duck::Duck(const Vector2D& initialPos, PlayerID_t id, ProjectilesController& projectilesController):
        DynamicObject(Speed::DUCK, Transform(initialPos, Vector2D(Size::DUCK, Size::DUCK)),
                      Life::DUCK),
        id(id),
        isShooting(false),
        isCrouched(false),
        isGrounded(true),
        isWounded(false),
        body(mySpace, Mass::DUCK),
        l(nullptr),
        myFlip(Flip::Right),
        myState(DuckState::IDLE),
        itemInHand(new PistolaCowboy(projectilesController, mySpace)),
        typeInHand(TypeCollectable::PISTOLA_COWBOY) {}

const Flip& Duck::GetFlip() const { return myFlip; }

void Duck::HandleDead() {
    myState = DuckState::DEAD;
    l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
    MarkAsDead();
}

void Duck::StopShooting() { isShooting = false; }

void Duck::StartShooting() { isShooting = true; }

void Duck::HandleReceiveDamage(uint8_t damage) {
    isWounded = true;
    DynamicObject::HandleReceiveDamage(damage);
}

void Duck::TryUseItem() {
    if (itemInHand) {
        itemInHand->Use(this);
    }
}

void Duck::StopUseItem() {
    if (itemInHand) {
        itemInHand->StopUse(this);
    }
}

void Duck::RegistListener(PlayerEventListener* listener) {
    l = listener;

    // on the first iteration, everything is new
    l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
}

void Duck::Update(StaticMap& map, float deltaTime) {
    DuckState initialState = myState;
    Vector2D initialPos = mySpace.GetPos();

    UpdatePosition(map, deltaTime);
    UpdateState();
    UpdateListener(initialState, initialPos);
}

void Duck::UpdateListener(const DuckState& initialState, const Vector2D& initialPos) {
    if (initialPos.IsFarFrom(mySpace.GetPos())) {
        l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
    }
    if (initialState != myState) {
        l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
    }
}

DuckState Duck::GetLowerPriorityState() {
    DuckState lowerPriorityState = (velocity.x) ? DuckState::RUNNING : DuckState::IDLE;
    if (!isGrounded) {
        lowerPriorityState = (body.GetVelocity().y > 0) ? DuckState::JUMPING : DuckState::FALLING;
    }
    return lowerPriorityState;
}

void Duck::UpdateState() {
    if (!(IsDead())) {
        myState = (isWounded) ? DuckState::WOUNDED : GetLowerPriorityState();
        isWounded = false;
    }
}

void Duck::TryJump() {
    if (isGrounded) {
        body.ApplyForce(Vector2D::Up() * 60);
    }
}

void Duck::ApplyGravity(StaticMap& map, float deltaTime) {
    body.Update(deltaTime);
    isGrounded = map.IsOnTheFloor(mySpace);
    if (isGrounded) {
        body.ResetGravity();
        CheckCollisionWithMap(map);
    }
}

void Duck::TryMoveLeft() {
    motionHandler.StartMoveLeft(velocity, speedX);
    if (myFlip != Flip::Left) {
        myFlip = Flip::Left;
        l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
    }
}

void Duck::TryMoveRight() {
    motionHandler.StartMoveRight(velocity, speedX);
    if (myFlip != Flip::Right) {
        myFlip = Flip::Right;
        l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
    }
}

void Duck::StopMoveRight() { motionHandler.StopMoveRight(velocity, speedX); }

void Duck::StopMoveLeft() { motionHandler.StopMoveLeft(velocity, speedX); }

void Duck::HandleOutOfBounds(float displacement) {
    if (displacement > 0) {
        Vector2D add = (myFlip == Flip::Left) ? (Vector2D::Right() * displacement) :
                                                (Vector2D::Left() * displacement);
        mySpace.Move(add);
    } else {
        std::cout << "[DUCK]: me salì del lìmite posterior. Morì.\n";
        myState = DuckState::DEAD_BY_FALLING;
        l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip));
        MarkAsDead();
    }
}

void Duck::HandleCollisionWithMap(const Transform& mapT) {
    Collision::ResolveStaticCollision(mySpace, mapT);
}
