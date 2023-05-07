#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan.h"
#include "PacMan2.h"
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


int playerLives2 = 3;
int loop2 = 1;
bool juego2 = true;
int randomEnemy2 = 0;
int countDeadEnemy2 = 0;

float deltaTime2 = 1.0f / 60.0f;

bool isDeath2 = false;
bool press_flag2 = true;
bool flag_up2 = true;
bool flag_down2 = true;
bool flag_right2 = true;
bool flag_left2 = true;



void buildobstacles2(block blockObj[7], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 475, 500, 70, Obstaculo);
    blockObj[1]= block(640, 475, 200, 70, Obstaculo);
    blockObj[2]= block(720, 105, 120, 370, Obstaculo);
    blockObj[3]= block(550, 105, 100, 300, Obstaculo);
    blockObj[4]= block(370, 105, 100, 370, Obstaculo);
    blockObj[5]= block(70, 310, 300, 100, Obstaculo);
    blockObj[6]= block(70, 110, 230, 130, Obstaculo);

}

void bluidPoints2(points pointsObj[], sf::Texture &Point){

    int posiciones_puntos[44][2]={{20,555},{120,555},{220,555},{320, 555},{550, 555},{650,555},
                                  {750, 555},{850, 555},{860,450},{860,350},{860,250},{860,150},
                                  {860,65},{760,65},{660,65},{560, 65},{460, 65},{360, 65},
                                  {260, 65},{160, 65},{60, 65},{20,125},{20, 205},{20, 305},
                                  {20, 405},{20, 480},{590, 500},{590, 430},{670, 430},{670, 330},
                                  {670, 230},{670, 140},{500, 430},{500, 330},{500, 230},{500,130},
                                  {100, 430},{200, 430},{300, 430},{100,260},{200,260},{300, 260},{320,200},
                                  {320,120}
    };

    for(int i = 0; i < 44; i++){
        pointsObj[i] = points(posiciones_puntos[i][0],posiciones_puntos[i][1], Point);

    }
}

