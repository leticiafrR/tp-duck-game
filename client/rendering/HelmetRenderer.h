#ifndef HELMET_RENDERER_H
#define HELMET_RENDERER_H

#include <string>

#include "client/Framework.h"
#include "multimedia/cache/SheetDataCache.h"

using std::string;

class HelmetRenderer: public Object2D {
private:
    TransformFollow follow;

public:
    explicit HelmetRenderer(Transform& playerT);

    void Update(bool flip, bool crouched);

    ~HelmetRenderer();
};

#endif
