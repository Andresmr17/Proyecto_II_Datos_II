#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan3.h"
#include "PacMan4.h"
#include "../Resorces/power.h"
#include "../Resorces/block.h"
#include "../Resorces/puntuacion_final.h"
#include "../Player/lives.h"
#include "../Player/player.h"
#include "../Resorces/points.h"
#include "../ghosts/ghosts.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char direccion_lvl3[3] = {'d', 'd', 'd'};
bool backtracking_move_lvl3 = false;
bool pathfinding_move_lvl3 = true;
bool ghost_normal_move_lvl3 = true;

bool ghost1_flag1_lvl3 = true;
bool ghost1_flag2_lvl3 = true;
bool ghost1_flag3_lvl3 = true;

bool ghost2_flag1_lvl3 = true;
bool ghost2_flag2_lvl3 = true;
bool ghost2_flag3_lvl3 = true;

bool ghost3_flag1_lvl3 = true;
bool ghost3_flag2_lvl3 = true;
bool ghost3_flag3_lvl3 = true;

int playerLives3 = 3;
int loop3 = 1;
bool juego3 = true;
int randomEnemy3 = 0;
int countDeadEnemy3 = 0;

float deltaTime3 = 1.0f / 60.0f;

bool isDeath3 = false;
bool press_flag3 = true;
bool flag_up3 = true;
bool flag_down3 = true;
bool flag_right3 = true;
bool flag_left3 = true;

bool turnPoweron3_1 = false;
bool eaten3 = false;

int verification_lvl3 = 0;
bool power_player_lvl3 = false;
int eliminate_ghost_lvl3 = 0;
bool set_ghostlvl3 = false;
int counter3 = 0;
bool one_lvl3 = true;




/**
 * @brief se encarga de hacer la intancia de las paredes mostradas en el juego
 * @param blockObj el objeto que se desea instanciar
 * @param Obstaculo la imagen que se desea colocar
 * @return no tiene retorno
 */
void buildobstacles3(block blockObj[10], sf::Texture &Obstaculo) {
    blockObj[0] = block(120, 110, 670, 50, Obstaculo);
    blockObj[1] = block(120, 490, 670, 50, Obstaculo);
    blockObj[2] = block(70, 50, 50, 237, Obstaculo);
    blockObj[3] = block(70, 360, 50, 237, Obstaculo);
    blockObj[4] = block(790, 50, 50, 237, Obstaculo);
    blockObj[5] = block(790, 360, 50, 237, Obstaculo);
    blockObj[6] = block(190, 235, 600, 50, Obstaculo);
    blockObj[7] = block(120, 50, 670, 60, Obstaculo);
    blockObj[8] = block(120, 542, 670, 55, Obstaculo);
    blockObj[9] = block(190, 360, 600, 50, Obstaculo);
}

/**
 * @brief se encarga de instanciar los puntos que se van a mostrar en la pantalla de juego
 * @param pointsObj son los objetos puntos que se van a crear
 * @param Point corresponde a la imagen que se desea mostrar
 */
void bluidPoints3(points pointsObj[], sf::Texture &Point){

    int posiciones_puntos[36][2]={
            {860,65},{20,135},{20,215},{20,315},
            {20,405},{20,480},{80, 315},{135, 315},
            {810, 315},{860, 215},{860, 315},{860, 405},
            {860, 480},{135, 185},{235, 185},{335, 185},
            {435, 185},{535, 185},{635, 185},{735,185},
            {135, 440},{235, 440},{335, 440},{435,440},
            {535,440},{635, 440},{735,440},{750,315},
            {23, 79}, {323, 304},{423, 304}, {523, 304},
            {623, 304},{223, 304}, {864, 148}, {863, 565}
    };

    for(int i = 0; i < 36; i++){
        pointsObj[i] = points(posiciones_puntos[i][0],posiciones_puntos[i][1], Point);
        pointsObj[i].seteat(false);
    }
}

/**
 * @brief se encarga de crear la ventana de juego junto con todos los componentes que se muestran en el trascurso del juego
 * @param nivel corresponde al nivel que se esta jugando
 * @param puntuacion corresponde a la puntuacion que el jugador tiene
 * @return retorna un numero no significativo
 */
