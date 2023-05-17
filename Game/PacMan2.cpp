#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan2.h"
#include "PacMan3.h"
#include "../Resorces/puntuacion_final.h"
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

int playerLives2 = 3;
int loop2 = 1;
bool juego2 = true;

bool ghost_normal_move_lvl2 = true;
bool backtracking_move_lvl2 = false;
bool pathfinding_move_lvl2 = true;

bool press_flag2 = true;
bool flag_up2 = true;
bool flag_down2 = true;
bool flag_right2 = true;
bool flag_left2 = true;

bool turnPoweron2_1 = false;
bool turnPoweron2_2 = false;
bool eaten2 = false;

bool ghost1_flag1_lvl2 = true;
bool ghost1_flag2_lvl2 = true;
bool ghost1_flag3_lvl2 = true;
bool ghost1_flag4_lvl2 = true;

bool ghost2_flag1_lvl2 = true;
bool ghost2_flag2_lvl2 = true;
bool ghost2_flag3_lvl2 = true;
bool ghost2_flag4_lvl2 = true;

int verification_lvl2 = 0;
bool power_player_lvl2 = false;
int eliminate_ghost = 0;
bool set_ghostlvl2 = false;
int counter2 = 0;
bool one_lvl2 = true;

char direccion_lvl2[2] = {'d', 'd'};


/**
 * @brief se encarga de hacer la intancia de las paredes mostradas en el juego
 * @param blockObj el objeto que se desea instanciar
 * @param Obstaculo la imagen que se desea colocar
 * @return no tiene retorno
 */
void buildobstacles2(block blockObj[6], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 369, 230, 230, Obstaculo);
    blockObj[1]= block(610, 369, 230, 230, Obstaculo);
    blockObj[2]= block(610, 50, 230, 230, Obstaculo);
    blockObj[3]= block(370, 50, 170, 230, Obstaculo);
    blockObj[4]= block(70, 50, 230, 230, Obstaculo);
    blockObj[5]= block(370, 369, 170, 230, Obstaculo);

}

/**
 * @brief se encarga de instanciar los puntos que se van a mostrar en la pantalla de juego
 * @param pointsObj son los objetos puntos que se van a crear
 * @param Point corresponde a la imagen que se desea mostrar
 */
