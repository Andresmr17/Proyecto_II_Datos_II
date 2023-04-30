#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan.h"
#include "../block.h"
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

bool leftRight = false;
bool moveDown = false;
bool isSpacePressed = false;
int countEnemyShoot = 0;
int countEnemyDeadBullets = 0;
int countShot = 0;
int countDeadBullets = 0;
int countDeadEnemy = 0;
int playerLives = 3;
bool game = true;
int bullettsStartX = 0;
int bulletStartMoveUp = 563;
int loop = 1;
int selectEnemyToShoot = 0;
int enemyLeft = 1;
bool juego = true;
bool notShoot = true;
int randomEnemy = 0;
int countEnemyShootDifference = 0;

//enemy obj[1];

void buildShelter(block blockObj[36], sf::Texture &meteor)
{
    float bblockX = 150;
    float bblockY = 450;
    float tempx = 0;
    float tempy = 0;
    int counter = 0;
    for(int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            bblockX += 20;
            if (bblockY == 480 && bblockX == 190 || bblockY == 480 && bblockX == 390 || bblockY == 480 && bblockX == 590)
            {
                //Do nothing
            }
            else
            {
                blockObj[counter] = block(bblockX, bblockY);
                blockObj[counter].setTexture(&meteor);
                counter++;
            }

        }
        bblockX += 140;
        if (bblockX == 750)
        {
            bblockX = 150;
            bblockY += 10;
        }

        if (bblockX == 0 && bblockY == -50)
        {
            bblockX = tempx;
            bblockY = tempy;
        }

    }
}


