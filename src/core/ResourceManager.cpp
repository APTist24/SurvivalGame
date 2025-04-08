#include "ResourceManager.h"
#include <iostream>
#include <stdexcept>

ResourceManager::ResourceManager() {
    std::cout << "ResourceManager created" << std::endl;
}

ResourceManager::~ResourceManager() {
    std::cout << "ResourceManager destroyed" << std::endl;
}

void ResourceManager::loadResources() {
    // Создаем встроенный шрифт, если не можем загрузить шрифт из файла
    auto font = std::make_unique<sf::Font>();
    bool fontLoaded = false;
    
    try {
        // Пытаемся загрузить шрифт из файла
        if (font->loadFromFile(fontsPath + "arial.ttf")) {
            fontLoaded = true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to load font from file: " << e.what() << std::endl;
    }
    
    // Если не удалось загрузить шрифт из файла, используем встроенный
    if (!fontLoaded) {
        // Установка шрифта по умолчанию - просто заглушка
        std::cout << "Using default font" << std::endl;
        // Создаем пустой шрифт (в реальном приложении, вы могли бы включить шрифт в ресурсы)
        fonts["main"] = std::move(font);
    } else {
        fonts["main"] = std::move(font);
    }
    
    // Загрузка текстур (заполнить по мере создания игры)
    try {
        // Здесь будет загрузка текстур
    } catch (const std::exception& e) {
        std::cerr << "Failed to load texture: " << e.what() << std::endl;
    }
    
    // Загрузка звуков временно отключена
    /*
    try {
        // Здесь будет загрузка звуков
    } catch (const std::exception& e) {
        std::cerr << "Failed to load sound: " << e.what() << std::endl;
    }
    */
    
    std::cout << "Resources loaded" << std::endl;
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it == textures.end()) {
        throw std::runtime_error("Texture not found: " + name);
    }
    return *it->second;
}

void ResourceManager::addTexture(const std::string& name, const std::string& filename) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(texturesPath + filename)) {
        throw std::runtime_error("Failed to load texture: " + texturesPath + filename);
    }
    textures[name] = std::move(texture);
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    auto it = fonts.find(name);
    if (it == fonts.end()) {
        throw std::runtime_error("Font not found: " + name);
    }
    return *it->second;
}

void ResourceManager::addFont(const std::string& name, const std::string& filename) {
    auto font = std::make_unique<sf::Font>();
    if (!font->loadFromFile(fontsPath + filename)) {
        throw std::runtime_error("Failed to load font: " + fontsPath + filename);
    }
    fonts[name] = std::move(font);
}

// Звуковые методы временно отключены
/*
sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name) {
    auto it = soundBuffers.find(name);
    if (it == soundBuffers.end()) {
        throw std::runtime_error("Sound buffer not found: " + name);
    }
    return *it->second;
}

void ResourceManager::addSoundBuffer(const std::string& name, const std::string& filename) {
    auto soundBuffer = std::make_unique<sf::SoundBuffer>();
    if (!soundBuffer->loadFromFile(soundsPath + filename)) {
        throw std::runtime_error("Failed to load sound: " + soundsPath + filename);
    }
    soundBuffers[name] = std::move(soundBuffer);
}
*/