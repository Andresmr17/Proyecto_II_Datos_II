#include"block.h"


block::block()
{

}
block::~block()
{

}
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
