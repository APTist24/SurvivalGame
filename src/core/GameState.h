#pragma once

#include <SFML/Graphics.hpp>

class Engine;

class GameState {
public:
    GameState(Engine& engine);
    virtual ~GameState() = default;
    
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    
    virtual void onEnter() {}
    virtual void onExit() {}

protected:
    Engine& engine;
};