#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player(ResourceManager& resourceManager, float x, float y, const std::string& texturePath)
    : Entity(resourceManager, x, y, texturePath) {}

void Player::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move(0, -deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move(0, deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move(-deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move(deltaTime, 0);

    hunger -= 5.f * deltaTime;
    if (hunger < 0) hunger = 0;
}

void Player::move(float dx, float dy) {
    sprite.move(dx * speed, dy * speed);
}