#include "pacman.h"
#include <iostream>
#include <QPainter>
#include "definitions.h"


bool     Pacman::scared_mode()
{
    return (scared);
}

void    Pacman::switch_scared()
{
    scared = !scared;
}

int     Pacman::get_score()
{
    return (score);
}


void    Pacman::add_score(int a)
{
    score += a;
}

void    Pacman::life_away()
{
    lives--;
}

int     Pacman::get_points()
{
    return (points);
}

int     Pacman::pac_direction()
{
    return (direction);
}

void    Pacman::update_scene()
{
    static bool cherry;

    if (map_char[pos_x][pos_y] == 'f')
    {
        map_char[pos_x][pos_y] = '0';
        add_score(10);
        points++;
        scene->removeItem(&(map_pix[pos_x][pos_y]));
    }
    if (map_char[pos_x][pos_y] == 'c')
    {
        add_score(200);
        map_char[pos_x][pos_y] = '0';
        scene->removeItem(&(map_pix[15][9]));
        cherry = false;
    }
    if (map_char[pos_x][pos_y] == 'e')
    {
        scared = true;
        map_char[pos_x][pos_y] = '0';
        scene->removeItem(&(map_pix[pos_x][pos_y]));
    }
    if (points == 50)
    {
        map_char[15][9] = 'c';
        if (!cherry)
        {
            map_pix[15][9].setPixmap(QPixmap(":/pics/cherries.png"));
            scene->addItem(&(map_pix[15][9]));
            cherry = true;
        }
    }
}

void    Pacman::print_score()
{
    text->setDefaultTextColor(0x00ffe5b4);
    text->setFont(QFont("times", 15));
    text->setPlainText("SCORE: " + QString::number(score) + "\t\tLIVES: " + QString::number(lives));
    text->setPos(10 , definitions::HEIGHT - 30);
}

Pacman::Pacman(char **map_c, QGraphicsPixmapItem **map_p, QGraphicsScene *sc)
{
    pos_x = 15;
    pos_y = 9;

    score = 0;
    points = 0;
    counter = 0;
    direction = 0;
    scared = 0;
    lives = 3;

    map_char = map_c;
    map_pix = map_p;

    scene = sc;
    text = new QGraphicsTextItem();
    message = new QGraphicsTextItem();
    this->setPixmap(QPixmap(":/pics/pacman_left.png"));
    this->setPos(pos_y * 32, pos_x * 32);
    scene->addItem(this);
    scene->addItem(text);
    print_score();
}

void    Pacman::keyPressEvent(QKeyEvent *b)
{
    if (b->key() == Qt::Key_Left)
     {
        this->direction = definitions::d_left;
        this->setPixmap(QPixmap(":/pics/pacman_left.png"));
     }
     if (b->key() == Qt::Key_Right)
     {
        this->direction = definitions::d_right;
         this->setPixmap(QPixmap(":/pics/pacman_right.png"));
     }
     if (b->key() == Qt::Key_Down)
     {
        this->direction = definitions::d_down;
        this->setPixmap(QPixmap(":/pics/pacman_down.png"));
     }
     if (b->key() == Qt::Key_Up)
     {
        this->direction = definitions::d_up;
        this->setPixmap(QPixmap(":/pics/pacman_up.png"));
     }
}
void Pacman::win_lost(){
    w_l = 0;
    if (points >= 149 )
    {
        win_frame();
        scene->removeItem(this);
        scene->removeItem(text);
        w_l = 1;
    }
     if (lives <= 0 )
      {
        lost_frame();
        scene->removeItem(this);
        scene->removeItem(text);
        w_l = 1;
      }
}

