#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class World {
    public:
        World(int width, int height);
        void generate();
        void draw(sf::RenderWindow& window);
    
    private:
        int width, height;
        std::vector<std::vector<Tile>> map;
    };