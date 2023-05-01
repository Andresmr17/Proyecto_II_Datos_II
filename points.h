#progma once
#include <SFML/Graphics.hpp>


class points :public sf::RectangleShape{

public:
    float x_point;
    float y_point;

    points();
    ~points();
    points(float pos_x, float pos_y, sf::Texture &texture);

};


