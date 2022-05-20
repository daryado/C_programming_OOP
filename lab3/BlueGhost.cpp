#include <cmath>
#include "ghosts.h"

BlueGhost::BlueGhost(QGraphicsScene *scene_, char **map, Pacman *pacman_) : baseghost()
{
    scene = scene_;
    pacman = pacman_;
    x_ghost = 9;
    y_ghost = 10;
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
    this->setPixmap(QPixmap(":/pics/inky.png"));
    this->setPos(y_ghost * 32, x_ghost * 32);
    scene->addItem(this);
}

void        BlueGhost::find_pacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scared_mode())
    {
        this->setPixmap(QPixmap(":/pics/inky.png"));
        targeting();
    }
    else
    {
        if (x_ghost == definitions::size_y - 2 && y_ghost == 1)
            pacman->switch_scared();
        else
        {
            this->setPixmap(QPixmap(":/pics/frightened.png"));
            x_target = definitions::size_y - 2;
            y_target = 1;
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

void BlueGhost::assign_to_friends(int n){
    path_map[red->get_x()][red->get_y()] = n;
    path_map[pink->get_x()][pink->get_y()] = n;
    path_map[orang->get_x()][orang->get_y()] = n;
}

void        BlueGhost::pos_default()
{
    x_ghost = 9;
    y_ghost = 10;

    x_target = x_ghost;
    y_target = y_ghost;
    direction = 0;
    this->setPos(y_ghost * 32, x_ghost * 32);
}

void        BlueGhost::targeting()
{
    int direction;
    int x_red;
    int y_red;
    int distance;

    direction = pacman->pac_direction();
    if (direction == definitions::d_up)
    {
        x_target = pacman->get_pacman_x() - 2;
        y_target = pacman->get_pacman_y();
        if (x_target < 0)
        {
            x_target = pacman->get_pacman_x();
            y_target = pacman->get_pacman_y();
        }
    }
    if (direction == definitions::d_down)
    {
        x_target = pacman->get_pacman_x() + 2;
        y_target = pacman->get_pacman_y();
    }
    if (direction == definitions::d_left)
    {
        x_target = pacman->get_pacman_x();
        y_target = pacman->get_pacman_y() - 2;
    }
    if (direction == definitions::d_right)
    {
        x_target = pacman->get_pacman_x();
        y_target = pacman->get_pacman_y() + 2;
    }
    x_red = red->get_x();
    y_red = red->get_y();
    distance = pow(x_red - x_target, 2);
    distance += pow(y_red - y_target, 2);
    distance = sqrt(distance);
    distance /= 2;
    x_target += distance;
    y_target += distance;
    if (x_target <= 0 || x_target >= (definitions::size_y - 1)
            || y_target <= 0 || y_target >= (definitions::size_x - 1))
    {
        x_target = 9;
        y_target = 10;
    }
    this->setPixmap(QPixmap(":/pics/inky.png"));
}

void        BlueGhost::combine_ghosts(RedGhost *red_, PinkGhost *pin_, OrangGhost *ora_)
{
    red = red_;
    pink = pin_;
    orang = ora_;
}

void    BlueGhost::ghost_move()
{
    if (pacman->get_points() >= 100)
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
