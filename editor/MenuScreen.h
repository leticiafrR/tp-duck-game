#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include <string>

#include "multimedia/Button.h"
#include "multimedia/Camera.h"
#include "multimedia/Image.h"
#include "multimedia/Text.h"

using std::string;
class MenuScreen {
    Camera& cam;
    Image background;
    Image logo;
    Button createLvl;
    Text textCreateLvl;
    Button editLvl;
    Text textEditLvl;
    bool running = true;
    void RenderListLevels();
    void RenderLvlName();
    bool option;

public:
    explicit MenuScreen(Camera& cam);
    bool run();
};
#endif
