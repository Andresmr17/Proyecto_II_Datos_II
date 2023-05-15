#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan4.h"
#include "../Resorces/block.h"
#include "../Player/lives.h"
#include "../Player/player.h"
#include "../Resorces/points.h"
#include "../Resorces/power.h"
#include "../Resorces/puntuacion_final.h"
#include "../ghosts/ghosts.h"
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char direccion_lvl4[4] = {'d', 'r', 'l', 'd'};
bool backtracking_move_lvl4 = false;
bool ghost_normal_move_lvl4 = true;

bool ghost1_flag1_lvl4 = true;
bool ghost1_flag2_lvl4 = true;
bool ghost1_flag3_lvl4 = true;

bool ghost2_flag1_lvl4 = true;
bool ghost2_flag2_lvl4 = true;
bool ghost2_flag3_lvl4 = true;

bool ghost3_flag1_lvl4 = true;
bool ghost3_flag2_lvl4 = true;
bool ghost3_flag3_lvl4 = true;

bool ghost4_flag1_lvl4 = true;
bool ghost4_flag2_lvl4 = true;
bool ghost4_flag3_lvl4 = true;

bool click = true;

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


bool turnPoweron4_1 = false;
bool turnPoweron4_2 = false;
bool eaten4 = false;

void buildobstacles4(block blockObj[5], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 530, 120, 69, Obstaculo);
    blockObj[1]= block(720, 50, 120, 240, Obstaculo);
    blockObj[2]= block(70, 290, 770, 70, Obstaculo);
    blockObj[3]= block(70, 120, 770, 100, Obstaculo);
    blockObj[4]= block(70, 430, 770, 100, Obstaculo);
}
void bluidPoints4(points pointsObj[], sf::Texture &Point){
    int posiciones_puntos[39][2]={{20,555},{220,555},{320, 555},{550, 555},{650,555},
                                  {750, 555},{860, 555},{860,450},{860,350},{860,250},{860,150},
                                  {860,65},{660,65},{560, 65},{460, 65},{360, 65},
                                  {260, 65},{160, 65},{60, 65},{20,125},{20, 205},{20, 305},
                                  {20, 405},{20, 480},{75, 380},{175, 380},{275, 380},{375, 380},
                                  {475, 380},{575, 380},{675, 380},{775, 380},{75, 240},{175,240},
                                  {275, 240},{375, 240},{475, 240},{575,240},{675,240}
    };
    for(int i = 0; i < 39; i++){
        pointsObj[i] = points(posiciones_puntos[i][0],posiciones_puntos[i][1], Point);
    }
}

