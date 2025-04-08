#include "Engine.h"
#include "../states/MainMenuState.h"
#include <iostream>

Engine::Engine() : isRunning(false) {
    std::cout << "Engine created" << std::endl;
}

Engine::~Engine() {
    std::cout << "Engine destroyed" << std::endl;
}

void Engine::initialize() {
    // Создаем окно
    window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode(windowWidth, windowHeight),
        windowTitle,
        sf::Style::Titlebar | sf::Style::Close
    );
    window->setFramerateLimit(60);

    // Инициализируем менеджер ресурсов
    resourceManager = std::make_unique<ResourceManager>();
    
    // Загружаем основные ресурсы
    resourceManager->loadResources();
    
    // Устанавливаем начальное состояние
    pushState(std::make_unique<MainMenuState>(*this));
    
    isRunning = true;
    std::cout << "Engine initialized" << std::endl;
}

void Engine::run() {
    std::cout << "Engine running" << std::endl;
    
    while (isRunning && window->isOpen()) {
        deltaTime = gameClock.restart().asSeconds();
        
        processEvents();
        update();
        render();
    }
}

void Engine::shutdown() {
    // Очищаем состояния
    states.clear();
    
    // Закрываем окно
    if (window && window->isOpen()) {
        window->close();
    }
    
    std::cout << "Engine shutdown" << std::endl;
}

void Engine::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        // Глобальные события
        if (event.type == sf::Event::Closed) {
            window->close();
            isRunning = false;
        }
        
        // События текущего состояния
        if (!states.empty()) {
            states.back()->handleEvent(event);
        }
    }
}

void Engine::update() {
    if (!states.empty()) {
        states.back()->update(deltaTime);
    } else {
        isRunning = false;
    }
}

void Engine::render() {
    window->clear(sf::Color(50, 50, 50));
    
    // Рендеринг состояний (от нижнего к верхнему)
    if (!states.empty()) {
        for (auto& state : states) {
            state->render(*window);
        }
    }
    
    window->display();
}

void Engine::changeState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        states.pop_back();
    }
    states.push_back(std::move(state));
}

void Engine::pushState(std::unique_ptr<GameState> state) {
    states.push_back(std::move(state));
}

void Engine::popState() {
    if (!states.empty()) {
        states.pop_back();
    }
}