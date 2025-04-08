#include "Engine.h"
#include "../states/MainMenuState.h"
#include <iostream>

Engine::Engine() : m_is_running(false)
{
    std::cout << "Engine created" << std::endl;
}

Engine::~Engine()
{
    std::cout << "Engine destroyed" << std::endl;
}

void Engine::Init()
{
    CreateWindow();

    InitResourceManager();

    PushState(std::make_unique<MainMenuState>(*this));

    m_is_running = true;
    
    std::cout << "Engine initialized" << std::endl;
}

void Engine::Run()
{
    std::cout << "Engine running" << std::endl;

    while (m_is_running && m_window->isOpen())
    {
        m_delta_time = m_game_clock.restart().asSeconds();

        ProcessEvents();
        Update();
        Render();
    }
}

void Engine::Shutdown()
{
    for (const auto& state : m_states)
    {
        state->onExit();
    }
    m_states.clear();
    
    if (m_window && m_window->isOpen())
    {
        m_window->close();
    }

    std::cout << "Engine Shutdown" << std::endl;
}

void Engine::ProcessEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        // Глобальные события
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
            m_is_running = false;
        }

        // События текущего состояния
        if (!m_states.empty())
        {
            m_states.back()->handleEvent(event);
        }
    }
}

void Engine::Update()
{
    if (!m_states.empty())
    {
        m_states.back()->update(m_delta_time);
    }
    else
    {
        m_is_running = false;
    }
}

void Engine::Render()
{
    m_window->clear(sf::Color(50, 50, 50));

    // Рендеринг состояний (от нижнего к верхнему)
    if (!m_states.empty())
    {
        for (auto& state : m_states)
        {
            state->render(*m_window);
        }
    }

    m_window->display();
}

void Engine::ChangeState(std::unique_ptr<GameState> state)
{
    if (!m_states.empty())
    {
        m_states.back()->onExit(); // Вызываем onExit для текущего состояния
        m_states.pop_back();
    }
    m_states.push_back(std::move(state));
    m_states.back()->onEnter(); // Вызываем onEnter для нового состояния
}

void Engine::PushState(std::unique_ptr<GameState> state)
{
    m_states.push_back(std::move(state));
    if (!m_states.empty())
    {
        m_states.back()->onEnter(); // Вызываем onEnter для нового состояния
    }
}

void Engine::PopState()
{
    if (!m_states.empty())
    {
        m_states.back()->onExit(); // Вызываем onExit перед удалением
        m_states.pop_back();
    }
}

void Engine::CreateWindow()
{
    constexpr auto WINDOW_NAME = "Survival Roguelike";
    constexpr auto WINDOW_WIDTH = 1280;
    constexpr auto WINDOW_HEIGHT = 720;

    m_window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        WINDOW_NAME,
        sf::Style::Titlebar | sf::Style::Close
    );
    m_window->setFramerateLimit(60);
}

void Engine::InitResourceManager()
{
    m_res_manager = std::make_unique<ResourceManager>();
    
    m_res_manager->loadResources();
}
