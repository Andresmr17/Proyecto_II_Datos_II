#include"block.h"


block::block()
{

}
block::~block()
{

}
block::block(float x, float y)
{

    setSize(sf::Vector2f(70, 70));
    blockX = x;
    blockY = y;
    setPosition(blockX, blockY);
    isDestroyed = false;
}
