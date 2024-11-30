#include "GameStatusScreen.h"

DuckResultItemGUI::DuckResultItemGUI(Vector2D pos, const PlayerData& duck, int count):
        imgColor("base_duck.png", RectTransform(pos, Vector2D(70, 70)),
                 DuckClientRenderer::GetColorById(duck.playerSkin), 20),
        txtNickname(duck.nickname, 30,
                    RectTransform(Vector2D(pos.x + 50, pos.y), Vector2D(300, 150),
                                  Vector2D(0.5, 0.5), Vector2D(0, 0.5)),
                    ColorExtension::White(), 20),
        txtCount(std::to_string(count), 35,
                 RectTransform(Vector2D(pos.x + 390, pos.y), Vector2D(150, 150), Vector2D(0.5, 0.5),
                               Vector2D(0, 0.5)),
                 ColorExtension::White(), 20) {

    imgColor.SetSourceRect(SheetDataCache::GetData("duck.yaml")["head"][0]);
}

DuckResultItemGUI::~DuckResultItemGUI() = default;


GameStatusScreen::GameStatusScreen(Camera& cam, vector<PlayerData> players,
                                   unordered_map<PlayerID_t, int> gameResults,
                                   std::optional<PlayerData> winner):
        BaseScreen(cam),
        imgBg(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), ColorExtension::Black()),
        txtTitle("", 40, RectTransform(Vector2D(0, -130), Vector2D(800, 120), Vector2D(0.5, 1)),
                 ColorExtension::White(), 10),
        btnBack(
                "back_icon.png", RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)),
                [this]() {
                    running = false;
                    AudioManager::GetInstance().PlayButtonSFX();
                },
                ColorExtension::White(), 11),
        timer(3.0f, [this]() { running = false; }) {


    if (winner.has_value()) {
        txtTitle.SetText("The winner is: " + winner.value().nickname);
        btnBack.SetActive(true);
    } else {
        txtTitle.SetText("Game status");
        btnBack.SetActive(false);
    }

    InitPlayersDisplay(players, gameResults);
}

GameStatusScreen::~GameStatusScreen() = default;

void GameStatusScreen::InitPlayersDisplay(vector<PlayerData> players,
                                          unordered_map<PlayerID_t, int> gameResults) {
    std::sort(players.begin(), players.end(), [&gameResults](PlayerData a, PlayerData b) {
        return gameResults[a.playerID] > gameResults[b.playerID];
    });

    Vector2D initialPos(-200, 100);
    for (const auto& it: players) {
        ducksGUI.emplace_back(
                std::make_shared<DuckResultItemGUI>(initialPos, it, gameResults[it.playerID]));
        initialPos += Vector2D::Down() * 80;
    }
}

void GameStatusScreen::InitRun() {
    if (!btnBack.GetVisible()) {
        timer.Start();
    }
}

void GameStatusScreen::TakeInput(SDL_Event event) {
    ButtonsManager::GetInstance().HandleEvent(event, cam);
}
void GameStatusScreen::Update(float deltaTime) {
    timer.Update(deltaTime);
    GUIManager::GetInstance().Draw(cam);
}
