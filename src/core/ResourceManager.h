#pragma once

#include <SFML/Graphics.hpp>
// Временно отключаем аудио
// #include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <memory>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();
    
    void loadResources();
    
    // Текстуры
    sf::Texture& getTexture(const std::string& name);
    void addTexture(const std::string& name, const std::string& filename);
    
    // Шрифты
    sf::Font& getFont(const std::string& name);
    void addFont(const std::string& name, const std::string& filename);
    
    // Звуки - временно отключены
    /*
    sf::SoundBuffer& getSoundBuffer(const std::string& name);
    void addSoundBuffer(const std::string& name, const std::string& filename);
    */

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
    // Временно отключаем аудио
    // std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers;
    
    // Пути к ресурсам
    std::string texturesPath = "resources/textures/";
    std::string fontsPath = "resources/fonts/";
    std::string soundsPath = "resources/sounds/";
};