#include "GameEngine.h"

GameEngine::GameEngine() {
    initWindow();

    initTextures();

    initGUI();

    initWorld();

    initPlayer();

    initMusic();

    initAsteroids();
}

GameEngine::~GameEngine() {
    delete window;

    delete world;

    delete sounds;

    delete gui;

    delete player;

    for (auto& item : textures)
        delete item.second;

    for (auto* i : asteroids){
        delete i;
    }

    for (auto* i : explosion){
        delete i;
    }
}

void GameEngine::initWindow(){
    window = new sf::RenderWindow(sf::VideoMode(1000, 800), "Interstellar 2", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(100);
}


void GameEngine::initTextures() {
    textures["BULLET"] = new sf::Texture;
    textures["BULLET"]->loadFromFile("Textures/bullet.png");
    textures["PLAYER"] = new sf::Texture;
    textures["PLAYER"]->loadFromFile("Textures/Spaceship.png");
    textures["WORLD"] = new sf::Texture;
    textures["WORLD"]->loadFromFile("Textures/space.png");
    textures["ASTEROIDS"] = new sf::Texture;
    textures["ASTEROIDS"]->loadFromFile("Textures/Asteroids.png");
    textures["BOOM"] = new sf::Texture;
    textures["BOOM"] -> loadFromFile("Textures/Explosion.png");
}

void GameEngine::initGUI() {
    gui = new GUI;
}

void GameEngine::initWorld() {
    world = new World(textures["WORLD"]);
}

void GameEngine::initAsteroids() {
    spawnTimerMax = 50.f;
    spawnTimer = spawnTimerMax;
}

void GameEngine::initPlayer() {
    player = new Player(textures["PLAYER"], textures["BULLET"]);
    player->setPosition((window->getSize().x  - player->getBounds().width) / 2 , window->getSize().y - player->getBounds().height);
}

void GameEngine::initMusic() {
    sounds = new Sounds;
    sounds->initMainTheme();
    sounds->initExplosion();
    sounds->initGameOver();
    sounds->playMainTheme();
}

void GameEngine::run() {
    sf::Clock clock;
    float deltaTime;
    while (window->isOpen()){
        deltaTime = clock.restart().asSeconds();

        updatePollEvents();

        if (player->getHp() > 0) {

            update();
            player->update(deltaTime);
            world->updateWorld(deltaTime);
            gui->update(static_cast<float>(player->hp) / player->hpMax, player->points);
            updateAsteroids(deltaTime);
            updateEffects(deltaTime);

        } else {
            updateEffects(deltaTime);
            gui->update(0.f, player->points);
            sounds->endMainTheme();
            sounds->playGameOver();
        }
        render();
    }
}

void GameEngine::updatePollEvents() {
    sf::Event ev;
    while (window->pollEvent(ev)){
        switch (ev.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
            default:
                break;
        }
    }
}

void GameEngine::update() {

    bool shooting = false;
    player->controlPlayer(shooting);
    if (shooting) {
        sounds->playShooting();
    }

    updateExplosion();

    updateCollisions();
}

void GameEngine::updateAsteroids(float deltaTime) {
    spawnTimer += 0.5f;
    if (spawnTimer >= spawnTimerMax) {
        asteroids.push_back(new Asteroid(textures["ASTEROIDS"], {float(rand() % window->getSize().x), -100.f}));
        spawnTimer = 0.f;
    }

    unsigned counter = 0;
    for (auto *asteroid : asteroids){
        asteroid->update(deltaTime);


        if (asteroid->getBounds().top > window->getSize().y){

            delete asteroids.at(counter);

            asteroids.erase(asteroids.begin() + counter);

        } else if (asteroid->getBounds().intersects(player->getBounds())){

            explosion.push_back(new Explosion(textures["BOOM"], asteroid->getPos()));

            player->takeDamage(asteroid->getDamage());

            delete asteroids.at(counter);

            asteroids.erase(asteroids.begin() + counter);

            sounds->playExplosion();
        }

        ++counter;
    }
}

void GameEngine::updateExplosion() {
    for (size_t i = 0; i < asteroids.size(); ++i){
        bool asteroidCrashed = false;

        for (size_t k = 0; k < player->sizeBullets() && !asteroidCrashed; ++k){
            if (asteroids[i]->getBounds().intersects(player->getBullet(k)->getBounds())){


                asteroids[i]->takeDamage(player->getDamage());
                if (asteroids[i]->getHp() == 0) {
                    player->takePoints(asteroids[i]->getPoints());

                    explosion.push_back(new Explosion(textures["BOOM"], asteroids[i]->getPos()));
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i);

                    sounds->playExplosion();
                }

                delete player->getBullet(k);
                player->deleteBullet(k);

                asteroidCrashed = true;
            }
        }
    }
}

void GameEngine:: updateEffects(float deltaTime) {
    for (size_t i = 0; i < explosion.size(); ++i){
        explosion[i]->update(deltaTime);
        if (explosion[i]->getRow() == explosion[i]->getMaxRow()){
            delete explosion[i];
            explosion.erase(explosion.begin() + i);
        }
    }
}

void GameEngine::updateCollisions() {
    // Bounfaries of window
    if (player->getBounds().left < 0.f){
        player->setPosition(0.f, player->getBounds().top);
    } else if (player->getBounds().left + player->getBounds().width >= window->getSize().x){
        player->setPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);
    }
   if (player->getBounds().top < 0.f){
        player->setPosition(player->getBounds().left, 0.f);
    } else if (player->getBounds().top + player->getBounds().height >= window->getSize().y){
        player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
    }
}

void GameEngine::render() {
    window->clear();

    world->renderWorld(window);

    gui->render(window);

    player->render(window);

    for (auto *asteroid :asteroids){
        asteroid->render(window);
    }

    for (auto *boom : explosion){
        boom->render(window);
    }

    if (player->getHp() <= 0){
        gui->renderGameOver(window);
    }

    window->display();
}






