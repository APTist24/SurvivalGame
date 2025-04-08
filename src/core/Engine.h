#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "GameState.h"
#include "ResourceManager.h"

class Engine
{
public:
    Engine();
    
    ~Engine();
    
    void Init();
    
    void Run();
    
    void Shutdown();
    
    sf::RenderWindow& GetWindow() { return *m_window; }
    
    ResourceManager& GetResourcesManager() { return *m_res_manager; }

    // State Mach, temp here
    void ChangeState(std::unique_ptr<GameState> state);
    
    void PushState(std::unique_ptr<GameState> state);
    
    void PopState();

private:
    void CreateWindow();

    void InitResourceManager();

    void ProcessEvents();
    
    void Update();
    
    void Render();

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    
    std::unique_ptr<ResourceManager> m_res_manager;
    
    std::vector<std::unique_ptr<GameState>> m_states;
    
    bool m_is_running{false};
    
    sf::Clock m_game_clock;
    
    float m_delta_time { 0.0f };
};
