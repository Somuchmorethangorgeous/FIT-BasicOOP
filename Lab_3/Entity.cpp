//
// Created by ruslan on 27.11.2020.
//

#include "Entity.h"

Entity::Entity(sf::Texture *texture, sf::Vector2f pos) {
    this->texture = *texture;
    texture->setSmooth(true);
    sprite.setTexture(*texture);
    sprite.setPosition(pos);
}

const int& Entity::getPoints() const{
    return points;
}

const unsigned int &Entity::getDamage() const {
    return damage;
}

void Entity::render(sf::RenderTarget *target) {
    target->draw(sprite);
}

const sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}

const sf::Vector2f Entity::getPos() const {
    return sprite.getPosition();
}

void Entity::takeDamage(const int dmg) {
    hp -= dmg;
    if (hp <= 0)
        hp = 0;
}

const int& Entity::getHp() const {
    return hp;
}


