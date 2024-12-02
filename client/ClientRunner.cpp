#include "ClientRunner.h"

PlayerData ClientRunner::LoadWinner(Client& client, vector<PlayerData> players) {
    PlayerID_t winnerId;
    LoadingScreen loadingWinner(
            gameKit, wasClosed,
            [&client, &winnerId]() {
                shared_ptr<FinalWinner> msg;

                if (client.TryRecvNetworkMsg(msg)) {
                    winnerId = msg->winner;
                    return true;
                }
                return false;
            },
            "GETTING WINNER...");
    loadingWinner.Run();
    auto it = std::find_if(players.begin(), players.end(),
                           [&winnerId](PlayerData p) { return p.playerID == winnerId; });
    return *it;
}

void ClientRunner::LoadFinalGroup(Client& client, bool& isFinalGroup) {
    std::cout << "Waiting for final group"
              << "\n";
    LoadingScreen loadingFinalGroup(
            gameKit, wasClosed,
            [&isFinalGroup, &client]() {
                shared_ptr<FinalGroupGame> finalGroupData;

                if (client.TryRecvNetworkMsg(finalGroupData)) {
                    isFinalGroup = finalGroupData->finalGroupGame;
                    std::cout << "Received final group"
                              << "\n";
                    return true;
                }
                return false;
            },
            "LOADING...");
    loadingFinalGroup.Run();
}

void ClientRunner::LoadRoundResults(Client& client, bool& matchEnded,
                                    unordered_map<PlayerID_t, int>& results) {
    LoadingScreen matchEndedScreen(
            gameKit, wasClosed,
            [&client, &matchEnded, &results]() {
                shared_ptr<GamesRecountDto> recountData;
                if (client.TryRecvNetworkMsg(recountData)) {
                    matchEnded = recountData->matchEnded;
                    results = recountData->results;
                    return true;
                }
                return false;
            },
            "GETTING RESULTS");
    matchEndedScreen.Run();
}

void ClientRunner::PlayRound(Client& client, MatchStartDto matchData, bool isInitial) {
    shared_ptr<GameSceneDto> mapData = nullptr;
    shared_ptr<Snapshot> firstSnapshot = nullptr;

    LoadingScreen(
            gameKit, wasClosed,
            [&client, &mapData, &firstSnapshot]() {
                if (!mapData)
                    client.TryRecvNetworkMsg(mapData);
                if (mapData && !firstSnapshot)
                    client.TryRecvNetworkMsg(firstSnapshot);
                return mapData && firstSnapshot;
            },
            "LOADING...")
            .Run();
    Gameplay(client, gameKit, wasClosed, matchData, *mapData, *firstSnapshot, isInitial).Run();
}

void ClientRunner::ErrorScreen(const string& text) {
    LoadingScreen(
            gameKit, wasClosed, []() { return false; }, text)
            .Run();
}

void ClientRunner::ShowResultsScreen(std::optional<PlayerData> winner,
                                     const vector<PlayerData>& players,
                                     const unordered_map<PlayerID_t, int>& gameResults) {

    DuckData duckData = gameKit.GetResourceManager().GetDuckData();
    GameStatusScreen(gameKit, wasClosed, players, gameResults, duckData, winner).Run();
}

ClientRunner::ClientRunner(Renderer& render, int fps):
        cam(std::move(render), 70, Rate(fps)), wasClosed(false), gameKit(cam) {}

ClientRunner::~ClientRunner() = default;

void ClientRunner::KillClient(Client& client) {
    std::cout << "Esperando hilos\n";
    if (client.IsConnected())
        client.KillComunicationThreads();
    client.JoinCommunicationThreads();
    std::cout << "Hilos matados\n";
}

void ClientRunner::PlayConnected(Client& client) try {
    bool isOwner;
    MatchListScreen(gameKit, wasClosed, client, isOwner).Run();

    if (wasClosed) {
        KillClient(client);
        return;
    }

    shared_ptr<MatchStartDto> matchDataPtr;
    LobbyScreen(gameKit, wasClosed, client, isOwner, matchDataPtr).Run();

    if (wasClosed) {
        KillClient(client);
        return;
    }

    MatchStartDto matchData = *matchDataPtr;

    // AudioManager::GetInstance().PlayGameMusic();
    bool matchEnded = false;
    unordered_map<PlayerID_t, int> roundResults;
    bool isInitial = true;
    while (!matchEnded && !wasClosed) {
        PlayRound(client, matchData, isInitial);

        isInitial = false;

        bool isFinalGroup = false;
        LoadFinalGroup(client, isFinalGroup);

        while (!isFinalGroup && !wasClosed) {
            PlayRound(client, matchData, isInitial);
            LoadFinalGroup(client, isFinalGroup);
        }

        LoadRoundResults(client, matchEnded, roundResults);

        if (!matchEnded) {
            ShowResultsScreen(std::nullopt, matchData.playersData, roundResults);
        }

        if (wasClosed) {
            KillClient(client);
            return;
        }
    }
    // gameKit.GetAudioManager().StopMusic();

    std::optional<PlayerData> winner = LoadWinner(client, matchData.playersData);

    ShowResultsScreen(winner, matchData.playersData, roundResults);

    KillClient(client);

} catch (const ServerUnavailable& e) {
    std::cerr << e.what() << std::endl;
    KillClient(client);
    ErrorScreen("Can't connect to server, please try again later");
} catch (const ResourceUndefined& e) {
    std::cerr << e.what() << std::endl;
    KillClient(client);
    ErrorScreen("An error occurred while loading resources");
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    KillClient(client);
    ErrorScreen("An unexpected error occurred, please try again later");
}

void ClientRunner::Run() {
    string nickname;
    MenuScreen(gameKit, wasClosed, nickname).Run();
    if (wasClosed)
        return;

    try {
        Client client("8080", "localhost", nickname);
        PlayConnected(client);

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        ErrorScreen("An unexpected error occurred, please try again later");
    }
}
