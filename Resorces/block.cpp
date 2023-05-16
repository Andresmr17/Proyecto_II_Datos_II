#include"block.h"


block::block()
{

}
block::~block()
{

}
/**
 * @brief Se encarga de crear los objetos que son paredes en el mapa
 * @param pos_x es la coordenada en el eje x
 * @param pos_y es la coordenada en el eje y
 * @param largo corresponde al valor de lo largo que se desea que sea la pared
 * @param ancho corresponde al valor de lo ancho que se desea que sea la pared
 * @param texture corresponde a la imagen que se le desea dar a la pared
 * @return No tiene retorno
 */
block::block(float pos_x, float pos_y, float largo, float ancho, sf::Texture &texture)
{

    ancho_block = ancho;
    largo_block = largo;
    setSize(sf::Vector2f(largo_block, ancho_block));
    blockX = pos_x;
    blockY = pos_y;
    setPosition(blockX, blockY);
    isDestroyed = false;
    setTexture(&texture);
}
