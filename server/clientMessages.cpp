#include "clientMessages.h"

#include <utility>

/********************** IMPLEMENTATION OF MATCH START SETTING MSSG ******************************/
MatchStartSettings::MatchStartSettings(SafeMap<PlayerID_t, PlayerInfo>& players, int numberSkins,
                                       Vector2D duckSize):
        duckSize(duckSize) {
    if (players.size() > numberSkins) {
        throw std::runtime_error(
                "ERROR: A unique assignment of skins to players cannot be made. Too many players");
    }
    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numberSkins - 1);

    players.applyToItems([this, &gen, &dis](PlayerID_t playerID, PlayerInfo& playerInfo) {
        int skinIndx;
        do {
            skinIndx = dis(gen);
        } while (skinsAssignation.find(skinIndx) != skinsAssignation.end());
        skinsAssignation[skinIndx] = std::make_tuple(playerID, playerInfo.nickName);
    });
}
// construyo un matchStartSetting y se lo regalo (move semantics) al protocolo para que lo envie
// aqui se deberìa enviar un MatchStartSettingsDto
void MatchStartSettings::sendMyself(ServerProtocol& protocol) const {
    MatchStartSettingsDto dto((int)skinsAssignation.size(), duckSize);
    int i = 0;
    for (auto it = skinsAssignation.begin(); it != skinsAssignation.end(); ++it) {
        std::tie(dto.playerIDs[i], dto.playerNicknames[i]) = it->second;
        dto.playerSkins[i] = it->first;
        i++;
    }
    protocol.sendMatchStartSettings(std::move(dto));
}

/*********************** IMPLEMENTATION OF GAME START SETTINGS MSSG ***************************/
// It is sending the plataforms , el nombre del tema,
// estoy guardandome en esta estructura en el heap una referencia a la plataformas con las que
// trabaja el mundo ademàs
// cppcheck-suppress passedByValue
GameStartSettings::GameStartSettings(std::string theme, std::vector<Transform> platforms):
        theme(theme), platforms(platforms) {}

void GameStartSettings::sendMyself(ServerProtocol& protocol) const {
    // construyo un dto que sea totalmente independiente de la existencia de este objeto
    GameStartSettingsDto dto(theme, platforms);
    protocol.sendGameStartSettings(std::move(dto));
    return;
}

/*********************** IMPLEMENTATION OF GAME UPDATE MSSG ***************************/
// en el caso en que el gameWorld si me de una copia del snapdhoot original (que irà editando)
GameUpdate::GameUpdate(Snapshot snapshot): snapshot(snapshot) {}

void GameUpdate::sendMyself(ServerProtocol& protocol) const {
    protocol.sendGameUpdate(snapshot);
    return;
}

// /************************ IMPLEMENTATION OF GAMES RECOUNT MSSG *****************************/

// cppcheck-suppress passedByValue
GamesRecount::GamesRecount(std::unordered_map<PlayerID_t, int> results, bool matchEnded):
        results(results), matchEnded(matchEnded) {}

void GamesRecount::sendMyself(ServerProtocol& protocol) const {
    GamesRecountDto dto(matchEnded, results);
    protocol.sendGamesRecount(std::move(dto));
    return;
}

/************************ IMPLEMENTATION OF MATCH RESULT MSSG *****************************/
MatchResult::MatchResult(PlayerID_t finalWinner): finalWinner(finalWinner) {}

void MatchResult::sendMyself(ServerProtocol& protocol) const {
    protocol.sendMatchWinner(finalWinner);
    protocol.endConnection();
    return;
}
