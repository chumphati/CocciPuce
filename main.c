#include "rule.h"
#include "initialization.h"
#include "simulation.h"
#include "ui/manager.h"
#include <unistd.h>

int main() {
    int defaultUI = CUI; //cui only implemented : display by default
    srand(time(NULL));

    //choose the display mode
    //because of a lack of time, the GUI mode is not implemented : only CUI can be displayed
    UIManager uiManager = {.mode = defaultUI};
    if (uiManager.mode == GUI) {
        printf("Error: sorry, gui mode are not yet implemented\n");
        exit(1);
    }

    //Choose the parameters for launching the simulation (by default with the parameters specified in the project)
    // The modifiable parameters are: the number of aphids and ladybirds, if the walls are transparent, if the ladybirds are added or not
    Simulation sim = customizeRules();

    //initialisation of the matrix (display it)
    sim.pot = initTomatosPotager(NB_ELEM_POTAGER);
    //display the potager without aphids and ladybirds
    showInitialTurn(uiManager, sim);

    //aphid initiation with size of the matrix because aphid number can be higher than original number.
    initPucerons(&sim.pot, sim.pucerons, sim.nbPucerons, sim.rules);
    //displaying the potager with aphids
    showTurnPuceronInvasion(uiManager, sim);

    //include ladybirds if the simulation level is 2
    if (sim.levelSimulation == LevelSimulationTwo) {
        initCoccinelles(sim.coccinelles, sim.nbCoccinelles, sim.pucerons, sim.nbPucerons, sim.rules);
        showTurnCoccinelleInvasion(uiManager, sim);
    }

    // pass rules, to avoid undefinable error of death which override the rule from simulation.
    Simulate(&sim, sim.rules);

    return 0;
}