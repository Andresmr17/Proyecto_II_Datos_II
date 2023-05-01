#pragma once
#include <SFML/Graphics.hpp>

class player :public sf::RectangleShape {

public:
    float playerX;
    float playerY;
    float playerSpeed;

    player();
    ~player();
    player(float x, float y, sf::Texture &texture);

};