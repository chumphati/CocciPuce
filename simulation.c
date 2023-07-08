#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "stdbool.h"
#include "simulation.h"
#include "model/puceron.h"
#include "model/coccinelle.h"
#include "ui/manager.h"

//execution of the main functions of the simulation in the order of execution of the guidelines: runs the whole simulation
//the functions fulfil the explicit role of their names
//details of the functions are in comments above each one below
void Simulate(Simulation *sim, Rule rule) {
    UIManager uiManager = {.mode = CUI};
    int i;
    for (i = 1; i <= rule.nbTurnLimit; i++) {
        updateTomatosLife(&sim->pot);

        puceronsMove(rule, sim->pucerons, sim->nbPucerons);
        //second call of the ladybird's orientation to compensate for the delay of the aphids' pursuit: (see report for the explanation of this choice)
        coccinelleOrientation(rule, sim->coccinelles, sim->nbCoccinelles, sim->pucerons, sim->nbPucerons);
        coccinelleMove(rule, sim->coccinelles, sim->nbCoccinelles);

        puceronsEat(&sim->pot, sim->pucerons, sim->nbPucerons);
        puceronsBirth(sim->pucerons, &sim->nbPucerons);
        puceronsDie(sim->pucerons, &sim->nbPucerons);
        puceronsOrientation(rule, sim->pot, sim->pucerons, sim->nbPucerons);

        coccinelleEat(sim->coccinelles, sim->nbCoccinelles, sim->pucerons, &sim->nbPucerons);
        coccinelleBirth(sim->coccinelles, &sim->nbCoccinelles);
        coccinelleDie(sim->coccinelles, &sim->nbCoccinelles);
        coccinelleOrientation(rule, sim->coccinelles, sim->nbCoccinelles, sim->pucerons, sim->nbPucerons);

        showTurnDelimiter(uiManager, i);
        showPotager(uiManager, *sim);

        // used to avoid really long latency when running if a high number of simulation turn is chosen
        usleep(10000);
    }
}

//if the aphid falls on a square with a tomato, even an immature one, it eats it and the life of the tomato drops to its minimum
//takes as input all the aphids, their number and the tomatoes in the potager
//modifies their values using pointers
void puceronsEat(Potager *potager, Puceron *pucerons, int sizePuceron) {
    int i;

    for (i = 0; i < sizePuceron; i++) {
        //if the tomato is at least immature, it is eaten
        if (getLifeState(potager->tomatos[pucerons[i].coord.x][pucerons[i].coord.y]) >= StateMiddleLife) {
            pucerons[i].nbTurnEat ++;
            potager->tomatos[pucerons[i].coord.x][pucerons[i].coord.y].life = TOMATO_MIN_LIFE;
        }

        pucerons[i].life = pucerons[i].life + 1; //the aphid gain one point of life
    }
}

//allows you to create a new aphid and place it randomly around the one that is reproducing
//takes as input all aphids and the number of aphids
//adds a new aphid (with all attributes of the aphid structure) to the array if the reproduction conditions are satisfied
void puceronsBirth(Puceron *pucerons, int *sizePuceron) {
    int i;
    int size = *sizePuceron;
    srand(time(NULL));
    Puceron p = {.nbTurnEat = 0, .isDead = false, .life = 0}; //default attributes of a new aphid

    for (i = 0; i < *sizePuceron; i++) {
        //if the birth condition are ok, create new aphid
        if (PuceronCanGiveBirth(pucerons[i])) {
            pucerons[i].nbTurnEat = 0;

            //choose possible coordinates
            p.coord.x = pucerons[i].coord.x + (rand()%3)-1;
            p.coord.y = pucerons[i].coord.y + (rand()%3)-1;

            if (p.coord.x < 0) {
                p.coord.x = rand()%2; //only 0 or 1
            } else if (p.coord.x > NB_ELEM_POTAGER) {
                p.coord.x = (rand()%2)-1; //only 0 or -1
            }
            if (p.coord.y < 0) {
                p.coord.y = rand()%2; //only 0 or 1
            } else if (p.coord.y > NB_ELEM_POTAGER) {
                p.coord.y = (rand()%2)-1; //only 0 or -1
            }

            //affects a random position
            p.direction = (rand()%DIRECTION_POSSIBLE)+1;

            pucerons[size] = p;

            size=size+1;
        }
    }

    *sizePuceron = size; //update the number of aphids in the table
}

