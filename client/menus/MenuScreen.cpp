#include "MenuScreen.h"

void MenuScreen::InitBackground() {
    guiManager.CreateImage(RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)), -1,
                           menuData.menuBgFile);

    guiManager.CreateImage(RectTransform(Vector2D(0, 240), Vector2D(575, 300)), 0,
                           menuData.logoBgFile);

    guiManager.CreateImage(RectTransform(Vector2D(0, -2), Vector2D(750, 80)), 1,
                           ColorExtension::Black().SetAlpha(80));
}

void MenuScreen::InitInput() {
    nicknamePlaceHolderText =
            guiManager.CreateText(RectTransform(Vector2D(0, 0), Vector2D(750, 80)), 2);

    nicknamePlaceHolderText->SetTextAndFontSize("Write your nickname", 50);
    nicknamePlaceHolderText->SetColor(ColorExtension::White().SetAlpha(120));

    nicknameText = guiManager.CreateText(RectTransform(Vector2D(0, 0), Vector2D(750, 80)), 3);
    nicknameText->SetTextAndFontSize("", 50);
}

void MenuScreen::InitStartButton() {
    btnStart = guiManager.CreateButton(RectTransform(Vector2D(0, -200), Vector2D(200, 80)), 3,
                                       [this]() {
                                           running = false;
                                           audioPlayer.PlayButtonSFX();
                                       });

    txtStartButton = guiManager.CreateText(RectTransform(Vector2D(0, -200), Vector2D(150, 80)), 4);
    txtStartButton->SetTextAndFontSize("START", 200);

    btnStartTween = TransformTween(&btnStart->GetTransform(),
                                   btnStart->GetTransform().GetSize() * 1.1f, 0.6f);


    txtStartButtonTween = TransformTween(&txtStartButton->GetTransform(),
                                         txtStartButton->GetTransform().GetSize() * 1.1f, 0.6f);
}


MenuScreen::MenuScreen(Camera& cam, ResourceManager& resource, bool& wasClosed, string& input):
        BaseScreen(cam, resource, wasClosed),
        menuData(resource.GetMenuData()),
        nicknameInput(input) {
    InitBackground();
    InitInput();
    InitStartButton();
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

    guiManager.HandleEvent(event, cam);
}


void MenuScreen::InitRun() {
    btnStartTween.SetLoops(-1, LoopType::Yoyo);
    txtStartButtonTween.SetLoops(-1, LoopType::Yoyo);

    btnStartTween.Play();
    txtStartButtonTween.Play();
}

void MenuScreen::Update(float deltaTime) {
    nicknameText->SetText(nicknameInput);

    nicknamePlaceHolderText->SetVisible(nicknameInput.size() == 0);

    btnStart->SetVisible(nicknameInput.size() != 0);
    txtStartButton->SetVisible(nicknameInput.size() != 0);

    btnStartTween.Update(deltaTime);
    txtStartButtonTween.Update(deltaTime);

    guiManager.Draw(cam);
}
