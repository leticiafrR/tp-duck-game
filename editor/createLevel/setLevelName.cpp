#include "setLevelName.h"

#include "editor/constantsEditor.h"
#include "multimedia/KeyboardExtension.h"

#include "constants.h"

SetLevelName::SetLevelName(Camera& c, ResourceManager& resource, bool& wasClosed):
        BaseScreen(c, resource, wasClosed) {

    guiManager.CreateImage(DUCK_BACKGROUND.c_str(),
                           RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)));
    guiManager.CreateImage(DUCK_GAME_LOGO.c_str(),
                           RectTransform(Vector2D(0, 240), Vector2D(575, 300)));

    guiManager.CreateImage(RectTransform(Vector2D(0, -2), Vector2D(750, 80)),
                           ColorExtension::Black().SetAlpha(80));


    nicknamePlaceHolderText = guiManager.CreateText(
            ENTER_LVL_NAME.c_str(), 50, RectTransform(Vector2D(0, 0), Vector2D(750, 80)),
            ColorExtension::White().SetAlpha(120));

    nicknameText = guiManager.CreateText("", 50, RectTransform(Vector2D(0, 0), Vector2D(750, 80)),
                                         ColorExtension::White());

    startButton = guiManager.CreateButton(
            BUTTON_1_IMAGE.c_str(), RectTransform(Vector2D(0, -200), Vector2D(200, 80)),
            [this]() { running = false; }, Color(40, 40, 40));

    buttonText = guiManager.CreateText(CREATE_LABEL.c_str(), 200,
                                       RectTransform(Vector2D(0, -200), Vector2D(150, 80)));
}

void SetLevelName::InitRun() {}

void SetLevelName::TakeInput(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&)event;

            switch (keyEvent.keysym.sym) {
                case SDLK_BACKSPACE:
                    if (nicknameInput.size() > 0)
                        nicknameInput.pop_back();
                    break;
                default:
                    if ((int)nicknameInput.size() == MAX_NAME_SIZE)
                        break;
                    if (!SDLExtension::IsAlphaNumeric(keyEvent.keysym.sym))
                        break;

                    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                    bool shiftPressed = (currentKeyStates[SDL_SCANCODE_LSHIFT] ||
                                         currentKeyStates[SDL_SCANCODE_RSHIFT]);

                    char c = static_cast<char>(keyEvent.keysym.sym);
                    if (shiftPressed)
                        c = std::toupper(c);
                    nicknameInput.push_back(c);
                    break;
            }
            break;
        }
    }

    guiManager.HandleEvent(event, cam);
}

void SetLevelName::Update([[maybe_unused]] float deltaTime) {
    nicknameText->SetText(nicknameInput);

    nicknamePlaceHolderText->SetVisible(nicknameInput.size() == 0);
    startButton->SetVisible(nicknameInput.size() != 0);
    buttonText->SetVisible(nicknameInput.size() != 0);

    guiManager.Draw(cam);
}

string SetLevelName::Render() {
    Run();
    return nicknameInput;
}

SetLevelName::~SetLevelName() {
    cam.ClearCacheItem(DUCK_BACKGROUND.c_str());
    cam.ClearCacheItem(DUCK_GAME_LOGO.c_str());
}
