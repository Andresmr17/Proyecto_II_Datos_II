#include <SFML/Graphics.hpp>
#include <iostream>
#include "puntuacion_final.h"

using namespace std;

/**
 * @brief Este metodo es el encargado de crear la ventana de bienvenida y según el botón presionado por el usuario
 * desplegar la ventana del juego o salir de este.
 * @param null Este método no recibe parámetros.
 * @return Retorna la ventana del juego.
 */

constexpr const char* const fondo = "/home/andres/CLionProjects/Proyecto_II_Datos_II/images/puntos.png";

int puntuacion_final::p(int score)
{
    string pp = std::to_string(score);

    // Crea una ventana de 680x300 con el título Score
    sf::RenderWindow window(sf::VideoMode(525, 400), "Score");

    // Activa la sincronización vertical (60 fps)
    window.setVerticalSyncEnabled(true);

    // Creamos un objeto fondo
    sf::Texture backgroundPic;
    // Intentamos cargarla
    if (!backgroundPic.loadFromFile(fondo))
    {
        return EXIT_FAILURE;
    }

    //Se crea el Sprite
    sf::Sprite sprite;
    // Asignamos la textura al sprite
    sprite.setTexture(backgroundPic);

    // Creamos un objeto fuente
    sf::Font font;
    // Intentamos cargarla
    if (!font.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/font/arial.ttf"))
    {
        return EXIT_FAILURE;
    }

    // Creamos otro texto con la misma fuente
    sf::Text dificultad("La puntuacion obtenida fue de: "+pp, font, 24);
    // Color del título
    dificultad.setColor(sf::Color(0, 255, 0));
    // Posición del texto
    dificultad.setPosition(75, 50);

    // Creamos un objeto boton
    sf::Texture salir;
    // Intentamos cargarla
    if (!salir.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/btnSalir2.png"))
    {
        return EXIT_FAILURE;
    }

    // Creamos otro texto con la misma fuente
    sf::Text salirT("Seleccione el boton Salir para dejar el juego", font, 24);
    // Color del título
    salirT.setColor(sf::Color(0, 255, 0));
    // Posición del texto
    salirT.setPosition(15, 250);

    //Se crea el Sprite
    sf::Sprite salirImage;
    // Asignamos el boton al sprite
    salirImage.setTexture(salir);
    salirImage.setPosition(200,300);

    // Game Loop mientras la ventana esté abierta
    while (window.isOpen())
    {
        // Creamos un objeto evento
        sf::Event event;
        // Procesamos la pila de eventos
        while (window.pollEvent(event))
        {
            // Si el evento es de tipo Closed cerramos la ventana
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                    sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                    if (salirImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        window.close();
                    }
                }
                    break;
            }
        }

        // Limpiamos la pantalla
        window.clear();

        // Dibujamos en pantalla
        window.draw(sprite);
        window.draw(dificultad);
        window.draw(salirT);

        window.draw(salirImage);

        // Actualizamos la ventana
        window.display();
    }
    return 0;
}