int PacMan::game()
{

    bool win = false;
    int score = 0;
    int kill = 1;
    int level = 1;
    bool levelUp = false;
    bool playSound = false;
    int highScoreInt = 0;
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
    if (!font.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/font/arial.ttf"))
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
    if (!upDown.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/UD.png"))
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
    sf::Texture meteor;
    if (!meteor.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Obstaculo.png"))
    {
        std::cout << "Error load image";
    }
    //create blok array
    block blockObj[33];
    float bblockX = 150;
    float bblockY = 450;
    float tempx = 0;
    float tempy = 0;
    //build meteor objets
    buildShelter(blockObj, meteor);

    sf::Texture enemyTexture;
    sf::Texture enemyTexture1;
    if (!enemyTexture.loadFromFile("images/fantasma1.png"))
    {
        std::cout << "Error load image";
    }

    /*
    //create enemy objects
    for (int i = 0; i < 1; i++)
    {
        x += 40;
        if (x >= 560)
        {
            x = 40;
            y += 50;
        }
        if (i>39)
            front = true;
        else
            front = false;
        obj[i] = enemy(x, y, front);
        if (i % 2 == 0)
            obj[i].setTexture(&enemyTexture);
        else
            obj[i].setTexture(&enemyTexture1);

    }*/

    //******************************************************************************************
    sf::RenderWindow window(sf::VideoMode(900, 650), "PacManCE");

    //Creación de formas y variables.
    sf::Texture backgroundPic;
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    if (!backgroundPic.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/fondo.png"))
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
    sf::Texture texture;
    if (!texture.loadFromFile("/home/luis/CLionProjects/Proyecto_II_Datos_II/images/Jugador.png"))
    {
        std::cout << "Error load image";
    }

    //player.setTexture(&texture);
    player player1 = player(0, 560, texture);
    lives live1 = lives(0, 610, texture);
    lives live2 = lives(100, 610, texture);
    lives live3 = lives(200, 610, texture);

    // set timepeFrame to 1 60th of a second. 60 frames per second
    sf::Time timePerFrame = sf::seconds(1.0f / 200.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    // the clock object keeps the time.
    sf::Clock clock;
    clock.restart();

    //window.setFramerateLimit(160);
    while (window.isOpen())
    {

        // chek if the close window button is clicked on.
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //get the time since last update and restart the clock
        timeSinceLastUpdate += clock.restart();
        //update every 60th of a second
        //only when the time since last update is greate than 1/60 update the world.


        if (timeSinceLastUpdate > timePerFrame)
        {

            // get keyboard input.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                player1.playerX = player1.playerX - player1.playerSpeed;
                if (player1.playerX <= -30)
                    player1.playerX = 730;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                player1.playerX = player1.playerX + player1.playerSpeed;
                if (player1.playerX > 760)
                    player1.playerX = 0;
            }
            /*
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                player1.playerX = player1.playerX - player1.playerSpeed;
                if (player1.playerX <= -30)
                    player1.playerX = 730;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                player1.playerX = player1.playerX + player1.playerSpeed;
                if (player1.playerX > 760)
                    player1.playerX = 0;
            }*/


            // update player position
            player1.setPosition(player1.playerX, player1.playerY);
            // clear the screen and draw all the shapes
            window.clear();
            window.draw(background);


            window.draw(lineTop, 5, sf::Lines);


            window.draw(line, 5, sf::Lines);

            /*
            for (int i = 0; i < 52; i++)//draw alive enemies
            {
                if (obj[i].enemyDeath == false)
                {
                    if (loop % 60 == 0)
                    {
                        if (i % 2 == 0)
                            obj[i].setTexture(&enemyTexture);
                        else
                            obj[i].setTexture(&enemyTexture1);
                    }
                    else if (loop % 30 == 0)
                    {
                        if (i % 2 == 0)
                            obj[i].setTexture(&enemyTexture1);
                        else
                            obj[i].setTexture(&enemyTexture);
                    }
                    window.draw(obj[i]);
                }
            }*/

            //Muestra las vidas del jugador
            if (playerLives == 3)
            {
                window.draw(live1);
                window.draw(live2);
                window.draw(live3);
            }
            else if (playerLives == 2)
            {
                window.draw(live1);
                window.draw(live2);
            }
            else if (playerLives == 1)
            {
                window.draw(live1);
            }
            window.draw(player1);

            for (int i = 0; i < 33; i++)//draw walls
            {
                if (blockObj[i].isDestroyed == false)
                    window.draw(blockObj[i]);
            }

            /*
            if (enemyLeft == 0)//all enemy died
            {
                if (level >= 5)
                {
                    game = false;
                }

                if (game)
                {

                    level++;
                    enemyLeft = 52;
                    kill = 40 + level * 2;

                    if (playerLives < 3)
                        playerLives++;

                    en.setClassSpeed(level);
                    countEnemyShoot = 0;
                    countEnemyDeadBullets = 0;
                    countShot = 0;
                    countDeadBullets = 0;
                    score += 500;
                    playerLevel.setString("Level : " + std::to_string(level));
                    scoreText.setString("Score : " + std::to_string(score));
                    resetBullets();
                }

            }*/

            window.draw(scoreText);

            window.draw(playerLevel);

            // reset the timeSinceLastUpdate to 0
            timeSinceLastUpdate = sf::Time::Zero;
            loop++;
            flyCount++;
        }

        //Menu control Exit game or Play again
        if (juego == false)
        {
            window.draw(messageTXT);
            window.draw(arrow);

            if (enemyLeft > 0)
            {
                messageTXT.setString("You Lose!");
                window.draw(messageTXT);
                win = true;
            }
            else if(win == false)
            {
                messageTXT.setString("You Won!");
                window.draw(messageTXT);
                win = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                win = false;
                level = 1;
                kill = 40;
                if(score>highScoreInt)
                    highScoreInt = score;

                //	gameWinner = false;
                //en.setClassSpeed(0.5f);

                score = 0;

                playerLevel.setString("Level : " + std::to_string(level));
                scoreText.setString("Score : " + std::to_string(score));

                //resetBullets();


                //rebuild all meteors
                buildShelter(blockObj, meteor);

                juego = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                //exit game
                window.close();
            }
        }

        window.display();

    }
    return 0;
}