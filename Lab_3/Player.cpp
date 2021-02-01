#include "Player.h"

Player::Player(sf::Texture *texture, sf::Texture *bulTexture): Entity(texture, {0.f, 0.f}){
    initVariables();
    initBulletTexture(bulTexture);
    sprite.setTextureRect(sf::IntRect(200,0, 500, 907));
    sprite.scale(0.2f, 0.2f);
}


void Player::initVariables() {
    speed = 6.f;

    attackMaxCD = 8.f;
    attackCD = attackMaxCD;

    damage = 4;
    hpMax = 100;
    hp = hpMax;
    points = 0;
}

void Player::initBulletTexture(sf::Texture* bulTexture) {
    bulletTexture = bulTexture;
}

void Player::render(sf::RenderTarget *target) {
    target->draw(sprite);
    for (auto *bullet : bullets)
        bullet->render(target);
}

void Player::setPosition(const float X, const float Y) {
    sprite.setPosition(X, Y);
}


void Player::move(const float dirX, const float dirY) {
    sprite.move(dirX * speed, dirY * speed);
}

void Player::controlPlayer(bool& shooting) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move(0.f, 1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canAttack()){
        static bool gun = false; // left and right guns
        if (gun) {
            bullets.push_back(new Shoot(bulletTexture,
                                        getPos().x,
                                        getPos().y + getBounds().height / 2.f));
            gun = false;
        } else {
            bullets.push_back(new Shoot(bulletTexture,
                                        getPos().x + getBounds().width * 0.7f,
                                        getPos().y + getBounds().height / 2.f));
            gun = true;
        }
        shooting = true;
    }

}

Player::~Player() {
    for (auto *bullet : bullets)
        delete bullet;
}


void Player::update(float deltaTime) {
    updateAttack();

    unsigned counter = 0;
    for (auto *bullet : bullets){
        bullet->update();

        if (bullet->getBounds().top + bullet->getBounds().height < 0){
            delete bullets.at(counter);
            bullets.erase(bullets.begin() + counter);
        }
        ++counter;
    }
}

void Player::updateAttack() {
    if (!canAttack())
        attackCD += 0.5f;
}

const bool Player::canAttack() {
    if (attackCD >= attackMaxCD) {
        attackCD = 0.f;
        return true;
    }
    return false;
}


const Shoot *Player::getBullet(const int i) const {
    return bullets.at(i);
}

const size_t Player::sizeBullets() const {
    return bullets.size();
}

void Player::deleteBullet(const int i) {
    bullets.erase(bullets.begin() + i);
}

void Player::takePoints(const int pts) {
    points += pts;
}



