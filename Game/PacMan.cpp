#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PacMan.h"
#include "PacMan2.h"
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
bool set_ghost = false;
int counter = 0;

bool ghost_normal_move_lvl1 = true;
bool backtracking_move_lvl1 = false;
char direccion_lvl1 = 'l';
bool flag_1 = true;
bool flag_2 = true;
bool flag_3 = true;
bool flag_4 = true;
bool flag_5 = true;
bool flag_6 = true;
bool flag_7 = true;
bool flag_8 = true;
bool move_ghost = true;
bool power_player = false;
bool one = true;
bool next_lvl = false;
int verification = 0;


/**
 * @brief se encarga de hacer la intancia de las paredes mostradas en el juego
 * @param blockObj el objeto que se desea instanciar
 * @param Obstaculo la imagen que se desea colocar
 * @return no tiene retorno
 */
void buildobstacles(block blockObj[4], sf::Texture &Obstaculo)
{
    blockObj[0]= block(70, 50, 100, 220, Obstaculo);
    blockObj[1]= block(740, 395, 100, 200, Obstaculo);
    blockObj[2]= block(70, 120, 770, 170, Obstaculo);
    blockObj[3]= block(70, 355, 770, 170, Obstaculo);

}

/**
 * @brief se encarga de instanciar los puntos que se van a mostrar en la pantalla de juego
 * @param pointsObj son los objetos puntos que se van a crear
 * @param Point corresponde a la imagen que se desea mostrar
 */
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
        pointsObj[i].seteat(false);

    }
}

/**
 * @brief se encarga de crear la ventana de juego junto con todos los componentes que se muestran en el trascurso del juego
 * @param nivel corresponde al nivel que se esta jugando
 * @param puntuacion corresponde a la puntuacion que el jugador tiene
 * @return retorna un numero no significativo
 */
