#ifndef PROTOCOLCODES_H
#define PROTOCOLCODES_H

typedef enum: uint8_t {
    Jump = 1,
    MoveRight,
    MoveLeft,
    LookUp,
    StopLookingUp,
    Shoot,
    StopShooting,
    Crouch,  // agacharse
    EquipWeapon,
    UnequipWeapon,
    StopMoving,

} Commands;

#endif
