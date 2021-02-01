#ifndef GAME_SOUNDS_H
#define GAME_SOUNDS_H

#include "SFML/Audio.hpp"

class Sounds {
private:
    sf::Music mainTheme;

    sf::Sound shooting;
    sf::SoundBuffer shootingBuf;

    sf::Sound explosion;
    sf::SoundBuffer explosionBuf;

    sf::SoundBuffer gameOverBuf;
    sf::Sound gameOver;
public:
    Sounds();
    virtual ~Sounds() = default;

    void initMainTheme();
    void initExplosion();
    void initGameOver();
    void initShooting();

    void playMainTheme();
    void playShooting();
    void endMainTheme();
    void playExplosion();
    void playGameOver();
};


#endif //GAME_SOUNDS_H