int PacMan::game( int nivel, int puntuacion) {

    ghosts ghost;
    bool win = false;
    int score = puntuacion;
    int kill = 1;
    int level = nivel;
    int tempScore = 0;

    int ramon_x [3] = {600,590,850};
    int ramon_y [3] = {55,535,310};

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
    block blockObj[4];

    //build meteor objets
    buildobstacles(blockObj, Obstaculo);

    sf::Texture Point;
    if (!Point.loadFromFile("/home/andres/CLionProjects/Proyecto_II_Datos_II/images/pac-dot.png")) {
        std::cout << "Error load image";
    }
    points pointsObj[31];
    bluidPoints(pointsObj, Point);

    int x = 850;
    int y = 65;
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
                    for (int i = 0; i < 4; i++) {
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
                    for (int i = 0; i < 4; i++) {
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
                    for (int i = 0; i < 4; i++) {

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
                    for (int i = 0; i < 4; i++) {
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

                for(int i = 0; i < 31; i++){
                    if (pointsObj[i].getGlobalBounds().intersects(player1.getGlobalBounds())) {
                        scoreText.setString("Puntuacion : " + std::to_string(score+=10));
                        pointsObj[i].setPosition(1000,1000);
                        pointsObj[i].seteat(true); //Indica cual punto fue comido
                    }
                }
            }

            if(backtracking_move_lvl1){
                //aqui debe ir el movimiento en backtracking
                move_ghost = false;
            }

            //Movimiento aleatorio
            if(ghost_normal_move_lvl1){
                if(flag_1){
                    if(ghost.getghostX() > 848 && ghost.getghostX() < 855 && ghost.getghostY() > 305 && ghost.getghostY() < 310){
                        char dir[3] = {'l', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl1 = dir[num];
                        cout << num << endl;
                        flag_1 = false;
                        flag_2 = true;
                        flag_3 = true;
                        flag_4 = true;
                        flag_5 = true;
                        flag_6 = true;
                        flag_7 = true;
                        flag_8 = true;
                    }
                }
                if(flag_2){
                    if(ghost.getghostX() > 848 && ghost.getghostX() < 855 && ghost.getghostY() > 545 && ghost.getghostY() < 547){
                        direccion_lvl1 = 'u';
                        flag_1 = true;
                        flag_2 = false;
                        flag_3 = true;
                        flag_4 = true;
                        flag_5 = true;
                        flag_6 = true;
                        flag_7 = true;
                        flag_8 = true;
                    }
                }
                if(flag_3){
                    if(ghost.getghostX() > 848 && ghost.getghostX() < 855 && ghost.getghostY() > 63 && ghost.getghostY() < 67){
                        char dir[2] = {'l', 'd'};
                        srand(time(NULL));
                        int num = rand()%2;
                        direccion_lvl1 = dir[num];
                        flag_1 = true;
                        flag_2 = true;
                        flag_3 = false;
                        flag_4 = true;
                        flag_5 = true;
                        flag_6 = true;
                        flag_7 = true;
                        flag_8 = true;
                    }
                }
                if(flag_4){
                    if(ghost.getghostX() > 180 && ghost.getghostX() < 183 && ghost.getghostY() > 63 && ghost.getghostY() < 67) {

                        direccion_lvl1 = 'r';
                        flag_1 = true;
                        flag_2 = true;
                        flag_3 = true;
                        flag_4 = false;
                        flag_5 = true;
                        flag_6 = true;
                        flag_7 = true;
                        flag_8 = true;
                    }
                }
                if(flag_5){
                    if(ghost.getghostX() > 10 && ghost.getghostX() < 12 && ghost.getghostY() > 305 && ghost.getghostY() < 310){
                        char dir[3] = {'r', 'd', 'u'};
                        srand(time(NULL));
                        int num = rand()%3;
                        direccion_lvl1 = dir[num];
                        cout << num << endl;
                        flag_1 = true;
                        flag_2 = true;
                        flag_3 = true;
                        flag_4 = true;
                        flag_5 = false;
                        flag_6 = true;
                        flag_7 = true;
                        flag_8 = true;
                    }
                }
                if(flag_6){
                    if(ghost.getghostX() > 10 && ghost.getghostX() < 12 && ghost.getghostY() > 62 && ghost.getghostY() < 66) {

                        direccion_lvl1 = 'd';
                        flag_1 = true;
                        flag_2 = true;
                        flag_3 = true;
                        flag_4 = true;
                        flag_5 = true;
                        flag_6 = false;
                        flag_7 = true;
                        flag_8 = true;
                    }
                }
                if(flag_7){
                    if(ghost.getghostX() > 10 && ghost.getghostX() < 12 && ghost.getghostY() > 542 && ghost.getghostY() < 545) {

                        char dir[2] = {'r', 'u'};
                        srand(time(NULL));
                        int num = rand()%2;
                        direccion_lvl1 = dir[num];
                        flag_1 = true;
                        flag_2 = true;
                        flag_3 = true;
                        flag_4 = true;
                        flag_5 = true;
                        flag_6 = true;
                        flag_7 = false;
                        flag_8 = true;
                    }
                }
                if(flag_8){
                    if(ghost.getghostX() > 683 && ghost.getghostX() < 685 && ghost.getghostY() > 542 && ghost.getghostY() < 545){
                        direccion_lvl1 = 'l';
                        flag_1 = true;
                        flag_2 = true;
                        flag_3 = true;
                        flag_4 = true;
                        flag_5 = true;
                        flag_6 = true;
                        flag_7 = true;
                        flag_8 = false;
                    }
                }
            }

            //Movimiento del fantasma
            if(move_ghost){
                if(direccion_lvl1 == 'u'){
                    float sx;
                    float sy;
                    sx = ghost.getghostX();
                    sy = ghost.getghostY() - ghost.speed;
                    ghost.setghostX(sx);
                    ghost.setghostY(sy);
                    ghost.setPosition(sx, sy);
                }

                if(direccion_lvl1 == 'd'){
                    float sx;
                    float sy;
                    sx = ghost.getghostX();
                    sy = ghost.getghostY() + ghost.speed;
                    ghost.setghostX(sx);
                    ghost.setghostY(sy);
                    ghost.setPosition(sx, sy);
                }
                if(direccion_lvl1 == 'r'){
                    float sx;
                    float sy;
                    sx = ghost.getghostX()+ ghost.speed;;
                    sy = ghost.getghostY() ;
                    ghost.setghostX(sx);
                    ghost.setghostY(sy);
                    ghost.setPosition(sx, sy);
                }
                if(direccion_lvl1 == 'l'){
                    float sx;
                    float sy;
                    sx = ghost.getghostX() - ghost.speed;;
                    sy = ghost.getghostY() ;
                    ghost.setghostX(sx);
                    ghost.setghostY(sy);
                    ghost.setPosition(sx, sy);
                }
            }


            if(ghost.getGlobalBounds().intersects(player1.getGlobalBounds())){
                if(power_player){
                    scoreText.setString("Puntuacion : " + std::to_string(score+=50));
                    ghost.setPosition(1000,1000);
                    set_ghost = true;
                }
                else{
                    int ramon = rand() % 3;
                    a = ramon_x[ramon];
                    b = ramon_y[ramon];
                    player1.playerX = a;
                    player1.playerY = b;
                    playerLives --;
                }

            }

            if(set_ghost){
                if (loop % 200 == 0)
                {
                    counter ++;
                    if (counter == 5){
                        ghost.setPosition(850,65);
                        move_ghost = true;
                        ghost_normal_move_lvl1 = true;
                        backtracking_move_lvl1 = false;
                        direccion_lvl1 = 'l';
                        power_player = false;

                    }
                }
            }

            if(turnPoweron_1){
                if(fruit.getGlobalBounds().intersects(player1.getGlobalBounds())){
                    cout << "El poder fue comido por el PacMan" << endl;
                    power_player = true;
                    fruit.setPosition(1000, 1000);
                    one = false;
                }
                else if (fruit.getGlobalBounds().intersects(ghost.getGlobalBounds())){

                }
            }



            // update player position
            player1.setPosition(player1.playerX, player1.playerY);
            // clear the screen and draw all the shapes
            window.clear();
            window.draw(background);
            window.draw(lineTop, 5, sf::Lines);
            window.draw(line, 5, sf::Lines);


            for (int i = 0; i < 4; i++)//draw walls
            {
                window.draw(blockObj[i]);
            }
            for (int i = 0; i < 31; i++)//draw points
            {
                window.draw(pointsObj[i]);
            }
            if (turnPoweron_1){
                if(one){
                    fruit.setPosition(10, 65);
                    window.draw(fruit);
                }
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

        //Detecta si la puntuación es multiplo de 200 para hacer que aparezca el poder
        if (score == 200){
            turnPoweron_1 = true;
            ghost_normal_move_lvl1 = false;
            backtracking_move_lvl1 = true;
        }

        if (playerLives == 0){
            puntuacion_final puntos;
            return puntos.p(score);
        }


        //Detecta si todos los puntos fueron comidos
        for(int i = 0; i < 31; i++){
            if(!pointsObj[i].geteat()){
                verification ++;
            }
        }


        //Cambia de nivel
        if(verification == 0){
            window.close();
            PacMan2 pacman;
            return pacman.game(nivel + 1, score);
        }

        verification = 0;


        window.display();
    }

    return 0;
}