void    Pacman::pac_move()
{
    win_lost();
    print_score();
    update_scene();
    if (direction == definitions::d_up)
    {
            if (pos_x == 0)
            {
               if (check_pass(definitions::size_y - 1, pos_y))
                   pos_x = definitions::size_y - 1;
            }
            else
                if (check_pass(pos_x - 1, pos_y))
                    pos_x--;
        }
        if (direction == definitions::d_down)
        {
            if (pos_x == definitions::size_y - 1)
            {
                if (check_pass(0, pos_y))
                    pos_x = 0;
            }
            else
                if (check_pass(pos_x + 1, pos_y))
                    pos_x++;
        }
        if (direction == definitions::d_left)
        {
            if (pos_y == 0)
            {
                if (check_pass(pos_x, definitions::size_x - 1))
                    pos_y = definitions::size_x - 1;
            }
            else
                if (check_pass(pos_x, pos_y - 1))
                    pos_y--;
        }
        if (direction == definitions::d_right)
        {
            if (pos_y == definitions::size_x - 1)
            {
                if (check_pass(pos_x, 0))
                    pos_y = 0;
            }
            else
                if (check_pass(pos_x, pos_y + 1))
                    pos_y++;
        }
        this->setPos(pos_y * 32, pos_x * 32);
}

int     Pacman::get_pacman_x(void)
{
    return (pos_x);
}

int     Pacman::get_pacman_y(void)
{
    return (pos_y);
}

int     Pacman::check_pass(int i_pos, int j_pos)
{
    if (map_char[i_pos][j_pos] == 'w')
        return (0);
    return (1);
}

void    Pacman::pac_pos_defaut()
{
    pos_x = 15;
    pos_y = 9;

    direction = 0;
    this->setPos(pos_y * 32, pos_x * 32);
}

void Pacman::win_frame(){

    for (int i = 5;i < 14;i++){
        map_pix[3][i].setPixmap(QPixmap(":/win/15.png"));
        map_pix[3][i].setPos(i * 32, 3 * 32);
        scene->addItem(&(map_pix[3][i]));
        map_pix[6][i].setPixmap(QPixmap(":/win/15.png"));
        map_pix[6][i].setPos(i * 32, 6 * 32);
        scene->addItem(&(map_pix[6][i]));
    }
    map_pix[4][5].setPixmap(QPixmap(":/win/15.png"));
    map_pix[4][5].setPos(5 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][5]));
    map_pix[5][5].setPixmap(QPixmap(":/win/15.png"));
    map_pix[5][5].setPos(5 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][5]));

    map_pix[4][13].setPixmap(QPixmap(":/win/15.png"));
    map_pix[4][13].setPos(13 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][13]));
    map_pix[5][13].setPixmap(QPixmap(":/win/15.png"));
    map_pix[5][13].setPos(13 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][13]));

    map_pix[4][6].setPixmap(QPixmap(":/win/win1.png"));
    map_pix[4][6].setPos(6 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][6]));
    map_pix[4][7].setPixmap(QPixmap(":/win/win2.png"));
    map_pix[4][7].setPos(7 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][7]));
    map_pix[4][8].setPixmap(QPixmap(":/win/win3.png"));
    map_pix[4][8].setPos(8 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][8]));
    map_pix[4][9].setPixmap(QPixmap(":/win/win4.png"));
    map_pix[4][9].setPos(9 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][9]));
    map_pix[4][10].setPixmap(QPixmap(":/win/win5.png"));
    map_pix[4][10].setPos(10 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][10]));
    map_pix[4][11].setPixmap(QPixmap(":/win/win6.png"));
    map_pix[4][11].setPos(11 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][11]));
    map_pix[4][12].setPixmap(QPixmap(":/win/win7.png"));
    map_pix[4][12].setPos(12 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][12]));
    map_pix[5][6].setPixmap(QPixmap(":/win/win8.png"));
    map_pix[5][6].setPos(6 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][6]));
    map_pix[5][7].setPixmap(QPixmap(":/win/win9.png"));
    map_pix[5][7].setPos(7 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][7]));
    map_pix[5][8].setPixmap(QPixmap(":/win/win10.png"));
    map_pix[5][8].setPos(8 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][8]));
    map_pix[5][9].setPixmap(QPixmap(":/win/win11.png"));
    map_pix[5][9].setPos(9 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][9]));
    map_pix[5][10].setPixmap(QPixmap(":/win/win12.png"));
    map_pix[5][10].setPos(10 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][10]));
    map_pix[5][11].setPixmap(QPixmap(":/win/win13.png"));
    map_pix[5][11].setPos(11 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][11]));
    map_pix[5][12].setPixmap(QPixmap(":/win/win14.png"));
    map_pix[5][12].setPos(12 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][12]));
}

