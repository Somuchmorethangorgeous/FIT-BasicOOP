#include "Sounds.h"

Sounds::Sounds() {
    initMainTheme();
    initExplosion();
    initShooting();
    initGameOver();
}

void Sounds::initMainTheme() {
    mainTheme.openFromFile("Sounds/mainTheme.wav");
    mainTheme.setLoop(true);
    mainTheme.setVolume(10.f);
}

void Sounds::initExplosion() {
    explosionBuf.loadFromFile("Sounds/boom.wav");
    explosion.setBuffer(explosionBuf);
    explosion.setVolume(10.f);
}

void Sounds::initGameOver() {
    gameOverBuf.loadFromFile("Sounds/gameOver.wav");
    gameOver.setBuffer(gameOverBuf);
    gameOver.setVolume(20.f);
}

void Sounds::initShooting() {
    shootingBuf.loadFromFile("Sounds/shoot.wav");
    shooting.setBuffer(shootingBuf);
    shooting.setVolume(10.f);
}

void Sounds::playMainTheme() {
    mainTheme.play();
}

void Sounds::endMainTheme(){
    mainTheme.stop();
}

void Sounds::playExplosion(){
    explosion.play();
}

void Sounds::playGameOver(){
    static bool anouncement = false;
    if (!anouncement) {
        gameOver.play();
        anouncement = true;
    }
}


void Sounds::playShooting() {
    shooting.play();
}