//if the conditions for death are met, the aphid disappears from the table and is replaced by the aphid of the last occupied index of the table
//takes as input all aphids and the number of aphids
void puceronsDie(Puceron *pucerons, int *sizePuceron) {
    int i;
    int size = *sizePuceron;

    for (i = 0; i < size; i++) {
        if (PuceronMustDie(pucerons[i])) {
            pucerons[i].isDead = true;
            pucerons[i].life = 0;
            pucerons[i] = pucerons[size-1];

            i=i-1;
            size=size-1;
        }
    }

    *sizePuceron = size; //update the number of aphids in the table
}

//the aphids move in the direction indicated by the orientation
//takes into account the rules (the bypass wall), all the aphids and the number of aphids
//changes the coordinates in the aphid table
void puceronsMove(Rule rule, Puceron *pucerons, int sizePuceron) {
    int i;
    for (i = 0; i < sizePuceron; i++) {
        //function that makes the aphid move according to the chosen rule
        PuceronMove(&pucerons[i], rule);
    }
}

//takes into account the rule (whether the walls are bypassed), the tomatoes in the garden (the orientation also depends on whether there are tomatoes or not around the aphid), all the aphids in the table and the number of aphids
//this function allows to choose a direction and to update it in the table for each aphid, according to the rules applied and the instructions
void puceronsOrientation(Rule rule, Potager potager, Puceron *pucerons, int sizePuceron) {
    int direction; //direction taken
    int sizeDirectionPossible; //nombre de direction qui sont atteignables (pas de murs bloqués et pas de coccinelles pucerons dessus dans le cas ou un puceron doit aller aléatoirement quelque part
    Coordonnees nextCoord;
    int i,j;
    int randomPosition;
    bool badCoord, bypassLifeTomato;

    // initiate an array if no tomato can be eaten near
    // fill it with direction containing the tomato
    int listDirectionPossible[DIRECTION_POSSIBLE];

    for (i = 0; i < sizePuceron; i++) {
        sizeDirectionPossible = 0;

        direction = pucerons[i].direction;
        bypassLifeTomato = false;

        for (j = 0; j < DIRECTION_POSSIBLE; ++j) {
            // to know if no tomato can be eat near of puceron
            if (j == DIRECTION_POSSIBLE) {
                bypassLifeTomato = true;
            }

            badCoord = false;

            nextCoord = NextCoordFromDirection(direction, pucerons[i].coord);
            // if walls are transparent
            if (rule.bypassWalls) {
                if (nextCoord.y >= NB_ELEM_POTAGER && nextCoord.x >= NB_ELEM_POTAGER) {
                    nextCoord.y = nextCoord.x = 0;
                } else if (nextCoord.y >= NB_ELEM_POTAGER) {
                    nextCoord.y = 0;
                } else if (nextCoord.x >= NB_ELEM_POTAGER) {
                    nextCoord.x = 0;
                } else if (nextCoord.x <= 0) {
                    nextCoord.x = NB_ELEM_POTAGER -1;
                } else if (nextCoord.y <= 0) {
                    nextCoord.y = NB_ELEM_POTAGER -1;
                } else if (nextCoord.y <= 0 && nextCoord.x <= 0) {
                    nextCoord.y = nextCoord.x = NB_ELEM_POTAGER - 1;
                }
            } else {
                // if walls are blocking
                if (
                    nextCoord.x < 0 || nextCoord.y < 0 ||
                    nextCoord.y >= NB_ELEM_POTAGER || nextCoord.x >= NB_ELEM_POTAGER
                ) {
                    badCoord = true;
                }
            }

            // if wall blocks or tomato is not ready to be eat,
            // OR pucerons are at position,
            // choose between other coord
            if (badCoord == true || getLifeState(potager.tomatos[nextCoord.x][nextCoord.y]) < StateMiddleLife ||
                PuceronsIsOnCoord(pucerons, sizePuceron, nextCoord)
                ) {

                // only if no wall blocks
                // if tomato not ready, pull in direction list
                if (badCoord == false) {
                    listDirectionPossible[sizeDirectionPossible] = direction;
                    sizeDirectionPossible++;
                }
                //else change direction and check if possible to move there
                direction = direction + 1;
                if (direction > DIRECTION_POSSIBLE) {
                    direction = MIN_DIRECTION;
                }
                continue;
            }

            break;
        }
        //if no direction with tomato, aphid go to a random position
        if (bypassLifeTomato) {
            srand(time(NULL));
            randomPosition = (rand()%sizeDirectionPossible)+1;
            direction = listDirectionPossible[randomPosition - 1];
        }

        pucerons[i].direction = direction; //update the position in the table
    }
}

