#ifndef EXITOPTIONS_H
#define EXITOPTIONS_H
#include <string>

#include "multimedia/BaseScreen.h"
#include "multimedia/Camera.h"
#include "multimedia/gui/Button.h"
#include "multimedia/gui/Image.h"
#include "multimedia/gui/Text.h"

using std::string;
class ExitOptions: public BaseScreen {
    Image* background;
    Image* logo;
    Button* Exit;
    Text* ExitText;
    Button* Menu;
    Text* MenuText;
    void RenderListLevels();
    void RenderLvlName();
    bool exit = false;

    void InitRun() override;
    void TakeInput(SDL_Event event) override;
    void Update(float deltaTime) override;

public:
    explicit ExitOptions(Camera& cam, ResourceManager& reosurce, bool& wasClosed);
    bool run();
    ~ExitOptions();
};
#endif
