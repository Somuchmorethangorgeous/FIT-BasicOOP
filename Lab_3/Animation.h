#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H

#include "SFML/Graphics.hpp"

class Animation {
private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
public:
    sf::IntRect uvRect;

    Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Animation() = default;

    const sf::Vector2u getImageInfo() const;
    void update(int row, float deltaTime);
    const int getColumn() const;
};


#endif //GAME_ANIMATION_H
