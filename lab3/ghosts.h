#ifndef GLOSTSDEFINITION_H
#define GLOSTSDEFINITION_H
#include "baseghost.h"
#include "pacman.h"
#include "definitions.h"

class       OrangGhost;
class       PinkGhost;
class       BlueGhost;

class RedGhost : public baseghost
{
private:
    PinkGhost* pink;
    OrangGhost* orang;
    BlueGhost* blue;
    Q_OBJECT
public:
    RedGhost(QGraphicsScene *sc, char **map, Pacman *pac);
    void assign_to_friends(int n);
    void pos_default();
    void targeting();
    void find_pacman();
    void combine_ghosts(PinkGhost *pin, OrangGhost *ora, BlueGhost *blu);
public slots:
    void ghost_move();
};

class PinkGhost : public baseghost
{
private:
    RedGhost* red;
    OrangGhost* orang;
    BlueGhost* blue;
    Q_OBJECT
public:
    PinkGhost(QGraphicsScene *sc, char **map, Pacman *pc);
    void assign_to_friends(int n);
    void pos_default();
    void targeting();
    void find_pacman();
    void combine_ghosts(RedGhost *red, BlueGhost *blu, OrangGhost *ora);
public slots:
    void ghost_move();
};

class BlueGhost : public baseghost
{
private:
    OrangGhost* orang;
    RedGhost* red;
    PinkGhost* pink;
    Q_OBJECT
public:
    BlueGhost(QGraphicsScene *sc, char **map, Pacman *pc);
    void assign_to_friends(int n);
    void pos_default();
    void targeting();
    void find_pacman();
    void combine_ghosts(RedGhost *red_, PinkGhost *pin_, OrangGhost *ora_);
public slots:
    void ghost_move();
};

class OrangGhost : public baseghost
{
private:
    BlueGhost* blue;
    PinkGhost* pink;
    RedGhost* red;
    Q_OBJECT
public:
    OrangGhost(QGraphicsScene *sc, char **map, Pacman *pc);
    void assign_to_friends(int n);
    void pos_default();
    void targeting();
    void find_pacman();
    void combine_ghosts(RedGhost *red_, PinkGhost *pin_, BlueGhost *blu_);
public slots:
    void    ghost_move();
};

#endif // GLOSTSDEFINITION_H
