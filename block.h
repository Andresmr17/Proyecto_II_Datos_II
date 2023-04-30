#pragma once


#include <SFML/Graphics.hpp>


class block :public sf::RectangleShape {

public:
    float blockX;
    float blockY;
    bool isDestroyed;

    block();
    ~block();
    block(float x, float y);
};
