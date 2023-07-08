#ifndef COCCIPUCE_POTAGER_H
#define COCCIPUCE_POTAGER_H

#include "tomato.h"
#include "../rule.h"

//type potager which groups the tomatoes and their life on the whole matrix
typedef struct Potager {
    Tomato tomatos[NB_ELEM_POTAGER][NB_ELEM_POTAGER];
} Potager;

void updateTomatosLife(Potager *potager);
#endif //COCCIPUCE_POTAGER_H
