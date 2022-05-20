#include <cmath>
#include "ghosts.h"

RedGhost::RedGhost(QGraphicsScene *scene_, char **map, Pacman *pacman_) : baseghost()
{
    scene = scene_;
    pacman = pacman_;
    x_ghost = 8;
    y_ghost = 9;
    for (int i = 0; i < definitions::size_y; i++)
        {
            for (int j = 0; j < definitions::size_x; j++)
           {
           if (map[i][j] == 'w')
           path_map[i][j] = definitions::barrier;
           else
           path_map[i][j] = definitions::empty;
        }
    }
    this->setPixmap(QPixmap(":/pics/blinky.png"));
    this->setPos(y_ghost * 32, x_ghost * 32);
    scene->addItem(this);
}

void RedGhost::find_pacman()
{
    d = 0;
    flag = 0;
    path_map[x_ghost][y_ghost] = d;
    if (intersect())
    {
        default_map();
        return ;
    }
    way_to_target();
    if (direction_near())
    {
        if (intersect())
        {
            default_map();
            return ;
        }
    }
    restore_path();
    set_direction();
    default_map();
}

void RedGhost::assign_to_friends(int n){
    path_map[blue->get_x()][blue->get_y()] = n;
    path_map[pink->get_x()][pink->get_y()] = n;
    path_map[orang->get_x()][orang->get_y()] = n;
}

void        RedGhost::pos_default()
{
    x_target = x_ghost;
    y_target = y_ghost;
    x_ghost = 9;
    y_ghost = 9;
    direction = 0;
    this->setPos(y_ghost * 32, x_ghost * 32);
}

void        RedGhost::targeting()
{
    if (!pacman->scared_mode())
    {
        x_target = pacman->get_pacman_x();
        y_target = pacman->get_pacman_y();
        this->setPixmap(QPixmap(":/pics/blinky.png"));
    }
    else
    {
        if (x_ghost == 1 && y_ghost == 1)
            pacman->switch_scared();
        else
        {
            this->setPixmap(QPixmap(":/pics/frightened.png"));
            x_target = 1;
            y_target = 1;
        }
    }
}

void        RedGhost::combine_ghosts( PinkGhost *pin_, OrangGhost *ora_, BlueGhost *blue_)
{
    blue = blue_;
    pink = pin_;
    orang = ora_;
}

void    RedGhost::ghost_move()
{
        targeting();
        find_pacman();
        if (direction == definitions::d_up)
        {
            if (not_a_wall(x_ghost - 1, y_ghost))
                x_ghost--;
        }
        if (direction == definitions::d_down)
        {
            if (not_a_wall(x_ghost + 1, y_ghost))
                x_ghost++;
        }
        if (direction == definitions::d_left)
        {
            if (not_a_wall(x_ghost, y_ghost - 1))
                y_ghost--;
        }
        if (direction == definitions::d_right)
        {
            if (not_a_wall(x_ghost, y_ghost + 1))
                y_ghost++;
        }
        this->setPos(y_ghost * 32, x_ghost * 32);
        if (intersect())
            return ;
}
