#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "GameState.h"
#include "ResourceManager.h"

class Engine {
public:
    Engine();
    ~Engine();

    void initialize();
    void run();
    void shutdown();
    
    // Геттеры для основных компонентов
    sf::RenderWindow& getWindow() { return *window; }
    ResourceManager& getResourceManager() { return *resourceManager; }
    
    // Управление состояниями
    void changeState(std::unique_ptr<GameState> state);
    void pushState(std::unique_ptr<GameState> state);
    void popState();

private:
    // Основные компоненты
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<ResourceManager> resourceManager;
    
    // Стек игровых состояний
    std::vector<std::unique_ptr<GameState>> states;
    
    // Настройки
    std::string windowTitle = "Survival Roguelike";
    int windowWidth = 1280;
    int windowHeight = 720;
    bool isRunning = false;
    
    // Управление временем
    sf::Clock gameClock;
    float deltaTime = 0.0f;
    
    void processEvents();
    void update();
    void render();
};