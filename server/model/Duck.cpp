#include "Duck.h"

#include "collectable/Weapon.h"
#include "common/Collision.h"
#include "map/staticMap.h"
#include "projectile/ProjectilesController.h"

#include "types.h"
/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/
Duck::Duck(const Vector2D& initialPos, ProjectilesController& projectilesController):
        DynamicObject(Speed::DUCK, Transform(initialPos, Vector2D(Size::DUCK, Size::DUCK))),
        isShooting(false),
        isCrouched(false),
        isGrounded(true),
        body(mySpace, Mass::DUCK),
        l(nullptr),
        myFlip(Flip::Right),
        myState(DuckState::IDLE),
        itemInHand(new LaserRifle(projectilesController, mySpace)) {}

void Duck::SayHello() { std::cout << "Hello!\n"; }
void Duck::RegistListener(PlayerEventListener* listener) {
    l = listener;
    l->Suscribe(&mySpace, &myFlip, &myState);

    // on the first iteration, everything is new
    l->Motion();
    l->Flipping();
    l->StateTransition();
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
        l->Motion();
    }
    if (initialState != myState) {
        l->StateTransition();
    }
}

void Duck::UpdateState() {
    myState = (velocity.x) ? DuckState::RUNNING : DuckState::IDLE;
    if (!isGrounded) {
        myState = (body.GetVelocity().y > 0) ? DuckState::JUMPING : DuckState::FALLING;
    }
}

void Duck::TryJump() {
    if (isGrounded) {
        body.ApplyForce(Vector2D::Up() * 40);
    }
}

void Duck::ApplyGravity(StaticMap& map, float deltaTime) {
    body.Update(deltaTime);
    isGrounded = map.IsOnTheFloor(mySpace);
    if (isGrounded) {
        body.ResetGravity();
        CheckCollisionWithMap(map);
    } else {
        // std::cout << "you're falling :( \n";
    }
}

void Duck::TryMoveLeft() {
    motionHandler.StartMoveLeft(velocity, speedX);
    if (myFlip != Flip::Left) {
        myFlip = Flip::Left;
        l->Flipping();
    }
}

void Duck::TryMoveRight() {
    motionHandler.StartMoveRight(velocity, speedX);
    if (myFlip != Flip::Right) {
        myFlip = Flip::Right;
        l->Flipping();
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
        MarkAsDead();
    }
}

void Duck::HandleCollisionWithMap(const Transform& mapT) {
    Collision::ResolveStaticCollision(mySpace, mapT);
}
