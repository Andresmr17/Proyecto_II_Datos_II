#pragma once

#include <SFML/Graphics.hpp>
#include "../Resorces/block.h"

class ghosts :public sf::RectangleShape {

public:

    sf::Texture ghostTexture;

    ghosts(float x, float y, bool isF);

    float ghostSpeed;
    float ghostX;
    float ghostY;
    float speed = 1.0f;
    bool ghostDeath;
    bool isFront;
    bool isFired;
    sf::Clock clock;

    ghosts();
    ~ghosts();

    void setghostY(float n);
    void setghostX(float n);
    float getghostX();
    float getghostY();
    void increaseClassSpeed(float number);
    float getClassSpeed();

    void moveGhost(float deltaTime);

    bool checkCollision(sf::CircleShape&,std::vector<sf::RectangleShape>&, float, float);
};