#include "serverProtocol.h"
/*                  ---------PUBLIC METHODS---------                  */
ServerProtocol::ServerProtocol(Socket&& peer): skt(std::move(peer)), assistant(skt) {}

std::string ServerProtocol::receiveNickName() {
    if (assistant.receiveNumberOneByte() == NICKNAME) {
        return assistant.receiveString();
    }
    throw BrokenProtocol();
}
void ServerProtocol::sendLocalId(uint16_t connectionId) {
    assistant.sendNumber(IDENTIFICATION);
    assistant.sendNumber(connectionId);
}

MatchSelection ServerProtocol::receiveMatchSelection() {
    if (assistant.receiveNumberOneByte() == MATCH_SELECTION) {
        auto matchID = assistant.receiveNumberTwoBytes();
        if (matchID == 0) {
            MatchSelection refresh;
            return refresh;
        }
        auto playersPerConnection = assistant.receiveNumberOneByte();
        MatchSelection matchSelection(matchID, playersPerConnection);
        return matchSelection;
    }
    throw BrokenProtocol();
}

void ServerProtocol::sendAvailableMatches(const std::vector<DataMatch>& matches) {
    assistant.sendNumber(AVAILABLE_MATCHES);

    uint8_t numberMatches = (uint8_t)matches.size();
    assistant.sendNumber(numberMatches);

    for (uint8_t i = 0; i < numberMatches; i++) {
        assistant.sendNumber(matches[i].currentPlayers);
        assistant.sendNumber(matches[i].maxPlayers);
        assistant.sendNumber(matches[i].matchID);
        assistant.sendString(matches[i].creatorNickname);
    }
}

void ServerProtocol::sendResultOfJoining(uint8_t eCode) {
    assistant.sendNumber(RESULT_JOINING);
    assistant.sendNumber(eCode);
}

void ServerProtocol::receiveStartMatchIntention() {
    if (assistant.receiveNumberOneByte() != START_MATCH_INTENTION) {
        throw BrokenProtocol();
    }
}

void ServerProtocol::sendStartMatchResult(bool success) {
    assistant.sendNumber(RESULT_STARTING);
    assistant.sendBoolean(success);
}

void ServerProtocol::sendMatchStartSettings(const MatchStartDto& matchStartDto) {
    assistant.sendNumber(MATCH_STARTING_SETTINGS);

    // sending the quatity of players
    uint8_t numberPlayers = (uint8_t)matchStartDto.playersData.size();
    assistant.sendNumber(numberPlayers);
    // sending the data of each player
    for (uint8_t i = 0; i < numberPlayers; i++) {
        assistant.sendNumber(matchStartDto.playersData[i].playerID);
        assistant.sendString(matchStartDto.playersData[i].nickname);
        assistant.sendNumber((uint8_t)matchStartDto.playersData[i].playerSkin);
    }
    // sending a duck size (vector)
    assistant.sendVector2D(matchStartDto.duckSize);
    // probably latter this mssg will contain the size of other items
}

VISIBILITY_BOTTOM_TOP ServerProtocol::encodeVisibleBottomTopEdges(
        const std::set<VISIBLE_EDGES>& edges) {
    if (edges.find(VISIBLE_EDGES::TOP) == edges.end()) {
        if (edges.find(VISIBLE_EDGES::BOTTOM) == edges.end()) {
            return VISIBILITY_BOTTOM_TOP::NONE_TB;
        }
        return VISIBILITY_BOTTOM_TOP::BTTM;
    }
    if (edges.find(VISIBLE_EDGES::BOTTOM) == edges.end()) {
        return VISIBILITY_BOTTOM_TOP::TP;
    }
    return VISIBILITY_BOTTOM_TOP::BOTH_TB;
}

VISIBILITY_RIGTH_LEFT ServerProtocol::encodeVisibleRightLeftEdges(
        const std::set<VISIBLE_EDGES>& edges) {
    if (edges.find(VISIBLE_EDGES::LEFT) == edges.end()) {
        if (edges.find(VISIBLE_EDGES::RIGHT) == edges.end()) {
            return VISIBILITY_RIGTH_LEFT::NONE_RL;
        }
        return VISIBILITY_RIGTH_LEFT::RG;
    }
    if (edges.find(VISIBLE_EDGES::RIGHT) == edges.end()) {
        return VISIBILITY_RIGTH_LEFT::LF;
    }
    return VISIBILITY_RIGTH_LEFT::BOTH_RL;
}

void ServerProtocol::sendGameStartSettings(const GameSceneDto& gameSceneDto) {
    assistant.sendNumber(GAME_SCENE);
    // sending the theme of the game
    assistant.sendString(gameSceneDto.theme);

    // sending the groundBlocks
    uint8_t numbGroundBlocks = (uint8_t)gameSceneDto.groundBlocks.size();
    assistant.sendNumber(numbGroundBlocks);
    for (auto& groundDto: gameSceneDto.groundBlocks) {
        // sending data of the visible edges
        assistant.sendNumber(encodeVisibleBottomTopEdges(groundDto.visibleEdges));
        assistant.sendNumber(encodeVisibleRightLeftEdges(groundDto.visibleEdges));
        // sending data of the  transform
        assistant.sendVector2D(groundDto.mySpace.GetSize());
        assistant.sendVector2D(groundDto.mySpace.GetPos());
    }

    // sending the boxes points
    assistant.sendNumber((uint8_t)gameSceneDto.boxesPoints.size());
    for (auto it = gameSceneDto.boxesPoints.begin(); it != gameSceneDto.boxesPoints.end(); ++it) {
        assistant.sendNumber(it->first);
        assistant.sendVector2D(it->second);
    }
}

