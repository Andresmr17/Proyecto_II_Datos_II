#include "power.h"

power::power() {}

power::~power() {}

power::power(float x, float y, sf::Texture &texture) {
    x_power = x;
    y_power = y;
    setSize(sf::Vector2f(50, 50));
    setPosition(x_power, y_power);
    setTexture(&texture);
}