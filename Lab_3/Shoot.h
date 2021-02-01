#ifndef GAME_SHOOT_H
#define GAME_SHOOT_H

#include "SFML/Graphics.hpp"

class Shoot {
private:
    sf::Sprite spriteBullet;

    sf::Vector2f direction;
    float movementSpeed;

public:
    Shoot(sf::Texture* texture, float pos_x, float pos_y);
    virtual ~Shoot() = default;

    //Getters
    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget* target);
};


#endif //GAME_SHOOT_H
