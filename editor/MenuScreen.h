#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include <string>

#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

using std::string;
class MenuScreen: public BaseScreen {
    void RenderListLevels();
    void RenderLvlName();
    int option;

public:
    explicit MenuScreen(Camera& cam, ResourceManager& reosurce, bool& wasClosed);
    int run();

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

    ~MenuScreen();
};
#endif