void ServerProtocol::sendGameEndingStatus(bool finalGroupGame) {
    assistant.sendNumber(GAME_ENDING);
    assistant.sendBoolean(finalGroupGame);
}

Command ServerProtocol::receiveCommand() {
    if (assistant.receiveNumberOneByte() == COMMAND) {
        auto commandCode = (CommandCode)assistant.receiveNumberOneByte();
        uint8_t indexLocalPlayer = assistant.receiveNumberOneByte();
        Command cmmd(commandCode, indexLocalPlayer);
        return cmmd;
    }
    throw BrokenProtocol();
}
void ServerProtocol::sendPlayerUpdates(const std::unordered_map<PlayerID_t, PlayerEvent>& updates) {
    assistant.sendNumber((uint8_t)updates.size());
    for (auto it = updates.begin(); it != updates.end(); ++it) {
        // playerID
        assistant.sendNumber(it->first);
        // PlayerEvent
        assistant.sendVector2D(it->second.motion);
        assistant.sendNumber((uint8_t)it->second.stateTransition);
        assistant.sendNumber((uint8_t)it->second.flipping);
        assistant.sendBoolean(it->second.isLookingUp);
        assistant.sendNumber((uint8_t)it->second.typeOnHand);
        assistant.sendBoolean(it->second.isCrouched);
        assistant.sendBoolean(it->second.cuacking);
        assistant.sendBoolean(it->second.hasArmor);
        assistant.sendBoolean(it->second.hasHelmet);
    }
}
void ServerProtocol::sendRaycastsEvents(const std::vector<ProjectileEventDto>& raycastsEvents) {
    uint8_t numberProjectiles = (uint8_t)raycastsEvents.size();
    assistant.sendNumber(numberProjectiles);
    for (auto it = raycastsEvents.begin(); it != raycastsEvents.end(); ++it) {
        assistant.sendNumber((uint8_t)it->type);
        assistant.sendVector2D(it->origin);
        assistant.sendVector2D(it->end);
    }
}
void ServerProtocol::sendCollectableDespawns(
        const std::vector<CollectableID_t>& collectableDespawns) {
    uint8_t numberDespawns = (uint8_t)collectableDespawns.size();
    assistant.sendNumber(numberDespawns);
    for (auto it = collectableDespawns.begin(); it != collectableDespawns.end(); ++it) {
        assistant.sendNumber((uint32_t)*it);
    }
}
void ServerProtocol::sendCollectableSpawns(
        const std::vector<CollectableSpawnEventDto>& collectableSpawns) {
    uint8_t numberSpawns = (uint8_t)collectableSpawns.size();
    assistant.sendNumber(numberSpawns);
    for (auto it = collectableSpawns.begin(); it != collectableSpawns.end(); ++it) {
        assistant.sendNumber((uint32_t)it->id);
        assistant.sendVector2D(it->position);
        assistant.sendNumber((uint8_t)it->type);
    }
}

void ServerProtocol::sendThrowableSpawns(
        const std::unordered_map<ThrowableID_t, ThrowableSpawnEventDto>& throwableSpawns) {
    assistant.sendNumber((uint8_t)throwableSpawns.size());
    for (auto it = throwableSpawns.begin(); it != throwableSpawns.end(); ++it) {
        // ThrowableID_t
        assistant.sendNumber(it->first);
        // ThrowableSpawnEventDto
        assistant.sendNumber((uint8_t)it->second.type);
        assistant.sendVector2D(it->second.position);
    }
}

void ServerProtocol::sendThrowableDespawns(const std::vector<ThrowableID_t>& throwableDespawns) {
    assistant.sendNumber((uint8_t)throwableDespawns.size());
    for (auto it = throwableDespawns.begin(); it != throwableDespawns.end(); ++it) {
        assistant.sendNumber((uint8_t)*it);
    }
}

void ServerProtocol::sendBoxesDespawns(const std::vector<BoxID_t>& boxesDespawns) {
    assistant.sendNumber((uint8_t)boxesDespawns.size());
    for (auto it = boxesDespawns.begin(); it != boxesDespawns.end(); ++it) {
        assistant.sendNumber((uint8_t)*it);
    }
}

void ServerProtocol::sendGameUpdate(const Snapshot& snapshot) {
    assistant.sendNumber(SNAPSHOT);
    assistant.sendBoolean(snapshot.gameOver);
    sendPlayerUpdates(snapshot.updates);

    sendRaycastsEvents(snapshot.raycastsEvents);

    sendCollectableDespawns(snapshot.collectableDespawns);
    sendCollectableSpawns(snapshot.collectableSpawns);

    sendThrowableSpawns(snapshot.throwableSpawns);
    sendThrowableDespawns(snapshot.throwableDespawns);
    sendBoxesDespawns(snapshot.boxesDespawns);
}

void ServerProtocol::sendGamesRecount(const GamesRecountDto& gamesRecount) {
    assistant.sendNumber(GAMES_RECOUNT);
    assistant.sendBoolean(gamesRecount.matchEnded);
    assistant.sendNumber((uint8_t)gamesRecount.results.size());
    for (auto it = gamesRecount.results.begin(); it != gamesRecount.results.end(); ++it) {
        assistant.sendNumber(it->first);
        assistant.sendNumber((uint8_t)it->second);
    }
}

void ServerProtocol::sendMatchWinner(PlayerID_t finalWinner) {
    assistant.sendNumber(END_MATCH);
    assistant.sendNumber(finalWinner);
}

void ServerProtocol::endConnection() {
    skt.shutdown(2);
    skt.close();
}
