#include <cmath>
#include "ghosts.h"

PinkGhost::PinkGhost(QGraphicsScene *scene_, char **map, Pacman *pacman_) : baseghost()
{
    x_ghost = 9;
    y_ghost = 9;
    scene = scene_;
    pacman = pacman_;
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
    this->setPixmap(QPixmap(":/pics/pinky.png"));
    this->setPos(y_ghost * 32, x_ghost * 32);
    scene->addItem(this);
}

void        PinkGhost::find_pacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scared_mode())
    {
        this->setPixmap(QPixmap(":/pics/pinky.png"));
        targeting();
    }
    else
    {
        if (x_ghost == 1 && y_ghost == definitions::size_x - 2)
            pacman->switch_scared();
        else
        {
            this->setPixmap(QPixmap(":/pics/frightened.png"));
            x_target = 1;
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

void PinkGhost::assign_to_friends(int n){
    path_map[red->get_x()][red->get_y()] = n;
    path_map[blue->get_x()][blue->get_y()] = n;
    path_map[orang->get_x()][orang->get_y()] = n;
}

void PinkGhost::pos_default()
{
    x_ghost = 9;
    y_ghost = 9;

    x_target = x_ghost;
    y_target = y_ghost;
    direction = 0;
    this->setPos(y_ghost * 32, x_ghost * 32);
}

void        PinkGhost::targeting()
{
    int direction;
    direction = pacman->pac_direction();
     if (direction == definitions::d_up)
     {
         x_target = pacman->get_pacman_x() - 4;
         y_target = pacman->get_pacman_y();
         if (x_target < 0)
         {
             x_target = pacman->get_pacman_x();
             y_target = pacman->get_pacman_y();
         }
     }
     if (direction == definitions::d_down)
     {
         x_target = pacman->get_pacman_x() + 4;
         y_target = pacman->get_pacman_y();
         if (x_target >= definitions::size_y)
         {
             x_target = pacman->get_pacman_x();
             y_target = pacman->get_pacman_y();
         }
     }
     if (direction == definitions::d_left)
     {
         x_target = pacman->get_pacman_x();
         y_target = pacman->get_pacman_y() - 4;
         if (y_target < 0)
         {
             x_target = pacman->get_pacman_x();
             y_target = pacman->get_pacman_y();
         }
     }
     if (direction == definitions::d_right)
     {
         x_target = pacman->get_pacman_x();
         y_target = pacman->get_pacman_y() + 4;
         if (y_target > definitions::size_x)
         {
             x_target = pacman->get_pacman_x();
             y_target = pacman->get_pacman_y();
         }
     }
     if (path_map[x_target][y_target] != definitions::restored_path)
     {
         x_target = pacman->get_pacman_x();
         y_target = pacman->get_pacman_y();
     }
}

void        PinkGhost::combine_ghosts(RedGhost *red_, BlueGhost *blu_, OrangGhost *ora_)
{
    red = red_;
    blue = blu_;
    orang = ora_;
}

void    PinkGhost::ghost_move()
{
    if (pacman->get_points() >= 50)
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
