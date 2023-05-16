#include "power.h"

power::power() {}

power::~power() {}

/**
 * @brief Se crea la imagen del poder que se presenta en el juego
 * @param x corresponde a la coordenada en el eje x
 * @param y corresponde a la coordenada en el eje y
 * @param texture corresponde a la imagen que se desea mostrar
 */
power::power(float x, float y, sf::Texture &texture) {
    x_power = x;
    y_power = y;
    setSize(sf::Vector2f(50, 50));
    setPosition(x_power, y_power);
    setTexture(&texture);
}