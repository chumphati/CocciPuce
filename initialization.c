#include <stdlib.h>
#include "initialization.h"
#include "model/potager.h"
#include "model/puceron.h"

//initialize the potager with the size of the constant defined in rule and put the mature tomatoes in each box
Potager initTomatosPotager(int NB_ELEM_POTAGER) {
    Potager potager;
    int i, j;
    Tomato t;

    for (i=0; i<NB_ELEM_POTAGER; i++){
        for (j=0; j<NB_ELEM_POTAGER; j++){
            t.life = TOMATO_MAX_LIFE;
            potager.tomatos[i][j] = t;
        }
    }

    return potager;
}

//random placement of the first aphids in the matrix, each one must be on a separate space
//affects the basic values of the aphids (coordinates, direction without it leaving the matrix, its life points, its number of turns having eaten)
void initPucerons(Potager *potager, Puceron listPucerons[], int nbPucerons, Rule rule) {
    Puceron puce;
    Coordonnees coord;
    int randomDir;
    int i;

    for (i = 0; i < nbPucerons; i++) {
         do {
             coord.x = (rand()%NB_ELEM_POTAGER)+1;
             coord.y = (rand()%NB_ELEM_POTAGER)+1;

             randomDir = (rand()%DIRECTION_POSSIBLE)+1;
        } while (
                !SpawnDirectionIsPossible(rule, coord, randomDir) ||
                PuceronsIsOnCoord(listPucerons, i, coord)
                );

        // do -1 because index begin to 0
        puce.coord.x = coord.x -1;
        puce.coord.y = coord.y -1;
        puce.direction = randomDir;

        puce.nbTurnEat = 0; //they have not eat
        puce.isDead = false; //they are alive
        puce.life = 0; //life initialize to 0

        listPucerons[i] = puce; //affects the information of each aphid in the table

        potager->tomatos[puce.coord.x][puce.coord.y].life = TOMATO_MIN_LIFE; //aphids eat the tomato
    }
}

//same fonction as initPuceron but for the ladybugs
//the difference is that they don't eat the tomatos & can't be initialize where there is an aphid
void initCoccinelles(Coccinelle listCocci[], int nbCocci, Puceron listPuceron[], int nbPuceron, Rule rule) {
    Coccinelle cocci;
    Coordonnees coord;
    int randomDir;
    int i;

    for (i = 0; i < nbCocci; i++) {
        do {
            coord.x = (rand()%NB_ELEM_POTAGER)+1;
            coord.y = (rand()%NB_ELEM_POTAGER)+1;

            randomDir = (rand()%DIRECTION_POSSIBLE)+1;
        } while (
                !SpawnDirectionIsPossible(rule, coord, randomDir) ||
                //ladybugs can't be on a position with another ladybug
                CoccinelleIsOnCoord(listCocci, i, coord) ||
                //ladybugs can't be on a position with an aphid
                PuceronsIsOnCoord(listPuceron, nbPuceron, coord)
                );

        // do -1 because index begin to 0
        cocci.coord.x = coord.x -1;
        cocci.coord.y = coord.y -1;
        cocci.direction = randomDir;

        cocci.nbTurnEat = 0;
        cocci.isDead = false;
        cocci.life = 0;

        listCocci[i] = cocci;
    }
}
