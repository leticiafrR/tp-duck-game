#include "MenuScreen.h"

#include "multimedia/ButtonsManager.h"

#include "LevelsScreen.h"
#include "constantsEditor.h"
const int WEIGHT_SCREEN = 940;
const int HIGH_SCREEN = 940;
MenuScreen::MenuScreen(Camera& cam): cam(cam) {}


void MenuScreen::RenderListLevels() {
    // bool joinSuccess = false;
    LevelsScreen lvlsScreen(cam);
    lvlsScreen.Render("JOINING LEVELS");
}
void MenuScreen::run() {
    // Initialize video, audio and text

    bool running = true;
    // Samples

    // Draws an sprite will be drawn with Transform in world position
    // Object2D duckSprite("base_duck.png", Transform(Vector2D(0, -20), Vector2D(5, 5)));
    // base_duck.png is an sprite sheet, so we need to get the exact rect to draw,
    // for this will be use SetSourceRect combine with SheedDatacache
    // duckSprite.SetSourceRect(SheetDataCache::GetData("duck.yaml")["idle"][0]);

    // GUI Image from file with the correct extension(.jpg/.png/etc)(which is taken from
    // assets/sprites).
    // Thie graphics with RectTransform will be drawn on screen position, in this sample with center
    // position and 1000x1000 size, anchored in center by default Layer order indicates how far back
    // or forward the graphic will be
    Image bg("duck_game_bg.jpg", RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
             ColorExtension::White(), 0);

    // GUI Text, needs a string to render, a font size, the rectTransform to fit the text, color and
    // layer order.
    // Text txtTitle("prueba!", 50, RectTransform(Vector2D::Zero(), Vector2D(400, 400)),
    //               ColorExtension::White(), 1);

    // Similar to image, but needs a callback (function/lambda) to run on pressed
    // In this case, the anchor for the button is (1,1) which means top right corner, the values can
    // be variable from (0,0) (bottom left corner) to (1, 1).
    // Just because the rect is anchored to top right corner, the position needs to be modified
    // around it, (-120, -120) means to move down and left to be visible on the screen.


    Button btnCreateLevel(
            BUTTON_IMAGE_PATH.c_str(),
            RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.85, 0.65)),
            [&running]() { running = false; }, Color(220, 220, 220), 1);

    // A text for the button, with same rectTransform values
    Text txtCreateButton(
            CREATE_LABEL.c_str(), 20,
            RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.85, 0.65)),
            ColorExtension::White(), 1);
    Button btnEditLevel(
            BUTTON_IMAGE_PATH.c_str(),
            RectTransform(Vector2D(-120, -120), Vector2D(300, 150), Vector2D(0.45, 0.65)),
            [this]() { this->RenderListLevels(); }, Color(220, 220, 220), 1);

    // A text for the button, with same rectTransform values
    Text txtEditButton(
            EDIT_LABEL.c_str(), 20,
            RectTransform(Vector2D(-120, -120), Vector2D(400, 400), Vector2D(0.45, 0.65)),
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
                case SDL_MOUSEBUTTONDOWN:  // Evento de clic del ratón
                    if (btnCreateLevel.IsTarget(event.button.x, event.button.y, cam)) {
                        std::cout << "Create Level" << std::endl;

                        break;
                    } else if (btnEditLevel.IsTarget(event.button.x, event.button.y, cam)) {
                        std::cout << "Edit Level" << std::endl;
                        break;
                    }
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
        // duckSprite.Draw(cam);

        // The cam will render all drawn items
        cam.Render();

        // Delay from framerate
        // cam.Delay();
    }
}
