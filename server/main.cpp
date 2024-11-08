
#include <iostream>
#include <string>
#include <utility>

#include "../data/snapshot.h"
#include "common/Vector2D.h"
#include "model/Game.h"

#include "messageSender.h"

int main() {
    // TestMoveRightAndFall();
    // TestMoveRightCollidingWithBoundsMap();

    Socket s = Socket("8080");
    ServerProtocol serv(std::move(s));
    serv.saludar();
    MatchExitSender exit(1);
    exit.Saludar();
    exit.execute(serv);

    return 0;
}


void MostrarEvento(const PlayerEvent& e) {
    std::string flipping = (e.flipping == Flip::Left) ? "Left" : "Right";
    std::string state = "Idle";
    if (e.stateTransition == DuckState::JUMPING) {
        state = "jumping";
    }
    if (e.stateTransition == DuckState::FALLING) {
        state = "falling";
    }
    if (e.stateTransition == DuckState::RUNNING) {
        state = "running";
    }
    std::cout << "---> POSITION: (" << e.motion.x << "," << e.motion.y << ")\n";
    std::cout << "---> FLIPPING: " << flipping << "\n";
    std::cout << "---> STATE: " << state << "\n";
}

void MostrarSnapshot(GameWorld& game) {
    float deltaTime = 0.04f;
    game.Update(deltaTime);
    Snapshot s = game.GetSnapshot();
    std::unordered_map<PlayerID_t, PlayerEvent> events = s.updates;
    for (const auto& pair: events) {
        std::cout << "se registrò 1 evento proveniente de [" << pair.first
                  << "]. Los datos fueron:\n";
        MostrarEvento(pair.second);
    }
}


Command Left(bool keyDown = true, PlayerID_t playerId = 1) {
    CommandCode code = (keyDown) ? CommandCode::MoveLeft_KeyDown : CommandCode::MoveLeft_KeyUp;
    return Command(code, playerId);
}

Command Right(bool keyDown = true, PlayerID_t playerId = 1) {
    CommandCode code = (keyDown) ? CommandCode::MoveRight_KeyDown : CommandCode::MoveRight_KeyUp;
    return Command(code, playerId);
}


void TestMoveRightCollidingWithBoundsMap() {
    GameWorld game = GameWorld(Vector2D(48, -6));

    std::cout << "\n1: INICIAL\n";
    MostrarSnapshot(game);

    std::cout << "\n2: Sin evento\n";
    MostrarSnapshot(game);

    std::cout << "\n3: Sin evento\n";
    MostrarSnapshot(game);

    std::cout << "\n4: Se mueve a derecha (deberìa chocar)\n";
    game.HandleCommand(Right());
    MostrarSnapshot(game);


    std::cout << "\n5: sigue chocandose\n";
    MostrarSnapshot(game);
    std::cout << "\n6: sigue chocandose\n";
    MostrarSnapshot(game);

    std::cout << "\n7: deja de moverse a derecha\n";
    game.HandleCommand(Right(false));
    MostrarSnapshot(game);

    std::cout << "\n8: quieto\n";
    MostrarSnapshot(game);
}

void TestMoveRightAndFall() {
    GameWorld game = GameWorld(Vector2D(16, -13));
    std::cout << "\n1: INICIAL (por default, todos nacen mirando a derecha con state IDLE)\n";
    MostrarSnapshot(game);

    std::cout << "\n2: Sin evento\n";
    MostrarSnapshot(game);

    std::cout << "\n3: Sin evento\n";
    MostrarSnapshot(game);

    std::cout << "\n4: Se mueve a derecha (en algun punto debe caer...)\n";
    game.HandleCommand(Right());
    MostrarSnapshot(game);


    std::cout << "\n5: quizàs cae\n";
    MostrarSnapshot(game);
    std::cout << "\n6: quizàs cae\n";
    MostrarSnapshot(game);

    std::cout << "\n7:\n";
    MostrarSnapshot(game);

    std::cout << "\n8:\n";
    MostrarSnapshot(game);

    std::cout << "\n9:\n";
    MostrarSnapshot(game);

    std::cout << "\n10: deja de moverse a derecha\n";
    game.HandleCommand(Right(false));
    MostrarSnapshot(game);

    std::cout << "\n11:\n";
    MostrarSnapshot(game);

    std::cout << "\n12:\n";
    MostrarSnapshot(game);
}
