#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include "common/Transform.h"


class StaticObject {
private:
    uint8_t objectID;
    Transform mySpace;

public:
    StaticObject(const int& posX, const int& posY, const int& sizeX, const int& sizeY, uint8_t ID):
            objectID(ID), mySpace(Vector2D(posX, posY), Vector2D(sizeX, sizeY), 0) {}
    Vector2D getPosition() { return mySpace.GetPos(); }
    Vector2D getSize() { return mySpace.GetSize(); }
    Transform getTransform() const { return mySpace; }
};

#endif
