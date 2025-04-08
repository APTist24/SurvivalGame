#pragma once

#include "../core/GameState.h"
#include "../core/Engine.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include <string>

class MainMenuState : public GameState {
public:
    MainMenuState(Engine& engine);
    
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    
    void onEnter() override;
    void onExit() override;

private:
    struct MenuItem {
        sf::Text text;
        std::function<void()> action;
    };
    
    std::vector<MenuItem> menuItems;
    int selectedIndex;
    
    sf::Text titleText;
    sf::RectangleShape background;
    
    void initMenuItems();
    void updateMenuItems();
    void startGame();
    void openOptions();
    void exitGame();
};