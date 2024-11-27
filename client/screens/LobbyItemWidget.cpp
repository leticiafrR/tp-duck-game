#include "LobbyItemWidget.h"

LobbyItemWidget::LobbyItemWidget(int id, const string& ownerName, int playerCount,
                                 int maxPlayersCount, CallbackParam<int> onJoin):
        lobbyId(id),
        matchConentImage(
                RectTransform(Transform(Vector2D(0, 0), Vector2D(900, 120)), Vector2D(0.5, 1)),
                Color(160, 160, 160), 0),
        matchOwnerText(
                ownerName + " lobby", 30,
                RectTransform(Transform(Vector2D(-280, 0), Vector2D(300, 120)), Vector2D(0.5, 1)),
                ColorExtension::White(), 1),
        matchPlayersText(
                "Players" + std::to_string(playerCount) + "/" + std::to_string(maxPlayersCount), 30,
                RectTransform(Transform(Vector2D(0, 0), Vector2D(180, 120)), Vector2D(0.5, 1)),
                ColorExtension::White(), 1),
        matchJoinButton(
                "button_1.png",
                RectTransform(Transform(Vector2D(280, 0), Vector2D(150, 80)), Vector2D(0.5, 1)),
                [this]() { this->onJoinClicked(this->lobbyId); }, Color(40, 40, 40), 1),
        matchJoinText(
                "Join", 30,
                RectTransform(Transform(Vector2D(280, 0), Vector2D(150, 80)), Vector2D(0.5, 1)),
                ColorExtension::White(), 2),
        onJoinClicked(onJoin) {}

LobbyItemWidget::~LobbyItemWidget() = default;

void LobbyItemWidget::MoveContent(Vector2D movement) {
    matchConentImage.GetRectTransform().Move(movement);

    matchOwnerText.GetRectTransform().Move(movement);
    matchPlayersText.GetRectTransform().Move(movement);

    matchJoinButton.GetRectTransform().Move(movement);
    matchJoinText.GetRectTransform().Move(movement);
}
