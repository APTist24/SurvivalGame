#pragma once

#include <SFML/Graphics.hpp>

enum class TileType {
    Grass,
    Stone,
    Water
};

class Tile {
public:
    Tile(TileType type, float x, float y);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape;
    TileType type;
};