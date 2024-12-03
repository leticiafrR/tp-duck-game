#include "Duck.h"

#include "collectable/CollectablesController.h"
#include "common/Collision.h"
#include "map/staticMap.h"
#include "projectile/ProjectilesController.h"
#include "throwable/ThrowablesController.h"

#include "physicsConstants.h"
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
        isFlapping(false),
        cooldownFlapping(COOLDOWN_FLAPPING),
        flappingTimer(0),
        body(mySpace, conf.getDuckMass(), COEFFICIENT_FRICTION_FLOOR),
        l(nullptr),
        myFlip(Flip::Right),
        myState(DuckState::IDLE),
        itemOnHand(nullptr),
        throwableOnHand(nullptr),
        typeOnHand(TypeItem::EMPTY) {}

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

void Duck::HandleReceiveDamage(uint8_t damage, uint8_t intensityExplotion) {
    if (!isCrouched && !equipment.AbsorbDamage()) {
        isWounded = true;
        life -= damage;
        RetrocessOrSlide(intensityExplotion);
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

void Duck::RetrocessOrSlide(float intensity, bool isSlide) {
    if (intensity) {
        Vector2D dir = GetLookVector(true);
        if (!isSlide) {
            dir.Rotate(HALF_A_TURN);
        }
        body.ApplyForce(dir * intensity);
    }
}

void Duck::RegistListener(PlayerEventListener* listener) {
    l = listener;
    TriggerEvent();
}

void Duck::LoseThrowableOnHand() {
    throwableOnHand.reset();
    typeOnHand = TypeItem::EMPTY;
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
    if (typeOnHand != TypeItem::EMPTY &&
        !(typeOnHand == TypeItem::HELMET || typeOnHand == TypeItem::ARMOR)) {
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
        body.ApplyForce(Vector2D::Up() * INTENSITY_JUMPING);
    } else {
        isFlapping = true;
    }
}

void Duck::UpdateFlapping(float deltaTime) {
    if (isFlapping && (flappingTimer <= 0) && body.GetVelocity().y < 0) {
        body.ApplyForce(Vector2D::Up() * INTENSITY_FLAPPING);
        isFlapping = false;
        flappingTimer = cooldownFlapping;
    } else if (isFlapping) {
        flappingTimer -= deltaTime;
    }
}

void Duck::ApplyGravity(const StaticMap& map, float deltaTime) {
    UpdateFlapping(deltaTime);
    body.Update(deltaTime);
    isGrounded = map.IsOnTheFloor(mySpace);
    if (isGrounded) {
        body.ResetGravity();
        CheckCollisionWithMap(map);
    }
}

void Duck::TryCollect(CollectablesController& c) {
    if (typeOnHand == TypeItem::EMPTY) {
        itemOnHand = c.TryCollect(mySpace, typeOnHand);
        TriggerEvent();
    }
}


bool Duck::TryDropCollectable(CollectablesController& collectables) {
    if (itemOnHand && isGrounded) {
        if (itemOnHand->StillReusable()) {
            collectables.AddCollectable(itemOnHand, mySpace.GetPos());
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
        return true;
    }
    return false;
}


void Duck::PrepareToThrow(std::shared_ptr<Throwable> throwable, TypeItem type) {
    itemOnHand.reset();
    throwableOnHand = throwable;
    typeOnHand = type;
    TriggerEvent();
}


void Duck::TryDrop(CollectablesController& collectables, ThrowablesController& throwables) {
    if (TryThrow(throwables) || TryDropCollectable(collectables)) {
        typeOnHand = TypeItem::EMPTY;
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
