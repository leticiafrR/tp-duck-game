#ifndef EXITOPTIONS_H
#define EXITOPTIONS_H
#include <string>

#include "multimedia/Camera.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

using std::string;
class ExitOptions {
    Camera& cam;
    Image background;
    Image logo;
    Button Exit;
    Text ExitText;
    Button Menu;
    Text MenuText;
    bool running = true;
    void RenderListLevels();
    void RenderLvlName();
    bool exit = false;

public:
    explicit ExitOptions(Camera& cam);
    bool run();
    ~ExitOptions();
};
#endif
