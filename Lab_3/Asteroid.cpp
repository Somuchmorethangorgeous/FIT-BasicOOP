#include "Asteroid.h"


Asteroid::Asteroid(sf::Texture *texture, sf::Vector2f pos) : Entity(texture, pos) {
    animation = new Animation(texture, sf::Vector2u(4, 4), 0.2f);
    //sprite
    type = rand() % 4;
    switch (type) {
        case 0:
            hpMax = 4;
            speed = 4;
            break;
        case 1:
            hpMax = 8;
            speed = 3;
            break;
        case 2:
            hpMax = 12;
            speed = 2;
            break;
        case 3:
            hpMax = 16;
            speed = 1;
            break;
    }
    hp = hpMax;
    damage = speed * 5;
    points = speed;
}

void Asteroid::update(float deltaTime) {
    animation->update(type, deltaTime);
    sprite.setTextureRect(animation->uvRect);
    sprite.move(0.f, speed);
}

Asteroid::~Asteroid() {
    delete animation;
}



