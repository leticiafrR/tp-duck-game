#include "BaseScreen.h"

BaseScreen::BaseScreen(Camera& cam): cam(cam), running(false) {}
BaseScreen::~BaseScreen() = default;

void BaseScreen::Run(bool& wasClosed) {
    if (wasClosed)
        return;

    running = true;

    InitRun();

    cam.InitRate();

    while (running) {
        cam.Clean();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                wasClosed = true;
                running = false;
                return;
            }
            TakeInput(event);
        }

        Update(cam.GetRateDeltatime());

        cam.Render();
        cam.Delay();
    }
}
