#pragma once


#include <SFML/Graphics.hpp>


class block :public sf::RectangleShape {

public:
    float blockX;
    float blockY;
    float ancho_block;
    float largo_block;
    bool isDestroyed;

    block();
    ~block();
    block(float pos_x, float pos_y, float largo, float ancho, sf::Texture &texture);
};
