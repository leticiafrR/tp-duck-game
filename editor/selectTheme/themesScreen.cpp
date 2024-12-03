#include "themesScreen.h"

#include "multimedia/gui/ButtonsManager.h"

#include "constants.h"

void ThemesScreen::ReadAvaiableThemes() {
    widgets.clear();
    YAML::Node config = YAML::LoadFile(THEME_PATH);
    std::vector<string> themes;
    for (YAML::const_iterator it = config.begin(); it != config.end(); ++it) {
        themes.emplace_back(it->first.as<std::string>());
    }

    int moveDelta = 130;
    Vector2D initialPos(0, -100);
    for (std::size_t i = 0; i < themes.size(); ++i) {

        widgets.emplace_back(guiManager, themes[i], [this](const std::string& name) {
            selectedTheme = name;
            running = false;
        });
        widgets.back().MoveContent(Vector2D::Down() * i * moveDelta + initialPos);
    }
}

ThemesScreen::ThemesScreen(Camera& cam, ResourceManager& resource, bool& wasClosed):
        BaseScreen(cam, resource, wasClosed), selectedTheme() {
    ReadAvaiableThemes();
}
ThemesScreen::~ThemesScreen() { cam.ClearCacheItem(DUCK_BACKGROUND.c_str()); }

void ThemesScreen::UpdateWidgetListPosition(Vector2D movement) {
    /*if (currentY + movement.y > scrollSize - 450 || currentY + movement.y < -10) {
        return;
    }*/
    currentY += movement.y;
    for (auto& widget: widgets) {
        widget.MoveContent(movement);
    }
}
string ThemesScreen::Render(bool lockerOnly) {

    Image* bg = guiManager.CreateImage(DUCK_BACKGROUND.c_str(),
                                       RectTransform(Vector2D::Zero(), Vector2D(2133, 1200)),
                                       ColorExtension::White(), 0);

    bg->SetVisible(!lockerOnly);

    Run();

    if (wasClosed)
        return "";

    return selectedTheme;
}

void ThemesScreen::InitRun() {}

void ThemesScreen::TakeInput(SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEWHEEL:
            Vector2D wheelDir = Vector2D::Down() * event.wheel.y;
            UpdateWidgetListPosition(wheelDir * cam.GetRateDeltatime() * 2500);
            break;
    }
    guiManager.HandleEvent(event, cam);
}
void ThemesScreen::Update([[maybe_unused]] float deltaTime) { guiManager.Draw(cam); }