int PacMan3::game( int nivel, int puntuacion) {

    ghosts ghost[3];
    bool win = false;
    int score = puntuacion;
    int kill = 1;
    int level = nivel;
    int tempScore = 0;

    int ramon_x [4] = {10,10,850,500};
    int ramon_y [4] = {540,80,305,305};

    int a;
    int b;

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
    block blockObj[10];

    //build meteor objets
    buildobstacles3(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[36];
    bluidPoints3(pointsObj, Point);

    int x = 850;
    int y = 60;

    sf::Texture ghost1Texture;
    if (!ghost1Texture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma1.png")) {
        std::cout << "Error load image";
    }
    sf::Texture ghost2Texture;
    if (!ghost2Texture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma2.png")) {
        std::cout << "Error load image";
    }
    sf::Texture ghost3Texture;
    if (!ghost3Texture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma3.png")) {
        std::cout << "Error load image";
    }

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

    //Crea objetos enemigos
    ghost[0] = ghosts(x, y, front);
    ghost[0].setTexture(&ghost1Texture);

    ghost[1] = ghosts(x, 160, front);
    ghost[1].setTexture(&ghost2Texture);

    ghost[2] = ghosts(x, 260, front);
    ghost[2].setTexture(&ghost3Texture);

    //player.setTexture(&texture);
    player player1 = player(12, 539, Right);
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
            if(press_flag3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    press_flag3 = false;


                    player1.setTexture(&Left);
                    for (int i = 0; i < 10; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_right3 && flag_up3 && flag_down3) {
                                //player1.playerX += 0;
                                flag_left3 = false;
                            } else {
                                flag_left3 = true;
                                flag_up3 = true;
                                flag_right3 = true;
                                flag_down3 = true;

                            }
                        }
                    }

                    if (flag_left3) {
                        if (player1.playerX <= 2) {
                            player1.playerX = player1.playerX - 0;
                        } else {
                            player1.playerX = player1.playerX - player1.playerSpeed;
                        }
                    }


                }
                press_flag3 = true;
            }

            if(press_flag3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    press_flag3 = false;
                    player1.setTexture(&Right);
                    for (int i = 0; i < 10; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left3 && flag_up3 && flag_down3) {
                                //player1.playerX += 0;
                                flag_right3 = false;
                            } else {
                                flag_right3 = true;
                                flag_up3 = true;
                                flag_left3 = true;
                                flag_down3 = true;
                            }
                        }
                    }

                    if (flag_right3) {
                        if (player1.playerX > 860) {
                            player1.playerX += 0;
                        } else {
                            player1.playerX = player1.playerX + player1.playerSpeed;
                        }
                    }

                }
                press_flag3 = true;
            }

            if(press_flag3) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    press_flag3 = false;
                    player1.setTexture(&Up);
                    for (int i = 0; i < 10; i++) {

                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {

                            if (flag_left3 && flag_right3 && flag_down3) {
                                //player1.playerX += 0;
                                flag_up3 = false;
                            } else {
                                flag_up3 = true;
                                flag_right3 = true;
                                flag_left3 = true;
                                flag_down3 = true;
                            }
                        }
                    }

                    if (flag_up3) {
                        if (player1.playerY < 52) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY - player1.playerSpeed;
                        }
                    }

                }
                press_flag3 = true;
            }

            if(press_flag3) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    press_flag3 = false;
                    player1.setTexture(&Down);
                    for (int i = 0; i < 10; i++) {
                        if (blockObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                            if (flag_left3 && flag_up3 && flag_right3) {
                                //player1.playerX += 0;
                                flag_down3 = false;
                            } else {
                                flag_down3 = true;
                                flag_right3 = true;
                                flag_up3 = true;
                                flag_left3 = true;
                            }
                        }
                    }

                    if (flag_down3) {
                        if (player1.playerY > 548) {
                            player1.playerY += 0;
                        } else {
                            player1.playerY = player1.playerY + player1.playerSpeed;
                        }
                    }
                }
                press_flag3 = true;

                for(int i = 0; i < 36; i++){
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score+=10));
                        pointsObj[i].setPosition(1000,1000);
                        pointsObj[i].seteat(true); //Indica cual punto fue comido

                    }
                }
            }

            //Movimiento en backtracking
            if(backtracking_move_lvl3){

                //Movimiento del fantasma naranja
                if(ghost1_flag1_lvl3){
                    if(ghost[0].getghostX() > 845 && ghost[0].getghostX() < 852 && ghost[0].getghostY() > 301 && ghost[0].getghostY() < 305)//1
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[0] = dir[num];
                        ghost1_flag1_lvl3 = false;
                        ghost1_flag2_lvl3 = true;
                        ghost1_flag3_lvl3 = true;
                    }
                }
                if(ghost[0].getghostX() > 845 && ghost[0].getghostX() < 852 && ghost[0].getghostY() > 545 && ghost[0].getghostY() < 550)//2
                {
                    direccion_lvl3[0] = 'u';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }
                if(ghost[0].getghostX() > 845 && ghost[0].getghostX() < 852 && ghost[0].getghostY() > 73 && ghost[0].getghostY() < 75)//3
                {
                    direccion_lvl3[0] = 'd';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }

                if(ghost1_flag2_lvl3){
                    if(ghost[0].getghostX() > 137 && ghost[0].getghostX() < 140 && ghost[0].getghostY() > 301 && ghost[0].getghostY() < 305)//4
                    {
                        char dir[4] = {'l', 'd', 'u', 'r'};
                        srand(time(NULL));
                        int num = rand()%4;
                        direccion_lvl3[0] = dir[num];
                        ghost1_flag2_lvl3 = false;
                        ghost1_flag1_lvl3 = true;
                        ghost1_flag3_lvl3 = true;
                    }
                }
                if(ghost[0].getghostX() > 137 && ghost[0].getghostX() < 140 && ghost[0].getghostY() > 176 && ghost[0].getghostY() < 180)//5
                {
                    if(direccion_lvl3[0] == 'u'){
                        direccion_lvl3[0] = 'r';
                    }
                    if(direccion_lvl3[0] == 'l'){
                        direccion_lvl3[0] = 'd';
                        ghost1_flag2_lvl3 = true;
                    }

                }
                if(ghost[0].getghostX() > 743 && ghost[0].getghostX() < 745 && ghost[0].getghostY() > 176 && ghost[0].getghostY() < 180)//6
                {
                    direccion_lvl3[0] = 'l';
                }

                if(ghost[0].getghostX() > 137 && ghost[0].getghostX() < 140 && ghost[0].getghostY() > 435 && ghost[0].getghostY() < 439)//7
                {
                    if(direccion_lvl3[0] == 'd'){
                        direccion_lvl3[0] = 'r';
                    }
                    if(direccion_lvl3[0] == 'l'){
                        direccion_lvl3[0] = 'u';
                        ghost1_flag2_lvl3 = true;
                    }

                }
                if(ghost[0].getghostX() > 743 && ghost[0].getghostX() < 745 && ghost[0].getghostY() > 435 && ghost[0].getghostY() < 439)//8
                {
                    direccion_lvl3[0] = 'l';
                }

                if(ghost1_flag3_lvl3){
                    if(ghost[0].getghostX() > 16 && ghost[0].getghostX() < 18 && ghost[0].getghostY() > 301 && ghost[0].getghostY() < 305)//9
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[0] = dir[num];
                        ghost1_flag2_lvl3 = true;
                        ghost1_flag1_lvl3 = true;
                        ghost1_flag3_lvl3 = false;
                    }
                }
                if(ghost[0].getghostX() > 16 && ghost[0].getghostX() < 18 && ghost[0].getghostY() > 73 && ghost[0].getghostY() < 75)//10
                {
                    direccion_lvl3[0] = 'd';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }
                if(ghost[0].getghostX() > 16 && ghost[0].getghostX() < 18 && ghost[0].getghostY() > 545 && ghost[0].getghostY() < 550)//11
                {
                    direccion_lvl3[0] = 'u';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }

                //Movimiento del fantasma rosado
                if(ghost2_flag1_lvl3){
                    if(ghost[1].getghostX() > 845 && ghost[1].getghostX() < 852 && ghost[1].getghostY() > 301 && ghost[1].getghostY() < 305)//1
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[1] = dir[num];
                        ghost2_flag1_lvl3 = false;
                        ghost2_flag2_lvl3 = true;
                        ghost2_flag3_lvl3 = true;
                    }
                }
                if(ghost[1].getghostX() > 845 && ghost[1].getghostX() < 852 && ghost[1].getghostY() > 545 && ghost[1].getghostY() < 550)//2
                {
                    direccion_lvl3[1] = 'u';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }
                if(ghost[1].getghostX() > 845 && ghost[1].getghostX() < 852 && ghost[1].getghostY() > 73 && ghost[1].getghostY() < 75)//3
                {
                    direccion_lvl3[1] = 'd';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }

                if(ghost2_flag2_lvl3){
                    if(ghost[1].getghostX() > 137 && ghost[1].getghostX() < 140 && ghost[1].getghostY() > 301 && ghost[1].getghostY() < 305)//4
                    {
                        char dir[4] = {'l', 'd', 'u', 'r'};
                        srand(time(NULL));
                        int num = rand()%4;
                        direccion_lvl3[1] = dir[num];
                        ghost2_flag2_lvl3 = false;
                        ghost2_flag1_lvl3 = true;
                        ghost2_flag3_lvl3 = true;
                    }
                }
                if(ghost[1].getghostX() > 137 && ghost[1].getghostX() < 140 && ghost[1].getghostY() > 176 && ghost[1].getghostY() < 180)//5
                {
                    if(direccion_lvl3[1] == 'u'){
                        direccion_lvl3[1] = 'r';
                    }
                    if(direccion_lvl3[1] == 'l'){
                        direccion_lvl3[1] = 'd';
                        ghost2_flag2_lvl3 = true;
                    }

                }
                if(ghost[1].getghostX() > 743 && ghost[1].getghostX() < 745 && ghost[1].getghostY() > 176 && ghost[1].getghostY() < 180)//6
                {
                    direccion_lvl3[1] = 'l';
                }

                if(ghost[1].getghostX() > 137 && ghost[1].getghostX() < 140 && ghost[1].getghostY() > 435 && ghost[1].getghostY() < 439)//7
                {
                    if(direccion_lvl3[1] == 'd'){
                        direccion_lvl3[1] = 'r';
                    }
                    if(direccion_lvl3[1] == 'l'){
                        direccion_lvl3[1] = 'u';
                        ghost2_flag2_lvl3 = true;
                    }

                }
                if(ghost[1].getghostX() > 743 && ghost[1].getghostX() < 745 && ghost[1].getghostY() > 435 && ghost[1].getghostY() < 439)//8
                {
                    direccion_lvl3[1] = 'l';
                }

                if(ghost2_flag3_lvl3){
                    if(ghost[1].getghostX() > 16 && ghost[1].getghostX() < 18 && ghost[1].getghostY() > 301 && ghost[1].getghostY() < 305)//9
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[1] = dir[num];
                        ghost2_flag2_lvl3 = true;
                        ghost2_flag1_lvl3 = true;
                        ghost2_flag3_lvl3 = false;
                    }
                }
                if(ghost[1].getghostX() > 16 && ghost[1].getghostX() < 18 && ghost[1].getghostY() > 73 && ghost[1].getghostY() < 75)//10
                {
                    direccion_lvl3[1] = 'd';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }
                if(ghost[1].getghostX() > 16 && ghost[1].getghostX() < 18 && ghost[1].getghostY() > 545 && ghost[1].getghostY() < 550)//11
                {
                    direccion_lvl3[1] = 'u';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }
            }

            //Movimiento en pathfinding
            if(pathfinding_move_lvl3){
                if(ghost3_flag1_lvl3){
                    if(ghost[2].getghostX() > 845 && ghost[2].getghostX() < 852 && ghost[2].getghostY() > 301 && ghost[2].getghostY() < 305)//1
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[2] = dir[num];
                        ghost3_flag1_lvl3 = false;
                        ghost3_flag2_lvl3 = true;
                        ghost3_flag3_lvl3 = true;
                    }
                }
                if(ghost[2].getghostX() > 845 && ghost[2].getghostX() < 852 && ghost[2].getghostY() > 545 && ghost[2].getghostY() < 550)//2
                {
                    direccion_lvl3[2] = 'u';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }
                if(ghost[2].getghostX() > 845 && ghost[2].getghostX() < 852 && ghost[2].getghostY() > 73 && ghost[2].getghostY() < 75)//3
                {
                    direccion_lvl3[2] = 'd';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }

                if(ghost3_flag2_lvl3){
                    if(ghost[2].getghostX() > 137 && ghost[2].getghostX() < 140 && ghost[2].getghostY() > 301 && ghost[2].getghostY() < 305)//4
                    {
                        char dir[4] = {'l', 'd', 'u', 'r'};
                        srand(time(NULL));
                        int num = rand()%4;
                        direccion_lvl3[2] = dir[num];
                        ghost3_flag2_lvl3 = false;
                        ghost3_flag1_lvl3 = true;
                        ghost3_flag3_lvl3 = true;
                    }
                }
                if(ghost[2].getghostX() > 137 && ghost[2].getghostX() < 140 && ghost[2].getghostY() > 176 && ghost[2].getghostY() < 180)//5
                {
                    if(direccion_lvl3[2] == 'u'){
                        direccion_lvl3[2] = 'r';
                    }
                    if(direccion_lvl3[2] == 'l'){
                        direccion_lvl3[2] = 'd';
                        ghost3_flag2_lvl3 = true;
                    }

                }
                if(ghost[2].getghostX() > 743 && ghost[2].getghostX() < 745 && ghost[2].getghostY() > 176 && ghost[2].getghostY() < 180)//6
                {
                    direccion_lvl3[2] = 'l';
                }

                if(ghost[2].getghostX() > 137 && ghost[2].getghostX() < 140 && ghost[2].getghostY() > 435 && ghost[2].getghostY() < 439)//7
                {
                    if(direccion_lvl3[2] == 'd'){
                        direccion_lvl3[2] = 'r';
                    }
                    if(direccion_lvl3[2] == 'l'){
                        direccion_lvl3[2] = 'u';
                        ghost3_flag2_lvl3 = true;
                    }

                }
                if(ghost[2].getghostX() > 743 && ghost[2].getghostX() < 745 && ghost[2].getghostY() > 435 && ghost[2].getghostY() < 439)//8
                {
                    direccion_lvl3[2] = 'l';
                }

                if(ghost3_flag3_lvl3){
                    if(ghost[2].getghostX() > 16 && ghost[2].getghostX() < 18 && ghost[2].getghostY() > 301 && ghost[2].getghostY() < 305)//9
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[2] = dir[num];
                        ghost3_flag2_lvl3 = true;
                        ghost3_flag1_lvl3 = true;
                        ghost3_flag3_lvl3 = false;
                    }
                }
                if(ghost[2].getghostX() > 16 && ghost[2].getghostX() < 18 && ghost[2].getghostY() > 73 && ghost[2].getghostY() < 75)//10
                {
                    direccion_lvl3[2] = 'd';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }
                if(ghost[2].getghostX() > 16 && ghost[2].getghostX() < 18 && ghost[2].getghostY() > 545 && ghost[2].getghostY() < 550)//11
                {
                    direccion_lvl3[2] = 'u';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }

            }

            if(ghost_normal_move_lvl3){

                //Movimiento del fantasma naranja
                if(ghost1_flag1_lvl3){
                    if(ghost[0].getghostX() > 845 && ghost[0].getghostX() < 852 && ghost[0].getghostY() > 301 && ghost[0].getghostY() < 305)//1
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[0] = dir[num];
                        ghost1_flag1_lvl3 = false;
                        ghost1_flag2_lvl3 = true;
                        ghost1_flag3_lvl3 = true;
                    }
                }
                if(ghost[0].getghostX() > 845 && ghost[0].getghostX() < 852 && ghost[0].getghostY() > 545 && ghost[0].getghostY() < 550)//2
                {
                    direccion_lvl3[0] = 'u';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }
                if(ghost[0].getghostX() > 845 && ghost[0].getghostX() < 852 && ghost[0].getghostY() > 73 && ghost[0].getghostY() < 75)//3
                {
                    direccion_lvl3[0] = 'd';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }

                if(ghost1_flag2_lvl3){
                    if(ghost[0].getghostX() > 137 && ghost[0].getghostX() < 140 && ghost[0].getghostY() > 301 && ghost[0].getghostY() < 305)//4
                    {
                        char dir[4] = {'l', 'd', 'u', 'r'};
                        srand(time(NULL));
                        int num = rand()%4;
                        direccion_lvl3[0] = dir[num];
                        ghost1_flag2_lvl3 = false;
                        ghost1_flag1_lvl3 = true;
                        ghost1_flag3_lvl3 = true;
                    }
                }
                if(ghost[0].getghostX() > 137 && ghost[0].getghostX() < 140 && ghost[0].getghostY() > 176 && ghost[0].getghostY() < 180)//5
                {
                    if(direccion_lvl3[0] == 'u'){
                        direccion_lvl3[0] = 'r';
                    }
                    if(direccion_lvl3[0] == 'l'){
                        direccion_lvl3[0] = 'd';
                        ghost1_flag2_lvl3 = true;
                    }

                }
                if(ghost[0].getghostX() > 743 && ghost[0].getghostX() < 745 && ghost[0].getghostY() > 176 && ghost[0].getghostY() < 180)//6
                {
                    direccion_lvl3[0] = 'l';
                }

                if(ghost[0].getghostX() > 137 && ghost[0].getghostX() < 140 && ghost[0].getghostY() > 435 && ghost[0].getghostY() < 439)//7
                {
                    if(direccion_lvl3[0] == 'd'){
                        direccion_lvl3[0] = 'r';
                    }
                    if(direccion_lvl3[0] == 'l'){
                        direccion_lvl3[0] = 'u';
                        ghost1_flag2_lvl3 = true;
                    }

                }
                if(ghost[0].getghostX() > 743 && ghost[0].getghostX() < 745 && ghost[0].getghostY() > 435 && ghost[0].getghostY() < 439)//8
                {
                    direccion_lvl3[0] = 'l';
                }

                if(ghost1_flag3_lvl3){
                    if(ghost[0].getghostX() > 16 && ghost[0].getghostX() < 18 && ghost[0].getghostY() > 301 && ghost[0].getghostY() < 305)//9
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[0] = dir[num];
                        ghost1_flag2_lvl3 = true;
                        ghost1_flag1_lvl3 = true;
                        ghost1_flag3_lvl3 = false;
                    }
                }
                if(ghost[0].getghostX() > 16 && ghost[0].getghostX() < 18 && ghost[0].getghostY() > 73 && ghost[0].getghostY() < 75)//10
                {
                    direccion_lvl3[0] = 'd';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }
                if(ghost[0].getghostX() > 16 && ghost[0].getghostX() < 18 && ghost[0].getghostY() > 545 && ghost[0].getghostY() < 550)//11
                {
                    direccion_lvl3[0] = 'u';
                    ghost1_flag1_lvl3 = true;
                    ghost1_flag2_lvl3 = true;
                    ghost1_flag3_lvl3 = true;
                }

                //Movimiento del fantasma rosado
                if(ghost2_flag1_lvl3){
                    if(ghost[1].getghostX() > 845 && ghost[1].getghostX() < 852 && ghost[1].getghostY() > 301 && ghost[1].getghostY() < 305)//1
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[1] = dir[num];
                        ghost2_flag1_lvl3 = false;
                        ghost2_flag2_lvl3 = true;
                        ghost2_flag3_lvl3 = true;
                    }
                }
                if(ghost[1].getghostX() > 845 && ghost[1].getghostX() < 852 && ghost[1].getghostY() > 545 && ghost[1].getghostY() < 550)//2
                {
                    direccion_lvl3[1] = 'u';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }
                if(ghost[1].getghostX() > 845 && ghost[1].getghostX() < 852 && ghost[1].getghostY() > 73 && ghost[1].getghostY() < 75)//3
                {
                    direccion_lvl3[1] = 'd';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }

                if(ghost2_flag2_lvl3){
                    if(ghost[1].getghostX() > 137 && ghost[1].getghostX() < 140 && ghost[1].getghostY() > 301 && ghost[1].getghostY() < 305)//4
                    {
                        char dir[4] = {'l', 'd', 'u', 'r'};
                        srand(time(NULL));
                        int num = rand()%4;
                        direccion_lvl3[1] = dir[num];
                        ghost2_flag2_lvl3 = false;
                        ghost2_flag1_lvl3 = true;
                        ghost2_flag3_lvl3 = true;
                    }
                }
                if(ghost[1].getghostX() > 137 && ghost[1].getghostX() < 140 && ghost[1].getghostY() > 176 && ghost[1].getghostY() < 180)//5
                {
                    if(direccion_lvl3[1] == 'u'){
                        direccion_lvl3[1] = 'r';
                    }
                    if(direccion_lvl3[1] == 'l'){
                        direccion_lvl3[1] = 'd';
                        ghost2_flag2_lvl3 = true;
                    }

                }
                if(ghost[1].getghostX() > 743 && ghost[1].getghostX() < 745 && ghost[1].getghostY() > 176 && ghost[1].getghostY() < 180)//6
                {
                    direccion_lvl3[1] = 'l';
                }

                if(ghost[1].getghostX() > 137 && ghost[1].getghostX() < 140 && ghost[1].getghostY() > 435 && ghost[1].getghostY() < 439)//7
                {
                    if(direccion_lvl3[1] == 'd'){
                        direccion_lvl3[1] = 'r';
                    }
                    if(direccion_lvl3[1] == 'l'){
                        direccion_lvl3[1] = 'u';
                        ghost2_flag2_lvl3 = true;
                    }

                }
                if(ghost[1].getghostX() > 743 && ghost[1].getghostX() < 745 && ghost[1].getghostY() > 435 && ghost[1].getghostY() < 439)//8
                {
                    direccion_lvl3[1] = 'l';
                }

                if(ghost2_flag3_lvl3){
                    if(ghost[1].getghostX() > 16 && ghost[1].getghostX() < 18 && ghost[1].getghostY() > 301 && ghost[1].getghostY() < 305)//9
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[1] = dir[num];
                        ghost2_flag2_lvl3 = true;
                        ghost2_flag1_lvl3 = true;
                        ghost2_flag3_lvl3 = false;
                    }
                }
                if(ghost[1].getghostX() > 16 && ghost[1].getghostX() < 18 && ghost[1].getghostY() > 73 && ghost[1].getghostY() < 75)//10
                {
                    direccion_lvl3[1] = 'd';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }
                if(ghost[1].getghostX() > 16 && ghost[1].getghostX() < 18 && ghost[1].getghostY() > 545 && ghost[1].getghostY() < 550)//11
                {
                    direccion_lvl3[1] = 'u';
                    ghost2_flag1_lvl3 = true;
                    ghost2_flag2_lvl3 = true;
                    ghost2_flag3_lvl3 = true;
                }

                //Movimiento del fantasma celeste
                if(ghost3_flag1_lvl3){
                    if(ghost[2].getghostX() > 845 && ghost[2].getghostX() < 852 && ghost[2].getghostY() > 301 && ghost[2].getghostY() < 305)//1
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[2] = dir[num];
                        ghost3_flag1_lvl3 = false;
                        ghost3_flag2_lvl3 = true;
                        ghost3_flag3_lvl3 = true;
                    }
                }
                if(ghost[2].getghostX() > 845 && ghost[2].getghostX() < 852 && ghost[2].getghostY() > 545 && ghost[2].getghostY() < 550)//2
                {
                    direccion_lvl3[2] = 'u';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }
                if(ghost[2].getghostX() > 845 && ghost[2].getghostX() < 852 && ghost[2].getghostY() > 73 && ghost[2].getghostY() < 75)//3
                {
                    direccion_lvl3[2] = 'd';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }

                if(ghost3_flag2_lvl3){
                    if(ghost[2].getghostX() > 137 && ghost[2].getghostX() < 140 && ghost[2].getghostY() > 301 && ghost[2].getghostY() < 305)//4
                    {
                        char dir[4] = {'l', 'd', 'u', 'r'};
                        srand(time(NULL));
                        int num = rand()%4;
                        direccion_lvl3[2] = dir[num];
                        ghost3_flag2_lvl3 = false;
                        ghost3_flag1_lvl3 = true;
                        ghost3_flag3_lvl3 = true;
                    }
                }
                if(ghost[2].getghostX() > 137 && ghost[2].getghostX() < 140 && ghost[2].getghostY() > 176 && ghost[2].getghostY() < 180)//5
                {
                    if(direccion_lvl3[2] == 'u'){
                        direccion_lvl3[2] = 'r';
                    }
                    if(direccion_lvl3[2] == 'l'){
                        direccion_lvl3[2] = 'd';
                        ghost3_flag2_lvl3 = true;
                    }

                }
                if(ghost[2].getghostX() > 743 && ghost[2].getghostX() < 745 && ghost[2].getghostY() > 176 && ghost[2].getghostY() < 180)//6
                {
                    direccion_lvl3[2] = 'l';
                }

                if(ghost[2].getghostX() > 137 && ghost[2].getghostX() < 140 && ghost[2].getghostY() > 435 && ghost[2].getghostY() < 439)//7
                {
                    if(direccion_lvl3[2] == 'd'){
                        direccion_lvl3[2] = 'r';
                    }
                    if(direccion_lvl3[2] == 'l'){
                        direccion_lvl3[2] = 'u';
                        ghost3_flag2_lvl3 = true;
                    }

                }
                if(ghost[2].getghostX() > 743 && ghost[2].getghostX() < 745 && ghost[2].getghostY() > 435 && ghost[2].getghostY() < 439)//8
                {
                    direccion_lvl3[2] = 'l';
                }

                if(ghost3_flag3_lvl3){
                    if(ghost[2].getghostX() > 16 && ghost[2].getghostX() < 18 && ghost[2].getghostY() > 301 && ghost[2].getghostY() < 305)//9
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl3[2] = dir[num];
                        ghost3_flag2_lvl3 = true;
                        ghost3_flag1_lvl3 = true;
                        ghost3_flag3_lvl3 = false;
                    }
                }
                if(ghost[2].getghostX() > 16 && ghost[2].getghostX() < 18 && ghost[2].getghostY() > 73 && ghost[2].getghostY() < 75)//10
                {
                    direccion_lvl3[2] = 'd';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }
                if(ghost[2].getghostX() > 16 && ghost[2].getghostX() < 18 && ghost[2].getghostY() > 545 && ghost[2].getghostY() < 550)//11
                {
                    direccion_lvl3[2] = 'u';
                    ghost3_flag1_lvl3 = true;
                    ghost3_flag2_lvl3 = true;
                    ghost3_flag3_lvl3 = true;
                }

            }

            //Movimiento de los fantasmas
            for(int i = 0; i < 3; i++){
                if(direccion_lvl3[i] == 'u'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX();
                    sy = ghost[i].getghostY() - ghost[i].speed;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }

                if(direccion_lvl3[i] == 'd'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX();
                    sy = ghost[i].getghostY() + ghost[i].speed;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
                if(direccion_lvl3[i] == 'r'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX() + ghost[i].speed;;
                    sy = ghost[i].getghostY() ;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
                if(direccion_lvl3[i] == 'l'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX() - ghost[i].speed;;
                    sy = ghost[i].getghostY() ;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
            }

            for(int i = 0; i < 4; i++){
                if(ghost[i].getGlobalBounds().intersects(player1.getGlobalBounds())){
                    if(power_player_lvl3){
                        scoreText.setString("Puntuacion : " + std::to_string(score+=50));
                        ghost[i].setPosition(1000,1000);
                        eliminate_ghost_lvl3 = i;
                        cout << "el fantasma eliminado fue " << i << endl;
                        set_ghostlvl3 = true;
                    }
                    else{
                        int ramon = rand() % 4;
                        a = ramon_x[ramon];
                        b = ramon_y[ramon];
                        player1.playerX = a;
                        player1.playerY = b;
                        playerLives3 --;
                    }

                }
            }

            if(set_ghostlvl3){
                cout << loop3 % 200 << endl;
                if (loop3 % 700 == 0)
                {
                    counter3 ++;
                    if (counter3 == 5){
                        ghost[eliminate_ghost_lvl3].setPosition(850,160);

                        ghost_normal_move_lvl3 = true;
                        backtracking_move_lvl3 = false;
                        direccion_lvl3[eliminate_ghost_lvl3] = 'd';
                        power_player_lvl3 = false;

                    }
                }

            }

            if(turnPoweron3_1){
                if(fruit.getGlobalBounds().intersects(player1.getGlobalBounds())){
                    cout << "El poder fue comido por el PacMan" << endl;
                    power_player_lvl3 = true;
                    fruit.setPosition(1000, 1000);
                    one_lvl3 = false;
                }
                for(int i = 0; i < 3; i++){
                    if (fruit.getGlobalBounds().intersects(ghost[i].getGlobalBounds())){

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


            for (int i = 0; i < 10; i++)//draw walls
            {
                window.draw(blockObj[i]);
            }
            for (int i = 0; i < 36; i++)//draw walls
            {
                window.draw(pointsObj[i]);
            }

            window.draw(scoreText);

            window.draw(playerLevel);

            // reset the timeSinceLastUpdate to 0
            timeSinceLastUpdate = sf::Time::Zero;
            loop3++;

        }

        window.draw(ghost[0]);
        window.draw(ghost[1]);
        window.draw(ghost[2]);

        //Muestra las vidas del jugador
        if (playerLives3== 3) {

            window.draw(live1);
            window.draw(live2);
            window.draw(live3);
        }
        else if (playerLives3 == 2) {

            window.draw(live1);
            window.draw(live2);
        }
        else if (playerLives3 == 1) {
            window.draw(live1);
        }
        window.draw(player1);

        if (puntuacion + 200 == score){
            turnPoweron3_1 = true;
        }

        if (turnPoweron3_1){
            if(one_lvl3){
                fruit.setPosition(10, 65);
                window.draw(fruit);
            }

        }

        if (playerLives3 == 0){
            puntuacion_final puntos;
            return puntos.p(score);
        }

        //Detecta si todos los puntos fueron comidos
        for(int i = 0; i < 36; i++){
            if(!pointsObj[i].geteat()){
                verification_lvl3 ++;
            }
        }

        //Cambia de nivel
        if(verification_lvl3 == 0){
            window.close();
            PacMan4 pacman;
            return pacman.game(nivel + 1, score);
        }

        verification_lvl3 = 0;


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition( window );
            cout << "x" << static_cast<float>( mousePos.x ) << endl;
            cout << "y" << static_cast<float>( mousePos.y ) << endl;
        }


        window.display();
    }



    return 0;
}

