#ifndef COCCIPUCE_TOMATO_H
#define COCCIPUCE_TOMATO_H

static const int TOMATO_MAX_LIFE = 20; //mature tomato
static const int TOMATO_MIN_LIFE = 0; //eaten tomato

//there are three states that tomatoes can take
enum State {
    StateBeginLife = 1, //eaten
    StateMiddleLife = 2, //green, growing again
    StateEndLife = 3 //mature
};

//structure containing the level of the tomato life
typedef struct Tomato {
    int life;
} Tomato;

const char* TomatoToString(Tomato t);
enum State getLifeState(Tomato t);

#endif //COCCIPUCE_TOMATO_H
