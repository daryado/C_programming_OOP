#include <QApplication>
#include <iostream>

#include "game.h"
#include "Validator.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Game* g;

    if (argc == 1 || argc > 2)
    {
        Exceptions::Invalid_number_of_args_error();
    }
    g = new Game(argv[1]);
    g->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    g->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    g->setFixedSize(WIDTH, HEIGHT);
    g->setSceneRect(0, 0, WIDTH, HEIGHT);
    g->show();
    g->ft_roll_game();
    return a.exec();
}
