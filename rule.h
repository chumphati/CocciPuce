#ifndef COCCIPUCE_RULE_H
#define COCCIPUCE_RULE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "stdbool.h"
#include "model/coordonnee.h"
#include "model/direction.h"

//matrix size
enum {
    NB_ELEM_POTAGER = 30
};

//structure including the rules that the user can choose when starting the simulation:
// the option of transparent walls and the number of simulation rounds
typedef struct Rule {
    bool bypassWalls;
    int nbTurnLimit;
} Rule;

bool SpawnDirectionIsPossible(Rule rule, Coordonnees coord, enum Direction direction);

#endif //COCCIPUCE_RULE_H
