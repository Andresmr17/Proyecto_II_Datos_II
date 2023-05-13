#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan4.h"
#include "../Resorces/block.h"
#include "../Player/lives.h"
#include "../Player/player.h"
#include "../Resorces/points.h"
#include "../Resorces/power.h"
#include "../ghosts/ghosts.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool ghost_move4 = true;
int playerLives4 = 3;
int loop4 = 1;
bool juego4 = true;
int randomEnemy4 = 0;
int countDeadEnemy4 = 0;
bool isDeath4 = false;

bool press_flag4 = true;
bool flag_up4 = true;
bool flag_down4 = true;
bool flag_right4 = true;
bool flag_left4 = true;

char direccion_lvl4 = 'd';

bool turnPoweron4_1 = false;
bool turnPoweron4_2 = false;
bool eaten4 = false;

void buildobstacles4(block blockObj[7], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 475, 500, 70, Obstaculo);
    blockObj[1]= block(640, 475, 200, 70, Obstaculo);
    blockObj[2]= block(720, 105, 120, 370, Obstaculo);
    blockObj[3]= block(550, 105, 100, 300, Obstaculo);
    blockObj[4]= block(370, 105, 100, 370, Obstaculo);
    blockObj[5]= block(70, 310, 300, 100, Obstaculo);
    blockObj[6]= block(70, 110, 230, 130, Obstaculo);
}
void bluidPoints4(points pointsObj[], sf::Texture &Point){
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

int PacMan4::game(int nivel, int puntuacion) {
    ghosts ghost;

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
    buildobstacles4(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[44];
    bluidPoints4(pointsObj, Point);
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

    ghost = ghosts(5, 60, front);
    ghost.setTexture(&ghostTexture);

    sf::Texture powerTexture;
    if (!powerTexture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Power.png")) {
        std::cout << "Error load image";
    }

    //obj[cantidad_fantasmas].move(i,d);

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
            if(press_flag4) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    press_flag4 = false;
                    player1.setTexture(&Left);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_right4 && flag_up4 && flag_down4) {
                                //player1.playerX += 0;
                                flag_left4 = false;
                            } else {
                                flag_left4 = true;
                                flag_up4 = true;
                                flag_right4 = true;
                                flag_down4 = true;
                            }
                        }
                    }
                    if (flag_left4) {
                        if (player1.playerX <= 2) {
                            player1.playerX = player1.playerX - 0;
                        } else {
                            player1.playerX = player1.playerX - player1.playerSpeed;
                        }
                    }
                }
                press_flag4 = true;
            }
            if(press_flag4) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    press_flag4 = false;
                    player1.setTexture(&Right);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left4 && flag_up4 && flag_down4) {
                                //player1.playerX += 0;
                                flag_right4 = false;
                            } else {
                                flag_right4 = true;
                                flag_up4 = true;
                                flag_left4 = true;
                                flag_down4 = true;
                            }
                        }
                    }
                    if (flag_right4) {
                        if (player1.playerX > 860) {
                            player1.playerX += 0;
                        } else {
                            player1.playerX = player1.playerX + player1.playerSpeed;
                        }
                    }
                }
                press_flag4 = true;
            }
            if(press_flag4) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    press_flag4 = false;
                    player1.setTexture(&Up);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left4 && flag_right4 && flag_down4) {
                                //player1.playerX += 0;
                                flag_up4 = false;
                            } else {
                                flag_up4 = true;
                                flag_right4 = true;
                                flag_left4 = true;
                                flag_down4 = true;
                            }
                        }
                    }
                    if (flag_up4) {
                        if (player1.playerY < 52) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY - player1.playerSpeed;
                        }
                    }
                }
                press_flag4 = true;
            }
            if(press_flag4) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    press_flag4 = false;
                    player1.setTexture(&Down);
                    for (int i = 0; i < 7; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left4 && flag_up4 && flag_right4) {
                                //player1.playerX += 0;
                                flag_down4 = false;
                            } else {
                                flag_down4 = true;
                                flag_right4 = true;
                                flag_up4 = true;
                                flag_left4 = true;
                            }
                        }
                    }
                    if (flag_down4) {
                        if (player1.playerY > 548) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY + player1.playerSpeed;
                        }
                    }
                }
                press_flag4 = true;
                for(int i = 0; i < 44; i++){
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score+=10));
                        pointsObj[i].setPosition(1000,1000);
                    }
                }
            }

            //Movimiento del fantasma
            if (ghost_move4){
                if (loop4 % 10 == 0 )
                {
                    if(ghost.getghostX() > 3 && ghost.getghostX() < 63 && ghost.getghostY() > 240 && ghost.getghostY() < 245){
                        char dir[2] = {'r', 'd'};
                        int num = rand()%2;
                        direccion_lvl4 = dir[0];
                        cout << num << endl;
                    }
                    if(direccion_lvl4 == 'd'){
                        float sx;
                        float sy;
                        sx = ghost.getghostX();
                        sy = ghost.getghostY() + ghost.speed;
                        ghost.setghostX(sx);
                        ghost.setghostY(sy);
                        ghost.setPosition(sx, sy);
                        loop4++;
                    }
                    if(direccion_lvl4 == 'r'){
                        float sx;
                        float sy;
                        sx = ghost.getghostX()+ ghost.speed;;
                        sy = ghost.getghostY() ;
                        ghost.setghostX(sx);
                        ghost.setghostY(sy);
                        ghost.setPosition(sx, sy);
                        loop4++;

                    }
                }
                loop4++;
            }


            /*if(sf::Event::MouseButtonPressed){
                sf::Mouse::getPosition( window );
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                cout << static_cast<float>( mousePos.x ) << endl;
                cout << static_cast<float>( mousePos.y ) << endl;
            }*/

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
            for (int i = 0; i < 44; i++)//draw points
            {
                window.draw(pointsObj[i]);
            }
            window.draw(scoreText);

            window.draw(playerLevel);

            window.draw(ghost);

            // reset the timeSinceLastUpdate to 0
            timeSinceLastUpdate = sf::Time::Zero;

        }

        //Dibuja fantasmas



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
        if (playerLives4 == 3) {
            window.draw(live1);
            window.draw(live2);
            window.draw(live3);
        }
        else if (playerLives4 == 2) {
            window.draw(live1);
            window.draw(live2);
        }
        else if (playerLives4 == 1) {
            window.draw(live1);
        }
        window.draw(player1);

        if (score == 1400){
            turnPoweron4_1 = true;
        }

        if (turnPoweron4_1 == true){
            fruit.setPosition(310, 250);
            window.draw(fruit);
        }

        if (score == 1600){
            turnPoweron4_2 = true;
        }

        if (turnPoweron4_2 == true){
            fruit.setPosition(585, 500);
            window.draw(fruit);
        }

        //Detecta si la puntuación máxima fue alcanzada
        if (score == 1760) {
            if (nivel == 4) {
                juego4 == false;
                window.close();
            }
        }

        /*else if(player){

        }*/

        //Menu control Exit game or Play again

        window.display();
    }
    return 0;
}