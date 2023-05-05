/*#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>

class Ghost {
private:
    sf::RectangleShape shape;
    float speed;
    int direction;
    bool collided;

public:
    Ghost(float x, float y, float size) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(size, size));
        shape.setFillColor(sf::Color::Red);
        speed = 100.0f;
        direction = rand() % 4;
        collided = false;
        shape.setPosition(200, 200);

    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    void move(float deltaTime, sf::RectangleShape obstacle) {
        sf::Vector2f movement(0.0f, 0.0f);
        float distance = speed * deltaTime;

        switch (direction) {
            case 0: // Up
                movement.y -= distance;
                break;
            case 1: // Down
                movement.y += distance;
                break;
            case 2: // Left
                movement.x -= distance;
                break;
            case 3: // Right
                movement.x += distance;
                break;
        }

        // Si el fantasma se sale de la ventana, volver a colocarlo en el centro
        if (shape.getPosition().x < 0 || shape.getPosition().x > 800 ||
            shape.getPosition().y < 0 || shape.getPosition().y > 600)
        {
            shape.move(3,3);
        }

        sf::FloatRect ghostBounds = shape.getGlobalBounds();
        sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();

        if (ghostBounds.intersects(obstacleBounds)) {
            collided = true;
            switch (direction) {
                case 0: // Up
                    movement.y = obstacle.getPosition().y + obstacle.getSize().y - ghostBounds.top;
                    break;
                case 1: // Down
                    movement.y = obstacle.getPosition().y - ghostBounds.height - ghostBounds.top;
                    break;
                case 2: // Left
                    movement.x = obstacle.getPosition().x + obstacle.getSize().x - ghostBounds.left;
                    break;
                case 3: // Right
                    movement.x = obstacle.getPosition().x - ghostBounds.width - ghostBounds.left;
                    break;
            }
        }

        shape.move(movement);

        if (collided) {
            collided = false;
            direction = rand() % 4;
        }
        else {
            if (rand() % 100 < 2) {
                direction = rand() % 4;
            }
        }
    }
};

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Ghost Movement");
    window.setFramerateLimit(60);

    sf::RectangleShape obstacle(sf::Vector2f(50.0f, 100.0f));
    obstacle.setPosition(300.0f, 200.0f);
    obstacle.setFillColor(sf::Color::Blue);

    Ghost ghost(50.0f, 50.0f, 30.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = 1.0f / 60.0f;

        ghost.move(deltaTime, obstacle);

        window.clear();

        ghost.draw(window);
        window.draw(obstacle);

        window.display();
    }

    return 0;
}*/