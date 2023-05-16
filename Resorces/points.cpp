#include "points.h"

points::points() {}

points::~points() {}

void points::seteat(bool n)
{
    eaten = n;
}

bool points::geteat() {
    return eaten;
}

points::points(float pos_x, float pos_y, sf::Texture &texture) {
    x_point = pos_x;
    y_point = pos_y;
    setSize(sf::Vector2f(30, 30));
    setPosition(x_point, y_point);
    setTexture(&texture);
}