#include "Shoot.h"

Shoot::Shoot(sf::Texture *texture, float pos_x, float pos_y) {
    spriteBullet.setTexture(*texture);
    spriteBullet.rotate(270);
    spriteBullet.scale(0.1f, 0.1f);
    spriteBullet.setPosition(pos_x, pos_y);
    direction.x = 0.f;
    direction.y = -1.f;
    movementSpeed = 10.f;
}

const sf::FloatRect Shoot::getBounds() const {
    return spriteBullet.getGlobalBounds();
}

void Shoot::update() {
    spriteBullet.move(movementSpeed * direction);
}

void Shoot::render(sf::RenderTarget *target) {
    target->draw(spriteBullet);
}
