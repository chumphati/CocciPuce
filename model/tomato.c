#include "tomato.h"

//returns the sign of the tomato depending of its growth state
const char* TomatoToString(Tomato t) {
    char *res;
    switch (getLifeState(t)) {
        case StateBeginLife:
            res = ".";
            break;
        case StateMiddleLife:
            res = "o";
            break;
        case StateEndLife:
            res = "O";
            break;
    }

    return res;
}

//returns the state of the tomato according to its life value
enum State getLifeState(Tomato t) {
    if (t.life >= TOMATO_MAX_LIFE) {
        return StateEndLife;
    }

    if (t.life >= 5 && t.life < TOMATO_MAX_LIFE) {
        return StateMiddleLife;
    }

    return StateBeginLife;
}