#ifndef BOXES_CONTROLLER_H
#define BOXES_CONTROLLER_H
#include <string>
#include <unordered_map>

#include "client/Framework.h"
#include "multimedia/2d/Object2D.h"

using std::unordered_map;

const string BOX_FILE = "box.jpg";

class BoxesController {
private:
    unordered_map<BoxID_t, Object2D> boxes;

public:
    BoxesController();
    ~BoxesController();

    void SpawnBox(BoxID_t id, Vector2D pos);
    void DespawnBox(BoxID_t id);

    void Draw(Camera& cam);
};

#endif
