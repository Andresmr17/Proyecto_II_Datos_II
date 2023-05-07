#include <SFML/Graphics.hpp>
#include "Game/PacMan.h"
#include <iostream>

using namespace std;

/**
 * @brief Este metodo es el encargado de crear la ventana de bienvenida y según el botón presionado por el usuario
 * desplegar la ventana del juego o salir de este.
 * @param null Este método no recibe parámetros.
 * @return Retorna la ventana del juego.
 */

constexpr const char* const fondo = "/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Bienvenida.png";

int main()
{
    // Crea una ventana de 640x480x32 con el título SFML window
    sf::RenderWindow window(sf::VideoMode(900, 700), "Inicio");

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

    // Creamos un objeto titulo, con su respectivo t3exto, fuente y tamaño.
    sf::Text titulo("Bienvenid@",font,48);
    // Color del título
    titulo.setColor(sf::Color(0, 255, 0));
    // Posición del título
    titulo.setPosition(325, 30);

    // Creamos otro texto con la misma fuente
    sf::Text dificultad("Seleccione el boton Iniciar para comenzar el juego", font, 32);
    // Color del título
    dificultad.setColor(sf::Color(0, 255, 0));
    // Posición del texto
    dificultad.setPosition(105, 135);

    // Creamos un objeto boton
    sf::Texture iniciar;
    // Intentamos cargarla
    if (!iniciar.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/btnIniciar.png"))
    {
        return EXIT_FAILURE;
    }

    //Se crea el Sprite
    sf::Sprite iniciarImage;
    // Asignamos el boton al sprite
    iniciarImage.setTexture(iniciar);
    iniciarImage.setPosition(300,250);

    // Creamos un objeto boton
    sf::Texture salir;
    // Intentamos cargarla
    if (!salir.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/btnSalir.png"))
    {
        return EXIT_FAILURE;
    }

    // Creamos otro texto con la misma fuente
    sf::Text salirT("Seleccione el boton Salir para dejar el juego", font, 32);
    // Color del título
    salirT.setColor(sf::Color(0, 255, 0));
    // Posición del texto
    salirT.setPosition(130, 450);

    //Se crea el Sprite
    sf::Sprite salirImage;
    // Asignamos el boton al sprite
    salirImage.setTexture(salir);
    salirImage.setPosition(300,525);

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
                    if (iniciarImage.getGlobalBounds().contains( mousePosF ) )
                    {
                        PacMan pacman;
                        return pacman.game(1,1,0);
                    }
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
        window.draw(titulo);
        window.draw(dificultad);
        window.draw(salirT);

        window.draw(iniciarImage);
        window.draw(salirImage);

        // Actualizamos la ventana
        window.display();
    }
    return 0;
}