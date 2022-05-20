#include <cmath>
#include "ghosts.h"

OrangGhost::OrangGhost(QGraphicsScene *scene_, char **map, Pacman *pacman_) : baseghost()
{
    scene = scene_;
    pacman = pacman_;
    x_ghost = 9;
    y_ghost = 8;
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
    this->setPixmap(QPixmap(":/pics/clyde.png"));
    this->setPos(y_ghost * 32, x_ghost * 32);
    scene->addItem(this);
}

void        OrangGhost::find_pacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scared_mode())
    {
        this->setPixmap(QPixmap(":/pics/clyde.png"));
        targeting();
    }
    else
    {
        if (x_ghost == definitions::size_y - 2 && y_ghost ==  definitions::size_x - 2)
            pacman->switch_scared();
        else
        {
            this->setPixmap(QPixmap(":/pics/frightened.png"));
            x_target = definitions::size_y - 2;
            y_target = definitions::size_x - 2;
        }
    }
    path_map[x_ghost][y_ghost] = d;
    if (intersect())
        return ;
    way_to_target();
    if (direction_near())
    {
        default_map();
        return ;
    }
    restore_path();
    set_direction();
    default_map();
}

void OrangGhost::assign_to_friends(int n){
    path_map[red->get_x()][red->get_y()] = n;
    path_map[pink->get_x()][pink->get_y()] = n;
    path_map[blue->get_x()][blue->get_y()] = n;
}

void        OrangGhost::pos_default()
{
    x_ghost = 9;
    y_ghost = 8;
    x_target = x_ghost;
    y_target = y_ghost;
    direction = 0;
    this->setPos(y_ghost * 32, x_ghost * 32);
}

void        OrangGhost::targeting()
{
    int distance;
    distance = pow(x_ghost - pacman->get_pacman_x(), 2);
    distance += pow(y_ghost - pacman->get_pacman_y(), 2);
    distance = sqrt(distance);
    if (distance <= 8)
    {
        x_target = pacman->get_pacman_x();
        y_target = pacman->get_pacman_y();
    }
    else
    {
        x_target = definitions::size_y - 2;
        y_target = 1;
    }
    this->setPixmap(QPixmap(":/pics/clyde.png"));
}

void        OrangGhost::combine_ghosts(RedGhost *red_, PinkGhost *pin_, BlueGhost *blu_)
{
    red = red_;
    pink = pin_;
    blue = blu_;
}

void    OrangGhost::ghost_move()
{
    if (pacman->get_points() >= 90)
    {
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
}
