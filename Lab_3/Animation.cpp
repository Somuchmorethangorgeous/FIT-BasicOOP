#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float (imageCount.y);
}

void Animation::update(int row, float deltaTime) {
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime){
        totalTime = 0.f;
        ++currentImage.x;
        if (currentImage.x == imageCount.x){
            currentImage.x = 0;
        }
    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}

const int Animation::getColumn() const {
    return currentImage.x;
}

const sf::Vector2u Animation::getImageInfo() const {
    return imageCount;
}

