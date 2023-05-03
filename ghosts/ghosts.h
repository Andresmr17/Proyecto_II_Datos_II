#pragma once

#include <SFML/Graphics.hpp>

class ghosts :public sf::RectangleShape {

public:
    ghosts(float x, float y, bool isF);

    float ghostSpeed;
    float ghostX;
    float ghostY;
    float classSpeed = 0.5f;
    bool ghostDeath;
    bool isFront;
    bool isFired;

    ghosts();
    ~ghosts();

    void setghostY(float n);
    void setghostX(float n);
    float getghostX();
    float getghostY();
    void increaseClassSpeed(float number);
    float getClassSpeed();
};