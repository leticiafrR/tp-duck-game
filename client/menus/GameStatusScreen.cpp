#include "GameStatusScreen.h"

DuckResultItemGUI::DuckResultItemGUI(Vector2D pos, GUIManager& guiManager,
                                     const PlayerData& playerData, DuckData duckData, int count) {
    guiManager
            .CreateImage(RectTransform(pos, Vector2D(70, 70)), 20, duckData.file,
                         DUCK_SKIN_COLORS.at(playerData.playerSkin))
            ->SetSourceRect(duckData.frames["head"][0]);

    guiManager.CreateText(RectTransform(Vector2D(pos.x + 50, pos.y), Vector2D(300, 150),
                                        Vector2D(0.5, 0.5), Vector2D(0, 0.5)),
                          20, playerData.nickname, 30);

    guiManager.CreateText(RectTransform(Vector2D(pos.x + 390, pos.y), Vector2D(150, 150),
                                        Vector2D(0.5, 0.5), Vector2D(0, 0.5)),
                          20, std::to_string(count), 35);
}

DuckResultItemGUI::~DuckResultItemGUI() = default;


GameStatusScreen::GameStatusScreen(Camera& cam, ResourceManager& resource, bool& wasClosed,
                                   vector<PlayerData> players,
                                   unordered_map<PlayerID_t, int> gameResults, DuckData duckData,
                                   std::optional<PlayerData> winner):
        BaseScreen(cam, resource, wasClosed), timer(3.0f, [this]() { running = false; }) {

    guiManager.CreateImage(RectTransform(Vector2D::Zero(), Vector2D(2000, 2000)), 0,
                           ColorExtension::Black());

    Text* txtTitle = guiManager.CreateText(
            RectTransform(Vector2D(0, -130), Vector2D(800, 120), Vector2D(0.5, 1)), 11, "", 40);

    btnBack = guiManager.CreateButton(
            RectTransform(Vector2D(60, -60), Vector2D(70, 70), Vector2D(0, 1)), 11,
            [this]() {
                running = false;
                audioPlayer.PlayButtonSFX();
            },
            BACK_BUTTON_FILE, ColorExtension::White());

    if (winner.has_value()) {
        txtTitle->SetText("The winner is: " + winner.value().nickname);
        btnBack->SetActive(true);
    } else {
        txtTitle->SetText("Game status");
        btnBack->SetActive(false);
    }

    InitPlayersDisplay(players, gameResults, duckData);
}

GameStatusScreen::~GameStatusScreen() = default;

void GameStatusScreen::InitPlayersDisplay(vector<PlayerData> players,
                                          unordered_map<PlayerID_t, int> gameResults,
                                          DuckData duckData) {
    std::sort(players.begin(), players.end(), [&gameResults](PlayerData a, PlayerData b) {
        return gameResults[a.playerID] > gameResults[b.playerID];
    });

    Vector2D initialPos(-200, 100);
    for (const auto& it: players) {
        ducksGUI.emplace_back(initialPos, guiManager, it, duckData, gameResults[it.playerID]);
        initialPos += Vector2D::Down() * 80;
    }
}

void GameStatusScreen::InitRun() {
    if (!btnBack->GetVisible()) {
        timer.Start();
    }
}

void GameStatusScreen::TakeInput(SDL_Event event) { guiManager.HandleEvent(event, cam); }
void GameStatusScreen::Update(float deltaTime) {
    timer.Update(deltaTime);
    guiManager.Draw(cam);
}
