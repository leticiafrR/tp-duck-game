#ifndef HELMET_H
#define HELMET_H

#include <string>

#include "client/Framework.h"

using std::string;

class HelmetRenderer: public Object2D {
private:
    TransformFollow follow;

public:
    explicit HelmetRenderer(Transform& playerT, CollectableData data);

    void Update(bool flip, bool crouched);

    ~HelmetRenderer();
};

#endif