int PacMan4::game(int nivel, int puntuacion) {
    ghosts ghost[4];

    bool win = false;
    int score = 1020;
    int kill = 1;
    int level = nivel;
    int tempScore = 0;

    int ramon_x [4] = {600,590,850,370};
    int ramon_y [4] = {55,535,310,370};

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
    block blockObj[5];
    //build meteor objets
    buildobstacles4(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[40];
    bluidPoints4(pointsObj, Point);
    int x = 850;
    int y = 60;
    bool front = false;

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
    sf::Texture ghost4Texture;
    if (!ghost4Texture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma4.png")) {
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

    ghost[0] = ghosts(5, 60, front);
    ghost[0].setTexture(&ghost1Texture);

    ghost[1] = ghosts(105, 66, front);
    ghost[1].setTexture(&ghost2Texture);

    ghost[2] = ghosts(205, 66, front);
    ghost[2].setTexture(&ghost3Texture);

    ghost[3] = ghosts(5, 160, front);
    ghost[3].setTexture(&ghost4Texture);

    sf::Texture powerTexture;
    if (!powerTexture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Power.png")) {
        std::cout << "Error load image";
    }

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
                    for (int i = 0; i < 5; i++) {
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
                    for (int i = 0; i < 5; i++) {
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
                    for (int i = 0; i < 5; i++) {
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
                    for (int i = 0; i < 5; i++) {
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

                for(int i = 0; i < 39; i++){
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score+=10));
                        pointsObj[i].setPosition(1000,1000);
                    }
                }
            }

            if(backtracking_move_lvl4){
                //Se agrega la logica del backtracking
            }

            if(ghost_normal_move_lvl4){

                //Movimiento del fantasma naranja
                if(ghost1_flag1_lvl4)
                {
                    if(ghost[0].getghostX() > 4 && ghost[0].getghostX() < 7 && ghost[0].getghostY() > 226 && ghost[0].getghostY() < 230)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl4 = false;
                        ghost1_flag2_lvl4 = true;
                        ghost1_flag3_lvl4 = true;
                    }
                }

                if(ghost1_flag2_lvl4)
                {
                    if(ghost[0].getghostX() > 4 && ghost[0].getghostX() < 7 && ghost[0].getghostY() > 371 && ghost[0].getghostY() < 375)//2
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl4 = true;
                        ghost1_flag2_lvl4 = false;
                        ghost1_flag3_lvl4 = true;
                    }
                }

                if(ghost[0].getghostX() > 4 && ghost[0].getghostX() < 7 && ghost[0].getghostY() > 537 && ghost[0].getghostY() < 539)//3
                {
                    direccion_lvl4[0] = 'u';
                    ghost1_flag1_lvl4 = true;
                    ghost1_flag2_lvl4 = true;
                    ghost1_flag3_lvl4 = true;
                }

                if(ghost[0].getghostX() > 4 && ghost[0].getghostX() < 7 && ghost[0].getghostY() > 65 && ghost[0].getghostY() < 67)//4
                {
                    if( direccion_lvl4[0] == 'u'){
                        direccion_lvl4[0] = 'r';
                    }
                    if( direccion_lvl4[0] == 'l'){
                        direccion_lvl4[0] = 'd';
                        ghost1_flag1_lvl4 = true;
                        ghost1_flag2_lvl4 = true;
                        ghost1_flag3_lvl4 = true;
                    }

                }

                if(ghost[0].getghostX() > 672 && ghost[0].getghostX() < 675 && ghost[0].getghostY() > 65 && ghost[0].getghostY() < 67)//5
                {
                    direccion_lvl4[0] = 'l';
                }

                if(ghost[0].getghostX() > 672 && ghost[0].getghostX() < 675 && ghost[0].getghostY() > 226 && ghost[0].getghostY() < 230)//6
                {
                    direccion_lvl4[0] = 'l';
                    ghost1_flag1_lvl4 = true;
                }

                if(ghost1_flag3_lvl4){
                    if(ghost[0].getghostX() > 855 && ghost[0].getghostX() < 859 && ghost[0].getghostY() > 371 && ghost[0].getghostY() < 375)//7
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl4 = true;
                        ghost1_flag2_lvl4 = true;
                        ghost1_flag3_lvl4 = false;
                    }
                }

                if(ghost[0].getghostX() > 855 && ghost[0].getghostX() < 859 && ghost[0].getghostY() > 545 && ghost[0].getghostY() < 549)//8
                {
                    if(direccion_lvl4[0] == 'd'){
                        direccion_lvl4[0] = 'l';
                    }
                    if(direccion_lvl4[0] == 'r') {
                        direccion_lvl4[0] = 'u';
                        ghost1_flag3_lvl4 = true;
                    }
                }

                if(ghost[0].getghostX() > 200 && ghost[0].getghostX() < 205 && ghost[0].getghostY() > 545 && ghost[0].getghostY() < 549)//9
                {
                    direccion_lvl4[0] = 'r';
                }

                if(ghost[0].getghostX() > 855 && ghost[0].getghostX() < 859 && ghost[0].getghostY() > 65 && ghost[0].getghostY() < 67)//10
                {
                    direccion_lvl4[0] = 'd';
                    ghost1_flag3_lvl4 = true;
                }

                //Movimiento del fantasma rosado
                if(ghost2_flag1_lvl4)
                {
                    if(ghost[1].getghostX() > 4 && ghost[1].getghostX() < 7 && ghost[1].getghostY() > 226 && ghost[1].getghostY() < 230)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl4 = false;
                        ghost2_flag2_lvl4 = true;
                        ghost2_flag3_lvl4 = true;
                    }
                }

                if(ghost2_flag2_lvl4)
                {
                    if(ghost[1].getghostX() > 4 && ghost[1].getghostX() < 7 && ghost[1].getghostY() > 371 && ghost[1].getghostY() < 375)//2
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl4 = true;
                        ghost2_flag2_lvl4 = false;
                        ghost2_flag3_lvl4 = true;
                    }
                }

                if(ghost[1].getghostX() > 4 && ghost[1].getghostX() < 7 && ghost[1].getghostY() > 537 && ghost[1].getghostY() < 539)//3
                {
                    direccion_lvl4[1] = 'u';
                    ghost2_flag1_lvl4 = true;
                    ghost2_flag2_lvl4 = true;
                    ghost2_flag3_lvl4 = true;
                }

                if(ghost[1].getghostX() > 4 && ghost[1].getghostX() < 7 && ghost[1].getghostY() > 65 && ghost[1].getghostY() < 67)//4
                {
                    if( direccion_lvl4[1] == 'u'){
                        direccion_lvl4[1] = 'r';
                    }
                    if( direccion_lvl4[1] == 'l'){
                        direccion_lvl4[1] = 'd';
                        ghost2_flag1_lvl4 = true;
                        ghost2_flag2_lvl4 = true;
                        ghost2_flag3_lvl4 = true;
                    }

                }

                if(ghost[1].getghostX() > 672 && ghost[1].getghostX() < 675 && ghost[1].getghostY() > 65 && ghost[1].getghostY() < 67)//5
                {
                    direccion_lvl4[1] = 'l';
                }

                if(ghost[1].getghostX() > 672 && ghost[1].getghostX() < 675 && ghost[1].getghostY() > 226 && ghost[1].getghostY() < 230)//6
                {
                    direccion_lvl4[1] = 'l';
                    ghost2_flag1_lvl4 = true;
                }

                if(ghost2_flag3_lvl4){
                    if(ghost[1].getghostX() > 855 && ghost[1].getghostX() < 859 && ghost[1].getghostY() > 371 && ghost[1].getghostY() < 375)//7
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl4 = true;
                        ghost2_flag2_lvl4 = true;
                        ghost2_flag3_lvl4 = false;
                    }
                }

                if(ghost[1].getghostX() > 855 && ghost[1].getghostX() < 859 && ghost[1].getghostY() > 545 && ghost[1].getghostY() < 549)//8
                {
                    if(direccion_lvl4[1] == 'd'){
                        direccion_lvl4[1] = 'l';
                    }
                    if(direccion_lvl4[1] == 'r') {
                        direccion_lvl4[1] = 'u';
                        ghost2_flag3_lvl4 = true;
                    }
                }

                if(ghost[1].getghostX() > 200 && ghost[1].getghostX() < 205 && ghost[1].getghostY() > 545 && ghost[1].getghostY() < 549)//9
                {
                    direccion_lvl4[1] = 'r';
                }

                if(ghost[1].getghostX() > 855 && ghost[1].getghostX() < 859 && ghost[1].getghostY() > 65 && ghost[1].getghostY() < 67)//10
                {
                    direccion_lvl4[1] = 'd';
                    ghost2_flag3_lvl4 = true;
                }

                //Movimiento del fantasma celeste
                if(ghost3_flag1_lvl4)
                {
                    if(ghost[2].getghostX() > 4 && ghost[2].getghostX() < 7 && ghost[2].getghostY() > 226 && ghost[2].getghostY() < 230)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[2] = dir[num];
                        cout << num << endl;
                        ghost3_flag1_lvl4 = false;
                        ghost3_flag2_lvl4 = true;
                        ghost3_flag3_lvl4 = true;
                    }
                }

                if(ghost3_flag2_lvl4)
                {
                    if(ghost[2].getghostX() > 4 && ghost[2].getghostX() < 7 && ghost[2].getghostY() > 371 && ghost[2].getghostY() < 375)//2
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[2] = dir[num];
                        cout << num << endl;
                        ghost3_flag1_lvl4 = true;
                        ghost3_flag2_lvl4 = false;
                        ghost3_flag3_lvl4 = true;
                    }
                }

                if(ghost[2].getghostX() > 4 && ghost[2].getghostX() < 7 && ghost[2].getghostY() > 537 && ghost[2].getghostY() < 539)//3
                {
                    direccion_lvl4[2] = 'u';
                    ghost3_flag1_lvl4 = true;
                    ghost3_flag2_lvl4 = true;
                    ghost3_flag3_lvl4 = true;
                }

                if(ghost[2].getghostX() > 4 && ghost[2].getghostX() < 7 && ghost[2].getghostY() > 65 && ghost[2].getghostY() < 67)//4
                {
                    if( direccion_lvl4[2] == 'u'){
                        direccion_lvl4[2] = 'r';
                    }
                    if( direccion_lvl4[2] == 'l'){
                        direccion_lvl4[2] = 'd';
                        ghost3_flag1_lvl4 = true;
                        ghost3_flag2_lvl4 = true;
                        ghost3_flag3_lvl4 = true;
                    }

                }

                if(ghost[2].getghostX() > 672 && ghost[2].getghostX() < 675 && ghost[2].getghostY() > 65 && ghost[2].getghostY() < 67)//5
                {
                    direccion_lvl4[2] = 'l';
                }

                if(ghost[2].getghostX() > 672 && ghost[2].getghostX() < 675 && ghost[2].getghostY() > 226 && ghost[2].getghostY() < 230)//6
                {
                    direccion_lvl4[2] = 'l';
                    ghost3_flag1_lvl4 = true;
                }

                if(ghost3_flag3_lvl4){
                    if(ghost[2].getghostX() > 855 && ghost[2].getghostX() < 859 && ghost[2].getghostY() > 371 && ghost[2].getghostY() < 375)//7
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[2] = dir[num];
                        cout << num << endl;
                        ghost3_flag1_lvl4 = true;
                        ghost3_flag2_lvl4 = true;
                        ghost3_flag3_lvl4 = false;
                    }
                }

                if(ghost[2].getghostX() > 855 && ghost[2].getghostX() < 859 && ghost[2].getghostY() > 545 && ghost[2].getghostY() < 549)//8
                {
                    if(direccion_lvl4[2] == 'd'){
                        direccion_lvl4[2] = 'l';
                    }
                    if(direccion_lvl4[2] == 'r') {
                        direccion_lvl4[2] = 'u';
                        ghost3_flag3_lvl4 = true;
                    }
                }

                if(ghost[2].getghostX() > 200 && ghost[2].getghostX() < 205 && ghost[2].getghostY() > 545 && ghost[2].getghostY() < 549)//9
                {
                    direccion_lvl4[2] = 'r';
                }

                if(ghost[2].getghostX() > 855 && ghost[2].getghostX() < 859 && ghost[2].getghostY() > 65 && ghost[2].getghostY() < 67)//10
                {
                    direccion_lvl4[2] = 'd';
                    ghost3_flag3_lvl4 = true;
                }

                //Movimiento del fantasma rojo
                if(ghost4_flag1_lvl4)
                {
                    if(ghost[3].getghostX() > 4 && ghost[3].getghostX() < 7 && ghost[3].getghostY() > 226 && ghost[3].getghostY() < 230)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[3] = dir[num];
                        cout << num << endl;
                        ghost4_flag1_lvl4 = false;
                        ghost4_flag2_lvl4 = true;
                        ghost4_flag3_lvl4 = true;
                    }
                }

                if(ghost4_flag2_lvl4)
                {
                    if(ghost[3].getghostX() > 4 && ghost[3].getghostX() < 7 && ghost[3].getghostY() > 371 && ghost[3].getghostY() < 375)//2
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[3] = dir[num];
                        cout << num << endl;
                        ghost4_flag1_lvl4 = true;
                        ghost4_flag2_lvl4 = false;
                        ghost4_flag3_lvl4 = true;
                    }
                }

                if(ghost[3].getghostX() > 4 && ghost[3].getghostX() < 7 && ghost[3].getghostY() > 537 && ghost[3].getghostY() < 539)//3
                {
                    direccion_lvl4[3] = 'u';
                    ghost4_flag1_lvl4 = true;
                    ghost4_flag2_lvl4 = true;
                    ghost4_flag3_lvl4 = true;
                }

                if(ghost[3].getghostX() > 4 && ghost[3].getghostX() < 7 && ghost[3].getghostY() > 65 && ghost[3].getghostY() < 67)//4
                {
                    if( direccion_lvl4[3] == 'u'){
                        direccion_lvl4[3] = 'r';
                    }
                    if( direccion_lvl4[3] == 'l'){
                        direccion_lvl4[3] = 'd';
                        ghost4_flag1_lvl4 = true;
                        ghost4_flag2_lvl4 = true;
                        ghost4_flag3_lvl4 = true;
                    }

                }

                if(ghost[3].getghostX() > 672 && ghost[3].getghostX() < 675 && ghost[3].getghostY() > 65 && ghost[3].getghostY() < 67)//5
                {
                    direccion_lvl4[3] = 'l';
                }

                if(ghost[3].getghostX() > 672 && ghost[3].getghostX() < 675 && ghost[3].getghostY() > 226 && ghost[3].getghostY() < 230)//6
                {
                    direccion_lvl4[3] = 'l';
                    ghost4_flag1_lvl4 = true;
                }

                if(ghost4_flag3_lvl4){
                    if(ghost[3].getghostX() > 855 && ghost[3].getghostX() < 859 && ghost[3].getghostY() > 371 && ghost[3].getghostY() < 375)//7
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl4[3] = dir[num];
                        cout << num << endl;
                        ghost4_flag1_lvl4 = true;
                        ghost4_flag2_lvl4 = true;
                        ghost4_flag3_lvl4 = false;
                    }
                }

                if(ghost[3].getghostX() > 855 && ghost[3].getghostX() < 859 && ghost[3].getghostY() > 545 && ghost[3].getghostY() < 549)//8
                {
                    if(direccion_lvl4[3] == 'd'){
                        direccion_lvl4[3] = 'l';
                    }
                    if(direccion_lvl4[3] == 'r') {
                        direccion_lvl4[3] = 'u';
                        ghost4_flag3_lvl4 = true;
                    }
                }

                if(ghost[3].getghostX() > 200 && ghost[3].getghostX() < 205 && ghost[3].getghostY() > 545 && ghost[3].getghostY() < 549)//9
                {
                    direccion_lvl4[3] = 'r';
                }

                if(ghost[3].getghostX() > 855 && ghost[3].getghostX() < 859 && ghost[3].getghostY() > 65 && ghost[3].getghostY() < 67)//10
                {
                    direccion_lvl4[3] = 'd';
                    ghost4_flag3_lvl4 = true;
                }



            }




            //Movimiento de los fantasmas

            for(int i = 0; i < 4; i++){
                if(direccion_lvl4[i] == 'u'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX();
                    sy = ghost[i].getghostY() - ghost[i].speed;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }

                if(direccion_lvl4[i] == 'd'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX();
                    sy = ghost[i].getghostY() + ghost[i].speed;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
                if(direccion_lvl4[i] == 'r'){
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX() + ghost[i].speed;;
                    sy = ghost[i].getghostY() ;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
                if(direccion_lvl4[i] == 'l'){
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
                    int ramon = rand() % 4;
                    a = ramon_x[ramon];
                    b = ramon_y[ramon];
                    player1.playerX = a;
                    player1.playerY = b;
                    playerLives4 --;
                }
            }


            // update player position
            player1.setPosition(player1.playerX, player1.playerY);

            // clear the screen and draw all the shapes
            window.clear();
            window.draw(background);
            window.draw(lineTop, 5, sf::Lines);
            window.draw(line, 5, sf::Lines);
            for (int i = 0; i < 6; i++)//draw walls
            {
                window.draw(blockObj[i]);
            }
            for (int i = 0; i < 39; i++)//draw points
            {
                window.draw(pointsObj[i]);
            }
            window.draw(scoreText);

            window.draw(playerLevel);

            window.draw(ghost[0]);
            window.draw(ghost[1]);
            window.draw(ghost[2]);
            window.draw(ghost[3]);

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

        if (score == 1200){
            turnPoweron4_1 = true;
        }

        if (turnPoweron4_1 == true){
            fruit.setPosition(585, 545);
            window.draw(fruit);
        }

        if (score == 1400){
            turnPoweron4_2 = true;
        }

        if (turnPoweron4_2 == true){
            fruit.setPosition(310, 230);
            window.draw(fruit);
        }

        if (playerLives4 == 0){
            puntuacion_final puntos;
            return puntos.p(score);
        }

        //Detecta si la puntuación máxima fue alcanzada
        if (score == 1410) {
            if (playerLives4 != 0) {
                juego4 == false;
                window.close();
                puntuacion_final puntos;
                return puntos.p(score);

            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(click){
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                cout << "x" << static_cast<float>( mousePos.x ) << endl;
                cout << "y" << static_cast<float>( mousePos.y ) << endl;
                click = false;
            }

        }

        window.display();
    }
    return 0;
}