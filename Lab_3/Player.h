#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Entity.h"
#include "Shoot.h"
#include <vector>

class Player : public Entity {
private:
    //Guns
    std::vector<Shoot*> bullets;
    sf::Texture* bulletTexture;

    float attackCD;
    float attackMaxCD;

    void initVariables();

public:

    Player(sf::Texture* texture, sf::Texture* bulTexture);
    ~Player() override;

    void initBulletTexture(sf::Texture* bulTexture);
    void controlPlayer(bool& shooting);
    void move(const float dirX, const float dirY);
    void update(float deltaTime) override;
    void updateAttack();
    const bool canAttack();

    void render(sf::RenderTarget* target) override;

    //Getters
    const Shoot* getBullet(const int i) const;
    const size_t sizeBullets() const;
    void deleteBullet(const int i);

    // Modifiers
    void setPosition(float X, float Y);
    void takePoints(const int points);
};


#endif //GAME_PLAYER_H
