#include "MenuScreen.h"

MenuScreen::MenuScreen(GameKit& kit, bool& wasClosed, string& input):
        BaseScreen(kit, wasClosed),
        bgImage(RectTransform(Vector2D::Zero(), Vector2D(2133, 1200))),
        logoImage(RectTransform(Vector2D(0, 240), Vector2D(575, 300))),
        inputBgImage(RectTransform(Transform(Vector2D(0, -2), Vector2D(750, 80))),
                     ColorExtension::Black().SetAlpha(80)),
        nicknamePlaceHolderText(RectTransform(Vector2D(0, 0), Vector2D(750, 80), Vector2D(0.5, 0.5),
                                              Vector2D(0.5, 0.5))),
        nicknameText(RectTransform(Vector2D(0, 0), Vector2D(750, 80), Vector2D(0.5, 0.5),
                                   Vector2D(0.5, 0.5))),
        startButton(RectTransform(Vector2D(0, -200), Vector2D(200, 80), Vector2D(0.5, 0.5),
                                  Vector2D(0.5, 0.5)),
                    ColorExtension::DarkGray()),
        buttonText(RectTransform(Vector2D(0, -200), Vector2D(150, 80), Vector2D(0.5, 0.5),
                                 Vector2D(0.5, 0.5))),
        nicknameInput(input),
        btnTween(startButton.GetTransform()),
        textTween(buttonText.GetTransform()) {

    bgImage.SetFile(menuData.menuBgFile);
    logoImage.SetFile(menuData.logoBgFile);

    nicknamePlaceHolderText.SetTextAndFontSize("Write your nickname", 50);
    nicknamePlaceHolderText.SetColor(ColorExtension::White().SetAlpha(120));
    nicknameText.SetTextAndFontSize("", 50);

    startButton.SetFile(BUTTON_FILE);
    startButton.SetCallback([this]() {
        running = false;
        gameKit.PlayButtonSFX();
    });
    buttonText.SetTextAndFontSize("START", 200);
}

MenuScreen::~MenuScreen() {
    cam.ClearCacheItem(menuData.menuBgFile);
    cam.ClearCacheItem(menuData.logoBgFile);
}

void MenuScreen::TakeInput(SDL_Event event) {
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

    ButtonsManager::GetInstance().HandleEvent(event, cam);
}


void MenuScreen::InitRun() {
    btnTween.SetTarget(startButton.GetSize() * 1.1f, 0.6f);
    textTween.SetTarget(buttonText.GetSize() * 1.1f, 0.6f);

    btnTween.SetLoops(-1, LoopType::Yoyo);
    textTween.SetLoops(-1, LoopType::Yoyo);

    btnTween.Play();
    textTween.Play();
}

void MenuScreen::Update(float deltaTime) {
    nicknameText.SetText(nicknameInput);

    nicknamePlaceHolderText.SetVisible(nicknameInput.size() == 0);
    startButton.SetVisible(nicknameInput.size() != 0);
    buttonText.SetVisible(nicknameInput.size() != 0);

    GUIManager::GetInstance().Draw(cam);
    TweenManager::GetInstance().Update(deltaTime);
}
