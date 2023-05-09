#pragma once
#include <SFML/Graphics.hpp>


class power :public sf::RectangleShape{

public:
    float x_power;
    float y_power;

    power();
    ~power();
    power(float pos_x, float pos_y, sf::Texture &texture);

};

