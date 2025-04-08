#pragma once
#include <core/ResourceManager.h>
#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity() = delete;
    Entity(ResourceManager& resourceManager, float x, float y, const std::string& texturePath);
    virtual ~Entity() = default;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;

protected:
    sf::Sprite sprite;
    float health = 100.f;
};