
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>

#include "multimedia/AudioManager.h"
#include "multimedia/Button.h"
#include "multimedia/ButtonsManager.h"
#include "multimedia/GUIManager.h"
#include "multimedia/Image.h"
#include "multimedia/Object2D.h"
#include "multimedia/Text.h"

using namespace SDL2pp;  // NOLINT

int main() {
    // Initialize video, audio and text
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLMixer sdlMixer(MIX_INIT_MP3 | MIX_INIT_OGG);
    AudioManager::GetInstance();
    SDLTTF ttf;

    // Creates a window
    Window window("Duck Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 940, 940,
                  SDL_WINDOW_RESIZABLE);

    // Creates a render
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    render.SetDrawBlendMode(SDL_BlendMode::SDL_BLENDMODE_BLEND);  // Allows transparency
    render.SetDrawColor(100, 100, 100, 255);

    // Create a camera with render, 70 camera size(zoom), and 60fps for framerate
    // The Size(zoom) can be update in runtime with cam.SetSize(float)
    Camera cam(std::move(render), 70, Rate(60));

    bool running = true;

    // Samples

    // Draws an sprite will be drawn with Transform in world position
    Object2D duckSprite("base_duck.png", Transform(Vector2D(0, -20), Vector2D(5, 5)));
    // base_duck.png is an sprite sheet, so we need to get the exact rect to draw,
    // for this will be use SetSourceRect combine with SheedDatacache
    duckSprite.SetSourceRect(SheetDataCache::GetData("duck.yaml")["idle"][0]);

    // GUI Image from file with the correct extension(.jpg/.png/etc)(which is taken from
    // assets/sprites).
    // Thie graphics with RectTransform will be drawn on screen position, in this sample with center
    // position and 1000x1000 size, anchored in center by default Layer order indicates how far back
    // or forward the graphic will be
    Image bg("duck_game_bg.jpg", RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
             ColorExtension::White(), 0);

    // GUI Text, needs a string to render, a font size, the rectTransform to fit the text, color and
    // layer order.
    Text txtTitle("SAMPLE!", 50, RectTransform(Vector2D::Zero(), Vector2D(400, 400)),
                  ColorExtension::White(), 1);

    // Similar to image, but needs a callback (function/lambda) to run on pressed
    // In this case, the anchor for the button is (1,1) which means top right corner, the values can
    // be variable from (0,0) (bottom left corner) to (1, 1).
    // Just because the rect is anchored to top right corner, the position needs to be modified
    // around it, (-120, -120) means to move down and left to be visible on the screen.
    Button btnExit(
            "button_1.png", RectTransform(Vector2D(-120, -120), Vector2D(100, 100), Vector2D(1, 1)),
            [&running]() { running = false; }, Color(40, 40, 40), 1);

    // A text for the button, with same rectTransform values
    Text txtExitButton("Exit", 20,
                       RectTransform(Vector2D(-120, -120), Vector2D(100, 100), Vector2D(1, 1)),
                       ColorExtension::White(), 1);

    // Loop
    while (running) {
        SDL_Event event;

        // Take sdl input(keyboard/mouse)
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:  // On x window button pressed
                    running = false;
                    break;
            }

            // If a button was pressed, this will handle its callback
            ButtonsManager::GetInstance().HandleEvent(event, cam);
        }

        // This is ok, the game drawing should happen before GUI drawing
        // duckSprite.Draw(cam);

        // All GUI items declared before on stack will be drawn by this
        GUIManager::GetInstance().Draw(cam);

        // For this sample, the drawing will be happen after, just to show that the duck is being
        // rendering
        duckSprite.Draw(cam);

        // The cam will render all drawn items
        cam.Render();

        // Delay from framerate
        cam.Delay();
    }

    return 0;
}
