#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "SFML/Graphics.hpp"

class Entity {
public:
    sf::Texture texture;
    sf::Sprite sprite;

    unsigned int hpMax;
    int hp;

    float speed;
    int points;
    unsigned int damage;

    Entity(sf::Texture* texture, sf::Vector2f pos);

    //Getters
    const sf::FloatRect getBounds() const;
    const sf::Vector2f getPos() const;
    const int& getHp() const;
    const int& getPoints() const;
    const unsigned int& getDamage() const;

    //Modifiers
    virtual void render(sf::RenderTarget* target);
    void takeDamage(const int dmg);

    virtual void update(float deltaTime) = 0;
    virtual ~Entity() = default;
};



#endif //GAME_ENTITY_H
