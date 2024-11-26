#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "multimedia/Camera.h"

class MenuScreen {
    Camera& cam;

public:
    explicit MenuScreen(Camera& cam);
    void run();
    void RenderListLevels();
};
#endif
