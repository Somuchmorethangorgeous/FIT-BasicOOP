#ifndef GAME_GAMEENGINE_H
#define GAME_GAMEENGINE_H


#include "World.h"
#include "Player.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "GUI.h"
#include "Sounds.h"
#include <map>
#include <iostream>

class GameEngine {
private:
    // Window
    sf::RenderWindow* window;

    //Textures
    std::map<std::string, sf::Texture*> textures;

    //Background
    World* world;

    //Player
    Player* player;

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<Asteroid*> asteroids;

    //GUI
    GUI* gui;

    //Effects
    std::vector<Explosion*> explosion;

    //Sounds
    Sounds* sounds;

    // functions
    void initWindow();
    void initTextures();
    void initGUI();
    void initWorld();
    void initPlayer();
    void initMusic();
    void initAsteroids();

public:
    GameEngine();
    ~GameEngine();

    void run();

    void update();
    void updateAsteroids(float deltaTime);
    void updateEffects(float deltaTime);
    void updateCollisions();
    void updateExplosion();

    void updatePollEvents();

    void render();
};


#endif //GAME_GAMEENGINE_H
