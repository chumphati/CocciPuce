#ifndef COCCIPUCE_PUCERON_H
#define COCCIPUCE_PUCERON_H

#include "stdbool.h"
#include "coordonnee.h"
#include "direction.h"
#include "potager.h"
#include <stdlib.h>
#include <time.h>

static const int PUCERON_MAX_LIFE = 10; //the aphids can survive 10 turns
static const int PUCERON_BIRTH_TURN = 5; //the aphids can give birth when they have eaten 5 tomatoes

//structure that contains all the attributes of the aphids :
//the coord, if it is alive or not, the number of time they eat, their life points and the direction they have to take
typedef struct Puceron {
    Coordonnees coord;
    bool isDead;
    int nbTurnEat;
    int life;
    enum Direction direction;
} Puceron;

const char* PuceronToString(Puceron p);
void PuceronMove(Puceron *p, Rule rule);
bool PuceronCanGiveBirth(Puceron p);
bool PuceronMustDie(Puceron p);
bool PuceronsIsOnCoord(Puceron pucerons[], int size, Coordonnees c);
#endif //COCCIPUCE_PUCERON_H
