#ifndef PACKMAN_H
#define PACKMAN_H

#include <QtCore/QObject>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "definitions.h"

class   Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int   pos_x;
    int   pos_y;
    int   direction;
    char  **map_char;
    QGraphicsPixmapItem **map_pix;
    QGraphicsScene     *scene;
    QGraphicsTextItem  *text;
    QGraphicsTextItem  *message;
    QGraphicsPixmapItem win;
    QGraphicsPixmapItem lost;
    int  lives;
    void update_scene();
    int  check_pass(int i_pos, int j_pos);
    bool scared;
    bool w_l;
    int counter;
    int score;
    int points;
public:
    Pacman(char **map_c, QGraphicsPixmapItem **map_pix, QGraphicsScene *scene);
    void    keyPressEvent(QKeyEvent *event);
    int     get_pacman_x(void);
    void    pac_pos_defaut();
    int     get_score();
    bool    scared_mode();
    void    switch_scared();
    int     pac_direction();
    int     get_pacman_y(void);
    void    add_score(int a);
    void    print_score();
    void    life_away();
    void    win_lost();
    int     get_points();
    void    lost_frame();
    void    win_frame();
public slots:
    void    pac_move();
};

#endif // PACKMAN_H
