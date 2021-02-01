#include "GUI.h"
#include <sstream>

GUI::GUI() {
   init();
}

void GUI::init() {
    font.loadFromFile("Fonts/pixel.TTF");
    initPointText();
    initPlayerHpBar();
    initGameOverText();
}

void GUI::initGameOverText() {
    gameOver.setPosition(300.f - gameOver.getGlobalBounds().width,
                         300.f - gameOver.getGlobalBounds().height);
    gameOver.setFont(font);
    gameOver.setCharacterSize(100);
    gameOver.setFillColor(sf::Color::Red);
    gameOver.setString("Game over!");
}

void GUI::initPlayerHpBar() {
    playerHPbar.setSize(sf::Vector2f(300.f, 25.f));
    playerHPbar.setFillColor(sf::Color::Red);
    playerHPbar.setPosition(sf::Vector2f(20.f, 20.f));

    playerHPbarBack = playerHPbar;
    playerHPbarBack.setFillColor(sf::Color(25, 25, 25, 100));
}

void GUI::initPointText() {
    pointText.setPosition(880.f, 25.f);
    pointText.setFont(font);
    pointText.setCharacterSize(30);
    pointText.setFillColor(sf::Color::White);
}

void GUI::update(float percents, int points) {
    std::stringstream ss;
    ss << "Pts " << points;
    pointText.setString(ss.str());
    playerHPbar.setSize(sf::Vector2f(300.f * percents, playerHPbar.getSize().y));
}

void GUI::render(sf::RenderTarget* window) {
    window->draw(pointText);
    window->draw(playerHPbar);
    window->draw(playerHPbarBack);
}

void GUI::renderGameOver(sf::RenderTarget *window) {
    window->draw(gameOver);
}
