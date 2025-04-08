#include "ResourceManager.h"
#include <iostream>
#include <stdexcept>

ResourceManager::ResourceManager()
{
    std::cout << "ResourceManager created" << std::endl;
}

ResourceManager::~ResourceManager()
{
    std::cout << "ResourceManager destroyed" << std::endl;
}

void ResourceManager::loadResources()
{
    // Загрузка шрифта
    auto font = std::make_unique<sf::Font>();
    std::string fontPath = "C:/sources/SurvivalGame/build/src/Debug/resources/fonts/arial.ttf";
    if (!font->loadFromFile(fontPath))
    {
        std::cerr << "Failed to load font " << fontPath << std::endl;
        std::cout << "Using default font" << std::endl;
    }
    else
    {
        std::cout << "Font loaded successfully from " << fontPath << std::endl;
    }
    fonts["main"] = std::move(font);

    // Загрузка текстуры игрока
    try
    {
        addTexture("player", "player.png"); // Используем "player" как ключ
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        // Создаем пустую текстуру как fallback
        auto fallbackTexture = std::make_unique<sf::Texture>();
        if (fallbackTexture->create(32, 32))
        {
            // Простой квадрат 32x32
            textures["player"] = std::move(fallbackTexture);
            std::cout << "Created fallback texture for player" << std::endl;
        }
    }

    std::cout << "Resources loaded" << std::endl;
}

sf::Texture& ResourceManager::getTexture(const std::string& name)
{
    auto it = textures.find(name);
    if (it == textures.end())
    {
        throw std::runtime_error("Texture not found: " + name);
    }
    return *it->second;
}

void ResourceManager::addTexture(const std::string& name, const std::string& filename)
{
    auto texture = std::make_unique<sf::Texture>();
    std::string fullPath = "C:/sources/SurvivalGame/build/src/Debug/resources/textures/player.png";
    std::cout << "Trying to load texture from: " << fullPath << std::endl;
    if (!texture->loadFromFile(fullPath))
    {
        throw std::runtime_error("Failed to load texture: " + fullPath);
    }
    textures[name] = std::move(texture);
}

sf::Font& ResourceManager::getFont(const std::string& name)
{
    auto it = fonts.find(name);
    if (it == fonts.end())
    {
        throw std::runtime_error("Font not found: " + name);
    }
    return *it->second;
}

void ResourceManager::addFont(const std::string& name, const std::string& filename)
{
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(fontsPath + filename))
    {
        throw std::runtime_error("Failed to load font: " + fontsPath + filename);
    }
    fonts[name] = std::move(font);
}
