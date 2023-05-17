#include"lives.h"

/**
 * @brief método destructor de la clase lives
 * @param null no tiene parámetros
 * @return no tiene retorno
 */
lives::lives()
{

}

/**
 * @brief método destructor de la clase lives
 * @param null no tiene parámetros
 * @return no tiene retorno
 */
lives::~lives()
{

}

/**
 * @brief Se encarga de crear las vidas del jugador que se muestran en la pantalla de juego
 * @param x coreesponde a las coordenadas en el eje x
 * @param y corresponde a las coordenadas en el eje y
 * @param texture corresponde a la imagen que se desea mostrar
 * @return no tiene retorno
 */
lives::lives(float x, float y, sf::Texture &texture)
{
    lv1X = x;
    lv1Y = y;
    setSize(sf::Vector2f(70, 30));
    setPosition(lv1X, lv1Y);
    setFillColor(sf::Color::Yellow);
    setTexture(&texture);
}