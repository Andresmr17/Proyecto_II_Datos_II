#pragma once
#include <SFML/Graphics.hpp>


class points :public sf::RectangleShape{

public:
    float x_point;
    float y_point;
    bool eaten;

    points();
    ~points();
    void seteat(bool n);
    bool geteat();
    points(float pos_x, float pos_y, sf::Texture &texture);

};


