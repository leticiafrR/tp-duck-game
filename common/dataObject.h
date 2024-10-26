#ifndef DATAOBJECT_H
#define DATAOBJECT_H
#include <cstdint>

#include "../client/Transform.h"

struct dataObject {
    [[clang::supress_unused]] uint8_t customID;
    Transform transform;

    dataObject(): customID(0), transform() {}
};
#endif
