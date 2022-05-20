#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <QTimer>
#include <QObject>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsPixmapItem>
#include "pacman.h"
#include "baseghost.h"
#include "ghosts.h"
#include "Validator.h"

#define WIDTH 608
#define HEIGHT 702
#define MAX_X 21
#define MAX_Y 19

class   Game : public QGraphicsView
{
private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem** map_pix;
    Pacman* pac;
    RedGhost* red;
    PinkGhost* pink;
    OrangGhost* orang;
    BlueGhost* blue;
    char** map_char;
    QTimer* timer_pacman;
    QTimer* timer_red;
    QTimer* timer_pink;
    QTimer* timer_orang;
    QTimer* timer_blue;
public:
    Game(char* file_name);
    ~Game();
    void create_maps();
    void ft_write_line_map(char* map, std::string str);
    void ft_roll_game();
    void build_a_map();
};

#endif // GAME_H
