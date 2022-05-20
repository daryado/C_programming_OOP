#include "game.h"


Game::~Game()
{
    delete scene;
    delete view;
    delete pac;
    delete pink;
    delete orang;
    delete blue;
    delete red;
    delete timer_pacman;
    delete timer_red;
    delete timer_pink;
    delete timer_orang;
    delete timer_blue;
    for (int i = 0; i < definitions::size_y; i++)
    {
        for (int j = 0; j < definitions::size_x; j++)
        {
            delete map_pix[i];
            delete map_char[i];
        }
    }
    delete []map_pix;
    delete []map_char;
}

void    Game::ft_roll_game()
{
    timer_red = new QTimer();
    timer_pink = new QTimer();
    timer_orang = new QTimer();
    timer_pacman = new QTimer();
    timer_blue = new QTimer();
    QObject::connect(timer_pacman, SIGNAL(timeout()), pac, SLOT(pac_move()));
    QObject::connect(timer_blue, SIGNAL(timeout()), blue, SLOT(ghost_move()));
    QObject::connect(timer_orang, SIGNAL(timeout()), orang, SLOT(ghost_move()));
    QObject::connect(timer_red, SIGNAL(timeout()), red, SLOT(ghost_move()));
    QObject::connect(timer_pink, SIGNAL(timeout()), pink, SLOT(ghost_move()));
    timer_pacman->start(300);
    timer_blue->start(400);
    timer_orang->start(400);
    timer_red->start(400);
    timer_pink->start(400);
}

void    Game::build_a_map()
{
    for (int i = 0; i < definitions::size_y; i++)
    {
        for (int j = 0; j < definitions::size_x; j++)
        {
            if (map_char[i][j] == 'w')
            {
                map_pix[i][j].setPixmap(QPixmap(":/pics/greystone.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
            if (map_char[i][j] == 'f')
            {
                map_pix[i][j].setPixmap(QPixmap(":/pics/ball.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
            if (map_char[i][j] == 'e')
            {
                map_pix[i][j].setPixmap(QPixmap(":/pics/energizer.png"));
                map_pix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(map_pix[i][j]));
            }
        }
    }
}

void    Game::create_maps()
{
    map_char = new char *[definitions::size_y];
    map_pix = new QGraphicsPixmapItem *[definitions::size_y];
    for (int i = 0; i < definitions::size_y; i++)
    {
        map_char[i] = new char[definitions::size_x];
        map_pix[i] = new QGraphicsPixmapItem[definitions::size_x];
    }
}

Game::Game(char *f_name)
{
    std::ifstream input;
    std::string st;
    int n;
    create_maps();
    input.open(f_name);
    if (!input.is_open())
    {
        Exceptions::File_missing_error();
    }
        n = 0;
        while (std::getline(input, st))
        {
            if (st.length() != definitions::size_x)
            {
                Exceptions::file_length_y_error();
            }
            for (int i = 0; i < definitions::size_x; i++)
                map_char[n][i] = st[i];
            n++;
        }
        if (n != definitions::size_y)
        {
            Exceptions::file_length_y_error();
        }
        input.close();
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    this->setScene(scene);
    build_a_map();
    this->setStyleSheet("background-color:black;");
    pac = new Pacman(map_char, map_pix, scene);
    pac->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    pac->setFocus();
    red = new RedGhost(scene, map_char, pac);
    pink = new PinkGhost(scene, map_char, pac);
    orang = new OrangGhost(scene, map_char, pac);
    blue = new BlueGhost(scene, map_char, pac);
    red->combine_ghosts(pink, orang, blue);
    pink->combine_ghosts(red, blue, orang);
    orang->combine_ghosts(red, pink, blue);
    blue->combine_ghosts(red, pink, orang);
}

