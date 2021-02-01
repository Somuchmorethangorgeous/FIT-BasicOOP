#ifndef GAME_EXPLOSION_H
#define GAME_EXPLOSION_H

#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <vector>

class Explosion {
private:
    sf::Sprite sprite;
    sf::Vector2f pos;

    int row;

    Animation* animation;
public:
    Explosion(sf::Texture* texture1, sf::Vector2f pos_);
    virtual ~Explosion();


    void update(float deltaTime);
    void render(sf::RenderTarget* target);
    const int getRow() const;
    const int getMaxRow() const;
};


#endif //GAME_EXPLOSION_H
