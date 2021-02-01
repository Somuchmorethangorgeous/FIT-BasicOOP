#ifndef GAME_GUI_H
#define GAME_GUI_H

#include "SFML/Graphics.hpp"

class GUI {
private:
    sf::RectangleShape playerHPbar;
    sf::RectangleShape playerHPbarBack;
    sf::Font font;

    sf::Text pointText;
    sf::Text gameOver;

    void init();
    void initGameOverText();
    void initPlayerHpBar();
    void initPointText();

public:
    GUI();
    virtual ~GUI() = default;

    void update(float percents, int points);
    void render(sf::RenderTarget* window);
    void renderGameOver(sf::RenderTarget* window);
};


#endif //GAME_GUI_H
