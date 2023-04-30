#pragma once
#include <SFML/Graphics.hpp>


class lives :public sf::RectangleShape {

public:
    float lv1X;
    float lv1Y;

    lives();
    ~lives();
    lives(float x, float y, sf::Texture &texture);
};
