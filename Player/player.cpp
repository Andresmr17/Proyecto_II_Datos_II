#include"player.h"

/**
 * @brief método constructor de la clase player
 */
player::player()
{

}

/**
 * @brief método destructor de la clase player
 */
player::~player()
{

}

/**
 * @brief método es el encargado de crear el objeto player.
 * @param x es la posición en el eje x del jugador.
 * @param y es la posición en el eje y del jugador.
 * @param texture es la textura del jugador.
 * @return Este método no retorna nada.
 */

player::player(float x, float y, sf::Texture &texture)
{
    playerX = 15;
    playerY = 300;
    playerSpeed = 20.0f;
    setSize(sf::Vector2f(70, 70));
    setPosition(playerX, playerY);
    setTexture(&texture);
}