int PacMan2::game(int cantidad_fantasmas, int nivel, int puntuacion) {
    ghosts obj[cantidad_fantasmas];
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
    if (!font.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/font/arial.ttf")) {
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
    if (!upDown.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/UD.png")) {
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
    if (!Obstaculo.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Obstaculo.png")) {
        std::cout << "Error load image";
    }
    //create blok array
    block blockObj[7];

    //build meteor objets
    buildobstacles2(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[44];
    bluidPoints2(pointsObj, Point);

    int x = 850;
    int y = 60;
    bool front = false;
    sf::Texture ghostTexture;
    if (!ghostTexture.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Fantasma1.png")) {
        std::cout << "Error load image";
    }

    //******************************************************************************************
    sf::RenderWindow window(sf::VideoMode(910, 650), "PacManCE");

    //Creación de formas y variables.
    sf::Texture backgroundPic;
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    if (!backgroundPic.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/fondo.png")) {
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
    if (!Up.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Up.png")) {
        std::cout << "Error load image";
    }
    if (!Down.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Down.png")) {
        std::cout << "Error load image";
    }
    if (!Right.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Right.png")) {
        std::cout << "Error load image";
    }
    if (!Left.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Left.png")) {
        std::cout << "Error load image";
    }

    //Crea objetos enemigos
    for (int i = 0; i < cantidad_fantasmas; i++) {

        y += 60;
        if (y >= 750) {
            y = 380;
            x += 60;
        }
        obj[i] = ghosts(x, y, front);
        obj[i].setTexture(&ghostTexture);
    }

    //player.setTexture(&texture);
    player player1 = player(420, 548, Right);
    lives live1 = lives(5, 610, Right);
    lives live2 = lives(100, 610, Right);
    lives live3 = lives(200, 610, Right);

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
            if(press_flag2) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    press_flag2 = false;


                    player1.setTexture(&Left);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_right2 && flag_up2 && flag_down2) {
                                //player1.playerX += 0;
                                flag_left2 = false;
                            } else {
                                flag_left2 = true;
                                flag_up2 = true;
                                flag_right2 = true;
                                flag_down2 = true;

                            }
                        }
                    }

                    if (flag_left2) {
                        if (player1.playerX <= 2) {
                            player1.playerX = player1.playerX - 0;
                        } else {
                            player1.playerX = player1.playerX - player1.playerSpeed;
                        }
                    }


                }
                press_flag2 = true;
            }

            if(press_flag2) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    press_flag2 = false;
                    player1.setTexture(&Right);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left2 && flag_up2 && flag_down2) {
                                //player1.playerX += 0;
                                flag_right2 = false;
                            } else {
                                flag_right2 = true;
                                flag_up2 = true;
                                flag_left2 = true;
                                flag_down2 = true;
                            }
                        }
                    }

                    if (flag_right2) {
                        if (player1.playerX > 860) {
                            player1.playerX += 0;
                        } else {
                            player1.playerX = player1.playerX + player1.playerSpeed;
                        }
                    }

                }
                press_flag2 = true;
            }

            if(press_flag2) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    press_flag2 = false;
                    player1.setTexture(&Up);
                    for (int i = 0; i < 7; i++) {

                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {

                            if (flag_left2 && flag_right2 && flag_down2) {
                                //player1.playerX += 0;
                                flag_up2 = false;
                            } else {
                                flag_up2 = true;
                                flag_right2 = true;
                                flag_left2 = true;
                                flag_down2 = true;
                            }
                        }
                    }

                    if (flag_up2) {
                        if (player1.playerY < 52) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY - player1.playerSpeed;
                        }
                    }

                }
                press_flag2 = true;
            }

            if(press_flag2) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    press_flag2 = false;
                    player1.setTexture(&Down);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left2 && flag_up2 && flag_right2) {
                                //player1.playerX += 0;
                                flag_down2 = false;
                            } else {
                                flag_down2 = true;
                                flag_right2 = true;
                                flag_up2 = true;
                                flag_left2 = true;
                            }
                        }
                    }

                    if (flag_down2) {
                        if (player1.playerY > 548) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY + player1.playerSpeed;
                        }
                    }
                }
                press_flag2 = true;

                for(int i = 0; i < 44; i++){
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score+=10));
                        pointsObj[i].setPosition(1000,1000);

                    }
                }
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
            loop2++;
        }

        //Dibuja enemigos vivos
        for (int i = 0; i < cantidad_fantasmas; i++)
        {
            if (obj[i].ghostDeath == false) {
                if (loop2 % 60 == 0) {
                    obj[i].setTexture(&ghostTexture);
                } else if (loop2 % 30 == 0) {
                    obj[i].setTexture(&ghostTexture);
                }
                window.draw(obj[i]);
            }
        }

        obj[cantidad_fantasmas].moveGhost(deltaTime2);

        /*//Si el enemigo alcanza al jugador
        for (int b = 0; b < cantidad_fantasmas - countDeadEnemy; b++)
        {
            if (obj[b].getGlobalBounds().intersects(player1.getGlobalBounds()) && obj[b].isDeath == false) {
                playerLives -=1;
                if (playerLives == 0)
                {
                    juego = false;
                }
            }
        }*/

        //Muestra las vidas del jugador
        if (playerLives2 == 3) {

            window.draw(live1);
            window.draw(live2);
            window.draw(live3);
        }
        else if (playerLives2 == 2) {

            window.draw(live1);
            window.draw(live2);
        }
        else if (playerLives2 == 1) {
            window.draw(live1);
        }
        window.draw(player1);

        //Detecta si la puntuación máxima fue alcanzada
        /*if (score == 440) {
            if (nivel != 4) {
                PacMan2 pacman;
                return pacman.game(1+1,1+1);;
            }
            if (juego) {
                if (nivel == 4) {
                    nivel = 0;
                }

                window.close();
                PacMan pacMan;
                return pacMan.game(cantidad_fantasmas + 1, nivel + 1);

            }
        }*/

        //Menu control Exit game or Play again
        if (juego2 == false) {
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

        window.display();
    }


    return 0;
}
