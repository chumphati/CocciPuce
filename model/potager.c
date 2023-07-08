#include "potager.h"

//update the life of the tomatoes for the round: they mature to their maximum of 1 per round
void updateTomatosLife(Potager *potager) {
    int i, j, tmpLife;
    Tomato t;

    for (i=0; i<NB_ELEM_POTAGER; i++){
        for (j=0; j<NB_ELEM_POTAGER; j++){
            tmpLife = potager->tomatos[i][j].life;

            t.life = tmpLife + 1;
            if (t.life > TOMATO_MAX_LIFE) {
                t.life = TOMATO_MAX_LIFE;
            }

            potager->tomatos[i][j] = t; //update in matrix
        }
    }
}
