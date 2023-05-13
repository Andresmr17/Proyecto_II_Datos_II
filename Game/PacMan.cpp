#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan.h"
#include "PacMan2.h"
#include "../Resorces/power.h"
#include "../Resorces/block.h"
#include "../Player/lives.h"
#include "../Player/player.h"
#include "../Resorces/points.h"
#include "../ghosts/ghosts.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int playerLives = 3;
int loop = 1;
bool juego = true;
int randomEnemy = 0;
int countDeadEnemy = 0;

float deltaTime = 1.0f / 60.0f;

bool isDeath = false;
bool press_flag = true;
bool flag_up = true;
bool flag_down = true;
bool flag_right = true;
bool flag_left = true;

bool turnPoweron_1 = false;
bool turnPoweron_2 = false;
bool eaten = false;

bool ghost_move = true;
char direccion1 = 'd';

void buildobstacles(block blockObj[4], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 50, 100, 220, Obstaculo);
    blockObj[1]= block(740, 395, 100, 200, Obstaculo);
    blockObj[2]= block(70, 120, 770, 170, Obstaculo);
    blockObj[3]= block(70, 355, 770, 170, Obstaculo);

}

void bluidPoints(points pointsObj[], sf::Texture &Point){

    int posiciones_puntos[31][2]={{260,65},{360, 65},{460, 65},{560,65},
                                  {660, 65},{760, 65},{860,65},{20,125},{20,205},{20,305},
                                  {20,405},{20,480},{60,555},{160, 555},{260, 555},{360, 555},
                                  {560, 555},{660, 555},{860,555},
                                  {860, 205},{860, 305},{860, 405},{860, 485},{107, 313}, {207, 313},
                                  {307, 313}, {407, 313}, {507, 313}, {607, 313}, {707, 313}, {807, 313}
    };

    for(int i = 0; i < 31; i++){
        pointsObj[i] = points(posiciones_puntos[i][0],posiciones_puntos[i][1], Point);

    }
}

