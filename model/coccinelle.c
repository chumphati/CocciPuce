#include "coccinelle.h"
#include "potager.h"

//returns the directional sign of the ladybird
const char* CoccinelleToString(Coccinelle c) {
    switch (c.direction) {
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

//movement of a ladybird
//depends on the rule (bypass wall or not)
//allows to modify the coordinates in the ladybird table
void CoccinelleMove(Coccinelle *c, Rule rule) {
    c->coord = NextCoordFromDirection(c->direction, c->coord);
    if (rule.bypassWalls) {
        if (c->coord.y >= NB_ELEM_POTAGER && c->coord.x >= NB_ELEM_POTAGER) {
            c->coord.y = c->coord.x = 0;
        } else if (c->coord.y >= NB_ELEM_POTAGER) {
            c->coord.y = 0;
        } else if (c->coord.x >= NB_ELEM_POTAGER) {
            c->coord.x = 0;
        } else if (c->coord.x <= 0) {
            c->coord.x = NB_ELEM_POTAGER - 1;
        } else if (c->coord.y <= 0) {
            c->coord.y = NB_ELEM_POTAGER - 1;
        } else if (c->coord.y <= 0 && c->coord.x <= 0) {
            c->coord.y = c->coord.x = NB_ELEM_POTAGER - 1;
        }
    }
}

//returns true if the condition of reproduction of the ladybird is respected (the ladybird has eaten 3 aphids)
bool CoccinelleCanGiveBirth(Coccinelle c) {
    return c.nbTurnEat >= COCCINELLE_BIRTH_TURN;
}

//returns true if the ladybird has reached its maximum life points: i.e. 20 turns
bool CoccinelleMustDie(Coccinelle c) {
    return c.life >= COCCINELLE_MAX_LIFE;
}

//allows the ladybirds to scan their surroundings to find an aphid
//takes as input the ladybird of interest, all aphids and their number
//returns an aphid with its attributes if there is one, otherwise returns an empty aphid
Puceron CoccinelleScan(Coccinelle c, Puceron pucerons[], int sizePuceron) {
    Puceron targetPuceron;
    targetPuceron.isDead = true;

    int diffX, diffY;
    int i;
    for (i = 0; i < sizePuceron; i++) {
        diffX = c.coord.x - pucerons[i].coord.x;
        diffY = c.coord.y - pucerons[i].coord.y;

        if (diffX < 0) {
            diffX = diffX * (-1);
        }
        if (diffY < 0) {
            diffY = diffY * (-1);
        }

        //if the aphid is close enough, it becomes the target
        if (diffX <= COCCINELLE_PORTEE && diffY <= COCCINELLE_PORTEE) {
            targetPuceron = pucerons[i];
        }
    }

    return targetPuceron;
}

//takes as input all the ladybirds, the coord of interest and their number
//looks if the coordinate is already those where an ladybirds is and returns true if it is the case
bool CoccinelleIsOnCoord(Coccinelle coccinelles[], int size, Coordonnees c) {
    for (int i = 0; i < size; i++) {
        if (coccinelles[i].coord.x == c.x && coccinelles[i].coord.y == c.y) {
            return true;
        }
    }

    return false;
}