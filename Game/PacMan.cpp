#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan.h"
#include "../block.h"
#include "../points.h"
//#include "fields.h"
//#include "enemy.h"
//#include "enemyFly.h"
#include "../Player/lives.h"
#include "../Player/player.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int playerLives = 3;
bool game = true;

int loop = 1;

int enemyLeft = 1;
bool juego = true;

int randomEnemy = 0;

bool press_flag = true;


bool flag_up = true;
bool flag_down = true;
bool flag_right = true;
bool flag_left = true;


//enemy obj[1];

void buildObstacles(block blockObj[7], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 475, 500, 70, Obstaculo);
    blockObj[1]= block(640, 475, 200, 70, Obstaculo);
    blockObj[2]= block(720, 105, 120, 370, Obstaculo);
    blockObj[3]= block(550, 105, 100, 300, Obstaculo);
    blockObj[4]= block(370, 105, 100, 370, Obstaculo);
    blockObj[5]= block(70, 310, 300, 100, Obstaculo);
    blockObj[6]= block(70, 110, 230, 130, Obstaculo);

}

void buildPoints(){

}


int PacMan::game()
{

    bool win = false;
    int score = 0;
    int kill = 1;
    int level = 1;
    int flyCount = 0;
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
    if (!font.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/font/arial.ttf"))
    {
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
    if (!upDown.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/UD.png"))
    {
        std::cout << "Error load image";
    }

    sf::RectangleShape arrow(sf::Vector2f(100, 70));
    float arrowX = 370;
    float arrowY = 400;
    float playerSpeed = 1.0f;
    arrow.setPosition(arrowX, arrowY);
    arrow.setTexture(&upDown);

    //enemy en;//static member of enemy class

    //create meteor objects
    sf::Texture Obstaculo;
    if (!Obstaculo.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Obstaculo.png"))
    {
        std::cout << "Error load image";
    }
    //create blok array
    block blockObj[7];
    //build meteor objets
    buildObstacles(blockObj, Obstaculo);


    sf::Texture Point;
    if (!Obstaculo.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/"))
    {
        std::cout << "Error load image";
    }
    points pointsObj[40];
    //buildPoints(pointsObj)

    sf::Texture enemyTexture;
    sf::Texture enemyTexture1;
    if (!enemyTexture.loadFromFile("images/fantasma1.png"))
    {
        std::cout << "Error load image";
    }

    //******************************************************************************************
    sf::RenderWindow window(sf::VideoMode(910, 650), "PacManCE");

    //Creación de formas y variables.
    sf::Texture backgroundPic;
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    if (!backgroundPic.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/fondo.png"))
    {
        std::cout << "Error load image";
    }
    else
    {
        TextureSize = backgroundPic.getSize(); //Get size of texture.
        WindowSize = window.getSize();             //Get size of window.

        float ScaleX = (float)WindowSize.x / TextureSize.x;
        float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

        background.setTexture(backgroundPic);
        background.setScale(ScaleX, ScaleY);      //Set scale.
    }

    //sf::RectangleShape player(sf::Vector2f(70, 30));
    sf::Texture Up;
    sf::Texture Down;
    sf::Texture Right;
    sf::Texture Left;
    if (!Up.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Up.png"))
    {
        std::cout << "Error load image";
    }
    if (!Down.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Down.png"))
    {
        std::cout << "Error load image";
    }
    if (!Right.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Right.png"))
    {
        std::cout << "Error load image";
    }
    if (!Left.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Left.png"))
    {
        std::cout << "Error load image";
    }

    //player.setTexture(&texture);
    player player1 = player(420, 548, Right);
    lives live1 = lives(0, 610, Right);
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
                                flag_left = true;
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
            }



            // update player position
            player1.setPosition(player1.playerX, player1.playerY);
            // clear the screen and draw all the shapes
            window.clear();
            window.draw(background);


            window.draw(lineTop, 5, sf::Lines);


            window.draw(line, 5, sf::Lines);




            //Muestra las vidas del jugador
            if (playerLives == 3) {
                window.draw(live1);
                window.draw(live2);
                window.draw(live3);
            } else if (playerLives == 2) {
                window.draw(live1);
                window.draw(live2);
            } else if (playerLives == 1) {
                window.draw(live1);
            }
            window.draw(player1);

            for (int i = 0; i < 33; i++)//draw walls
            {
                if (blockObj[i].isDestroyed == false)
                    window.draw(blockObj[i]);
            }

            window.draw(scoreText);

            window.draw(playerLevel);

            // reset the timeSinceLastUpdate to 0
            timeSinceLastUpdate = sf::Time::Zero;
            loop++;
            flyCount++;
        }

        //Menu control Exit game or Play again
        if (juego == false) {
            window.draw(messageTXT);
            window.draw(arrow);

            if (enemyLeft > 0) {
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