void bluidPoints2(points pointsObj[], sf::Texture &Point){

    int posiciones_puntos[31][2]={
                                  {20,125},{20,205},{20,305},
                                  {20,405},{20,480},{100, 315},{200, 315},
                                  {320, 315},{860, 225},{860, 305},{860, 405},
                                  {860, 485},{660, 315},{780, 315},{560, 125},
                                  {560, 205},{560, 305},{315,405},{315, 480},
                                  {560, 405},{560, 480},{320,200},{320,120},
                                  {23, 549}, {322, 555}, {562, 558}, {862, 565},
                                  {324, 70}, {860, 155}, {561, 67}, {860, 90}

    };

    for(int i = 0; i < 31; i++){
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
int PacMan2::game( int nivel, int puntuacion) {
    ghosts ghost[2];
    int score = puntuacion;
    int level = nivel;

    int ramon_x[4] = {555, 330, 570, 850};
    int ramon_y[4] = {55, 315, 315, 310};

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
    block blockObj[6];

    //build meteor objets
    buildobstacles2(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[32];
    bluidPoints2(pointsObj, Point);

    bool front = false;
    sf::Texture ghost1Texture;
    if (!ghost1Texture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma1.png")) {
        std::cout << "Error load image";
    }
    sf::Texture ghost2Texture;
    if (!ghost2Texture.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/Fantasma2.png")) {
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
    ghost[1] = ghosts(10, 220, front);
    ghost[1].setTexture(&ghost1Texture);

    ghost[0] = ghosts(10, 120, front);
    ghost[0].setTexture(&ghost2Texture);

    //player.setTexture(&texture);
    player player1 = player(447, 300, Right);
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
            if (press_flag2) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    press_flag2 = false;


                    player1.setTexture(&Left);
                    for (int i = 0; i < 6; i++) {
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

            if (press_flag2) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    press_flag2 = false;
                    player1.setTexture(&Right);
                    for (int i = 0; i < 6; i++) {
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

            if (press_flag2) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    press_flag2 = false;
                    player1.setTexture(&Up);
                    for (int i = 0; i < 6; i++) {

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

            if (press_flag2) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    press_flag2 = false;
                    player1.setTexture(&Down);
                    for (int i = 0; i < 6; i++) {
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

                for (int i = 0; i < 32; i++) {
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score += 10));
                        pointsObj[i].setPosition(1000, 1000);
                        pointsObj[i].seteat(true); //Indica cual punto fue comido

                    }
                }
            }

            //Movimiento en backtracking
            if (backtracking_move_lvl2) {
                if (ghost1_flag1_lvl2) {
                    if (ghost[0].getghostX() > 8 && ghost[0].getghostX() < 12 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = false;
                        ghost1_flag2_lvl2 = true;
                        ghost1_flag3_lvl2 = true;
                        ghost1_flag4_lvl2 = true;
                    }
                }
                if (ghost[0].getghostX() > 8 && ghost[0].getghostX() < 12 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 595)//2
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 8 && ghost[0].getghostX() < 12 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//3
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost1_flag2_lvl2) {
                    if (ghost[0].getghostX() > 315 && ghost[0].getghostX() < 320 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//4
                    {
                        char dir[4] = {'r', 'd', 'u', 'l'};
                        srand(time(NULL));
                        int num = rand() % 4;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = true;
                        ghost1_flag2_lvl2 = false;
                        ghost1_flag3_lvl2 = true;
                        ghost1_flag4_lvl2 = true;
                    }
                }

                if (ghost[0].getghostX() > 315 && ghost[0].getghostX() < 320 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 595)//5
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 315 && ghost[0].getghostX() < 320 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//6
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost1_flag3_lvl2) {
                    if (ghost[0].getghostX() > 554 && ghost[0].getghostX() < 560 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//7
                    {
                        char dir[4] = {'r', 'd', 'u', 'l'};
                        srand(time(NULL));
                        int num = rand() % 4;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = true;
                        ghost1_flag2_lvl2 = true;
                        ghost1_flag3_lvl2 = false;
                        ghost1_flag4_lvl2 = true;
                    }
                }
                if (ghost[0].getghostX() > 554 && ghost[0].getghostX() < 560 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 595)//8
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 554 && ghost[0].getghostX() < 560 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//9
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost1_flag4_lvl2) {
                    if (ghost[0].getghostX() > 855 && ghost[0].getghostX() < 860 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//10
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = true;
                        ghost1_flag2_lvl2 = true;
                        ghost1_flag3_lvl2 = true;
                        ghost1_flag4_lvl2 = false;
                    }
                }
                if (ghost[0].getghostX() > 855 && ghost[0].getghostX() < 860 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 560)//11
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 855 && ghost[0].getghostX() < 860 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//12
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
            }

            //Movimiento en pathfinding
            if (pathfinding_move_lvl2) {

                if (ghost2_flag1_lvl2) {
                    if (ghost[1].getghostX() > 8 && ghost[1].getghostX() < 12 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = false;
                        ghost2_flag2_lvl2 = true;
                        ghost2_flag3_lvl2 = true;
                        ghost2_flag4_lvl2 = true;
                    }
                }
                if (ghost[1].getghostX() > 8 && ghost[1].getghostX() < 12 && ghost[1].getghostY() > 550 &&
                    ghost[1].getghostY() < 595)//2
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost[1].getghostX() > 8 && ghost[1].getghostX() < 12 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//3
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost2_flag2_lvl2) {
                    if (ghost[1].getghostX() > 315 && ghost[1].getghostX() < 320 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//4
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = true;
                        ghost2_flag2_lvl2 = false;
                        ghost2_flag3_lvl2 = true;
                        ghost2_flag4_lvl2 = true;
                    }
                }

                if (ghost[1].getghostX() > 315 && ghost[1].getghostX() < 320 && ghost[1].getghostY() > 550 &&
                    ghost[1].getghostY() < 595)//5
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost[1].getghostX() > 315 && ghost[1].getghostX() < 320 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//6
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost2_flag3_lvl2) {
                    if (ghost[1].getghostX() > 554 && ghost[1].getghostX() < 560 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//7
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = true;
                        ghost2_flag2_lvl2 = true;
                        ghost2_flag3_lvl2 = false;
                        ghost2_flag4_lvl2 = true;
                    }
                }
                if (ghost[1].getghostX() > 554 && ghost[1].getghostX() < 560 && ghost[1].getghostY() > 550 &&
                    ghost[1].getghostY() < 595)//8
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost[1].getghostX() > 554 && ghost[1].getghostX() < 560 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//9
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost2_flag4_lvl2) {
                    if (ghost[1].getghostX() > 850 && ghost[1].getghostX() < 860 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//10
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = true;
                        ghost2_flag2_lvl2 = true;
                        ghost2_flag3_lvl2 = true;
                        ghost2_flag4_lvl2 = false;
                    }
                }
                if (ghost[1].getghostX() > 850 && ghost[1].getghostX() < 860 && ghost[1].getghostY() > 560 &&
                    ghost[1].getghostY() < 565)//11
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }

                if (ghost[1].getghostX() > 850 && ghost[1].getghostX() < 860 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//12
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
            }


            //Movimiento del fantasma rosado
            if (ghost_normal_move_lvl2) {
                if (ghost1_flag1_lvl2) {
                    if (ghost[0].getghostX() > 8 && ghost[0].getghostX() < 12 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = false;
                        ghost1_flag2_lvl2 = true;
                        ghost1_flag3_lvl2 = true;
                        ghost1_flag4_lvl2 = true;
                    }
                }
                if (ghost[0].getghostX() > 8 && ghost[0].getghostX() < 12 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 595)//2
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 8 && ghost[0].getghostX() < 12 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//3
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost1_flag2_lvl2) {
                    if (ghost[0].getghostX() > 315 && ghost[0].getghostX() < 320 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//4
                    {
                        char dir[4] = {'r', 'd', 'u', 'l'};
                        srand(time(NULL));
                        int num = rand() % 4;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = true;
                        ghost1_flag2_lvl2 = false;
                        ghost1_flag3_lvl2 = true;
                        ghost1_flag4_lvl2 = true;
                    }
                }

                if (ghost[0].getghostX() > 315 && ghost[0].getghostX() < 320 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 595)//5
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 315 && ghost[0].getghostX() < 320 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//6
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost1_flag3_lvl2) {
                    if (ghost[0].getghostX() > 554 && ghost[0].getghostX() < 560 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//7
                    {
                        char dir[4] = {'r', 'd', 'u', 'l'};
                        srand(time(NULL));
                        int num = rand() % 4;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = true;
                        ghost1_flag2_lvl2 = true;
                        ghost1_flag3_lvl2 = false;
                        ghost1_flag4_lvl2 = true;
                    }
                }
                if (ghost[0].getghostX() > 554 && ghost[0].getghostX() < 560 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 595)//8
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 554 && ghost[0].getghostX() < 560 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//9
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost1_flag4_lvl2) {
                    if (ghost[0].getghostX() > 855 && ghost[0].getghostX() < 860 && ghost[0].getghostY() > 306 &&
                        ghost[0].getghostY() < 310)//10
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[0] = dir[num];
                        cout << num << endl;
                        ghost1_flag1_lvl2 = true;
                        ghost1_flag2_lvl2 = true;
                        ghost1_flag3_lvl2 = true;
                        ghost1_flag4_lvl2 = false;
                    }
                }
                if (ghost[0].getghostX() > 855 && ghost[0].getghostX() < 860 && ghost[0].getghostY() > 550 &&
                    ghost[0].getghostY() < 560)//11
                {
                    direccion_lvl2[0] = 'u';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }
                if (ghost[0].getghostX() > 855 && ghost[0].getghostX() < 860 && ghost[0].getghostY() > 60 &&
                    ghost[0].getghostY() < 65)//12
                {
                    direccion_lvl2[0] = 'd';
                    ghost1_flag1_lvl2 = true;
                    ghost1_flag2_lvl2 = true;
                    ghost1_flag3_lvl2 = true;
                    ghost1_flag4_lvl2 = true;
                }

                //Movimiento del fantasma naranja

                if (ghost2_flag1_lvl2) {
                    if (ghost[1].getghostX() > 8 && ghost[1].getghostX() < 12 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//1
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = false;
                        ghost2_flag2_lvl2 = true;
                        ghost2_flag3_lvl2 = true;
                        ghost2_flag4_lvl2 = true;
                    }
                }
                if (ghost[1].getghostX() > 8 && ghost[1].getghostX() < 12 && ghost[1].getghostY() > 550 &&
                    ghost[1].getghostY() < 595)//2
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost[1].getghostX() > 8 && ghost[1].getghostX() < 12 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//3
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost2_flag2_lvl2) {
                    if (ghost[1].getghostX() > 315 && ghost[1].getghostX() < 320 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//4
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = true;
                        ghost2_flag2_lvl2 = false;
                        ghost2_flag3_lvl2 = true;
                        ghost2_flag4_lvl2 = true;
                    }
                }

                if (ghost[1].getghostX() > 315 && ghost[1].getghostX() < 320 && ghost[1].getghostY() > 550 &&
                    ghost[1].getghostY() < 595)//5
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost[1].getghostX() > 315 && ghost[1].getghostX() < 320 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//6
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost2_flag3_lvl2) {
                    if (ghost[1].getghostX() > 554 && ghost[1].getghostX() < 560 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//7
                    {
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = true;
                        ghost2_flag2_lvl2 = true;
                        ghost2_flag3_lvl2 = false;
                        ghost2_flag4_lvl2 = true;
                    }
                }
                if (ghost[1].getghostX() > 554 && ghost[1].getghostX() < 560 && ghost[1].getghostY() > 550 &&
                    ghost[1].getghostY() < 595)//8
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost[1].getghostX() > 554 && ghost[1].getghostX() < 560 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//9
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
                if (ghost2_flag4_lvl2) {
                    if (ghost[1].getghostX() > 850 && ghost[1].getghostX() < 860 && ghost[1].getghostY() > 306 &&
                        ghost[1].getghostY() < 310)//10
                    {
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand() % 3;
                        direccion_lvl2[1] = dir[num];
                        cout << num << endl;
                        ghost2_flag1_lvl2 = true;
                        ghost2_flag2_lvl2 = true;
                        ghost2_flag3_lvl2 = true;
                        ghost2_flag4_lvl2 = false;
                    }
                }
                if (ghost[1].getghostX() > 850 && ghost[1].getghostX() < 860 && ghost[1].getghostY() > 560 &&
                    ghost[1].getghostY() < 565)//11
                {
                    direccion_lvl2[1] = 'u';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }

                if (ghost[1].getghostX() > 850 && ghost[1].getghostX() < 860 && ghost[1].getghostY() > 60 &&
                    ghost[1].getghostY() < 65)//12
                {
                    direccion_lvl2[1] = 'd';
                    ghost2_flag1_lvl2 = true;
                    ghost2_flag2_lvl2 = true;
                    ghost2_flag3_lvl2 = true;
                    ghost2_flag4_lvl2 = true;
                }
            }

            for (int i = 0; i < 2; i++) {
                if (direccion_lvl2[i] == 'u') {
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX();
                    sy = ghost[i].getghostY() - ghost[i].speed;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }

                if (direccion_lvl2[i] == 'd') {
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX();
                    sy = ghost[i].getghostY() + ghost[i].speed;
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
                if (direccion_lvl2[i] == 'r') {
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX() + ghost[i].speed;;
                    sy = ghost[i].getghostY();
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
                if (direccion_lvl2[i] == 'l') {
                    float sx;
                    float sy;
                    sx = ghost[i].getghostX() - ghost[i].speed;;
                    sy = ghost[i].getghostY();
                    ghost[i].setghostX(sx);
                    ghost[i].setghostY(sy);
                    ghost[i].setPosition(sx, sy);
                }
            }

            for (int i = 0; i < 2; i++) {
                if (ghost[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                    if (power_player_lvl2) {
                        cout << "el fantasma eliminado fue el " << i << endl;
                        scoreText.setString("Puntuacion : " + std::to_string(score += 50));
                        ghost[i].setPosition(1000, 1000);
                        eliminate_ghost = i;
                        set_ghostlvl2 = true;

                    } else {
                        int ramon = rand() % 4;
                        a = ramon_x[ramon];
                        b = ramon_y[ramon];
                        player1.playerX = a;
                        player1.playerY = b;
                        playerLives2--;
                    }

                }
            }

            if (set_ghostlvl2) {
                if (loop2 % 200 == 0) {
                    counter2++;
                    if (counter2 == 5) {
                        ghost[eliminate_ghost].setPosition(10, 220);

                        ghost_normal_move_lvl2 = true;
                        backtracking_move_lvl2 = false;
                        direccion_lvl2[eliminate_ghost] = 'd';
                        power_player_lvl2 = false;

                    }
                }
            }

            if (turnPoweron2_1) {
                if (fruit.getGlobalBounds().intersects(player1.getGlobalBounds())) {
                    cout << "El poder fue comido por el PacMan" << endl;
                    power_player_lvl2 = true;
                    fruit.setPosition(1000, 1000);
                    one_lvl2 = false;
                }
                for (int i = 0; i < 2; i++) {
                    if (fruit.getGlobalBounds().intersects(ghost[i].getGlobalBounds())) {

                    }
                }

            }

            if (turnPoweron2_2) {
                if (fruit.getGlobalBounds().intersects(player1.getGlobalBounds())) {
                    cout << "El poder fue comido por el PacMan" << endl;
                    power_player_lvl2 = true;
                    fruit.setPosition(1000, 1000);
                    one_lvl2 = false;
                }
                for (int i = 0; i < 2; i++) {
                    if (fruit.getGlobalBounds().intersects(ghost[i].getGlobalBounds())) {

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


            for (int i = 0; i < 6; i++)//draw walls
            {
                window.draw(blockObj[i]);
            }
            for (int i = 0; i < 32; i++)//draw walls
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

        window.draw(ghost[0]);
        window.draw(ghost[1]);

        //Muestra las vidas del jugador
        if (playerLives2 == 3) {

            window.draw(live1);
            window.draw(live2);
            window.draw(live3);
        } else if (playerLives2 == 2) {

            window.draw(live1);
            window.draw(live2);
        } else if (playerLives2 == 1) {
            window.draw(live1);
        }
        window.draw(player1);

        //Verificacion para activar el primer poder
        if (puntuacion + 200 == score) {
            turnPoweron2_1 = true;
        }

        if (turnPoweron2_1) {
            if (one_lvl2) {
                fruit.setPosition(555, 300);
                window.draw(fruit);
            }

        }

        //Verificacion para activar el segundo poder
        if (puntuacion + 400 == score) {
            turnPoweron2_2 = true;
        }
        if (turnPoweron2_2) {
            if (one_lvl2) {
                fruit.setPosition(10, 65);
                window.draw(fruit);
            }
        }

        if (playerLives2 == 0) {
            puntuacion_final puntos;
            return puntos.p(score);
        }

        //Detecta si todos los puntos fueron comidos
        for (int i = 0; i < 31; i++) {
            if (!pointsObj[i].geteat()) {
                verification_lvl2++;
            }
        }

        //Cambia de nivel
        if (verification_lvl2 == 0) {
            window.close();
            PacMan3 pacman;
            return pacman.game(nivel + 1, score);
        }

        verification_lvl2 = 0;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            cout << "x" << static_cast<float>( mousePos.x ) << endl;
            cout << "y" << static_cast<float>( mousePos.y ) << endl;
        }

        window.display();
    }
}