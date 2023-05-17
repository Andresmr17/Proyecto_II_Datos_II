#include "points.h"

/**
 * @brief método destructor de la clase points
 * @param null no tiene parámetros
 * @return no tiene retorno
 */
points::points() {}

/**
 * @brief método destructor de la clase points
 * @param null no tiene parámetros
 * @return no tiene retorno
 */
points::~points() {}

/**
 * @brief Coloca un booleano
 * @param n es valor booleano que se desea asignar
 * @return No tiene retorno
 */
void points::seteat(bool n)
{
    eaten = n;
}

/**
 * @brief Obtiene el valor booleano de algun punto
 * @param No tiene parametros
 * @return Retorna el valor booleano
 */
bool points::geteat() {
    return eaten;
}

/**
 * @brief Se encarga de crear el objeto punto dandole la posicion en x e y junto con la imagen
 * @param pos_x es la coordenada en el eje x
 * @param pos_y es la coordenada en el eje y
 * @param texture corresponde a la imagen que se desea colocar
 * @return No tiene retorno
 */
points::points(float pos_x, float pos_y, sf::Texture &texture) {
    x_point = pos_x;
    y_point = pos_y;
    setSize(sf::Vector2f(30, 30));
    setPosition(x_point, y_point);
    setTexture(&texture);
}