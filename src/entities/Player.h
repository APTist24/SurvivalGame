#pragma once
#include "Entity.h"
#include "../core/ResourceManager.h"

class Player : public Entity {
public:
    Player(ResourceManager& resourceManager, float x, float y, const std::string& texturePath);
    void update(float deltaTime) override;
    void move(float dx, float dy);

private:
    float speed = 200.f;
    float hunger = 100.f;
};