//the ladybugs move in the direction indicated by the orientation
//takes into account the rules (the bypass wall), all the ladybugs and the number of ladybugs
//changes the coordinates in the ladybugs table
void coccinelleMove(Rule rule, Coccinelle *coccinelle, int sizeCoccinelles) {
    int i;
    for (i = 0; i < sizeCoccinelles; i++) {
        //function that makes the ladybugs move according to the chosen rule
        CoccinelleMove(&coccinelle[i], rule);
    }
}

//takes as input all ladybirds and aphids and their numbers
//the ladybirds eat the aphids if they are on the same coordinates
//then the aphid dies as in the puceronDie function
void coccinelleEat(Coccinelle *coccinelles, int sizeCoccinelles, Puceron *pucerons, int *sizePuceron) {
    int i, j;
    int sizeFinal = *sizePuceron;
    for (i = 0; i < sizeCoccinelles; i++) {
        for (j = 0; j < *sizePuceron; j++) {
            if (coccinelles[i].coord.x == pucerons[j].coord.x && coccinelles[i].coord.y == pucerons[j].coord.y) {
                coccinelles[i].nbTurnEat = coccinelles[i].nbTurnEat + 1; //ladybugs have eaten once
                pucerons[j].isDead = true; //aphid die
                pucerons[j] = pucerons[sizeFinal-1];
                sizeFinal--;
                break;
            }
        }
        coccinelles[i].life = coccinelles[i].life + 1; //ladybug gain one point of life
        *sizePuceron = sizeFinal; //update the number of aphid
    }
}

//if the reproduction conditions of the ladybird are respected, a new one is created and appears on a position around
//we take as input the ladybirds and their number
//the new ladybirds are added to their table
void coccinelleBirth(Coccinelle *coccinelles, int *sizeCoccinelles) {
    int size = *sizeCoccinelles;
    int i;
    Coccinelle c = {.nbTurnEat = 0, .isDead = false, .life = 0}; //default attributes of a new ladybug

    for (i = 0; i < *sizeCoccinelles; i++) {
        //if the birth condition are ok, create new ladybug
        if (CoccinelleCanGiveBirth(coccinelles[i])) {
            coccinelles[i].nbTurnEat = 0;

            //choose possible coordinates
            c.coord.x = coccinelles[i].coord.x + (rand()%3)-1;
            c.coord.y = coccinelles[i].coord.y + (rand()%3)-1;

            if (c.coord.x < 0) {
                c.coord.x = rand()%2;
            } else if (c.coord.x > NB_ELEM_POTAGER) {
                c.coord.x = (rand()%2)-1;
            }
            if (c.coord.y < 0) {
                c.coord.y = rand()%2;
            } else if (c.coord.y > NB_ELEM_POTAGER) {
                c.coord.y = (rand()%2)-1;
            }

            //affects a random position
            c.direction = (rand()%DIRECTION_POSSIBLE)+1;

            coccinelles[size] = c;

            size=size+1;
        }
    }

    *sizeCoccinelles = size; //update the number of ladybug
}

