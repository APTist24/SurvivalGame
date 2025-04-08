#include "GameplayState.h"
#include "../core/Engine.h"
#include <iostream>

GameplayState::GameplayState(Engine& engine)
    : GameState(engine),
      player(engine.GetResourcesManager(), 100.f, 100.f, "player"),  // "player" вместо "player.png"
      world(25, 19)
{
    world.generate();
}

void GameplayState::onEnter() {
    std::cout << "Вход в игровой процесс" << std::endl;
}

void GameplayState::onExit() {
    std::cout << "Выход из игрового процесса" << std::endl;
}

void GameplayState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        engine.PopState();
    }
}

void GameplayState::update(float deltaTime) {
    player.update(deltaTime);
}

void GameplayState::render(sf::RenderWindow& window) {
    world.draw(window);
    player.draw(window);
}