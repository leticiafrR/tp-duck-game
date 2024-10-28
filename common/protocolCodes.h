#ifndef PROTOCOLCODES_H
#define PROTOCOLCODES_H

typedef enum: uint8_t {
    UP = 1,
    RIGHT,
    LEFT,
    DOWN,
    SHOOT,
    FIT_OUT,  // equipar, podemos ponerle un nombre mas acorde
    KEY_UP,
    KEY_DOWN,
} KEYS;

#endif
