#include "Entity.h"

Entity::Entity(ResourceManager& resourceManager, float x, float y, const std::string& texturePath) {
    sprite.setTexture(resourceManager.getTexture(texturePath));
    sprite.setPosition(x, y);
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}