#include "MainMenuState.h"
#include "../states/GameplayState.h"
#include "../core/Engine.h"
#include <iostream>

MainMenuState::MainMenuState(Engine& engine) : GameState(engine), selectedIndex(0) {
    std::cout << "MainMenuState created" << std::endl;
}

void MainMenuState::onEnter() {
    std::cout << "Entering main menu" << std::endl;
    
    // Настройка фона
    background.setSize(sf::Vector2f(engine.GetWindow().getSize()));
    background.setFillColor(sf::Color(20, 20, 40));
    
    // Настройка заголовка
    titleText.setFont(engine.GetResourcesManager().getFont("main"));
    titleText.setString("Survival Roguelike");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    
    // Центрирование заголовка
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    titleText.setPosition(
        engine.GetWindow().getSize().x / 2.0f,
        engine.GetWindow().getSize().y * 0.2f
    );
    
    // Инициализация пунктов меню
    initMenuItems();
}

void MainMenuState::onExit() {
    std::cout << "Exiting main menu" << std::endl;
}

void MainMenuState::initMenuItems() {
    menuItems.clear();
    
    // Получаем шрифт
    const sf::Font& font = engine.GetResourcesManager().getFont("main");
    
    // Создаем пункты меню с функциями обратного вызова
    MenuItem playItem;
    playItem.text.setFont(font);
    playItem.text.setString("Play");
    playItem.text.setCharacterSize(36);
    playItem.action = [this]() { startGame(); };
    
    MenuItem optionsItem;
    optionsItem.text.setFont(font);
    optionsItem.text.setString("Options");
    optionsItem.text.setCharacterSize(36);
    optionsItem.action = [this]() { openOptions(); };
    
    MenuItem exitItem;
    exitItem.text.setFont(font);
    exitItem.text.setString("Exit");
    exitItem.text.setCharacterSize(36);
    exitItem.action = [this]() { exitGame(); };
    
    // Добавляем пункты в меню
    menuItems.push_back(playItem);
    menuItems.push_back(optionsItem);
    menuItems.push_back(exitItem);
    
    // Позиционирование пунктов меню
    float yPos = engine.GetWindow().getSize().y * 0.4f;
    const float yOffset = 60.0f;
    
    for (auto& item : menuItems) {
        sf::FloatRect bounds = item.text.getLocalBounds();
        item.text.setOrigin(bounds.width / 2, bounds.height / 2);
        item.text.setPosition(engine.GetWindow().getSize().x / 2.0f, yPos);
        yPos += yOffset;
    }
    
    // Установка начального выбранного пункта
    selectedIndex = 0;
    updateMenuItems();
}

void MainMenuState::updateMenuItems() {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (i == selectedIndex) {
            menuItems[i].text.setFillColor(sf::Color::Yellow);
            menuItems[i].text.setStyle(sf::Text::Bold);
        } else {
            menuItems[i].text.setFillColor(sf::Color::White);
            menuItems[i].text.setStyle(sf::Text::Regular);
        }
    }
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex > 0) ? selectedIndex - 1 : menuItems.size() - 1;
            updateMenuItems();
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex < menuItems.size() - 1) ? selectedIndex + 1 : 0;
            updateMenuItems();
        } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
            if (selectedIndex >= 0 && selectedIndex < menuItems.size()) {
                menuItems[selectedIndex].action();
            }
        }
    }
}

void MainMenuState::update(float deltaTime) {
    // Анимации или другие обновления, если нужно
}

void MainMenuState::render(sf::RenderWindow& window) {
    std::cout << "Rendering MainMenuState" << std::endl;
    window.draw(background);
    window.draw(titleText);
    for (const auto& item : menuItems) {
        window.draw(item.text);
    }
}

void MainMenuState::startGame() {
    std::cout << "Запуск игры" << std::endl;
    engine.PushState(std::make_unique<GameplayState>(engine));
}

void MainMenuState::openOptions() {
    std::cout << "Opening options" << std::endl;
    // Здесь мы переходим в настройки
    // engine.PushState(std::make_unique<OptionsState>(engine));
    // Пока заглушка
    std::cout << "Options would open here (not implemented yet)" << std::endl;
}

void MainMenuState::exitGame() {
    std::cout << "Exiting game" << std::endl;
    engine.GetWindow().close();
}