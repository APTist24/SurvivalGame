#pragma once
#include "../core/GameState.h"
#include "../entities/Player.h"
#include "../world/World.h"

class GameplayState : public GameState {
public:
    GameplayState(Engine& engine);
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;

private:
    Player player;
    World world;
};