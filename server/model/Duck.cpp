#include "Duck.h"

#include "collectable/CollectablesController.h"
#include "common/Collision.h"
#include "map/staticMap.h"
#include "projectile/ProjectilesController.h"
#include "throwable/ThrowablesController.h"


/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/

#define COEFFICIENT_FRICTION_FLOOR 200
Duck::Duck(const Vector2D& initialPos, PlayerID_t id, const Config& conf):
        DynamicObject(Transform(initialPos, Vector2D(conf.getDuckSize(), conf.getDuckSize()))),
        id(id),
        speedX(conf.getDuckSpeed()),
        life(conf.getDuckLife()),
        isShooting(false),
        isLookingUp(false),
        isCrouched(false),
        isGrounded(true),
        isWounded(false),
        body(mySpace, conf.getDuckMass(), COEFFICIENT_FRICTION_FLOOR),
        l(nullptr),
        myFlip(Flip::Right),
        myState(DuckState::IDLE),
        itemOnHand(nullptr),
        throwableOnHand(nullptr),
        typeOnHand(TypeCollectable::EMPTY) {}

void Duck::TriggerEvent(bool cuack) {
    l->NewPlayerEvent(
            id, PlayerEvent(mySpace.GetPos(), myState, myFlip, isLookingUp, typeOnHand, isCrouched,
                            cuack, equipment.HasArmor(), equipment.HasHelmet()));
}

void Duck::Cuack() { TriggerEvent(true); }

const Flip& Duck::GetFlip() const { return myFlip; }

bool Duck::IsShooting() const { return isShooting; }

void Duck::HandleDead() {
    myState = DuckState::DEAD;
    TriggerEvent();
    MarkAsDead();
}

void Duck::LookUp() {
    isLookingUp = true;
    TriggerEvent();
}

void Duck::StopLookUp() {
    isLookingUp = false;
    TriggerEvent();
}

// it is supposed to doesn let you make a move
void Duck::Crouch() {
    isCrouched = true;
    TriggerEvent();
}

void Duck::StopCrouch() {
    isCrouched = false;
    TriggerEvent();
}

void Duck::StopShooting() { isShooting = false; }

void Duck::StartShooting() { isShooting = true; }

void Duck::HandleReceiveDamage(uint8_t damage) {
    if (!isCrouched && !equipment.AbsorbDamage()) {
        isWounded = true;
        life -= damage;
        if (life <= 0) {
            HandleDead();
        }
    } else if (!isCrouched) {
        TriggerEvent();
    }
}

void Duck::TryUseItem() {
    if (itemOnHand) {
        itemOnHand->Use(this);
    }
}

void Duck::StopUseItem() {
    if (itemOnHand) {
        itemOnHand->StopUse(this);
    }
}

void Duck::ApplyRecoil(float intensity) {
    body.ApplyForce(((myFlip == Flip::Left) ? Vector2D::Right() : Vector2D::Left()) * intensity);
}

void Duck::RegistListener(PlayerEventListener* listener) {
    l = listener;
    // on the first iteration, everything is new
    TriggerEvent();
}

void Duck::LoseThrowableOnHand() {
    throwableOnHand.reset();
    typeOnHand = TypeCollectable::EMPTY;
    TriggerEvent();
}
bool Duck::TryUpdateThrowable(const StaticMap& map, float deltaTime) {
    if (throwableOnHand) {
        throwableOnHand->FollowPosition(mySpace.GetPos());
        throwableOnHand->Update(map, deltaTime);
        if (throwableOnHand->IsDead())
            LoseThrowableOnHand();
        return true;
    }
    return false;
}
void Duck::TryUpdateCollectable(float deltaTime) {
    if (itemOnHand) {
        itemOnHand->Update(deltaTime);
        if (isShooting) {
            itemOnHand->Use(this);
        }
    }
}

void Duck::UpdateHand(const StaticMap& map, float deltaTime) {
    if (typeOnHand != TypeCollectable::EMPTY &&
        !(typeOnHand == TypeCollectable::HELMET || typeOnHand == TypeCollectable::ARMOR)) {
        if (!TryUpdateThrowable(map, deltaTime)) {
            TryUpdateCollectable(deltaTime);
        }
    }
}

Vector2D Duck::GetLookVector(bool justLaterals) {
    if (!isLookingUp || justLaterals) {
        return ((myFlip == Flip::Left) ? Vector2D::Left() : Vector2D::Right());
    }
    return Vector2D::Up();
}

void Duck::Update(const StaticMap& map, float deltaTime) {
    DuckState initialState = myState;
    Vector2D initialPos = mySpace.GetPos();

    UpdatePosition(map, deltaTime);
    UpdateHand(map, deltaTime);
    UpdateState();
    UpdateListener(initialState, initialPos);
}

void Duck::UpdateListener(const DuckState& initialState, const Vector2D& initialPos) {
    if (initialPos.IsFarFrom(mySpace.GetPos())) {
        TriggerEvent();
    }
    if (initialState != myState) {
        TriggerEvent();
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

void Duck::ApplyGravity(const StaticMap& map, float deltaTime) {
    body.Update(deltaTime);
    isGrounded = map.IsOnTheFloor(mySpace);
    if (isGrounded) {
        body.ResetGravity();
        CheckCollisionWithMap(map);
    }
}

void Duck::TryCollect(CollectablesController& c) {
    if (typeOnHand == TypeCollectable::EMPTY) {
        itemOnHand = c.TryCollect(mySpace, typeOnHand);
        TriggerEvent();
    }
}


bool Duck::TryDropCollectable(CollectablesController& collectables) {
    if (itemOnHand && isGrounded) {
        if (itemOnHand->StillReusable()) {
            collectables.Drop(itemOnHand, mySpace.GetPos());
        }
        itemOnHand.reset();
        return true;
    }
    return false;
}

bool Duck::TryThrow(ThrowablesController& throwables) {
    if (throwableOnHand) {
        throwables.Throw(throwableOnHand, mySpace.GetPos(), GetLookVector());
        throwableOnHand.reset();
        std::cout << "tenias un throwable\n";
        return true;
    }
    return false;
}


void Duck::PrepareToThrow(std::shared_ptr<Throwable> throwable) {
    itemOnHand.reset();
    throwableOnHand = throwable;
}


void Duck::TryDrop(CollectablesController& collectables, ThrowablesController& throwables) {
    if (TryThrow(throwables) || TryDropCollectable(collectables)) {
        typeOnHand = TypeCollectable::EMPTY;
        TriggerEvent();
    }
}

void Duck::TryMoveLeft() {
    motionHandler.StartMoveLeft(velocity, speedX);
    if (myFlip != Flip::Left) {
        myFlip = Flip::Left;
        TriggerEvent();
    }
}

void Duck::TryMoveRight() {
    motionHandler.StartMoveRight(velocity, speedX);
    if (myFlip != Flip::Right) {
        myFlip = Flip::Right;
        TriggerEvent();
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
        TriggerEvent();
        MarkAsDead();
    }
}

void Duck::HandleCollisionWithMap(const Transform& mapT) {
    Collision::ResolveStaticCollision(mySpace, mapT);
}

void Duck::TryEquip() {
    if (equipment.TryEquip(typeOnHand)) {
        itemOnHand.reset();
        TriggerEvent();
    }
}
