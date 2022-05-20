#include <QGraphicsPixmapItem>
#include "baseghost.h"

void baseghost::way_to_target()
{
    int i;
    int j;
    int k;
    assign_to_friends(definitions::barrier);
    while (!flag && path_map[x_target][y_target] == definitions::empty)
    {
        i = 0;
        flag = 1;
        while (i < definitions::size_y)
        {
            j = 0;
            while (j < definitions::size_x)
            {
                if (path_map[i][j] == d)
                {
                    k = 0;
                    while (k < 4)
                    {
                        i_x = x_dir[k] + i;
                        i_y = y_dir[k] + j;
                        if ((i_x >= 0 && i_x < definitions::size_y) && (i_y >= 0 && i_y < definitions::size_x) && (path_map[i_x][i_y] == definitions::empty))
                        {
                            path_map[i_x][i_y] = d + 1;
                            flag = 0;
                        }
                        k++;
                    }
                }
                j++;
            }
            i++;
        }
        d++;
    }
    assign_to_friends(0);
}


int     baseghost::get_x()
{
    return (x_ghost);
}

int     baseghost::get_y()
{
    return (y_ghost);
}

int     baseghost::not_a_wall(int i_pos, int j_pos)
{
    if (path_map[i_pos][j_pos] == definitions::barrier)
        return (0);
    return (1);
}

void        baseghost::set_direction()
{
    if (x_ghost + 1 < definitions::size_y)
    {
        if (path_map[x_ghost + 1][y_ghost] == definitions::restored_path)
            direction = definitions::d_down;
    }
    if (x_ghost - 1 >= 0)
    {
        if (path_map[x_ghost - 1][y_ghost] == definitions::restored_path)
            direction = definitions::d_up;
    }
    if (y_ghost + 1 < definitions::size_y)
    {
        if (path_map[x_ghost][y_ghost + 1] == definitions::restored_path)
            direction = definitions::d_right;
    }
    if (y_ghost - 1 < definitions::size_y)
    {
        if (path_map[x_ghost][y_ghost - 1] == definitions::restored_path)
            direction = definitions::d_left;
    }
}

int        baseghost::intersect()
{
    if (x_ghost == pacman->get_pacman_x() && y_ghost == pacman->get_pacman_y()
            && !pacman->scared_mode())
    {
        default_map();
        pacman->pac_pos_defaut();
        pacman->life_away();
        return (1);
    }
    if (x_ghost == pacman->get_pacman_x() && y_ghost == pacman->get_pacman_y()
            && pacman->scared_mode())
    {
        default_map();
        x_ghost = 8;
        y_ghost = 9;
        this->setPos(y_ghost * 32, x_ghost * 32);
        pacman->add_score(100);
        return (1);
    }
    return (0);
}

void        baseghost::default_map()
{
    for (int i = 0; i < definitions::size_y; i++)
    {
        for (int j = 0; j < definitions::size_x; j++)
        {
            if (path_map[i][j] != definitions::barrier)
                path_map[i][j] = definitions::empty;
        }
    }
}

void        baseghost::restore_path()
{
    int i;
    int j;
    int k;
    i = x_target;
    j = y_target;
    while (d > 0)
    {
        d--;
        k = 0;
        while (k < 4)
        {
            i_x = i + x_dir[k];
            i_y = j + y_dir[k];
            if (i_x >= 0 && i_x < definitions::size_y && i_y >= 0 && i_y < definitions::size_x && path_map[i_x][i_y] == d)
            {
                path_map[i_x][i_y] = definitions::restored_path;
                i = i + x_dir[k];
                j = j + y_dir[k];
                break ;
            }
            k++;
        }
    }
}

int         baseghost::direction_near()
{
    int flag;
    flag = 0;
    if (x_ghost + 1 < definitions::size_y)
    {
        if (x_ghost + 1 == x_target && y_ghost == y_target)
        {
            direction = definitions::d_down;
            flag = 1;
        }
    }
    if (x_ghost - 1 >= 0)
    {
        if (x_ghost -1 == x_target && y_ghost == y_target)
        {
            direction = definitions::d_up;
            flag = 1;
        }
    }
    if (y_ghost + 1 < definitions::size_y)
    {
        if (x_ghost == x_target && y_ghost + 1 == y_target)
        {
            direction = definitions::d_right;
            flag = 1;
        }
    }
    if (y_ghost - 1 < definitions::size_y)
    {
        if (x_ghost == x_target && y_ghost - 1 == y_target)
        {
            direction = definitions::d_left;
            flag = 1;
        }
    }
    if (flag)
        return (1);
    return (0);
}

void baseghost::find_pacman(){};

