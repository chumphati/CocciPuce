#include "manager.h"

//the functions in this file were created with the intention of integrating the gui (graphic)
//due to lack of time only the cui is available here

//used in main.c to call the choices at the beginning in the terminal
Simulation customizeRules() {
    Simulation sim;
    sim = customizeRulesCUI();
    return sim;
}

//used in main.c to call the choices at the beginning in the terminal
void showTurnCoccinelleInvasion(UIManager manager, Simulation sim) {
    if (manager.mode == CUI) {
        showTurnCoccinelleInvasionCUI(sim.pot, sim.pucerons, sim.nbPucerons, sim.coccinelles, sim.nbCoccinelles);
    }
}

//used in main.c to display of the initialization of aphids
void showTurnPuceronInvasion(UIManager manager, Simulation sim) {
    if (manager.mode == CUI) {
        showTurnPuceronInvasionCUI(sim.pot, sim.pucerons, sim.nbPucerons);
    }
}

//used in main.c to display of the initialization of the empty matrix with the tomato
void showInitialTurn(UIManager manager, Simulation sim) {
    if (manager.mode == CUI) {
        showInitialTurnCUI(sim.pot);
    }
}

//used in main.c to show the delimitation to recognise the turns in the terminal
void showTurnDelimiter(UIManager manager, int nbTurn) {
    if (manager.mode == CUI) {
        showTurnDelimiterCUI(nbTurn);
    }
}

//used in main.c to show the potager in terminal with the tomato, aphids and ladybugs
void showPotager(UIManager manager, Simulation sim) {
    if (manager.mode == CUI) {
        showPotagerCUI(sim.pot, sim.pucerons, sim.nbPucerons, sim.coccinelles, sim.nbCoccinelles);
    }
}