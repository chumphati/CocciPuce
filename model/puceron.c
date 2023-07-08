#include "puceron.h"
#include "direction.h"

//returns the directional sign of the aphid
const char* PuceronToString(Puceron p) {
    switch (p.direction) {
        case North:
            return "∧";
        case South:
            return "∨";
        case East:
            return ">";
        case West:
            return "<";
        case South_east:
        case North_west:
            return "\\";
        case North_east:
        case South_west:
            return "/";
    }
    return " ";
}

//movement of a aphid
//depends on the rule (bypass wall or not)
//allows to modify the coordinates in the aphid table
void PuceronMove(Puceron *p, Rule rule) {
    p->coord = NextCoordFromDirection(p->direction, p->coord);
    if (rule.bypassWalls) {
        if (p->coord.y >= NB_ELEM_POTAGER && p->coord.x >= NB_ELEM_POTAGER) {
            p->coord.y = p->coord.x = 0;
        } else if (p->coord.y >= NB_ELEM_POTAGER) {
            p->coord.y = 0;
        } else if (p->coord.x >= NB_ELEM_POTAGER) {
            p->coord.x = 0;
        } else if (p->coord.x <= 0) {
            p->coord.x = NB_ELEM_POTAGER - 1;
        } else if (p->coord.y <= 0) {
            p->coord.y = NB_ELEM_POTAGER - 1;
        } else if (p->coord.y <= 0 && p->coord.x <= 0) {
            p->coord.y = p->coord.x = NB_ELEM_POTAGER - 1;
        }
    }
}

//returns true if the aphid has reached its maximum life points: i.e. 10 turns
bool PuceronMustDie(Puceron p) {
    return p.life >= PUCERON_MAX_LIFE;
}

//returns true if the condition of reproduction of the aphid is respected (the aphid has eaten 5 tomatoes)
bool PuceronCanGiveBirth(Puceron p) {
    return p.nbTurnEat >= PUCERON_BIRTH_TURN;
}

//takes as input all the aphids, the coord of interest and their number
//looks if the coordinate is already those where an aphid is and returns true if it is the case
bool PuceronsIsOnCoord(Puceron pucerons[], int size, Coordonnees c) {
    for (int i = 0; i < size; i++) {
        if (pucerons[i].coord.x == c.x && pucerons[i].coord.y == c.y) {
            return true;
        }
    }

    return false;
}