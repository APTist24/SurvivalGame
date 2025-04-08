#include "World.h"
#include <random>

World::World(int width, int height) : width(width), height(height) {
    generate();  // Генерируем карту сразу при создании
}

void World::generate() {
    map.clear();
    map.resize(height);  // Создаем нужное количество строк

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);  // Предположим, у нас 3 типа тайлов

    for (int y = 0; y < height; ++y) {
        map[y].reserve(width);  // Резервируем место для width тайлов
        for (int x = 0; x < width; ++x) {
            int type = dist(gen);
            map[y].emplace_back(static_cast<TileType>(type), x * 32.f, y * 32.f);  // Создаем тайл
        }
    }
}

void World::draw(sf::RenderWindow& window) {
    for (const auto& row : map) {
        for (const auto& tile : row) {
            tile.draw(window);
        }
    }
}