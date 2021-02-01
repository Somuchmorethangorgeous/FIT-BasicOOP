#ifndef GAME_ASTEROID_H
#define GAME_ASTEROID_H

#include "Entity.h"
#include "Animation.h"

class Asteroid: public Entity {
private:
    Animation* animation;
    int type;
public:
    Asteroid(sf::Texture* texture, sf::Vector2f pos);
    ~Asteroid() override;

    void update(float deltaTime) override;
};


#endif //GAME_ASTEROID_H
