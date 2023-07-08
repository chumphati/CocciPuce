#ifndef COCCIPUCE_SIMULATION_H
#define COCCIPUCE_SIMULATION_H

#include "rule.h"
#include "model/potager.h"
#include "model/puceron.h"
#include "model/coccinelle.h"

//level of simulation : with or without ladybugs
enum LevelSimulation {
    LevelSimulationOne=1, // without ladybugs
    LevelSimulationTwo=2, // with ladybugs
};

//instructions for the simulation: rules, simulation level, tables of aphids and ladybirds, number of aphids and ladybirds
//selected or default parameters needed for the above functions
typedef struct Simulation {
    Rule rules;
    enum LevelSimulation levelSimulation;
    Potager pot;
    Puceron pucerons[NB_ELEM_POTAGER*NB_ELEM_POTAGER];
    int nbPucerons;
    Coccinelle coccinelles[NB_ELEM_POTAGER*NB_ELEM_POTAGER];
    int nbCoccinelles;
} Simulation;

void Simulate(Simulation *sim, Rule rule);

void puceronsMove(Rule rule, Puceron *pucerons, int sizePuceron);
void puceronsEat(Potager *potager, Puceron *pucerons, int sizePuceron);
void puceronsBirth(Puceron *pucerons, int *sizePuceron);
void puceronsDie(Puceron *pucerons, int *sizePuceron);
void puceronsOrientation(Rule rule, Potager potager, Puceron *pucerons, int sizePuceron);

void coccinelleMove(Rule rule, Coccinelle *coccinelles, int sizeCoccinelles);
void coccinelleEat(Coccinelle *coccinelles, int sizeCoccinelles, Puceron *pucerons, int *sizePuceron);
void coccinelleBirth(Coccinelle *coccinelles, int *sizeCoccinelles);
void coccinelleDie(Coccinelle *coccinelles, int *sizeCoccinelles);
void coccinelleOrientation(Rule rule, Coccinelle *coccinelles, int sizeCoccinelles, Puceron *puceron, int sizePuceron);

#endif //COCCIPUCE_SIMULATION_H
