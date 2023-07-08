#ifndef COCCIPUCE_INITIALIZATION_H
#define COCCIPUCE_INITIALIZATION_H

#include "model/tomato.h"
#include "rule.h"
#include "model/potager.h"
#include "model/puceron.h"
#include "model/coccinelle.h"

Potager initTomatosPotager(int NB_ELEM_POTAGER);
void initPucerons(Potager* potager, Puceron listPucerons[], int nbPucerons, Rule rule);
void initCoccinelles(Coccinelle listCocci[], int nbCoccinelles, Puceron listPuceron[], int nbPuceron, Rule rule);

#endif //COCCIPUCE_INITIALIZATION_H