void Pacman::lost_frame(){

    for (int i = 5;i < 14;i++){
        map_pix[3][i].setPixmap(QPixmap(":lost/15.png"));
        map_pix[3][i].setPos(i * 32, 3 * 32);
        scene->addItem(&(map_pix[3][i]));
        map_pix[6][i].setPixmap(QPixmap(":lost/15.png"));
        map_pix[6][i].setPos(i * 32, 6 * 32);
        scene->addItem(&(map_pix[6][i]));
    }
    map_pix[4][5].setPixmap(QPixmap(":lost/15.png"));
    map_pix[4][5].setPos(5 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][5]));
    map_pix[5][5].setPixmap(QPixmap(":lost/15.png"));
    map_pix[5][5].setPos(5 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][5]));

    map_pix[4][13].setPixmap(QPixmap(":lost/15.png"));
    map_pix[4][13].setPos(13 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][13]));
    map_pix[5][13].setPixmap(QPixmap(":lost/15.png"));
    map_pix[5][13].setPos(13 * 32, 5 * 32);
    scene->addItem(&(map_pix[4][13]));

    map_pix[4][6].setPixmap(QPixmap(":lost/lost1.png"));
    map_pix[4][6].setPos(6 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][6]));
    map_pix[4][7].setPixmap(QPixmap(":lost/lost2.png"));
    map_pix[4][7].setPos(7 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][7]));
    map_pix[4][8].setPixmap(QPixmap(":lost/lost3.png"));
    map_pix[4][8].setPos(8 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][8]));
    map_pix[4][9].setPixmap(QPixmap(":lost/lost4.png"));
    map_pix[4][9].setPos(9 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][9]));
    map_pix[4][10].setPixmap(QPixmap(":lost/lost5.png"));
    map_pix[4][10].setPos(10 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][10]));
    map_pix[4][11].setPixmap(QPixmap(":lost/lost6.png"));
    map_pix[4][11].setPos(11 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][11]));
    map_pix[4][12].setPixmap(QPixmap(":lost/lost7.png"));
    map_pix[4][12].setPos(12 * 32, 4 * 32);
    scene->addItem(&(map_pix[4][12]));
    map_pix[5][6].setPixmap(QPixmap(":lost/lost8.png"));
    map_pix[5][6].setPos(6 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][6]));
    map_pix[5][7].setPixmap(QPixmap(":lost/lost9.png"));
    map_pix[5][7].setPos(7 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][7]));
    map_pix[5][8].setPixmap(QPixmap(":lost/lost10.png"));
    map_pix[5][8].setPos(8 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][8]));
    map_pix[5][9].setPixmap(QPixmap(":lost/lost11.png"));
    map_pix[5][9].setPos(9 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][9]));
    map_pix[5][10].setPixmap(QPixmap(":lost/lost12.png"));
    map_pix[5][10].setPos(10 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][10]));
    map_pix[5][11].setPixmap(QPixmap(":lost/lost13.png"));
    map_pix[5][11].setPos(11 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][11]));
    map_pix[5][12].setPixmap(QPixmap(":lost/lost14.png"));
    map_pix[5][12].setPos(12 * 32, 5 * 32);
    scene->addItem(&(map_pix[5][12]));
}
