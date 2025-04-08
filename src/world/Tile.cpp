#include "Tile.h"

namespace
{
    constexpr auto TILE_SIZE = 32.f;
}

Tile::Tile(TileType type, float x, float y) : type(type) {
    shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setPosition(x, y);
    
    switch (type) {
        case TileType::Grass:
            shape.setFillColor(sf::Color::Green);
            break;
        case TileType::Stone:
            shape.setFillColor(sf::Color(128, 128, 128));
            break;
        case TileType::Water:
            shape.setFillColor(sf::Color::Blue);
            break;
    }
}

void Tile::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}