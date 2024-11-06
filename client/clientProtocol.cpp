#include "clientProtocol.h"

ClientProtocol::ClientProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

void ClientProtocol::sendNickname(const std::string& nickname) {
    assistant.sendNumber(NICKNAME);
    assistant.sendString(nickname);
}

bool ClientProtocol::receiveStateOfJoining() {
    if (assistant.receiveNumberOneByte() == RESULT_JOINING) {
        uint8_t response = assistant.receiveNumberOneByte();
        if (response == (uint8_t)1)
            return true;
        else if (response == (uint8_t)0)
            return false;
    }
    throw BrokenProtocol();
}

MatchStartDto ClientProtocol::receiveMachStartDto() {
    if (assistant.receiveNumberOneByte() == MATCH_STARTING) {
        // debo de recibir un vector de PlayerData
        auto numberPlayers = assistant.receiveNumberOneByte();
        std::vector<PlayerData> playersData((size_t)numberPlayers);
        for (uint8_t i = 0; i < numberPlayers; i++) {
            // recibimos los datos de cada Player y construimos PlayersData
            auto ID = assistant.receiveNumberFourBytes();
            auto nickname = assistant.receiveString();
            auto numberSkin = assistant.receiveNumberOneByte();
            playersData[i] = PlayerData{ID, numberSkin, std::move(nickname)};
        }
        Vector2D duckSize = assistant.receiveVector2D();

        return MatchStartDto{std::move(playersData), std::move(duckSize)};
    }
    throw BrokenProtocol();
}

GameSceneDto ClientProtocol::receiveGameSceneDto() {
    if (assistant.receiveNumberOneByte() == GAME_SCENE) {
        auto theme = assistant.receiveString();

        // receiving the vector of transforms of the platforms
        auto numberPlatforms = assistant.receiveNumberOneByte();
        std::vector<Transform> platforms(numberPlatforms);
        for (uint8_t i = 0; i < numberPlatforms; i++) {
            // recibimos cada uno de los Transforms
            Vector2D size = assistant.receiveVector2D();
            Vector2D pos = assistant.receiveVector2D();
            platforms[i] = Transform(pos, size);
        }

        // receiving the vector of GroundDto's of the groundBlocks
        auto numberGroundB = assistant.receiveNumberOneByte();
        std::vector<GroundDto> groundBlocks(numberGroundB);
        for (uint8_t i = 0; i < numberGroundB; i++) {
            // receiving the visible edges
            std::set<VISIBLE_EDGES> edges;
            auto bttm_tp = assistant.receiveNumberOneByte();
            if (bttm_tp == V_BTTM_TOP::BOTH_TB || bttm_tp == V_BTTM_TOP::TOP)
                edges.insert(VISIBLE_EDGES::TOP);

            if (bttm_tp == V_BTTM_TOP::BOTH_TB || bttm_tp == V_BTTM_TOP::BTTM)
                edges.insert(VISIBLE_EDGES::BOTTOM);

            auto rg_lf = assistant.receiveNumberOneByte();
            if (rg_lf == V_RG_LF::BOTH_RL || rg_lf == V_RG_LF::RG)
                edges.insert(VISIBLE_EDGES::RIGHT);

            if (rg_lf == V_RG_LF::BOTH_RL || rg_lf == V_RG_LF::LF)
                edges.insert(VISIBLE_EDGES::LEFT);

            // receiving the data of their transforms
            auto size = assistant.receiveVector2D();
            auto pos = assistant.receiveVector2D();
            Transform transform(pos, size);

            // building the GroundDto
            groundBlocks[i] = GroundDto{std::move(transform), std::move(edges)};
        }
        return GameSceneDto{theme, platforms, groundBlocks};
    }
    throw BrokenProtocol();
}

Snapshot ClientProtocol::receiveGameUpdateDto() {
    if (assistant.receiveNumberOneByte() == SNAPSHOT) {
        // game is over?
        auto gameOverCode = assistant.receiveNumberOneByte();
        if (gameOverCode != 1 && gameOverCode != 0)
            throw BrokenProtocol();
        bool gameOver = gameOverCode == 1 ? true : false;

        // receiving the cont of the map player ID and position vector
        std::unordered_map<PlayerID_t, PlayerEvent> updates;
        uint8_t numberUpdates = assistant.receiveNumberOneByte();
        for (uint8_t i = 0; i < numberUpdates; i++) {
            // playerID
            auto ID = assistant.receiveNumberFourBytes();
            // PlayerEvent
            auto evMotion = assistant.receiveVector2D();
            auto evState = (DuckState)assistant.receiveNumberOneByte();
            auto evFlip = (Flip)assistant.receiveNumberOneByte();
            // building PlayerEvent
            updates[ID] = PlayerEvent{evMotion, evState, evFlip};
        }
        return Snapshot(gameOver, updates);
    }
    throw BrokenProtocol();
}

GamesRecountDto ClientProtocol::receiveGamesRecountDto() {
    if (assistant.receiveNumberOneByte() == GAMES_RECOUNT) {
        auto matchEndedCode = assistant.receiveNumberOneByte();
        if (matchEndedCode != 1 && matchEndedCode != 0)
            throw BrokenProtocol();
        bool matchEnded = matchEndedCode == 1 ? true : false;
        // receiving the map of games won by each player
        std::unordered_map<PlayerID_t, int> results;
        auto numberElements = assistant.receiveNumberOneByte();
        for (uint8_t i = 0; i < numberElements; i++) {
            auto id = assistant.receiveNumberFourBytes();
            auto count = assistant.receiveNumberOneByte();
            results[id] = (int)count;
        }
        return GamesRecountDto(matchEnded, std::move(results));
    }
    throw BrokenProtocol();
}

PlayerID_t ClientProtocol::receiveMatchWinner() {
    if (assistant.receiveNumberOneByte() == END_MATCH) {
        return assistant.receiveNumberFourBytes();
    }
    throw BrokenProtocol();
}

void ClientProtocol::sendCommand(Command cmmd) {
    assistant.sendNumber(COMMAND);
    assistant.sendNumber((uint8_t)cmmd.cmd);
}

void ClientProtocol::endConnection() {
    skt.shutdown(1);
    skt.close();
}
