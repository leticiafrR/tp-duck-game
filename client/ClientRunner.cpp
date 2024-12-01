#include "ClientRunner.h"

PlayerData ClientRunner::LoadWinner(Client& client, vector<PlayerData> players) {
    PlayerID_t winnerId;
    LoadingScreen loadingWinner(
            cam, wasClosed,
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
            cam, wasClosed,
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
            cam, wasClosed,
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
            cam, wasClosed,
            [&client, &mapData, &firstSnapshot]() {
                if (!mapData)
                    client.TryRecvNetworkMsg(mapData);
                if (mapData && !firstSnapshot)
                    client.TryRecvNetworkMsg(firstSnapshot);
                return mapData && firstSnapshot;
            },
            "LOADING...")
            .Run();
    Gameplay(client, cam, wasClosed, matchData, *mapData, *firstSnapshot, isInitial).Run();
}

void ClientRunner::ErrorScreen(const string& text) {
    LoadingScreen(
            cam, wasClosed, []() { return false; }, text)
            .Run();
}

void ClientRunner::ShowResultsScreen(std::optional<PlayerData> winner,
                                     const vector<PlayerData>& players,
                                     const unordered_map<PlayerID_t, int>& gameResults) {

    GameStatusScreen(cam, wasClosed, players, gameResults, winner).Run();
}

ClientRunner::ClientRunner(Renderer& render, int fps):
        cam(std::move(render), 70, Rate(fps)), wasClosed(false) {}

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
    MatchListScreen(cam, wasClosed, client, isOwner).Run();

    if (wasClosed) {
        KillClient(client);
        return;
    }

    shared_ptr<MatchStartDto> matchDataPtr;
    LobbyScreen(cam, wasClosed, client, isOwner, matchDataPtr).Run();

    if (wasClosed) {
        KillClient(client);
        return;
    }

    MatchStartDto matchData = *matchDataPtr;

    AudioManager::GetInstance().PlayGameMusic();
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
    AudioManager::GetInstance().StopMusic();

    std::optional<PlayerData> winner = LoadWinner(client, matchData.playersData);

    ShowResultsScreen(winner, matchData.playersData, roundResults);

    KillClient(client);

} catch (const ServerUnavailable& e) {
    std::cerr << e.what() << std::endl;
    client.JoinCommunicationThreads();
    ErrorScreen("Can't connect to server, please try again later");
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    client.JoinCommunicationThreads();
    ErrorScreen("An unexpected error occurred, please try again later");
}

void ClientRunner::Run() {
    string nickname;
    MenuScreen(cam, wasClosed, nickname).Run();
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
