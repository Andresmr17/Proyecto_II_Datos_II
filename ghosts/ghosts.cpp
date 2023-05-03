#include "ghosts.h"

/**
 * @brief método constructor de la clase ghosts
 * @param null no tiene parámetros
 * @return no tiene retorno
 */
ghosts::ghosts()
{

}

/**
 * @brief método destructor de la clase ghosts
 * @param null no tiene parámetros
 * @return no tiene retorno
 */
ghosts::~ghosts()
{

}

/**
 * @brief método es el encargado de crear los objetos ghosts
 * @param x es la posición en el eje x del fantasma
 * @param y es la posición en el eje y del fantasma
 * @param isF significa si está vivo
 * @return no tiene retorno
 */
ghosts::ghosts(float x, float y, bool isF)
{
    setSize(sf::Vector2f(50, 50));
    ghostX = x;
    ghostY = y;
    isFront = isF;
    isFired = false;
    setPosition(ghostX, ghostY);
    ghostSpeed = getClassSpeed();
    ghostDeath = false;

}

/**
 * @brief Es el metodo encargado de poner la posicion en y
 * @param n es la posicion en y
 * @return No tiene retorno
 */
void ghosts::setghostY(float n)
{
    ghostY = n;
}

/**
 * @brief Es el metodo encargado de poner la posicion en x
 * @param n es la posicion en x
 * @return No tiene retorno
 */
void ghosts::setghostX(float n)
{
    ghostX = n;
}

/**
 * @brief Es el metodo encargado de obtener la posicion en x
 * @param null no tiene parámetros
 * @return Retorna la posicion en x
 */
float ghosts::getghostX()
{
    return ghostX;
}

/**
 * @brief Es el metodo encargado de obtener la posicion en y
 * @return Retorna la posicion en y
 */
float ghosts::getghostY()
{
    return ghostY;
}

/**
 * @brief Metodo encargado de aumentar la velocidad de los enemigos
 * @param number es el aumento de la velocidad
 * @return No tiene retorno
 */
void ghosts::increaseClassSpeed(float number)
{
    classSpeed += number;
}

/**
 * @brief Metodo encargado de obtener la velocidad de los enemigos
 * @return Retorna la velocidad
 */
float ghosts::getClassSpeed()
{
    return classSpeed;
}