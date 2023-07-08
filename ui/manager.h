#ifndef COCCIPUCE_MANAGER_H
#define COCCIPUCE_MANAGER_H

#include "../simulation.h"
#include "cui.h"

//was intended to differentiate between cui and gui
enum ModeUI {
    CUI=1, // ui Console
    GUI=2, // ui Graphic
};

//define what manager to use (gui not available)
typedef struct UIManager {
    enum ModeUI mode;
} UIManager;

Simulation customizeRules();
void showTurnCoccinelleInvasion(UIManager manager, Simulation sim);
void showTurnPuceronInvasion(UIManager manager, Simulation sim);
void showInitialTurn(UIManager manager, Simulation sim);
void showTurnDelimiter(UIManager manager, int nbTurn);
void showPotager(UIManager manager, Simulation sim);

#endif //COCCIPUCE_MANAGER_H
