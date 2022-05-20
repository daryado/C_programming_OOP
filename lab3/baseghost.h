#ifndef GLOST_H
#define GLOST_H

#include "pacman.h"
#include "definitions.h"

class   baseghost : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    int d;
    int x_ghost;
    int y_ghost;
    int i_x;
    int i_y;
    int flag;
    int x_target;
    int y_target;
    int direction;
    int path_map[definitions::size_y][definitions::size_x];
    int x_dir[4] = { 1, -1, 0, 0 };
    int y_dir[4] = { 0, 0, 1, -1 };
    Pacman          *pacman;
    QGraphicsScene  *scene;
public:
    void default_map();
    void restore_path();
    void set_direction();
    virtual void find_pacman() = 0;
    void    way_to_target();
    virtual void assign_to_friends(int n) = 0;
    int intersect();
    int direction_near();
    int get_x();
    int get_y();
    int not_a_wall(int i_pos, int j_pos);
    virtual void pos_default() = 0;
    virtual void targeting() = 0;
    baseghost(){};
public slots:
    virtual void    ghost_move() = 0;
};

#endif // GLOST_H
