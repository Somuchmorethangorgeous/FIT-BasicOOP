#include "Explosion.h"

Explosion::Explosion(sf::Texture *texture1, sf::Vector2f pos_) {
    animation = new Animation(texture1, sf::Vector2u(5,4), 0.0005f);
    pos = pos_;
    row = 0;
    sprite.setTexture(*texture1);
}

void Explosion::update(float deltaTime) {
    animation->update(row, deltaTime);
    sprite.setTextureRect(animation->uvRect);
    sprite.setPosition(pos);
    if (animation->getColumn() == animation->getImageInfo().y){
        ++row;
    }
}

void Explosion::render(sf::RenderTarget *target) {
    target->draw(sprite);
}

const int Explosion::getRow() const {
    return row;
}

const int Explosion::getMaxRow() const {
    return animation->getImageInfo().y;
}

Explosion::~Explosion() {
    delete animation;
}