int PacMan::game(int cantidad_fantasmas, int nivel, int puntuacion) {

    ghosts ghost;
    int ghostLeft = cantidad_fantasmas;
    bool win = false;
    int score = puntuacion;
    int kill = 1;
    int level = nivel;
    int tempScore = 0;

    sf::Vertex lineTop[] =//horizontal line
            {
                    sf::Vertex(sf::Vector2f(0, 50)),
                    sf::Vertex(sf::Vector2f(900, 50))
            };
    sf::Vertex line[] =//horizontal line
            {
                    sf::Vertex(sf::Vector2f(0, 600)),
                    sf::Vertex(sf::Vector2f(900, 600))
            };

    //Fuente del texto
    sf::Font font;
    if (!font.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/font/arial.ttf")) {
        std::cout << "Can't load font";
    }

    //Texto de la puntuación del jugador
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(sf::Vector2f(10, 10));
    scoreText.setString("Puntuacion : " + std::to_string(score));

    //Texto del novel que se encuentra el jugador
    sf::Text playerLevel;
    playerLevel.setFont(font);
    playerLevel.setCharacterSize(24);
    playerLevel.setStyle(sf::Text::Bold);
    playerLevel.setPosition(sf::Vector2f(680, 10));
    playerLevel.setString("Nivel : " + std::to_string(level));

    //Game message
    sf::Text messageTXT;;
    messageTXT.setFont(font);
    messageTXT.setCharacterSize(44);
    messageTXT.setStyle(sf::Text::Bold);
    messageTXT.setString("Default Message");
    messageTXT.setPosition(sf::Vector2f(320, 250));

    //Arrow up - Down
    sf::Texture upDown;
    if (!upDown.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/UD.png")) {
        std::cout << "Error load image";
    }

    sf::RectangleShape arrow(sf::Vector2f(100, 70));
    float arrowX = 370;
    float arrowY = 400;
    float playerSpeed = 1.0f;
    arrow.setPosition(arrowX, arrowY);
    arrow.setTexture(&upDown);


    //create obstacles objects
    sf::Texture Obstaculo;
    if (!Obstaculo.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Obstaculo.png")) {
        std::cout << "Error load image";
    }
    //create blok array
    block blockObj[7];

    //build meteor objets
    buildobstacles(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[44];
    bluidPoints(pointsObj, Point);

    int x = 850;
    int y = 60;
    bool front = false;
    sf::Texture ghostTexture;
    if (!ghostTexture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma1.png")) {
        std::cout << "Error load image";
    }

    //******************************************************************************************
    sf::RenderWindow window(sf::VideoMode(910, 650), "PacManCE");

    //Creación de formas y variables.
    sf::Texture backgroundPic;
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    if (!backgroundPic.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/fondo.png")) {
        std::cout << "Error load image";
    } else {
        TextureSize = backgroundPic.getSize(); //Get size of texture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float) WindowSize.y / TextureSize.y;     //Calculate scale.

        background.setTexture(backgroundPic);
        background.setScale(ScaleX, ScaleY);      //Set scale.
    }

    //sf::RectangleShape player(sf::Vector2f(70, 30));
    sf::Texture Up;
    sf::Texture Down;
    sf::Texture Right;
    sf::Texture Left;
    if (!Up.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Up.png")) {
        std::cout << "Error load image";
    }
    if (!Down.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Down.png")) {
        std::cout << "Error load image";
    }
    if (!Right.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Right.png")) {
        std::cout << "Error load image";
    }
    if (!Left.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Left.png")) {
        std::cout << "Error load image";
    }

    sf::Texture powerTexture;
    if (!powerTexture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Power.png")) {
        std::cout << "Error load image";
    }


    ghost = ghosts(x, y, front);
    ghost.setTexture(&ghostTexture);


    //player.setTexture(&texture);
    player player1 = player(420, 548, Right);
    lives live1 = lives(5, 610, Right);
    lives live2 = lives(100, 610, Right);
    lives live3 = lives(200, 610, Right);

    power fruit = power(310, 250, powerTexture);

    // set timepeFrame to 1 60th of a second. 60 frames per second
    sf::Time timePerFrame = sf::seconds(1.0f / 200.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // the clock object keeps the time.
    sf::Clock clock;
    clock.restart();


    //window.setFramerateLimit(160);
    while (window.isOpen()) {

        // chek if the close window button is clicked on.
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //get the time since last update and restart the clock
        timeSinceLastUpdate += clock.restart();
        //update every 60th of a second
        //only when the time since last update is greate than 1/60 update the world.


        if (timeSinceLastUpdate > timePerFrame) {

            // get keyboard input.
            if(press_flag) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    press_flag = false;


                    player1.setTexture(&Left);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_right && flag_up && flag_down) {
                                //player1.playerX += 0;
                                flag_left = false;
                            } else {
                                flag_left= true;
                                flag_up = true;
                                flag_right = true;
                                flag_down = true;

                            }
                        }
                    }

                    if (flag_left) {
                        if (player1.playerX <= 2) {
                            player1.playerX = player1.playerX - 0;
                        } else {
                            player1.playerX = player1.playerX - player1.playerSpeed;
                        }
                    }


                }
                press_flag = true;
            }

            if(press_flag) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    press_flag = false;
                    player1.setTexture(&Right);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left && flag_up && flag_down) {
                                //player1.playerX += 0;
                                flag_right = false;
                            } else {
                                flag_right = true;
                                flag_up = true;
                                flag_left = true;
                                flag_down = true;
                            }
                        }
                    }

                    if (flag_right) {
                        if (player1.playerX > 860) {
                            player1.playerX += 0;
                        } else {
                            player1.playerX = player1.playerX + player1.playerSpeed;
                        }
                    }

                }
                press_flag = true;
            }

            if(press_flag) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    press_flag = false;
                    player1.setTexture(&Up);
                    for (int i = 0; i < 7; i++) {

                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {

                            if (flag_left && flag_right && flag_down) {
                                //player1.playerX += 0;
                                flag_up = false;
                            } else {
                                flag_up = true;
                                flag_right = true;
                                flag_left = true;
                                flag_down = true;
                            }
                        }
                    }

                    if (flag_up) {
                        if (player1.playerY < 52) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY - player1.playerSpeed;
                        }
                    }

                }
                press_flag = true;
            }

            if(press_flag) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    press_flag = false;
                    player1.setTexture(&Down);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left && flag_up && flag_right) {
                                //player1.playerX += 0;
                                flag_down = false;
                            } else {
                                flag_down = true;
                                flag_right = true;
                                flag_up = true;
                                flag_left = true;
                            }
                        }
                    }

                    if (flag_down) {
                        if (player1.playerY > 548) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY + player1.playerSpeed;
                        }
                    }
                }
                press_flag = true;

                for(int i = 0; i < 44; i++){
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score+=10));
                        pointsObj[i].setPosition(1000,1000);

                    }
                }
            }

            if(direccion1 == 'u'){
                float sx;
                float sy;
                sx = ghost.getghostX();
                sy = ghost.getghostY() - ghost.speed;
                ghost.setghostX(sx);
                ghost.setghostY(sy);
                ghost.setPosition(sx, sy);
            }

            if(direccion1 == 'd'){
                float sx;
                float sy;
                sx = ghost.getghostX();
                sy = ghost.getghostY() + ghost.speed;
                ghost.setghostX(sx);
                ghost.setghostY(sy);
                ghost.setPosition(sx, sy);
            }
            if(direccion1 == 'r'){
                float sx;
                float sy;
                sx = ghost.getghostX()+ ghost.speed;;
                sy = ghost.getghostY() ;
                ghost.setghostX(sx);
                ghost.setghostY(sy);
                ghost.setPosition(sx, sy);
            }
            if(direccion1 == 'l'){
                float sx;
                float sy;
                sx = ghost.getghostX() - ghost.speed;;
                sy = ghost.getghostY() ;
                ghost.setghostX(sx);
                ghost.setghostY(sy);
                ghost.setPosition(sx, sy);
            }

            // update player position
            player1.setPosition(player1.playerX, player1.playerY);
            // clear the screen and draw all the shapes
            window.clear();
            window.draw(background);
            window.draw(lineTop, 5, sf::Lines);
            window.draw(line, 5, sf::Lines);


            for (int i = 0; i < 7; i++)//draw walls
            {
                window.draw(blockObj[i]);
            }
            for (int i = 0; i < 44; i++)//draw walls
            {
                window.draw(pointsObj[i]);
            }

            window.draw(scoreText);

            window.draw(playerLevel);

            // reset the timeSinceLastUpdate to 0
            timeSinceLastUpdate = sf::Time::Zero;
            loop++;
        }

        window.draw(ghost);


        //Muestra las vidas del jugador
        if (playerLives == 3) {

            window.draw(live1);
            window.draw(live2);
            window.draw(live3);
        }
        else if (playerLives == 2) {

            window.draw(live1);
            window.draw(live2);
        }
        else if (playerLives == 1) {
            window.draw(live1);
        }
        window.draw(player1);

        if (score == 200){
            turnPoweron_1 = true;
        }

        if (turnPoweron_1 == true){
            fruit.setPosition(10, 65);
            window.draw(fruit);
        }

        if (score == 400){
            turnPoweron_2 = true;
        }
        if (turnPoweron_2 == true){
            fruit.setPosition(845, 790);
            window.draw(fruit);
        }

        //Detecta si la puntuación máxima fue alcanzada
        if (score == 440) {
            if (nivel == 1) {
                window.close();
                PacMan2 pacman;
                return pacman.game(cantidad_fantasmas +1, nivel + 1, score);;
            }
        }

        //Menu control Exit game or Play again
        if (juego == false) {
            window.draw(messageTXT);
            window.draw(arrow);

            if (ghostLeft > 0) {
                messageTXT.setString("You Lose!");
                window.draw(messageTXT);
                win = true;
            } else if (win == false) {
                messageTXT.setString("You Won!");
                window.draw(messageTXT);
                win = true;
                //exit game
                window.close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition( window );
            cout << "x" << static_cast<float>( mousePos.x ) << endl;
            cout << "y" << static_cast<float>( mousePos.y ) << endl;
        }








        window.display();
    }

    return 0;
}
