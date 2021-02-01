#include "World.h"

World::World(sf::Texture* texture) {
    initWorld(texture);
}

void World::initWorld(sf::Texture* texture) {
    backgroundSpeed = 30.f;
    texture->setSmooth(false);
    texture->setRepeated(true);

    bgSize.x = texture->getSize().x;
    bgSize.y = texture->getSize().y;
    bgY = 0.f;

    worldBackground.setTexture(*texture);
    worldBackground.setTextureRect(sf::IntRect(0, 0, 1000, 800));
}

void World::renderWorld(sf::RenderTarget* window) {
    window->draw(worldBackground);
}

void World::updateWorld(float deltaTime) {
    if (bgY < 800.f) {
        bgY -= backgroundSpeed * deltaTime;
    } else {
        bgY = 0.f;
    }
    worldBackground.setTextureRect(sf::IntRect(0, bgY, 1000, 800));
}