//as for aphids, if the conditions are respected the ladybird dies and is replaced in the table by the one with the last index
void coccinelleDie(Coccinelle *coccinelles, int *sizeCoccinelles) {
    int size = *sizeCoccinelles;
    int i;

    for (i = 0; i < size; i++) {
        //si les conditions sont atteintes pour la mort
        if (CoccinelleMustDie(coccinelles[i])) {
            coccinelles[i].isDead = true;
            coccinelles[i].life = 0;
            coccinelles[i] = coccinelles[size-1];

            i=i-1;
            size=size-1;
        }
    }

    *sizeCoccinelles = size; //update the number of ladybugs
}

//ladybirds move randomly unless they spot an aphid in their range, in which case they move in their direction
//takes as input the rules (if bypass wall or not), all ladybirds and aphids and their number
//it allows to modify the direction of the ladybirds in their table in order to respect the instructions
void coccinelleOrientation(Rule rule, Coccinelle *coccinelles, int sizeCoccinelles, Puceron *pucerons, int sizePuceron) {
    int direction;
    int sizeDirectionPossible;
    Coordonnees nextCoord;
    Puceron targetPuceron;
    int i, j, randomPosition;
    bool badCoord, hasCocci;

    // initiate an array if no aphid can be eat near.
    int listDirectionPossible[DIRECTION_POSSIBLE];

    for (i = 0; i < sizeCoccinelles; ++i) {
        sizeDirectionPossible = 0;
        direction = coccinelles[i].direction;

        //scan returns only the first aphid found
        targetPuceron = CoccinelleScan(coccinelles[i], pucerons, sizePuceron); //get a targeted aphid or not

        for (j = 0; j < DIRECTION_POSSIBLE; j++) {
            if (!targetPuceron.isDead) { //if aphid is find we search the direct to go in its direction
                targetPuceron.isDead = true; //set is dead to true to say to the function to not repeat the search for aphids
                direction = GetDirectionBetweenCoordonnes(coccinelles[i].coord, targetPuceron.coord); //get the direction to go to the aphid
                j--;
            }

            badCoord = false;
            nextCoord = NextCoordFromDirection(direction, coccinelles[i].coord);

            //if walls are transparent
            if (rule.bypassWalls) {
                if (nextCoord.y >= NB_ELEM_POTAGER && nextCoord.x >= NB_ELEM_POTAGER) {
                    nextCoord.y = nextCoord.x = 0;
                } else if (nextCoord.y >= NB_ELEM_POTAGER) {
                    nextCoord.y = 0;
                } else if (nextCoord.x >= NB_ELEM_POTAGER) {
                    nextCoord.x = 0;
                } else if (nextCoord.x <= 0) {
                    nextCoord.x = NB_ELEM_POTAGER - 1;
                } else if (nextCoord.y <= 0) {
                    nextCoord.y = NB_ELEM_POTAGER - 1;
                } else if (nextCoord.y <= 0 && nextCoord.x <= 0) {
                    nextCoord.y = nextCoord.x = NB_ELEM_POTAGER - 1;
                }
            } else {
                //if walls are blocking
                if (
                    nextCoord.x < 0 || nextCoord.y < 0 ||
                    nextCoord.y >= NB_ELEM_POTAGER || nextCoord.x >= NB_ELEM_POTAGER){
                    badCoord = true;
                }
            }

            hasCocci = CoccinelleIsOnCoord(coccinelles, sizeCoccinelles, nextCoord); //verify if a ladybug is already on the targeted coord
            if (badCoord == false && !hasCocci) {
                listDirectionPossible[sizeDirectionPossible] = direction;
                sizeDirectionPossible++;
            }
            //if wall blocks or there is a ladybug on this coord: choose between other coord
            if (badCoord == true || hasCocci){
                direction = direction + 1;
                if (direction > DIRECTION_POSSIBLE) {
                    direction = MIN_DIRECTION;
                }
                continue;
            }

            break;
        }

        //if no direction with aphids, ladybugs go to a random position
        srand(time(NULL));
        randomPosition = (rand()%sizeDirectionPossible)+1;
        direction = listDirectionPossible[randomPosition - 1];

        coccinelles[i].direction = direction;
    }
}
