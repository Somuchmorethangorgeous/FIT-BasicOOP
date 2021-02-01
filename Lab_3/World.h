#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class World {
private:
    sf::Sprite worldBackground;

    sf::Vector2f bgSize;

    float backgroundSpeed;
    float bgY;

public:
    World(sf::Texture* texture);
    virtual ~World() = default;

    void initWorld(sf::Texture* texture);
    void updateWorld(float deltaTime);
    void renderWorld(sf::RenderTarget* window);
};


#endif //GAME_WORLD_H
