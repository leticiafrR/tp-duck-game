#include "Duck.h"

#include "collectable/CollectablesController.h"
#include "common/Collision.h"
#include "map/staticMap.h"
#include "projectile/ProjectilesController.h"
#include "weapon/instant/DuelingPistol.h"
#include "weapon/instant/Shotgun.h"

/*******************************************************************************************/
/*                                DEFINITIONS                                              */
/*******************************************************************************************/
Duck::Duck(const Vector2D& initialPos, PlayerID_t id, const Config& conf):
        DynamicObject(conf.getDuckSpeed(),
                      Transform(initialPos, Vector2D(conf.getDuckSize(), conf.getDuckSize())),
                      conf.getDuckLife()),
        id(id),
        isShooting(false),
        isLookingUp(false),
        isCrouched(false),
        isGrounded(true),
        isWounded(false),
        body(mySpace, conf.getDuckMass()),
        l(nullptr),
        myFlip(Flip::Right),
        myState(DuckState::IDLE),
        itemOnHand(nullptr),
        typeOnHand(TypeCollectable::LASER_RIFLE) {}

void Duck::TriggerEvent(bool cuack) {
    l->NewPlayerEvent(id, PlayerEvent(mySpace.GetPos(), myState, myFlip, isLookingUp, typeOnHand,
                                      isCrouched, cuack));
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
    if (!isCrouched) {
        isWounded = true;
        DynamicObject::HandleReceiveDamage(damage);
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

bool Duck::HasWeaponOnHand() {
    return (itemOnHand &&
            !(typeOnHand == TypeCollectable::HELMET || typeOnHand == TypeCollectable::ARMOR));
}

void Duck::UpdateWeapon(float deltaTime) {
    if (HasWeaponOnHand()) {
        itemOnHand->Update(deltaTime);
        if (isShooting) {
            itemOnHand->Use(this);
        }
    }
}

Vector2D Duck::GetLookVector() {
    if (isLookingUp) {
        return Vector2D::Up();
    }
    return ((myFlip == Flip::Left) ? Vector2D::Left() : Vector2D::Right());
}

void Duck::Update(StaticMap& map, float deltaTime) {
    DuckState initialState = myState;
    Vector2D initialPos = mySpace.GetPos();

    UpdatePosition(map, deltaTime);
    UpdateWeapon(deltaTime);
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

void Duck::ApplyGravity(StaticMap& map, float deltaTime) {
    body.Update(deltaTime);
    isGrounded = map.IsOnTheFloor(mySpace);
    if (isGrounded) {
        body.ResetGravity();
        CheckCollisionWithMap(map);
        // std::cout << "pos grounded y con collisiones resueltas: "<<
        // mySpace.GetPos().ToString()<<std::endl;
    }
}

void Duck::TryCollect(CollectablesController& c) {
    std::cout << "you'll try to collect an item\n";
    if (!itemOnHand) {
        itemOnHand = c.PickCollectable(mySpace, typeOnHand);
        std::cout << "[duck]: collected!\n";
    }
}
void Duck::TryDrop(CollectablesController& c) {
    if (itemOnHand) {
        c.Drop(itemOnHand, mySpace.GetPos());
        std::cout << "[duck]: efectivamente soltado\n";
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
