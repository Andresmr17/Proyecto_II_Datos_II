#include "PacMan.h"

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief Este método es el que contiene la lógica del juego
 * @param null Este método no recibe parámetros.
 * @return este método no retorna nada.
 */

int PacMan::game(){
    {

        float x_coord = 70;
        float y_coord = 70;

        sf::RenderWindow window(sf::VideoMode(900, 600), "SFML works!");

        sf::CircleShape nave(15,3);
        nave.setPosition(x_coord, y_coord);
        nave.setFillColor(sf::Color::Blue);
        using namespace std;

        sf::Texture texture;
        if (!texture.loadFromFile("images/Jugador.png")) {
            std::cout << "Error load image";
        }


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            //eventos del teclado
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if(x_coord > 875){
                    x_coord  += 0;
                }
                else{
                    x_coord  += 0.2;}
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                if(x_coord < 2){
                    x_coord  += 0;
                }
                else{
                    x_coord  -= 0.2;}
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                if(y_coord < 2){
                    y_coord  += 0;
                }
                else{
                    y_coord  -= 0.2;}

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                if(y_coord > 575){
                    y_coord  += 0;
                }
                else{
                    y_coord  += 0.2;}

            }

            window.clear();
            nave.setPosition(x_coord, y_coord); //cambia la posición de la nave por el evento de teclado
            window.draw(nave);
            window.display();
        }

        return 0;
    }
}