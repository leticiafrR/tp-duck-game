#include <iostream>
#include <string>

#include "model/Game.h"

Command Shoot(PlayerID_t id = 1) { return Command(CommandCode::UseItem_KeyDown, id); }
bool gameOver;
std::unordered_map<PlayerID_t, PlayerEvent> updates;
std::vector<InstantProjectileEventDto> raycastsEvents;

Vector2D motion;
DuckState stateTransition;
Flip flipping;

void ShowVector(const Vector2D& vector) { std::cout << "(" << vector.x << "," << vector.y << ")"; }
std::string State(const DuckState& d) {
    if (d == DuckState::DEAD) {
        return "dead";
    }
    if (d == DuckState::IDLE) {
        return "idle";
    }
    if (d == DuckState::FALLING) {
        return "falling";
    }
    if (d == DuckState::JUMPING) {
        return "jumping";
    }
    if (d == DuckState::WOUNDED) {
        return "wounded";
    }
    return "running";
}
std::string Flipping(Flip flipping) {
    if (flipping == Flip::Left) {
        return "left";
    }
    if (flipping == Flip::Right) {
        return "right";
    }
    return "up";
}
void ShowPlayerEvent(const PlayerEvent& event) {
    std::cout << "  [playerEvent] motion:";
    ShowVector(event.motion);
    std::cout << std::endl;
    std::cout << "  [playerEvent] duckState: " << State(event.stateTransition) << std::endl;
    std::cout << "  [playerEvent] duck Flip: " << Flipping(event.flipping) << std::endl;
}

void ShowPlayerEvents(const std::unordered_map<PlayerID_t, PlayerEvent>& updates) {
    for (auto pair: updates) {
        std::cout << "  [playerEvent] ID: " << pair.first << "\n";
        ShowPlayerEvent(pair.second);
    }
}

std::string TypeProjectileStr(const TypeProjectile& type) {
    if (type == TypeProjectile::BANANA) {
        return "banana";
    }
    if (type == TypeProjectile::BULLET) {
        return "bullet";
    }
    if (type == TypeProjectile::LASER) {
        return "Rayo laser";
    }
    return "projectile not reconized";
}


void ShowProjectileEvent(const InstantProjectileEventDto& e) {
    std::cout << "***[ProjectilesEvents] type: " << TypeProjectileStr(e.type) << std::endl;
    std::cout << "***[ProjectilesEvents] origin: ";
    ShowVector(e.origin);
    std::cout << std::endl;
    std::cout << "***[ProjectilesEvents] end: ";
    ShowVector(e.end);
    std::cout << std::endl;
}
void ShowProjectilesEvents(const std::vector<InstantProjectileEventDto>& raycastsEvents) {
    for (auto e: raycastsEvents) {
        ShowProjectileEvent(e);
    }
}
void ShowSnapshot(const Snapshot& s) {
    std::cout << "MOSTRANDO SNAPSHOT\n";
    std::cout << "-> isGamover: " << (gameOver ? "YES" : "NO") << std::endl;
    std::cout << "-> player events: " << std::endl;
    ShowPlayerEvents(s.updates);
    std::cout << "-> InstantProjectileEventDto: " << std::endl;
    ShowProjectilesEvents(s.raycastsEvents);
}

int main() {
    /* code */
    float deltaTime = 0.04f;
    GameWorld game(Vector2D(0, 13));
    game.Update(deltaTime);


    std::cout << "______[1] se handlea commando para disparar\n";
    game.HandleCommand(Shoot());
    game.Update(deltaTime);
    ShowSnapshot(game.GetSnapshot());


    return 0;
}
