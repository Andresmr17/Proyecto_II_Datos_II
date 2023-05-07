#pragma once

#include <SFML/Graphics.hpp>

class ghosts :public sf::RectangleShape {

public:
    ghosts(float x, float y, bool isF);

    float ghostSpeed;
    float ghostX;
    float ghostY;
    float speed = 7.0f;
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
    void move(int i, float d);
};