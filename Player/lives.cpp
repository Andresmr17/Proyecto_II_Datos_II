#include"lives.h"

lives::lives()
{

}
lives::~lives()
{

}
lives::lives(float x, float y, sf::Texture &texture)
{
    lv1X = x;
    lv1Y = y;
    setSize(sf::Vector2f(70, 30));
    setPosition(lv1X, lv1Y);
    setFillColor(sf::Color::Green);
    setTexture(&texture);
}