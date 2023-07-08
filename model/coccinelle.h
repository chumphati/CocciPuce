#ifndef COCCIPUCE_COCCINELLE_H
#define COCCIPUCE_COCCINELLE_H

#include "coordonnee.h"
#include "direction.h"
#include "stdbool.h"
#include "potager.h"
#include "puceron.h"

static const int COCCINELLE_MAX_LIFE = 20; //the ladybug can survive 20 turns maximum
static const int COCCINELLE_BIRTH_TURN = 3; //the ladybug can give birth if it has eaten 3 aphids
static const int COCCINELLE_PORTEE = 3; //the ladybug can scan the aphid 3 squares around it

//ladybug type
//contains its coord, direction, if it's alive or not, its life points and the number of turn it has eaten
typedef struct Coccinelle {
    Coordonnees coord;
    enum Direction direction;
    bool isDead;
    int nbTurnEat;
    int life;
} Coccinelle;


const char* CoccinelleToString(Coccinelle c);
void CoccinelleMove(Coccinelle *c, Rule rule);
bool CoccinelleCanGiveBirth(Coccinelle c);
bool CoccinelleMustDie(Coccinelle c);

Puceron CoccinelleScan(Coccinelle c, Puceron pucerons[], int sizePuceron);

bool CoccinelleIsOnCoord(Coccinelle coccinelles[], int size, Coordonnees c);

#endif //COCCIPUCE_COCCINELLE_H
