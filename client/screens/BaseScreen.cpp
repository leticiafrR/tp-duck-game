#include "BaseScreen.h"

BaseScreen::BaseScreen(Camera& cam): cam(cam), wasClosed(false), running(false) {}
BaseScreen::~BaseScreen() = default;

bool BaseScreen::WasClosed() { return wasClosed; }

void BaseScreen::Run() {
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
