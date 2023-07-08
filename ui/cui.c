#include <stdio.h>

#include "cui.h"

const char NoCustomRules = 'N'; //choose no (scanf)
const char CustomRules   = 'Y'; //choose yes (scanf)

//allows the user to make the variable and simulation choices at the beginning in the console
Simulation customizeRulesCUI() {
    Simulation sim;
    Rule rule;
    char inputCustomRules, inputBypassWall;
    char inputLevelSimulation[1];
    char inputNbLadybug[3], inputNbAhpid[3], nbTurnSimulation[4];
    long valueLevelSimulation, valueNbAphid, valueNbLadybug, valueNbTurn;

    printf("\033[0;32mChoose the Simulation level\n");
    printf("\t Level : \n");
    printf("\033[0m");

    printf("\t(1) or (2): ");
    scanf("%s", inputLevelSimulation);

    valueLevelSimulation = strtol(inputLevelSimulation, NULL, 10);

    if (valueLevelSimulation != LevelSimulationOne && valueLevelSimulation != LevelSimulationTwo) {
        printf("\033[0;31mError: Accepted values are 1 or 2 ! Input : %ld", valueLevelSimulation);
        printf("\033[0m");
        exit(1);
    }
    sim.levelSimulation = valueLevelSimulation;

    printf("\033[0;32mSimulation turns\n");
    printf("\t Choose the number of simulation rounds you want : \n");
    printf("\033[0m");

    printf("\t(> 1) and (< 999) : ");
    scanf("%s", nbTurnSimulation);
    valueNbTurn = strtol(nbTurnSimulation, NULL, 10);
    rule.nbTurnLimit = (int) valueNbTurn;
    if (valueNbTurn < 1 || valueNbTurn > 3900) {
        printf("\033[0;31mError: Accepted values are between 1 and 999 ! Input: %s", nbTurnSimulation);
        printf("\033[0m");
        exit(1);
    }

    printf("\033[0;32mWould you like to customize the rules and the number of ladybug/aphid spawned at the beginning?\n");
    printf("If No, the default values will be applied (e.g. the project file : 20 aphids, 10 ladybirds if Level = 2 (0 otherwise), bypass walls = false)\n");
    printf("\033[0m");
    printf("\t(Y)es or (N)o : ");
    scanf(" %c", &inputCustomRules);

    printf("\n\n");
    if (inputCustomRules != NoCustomRules && inputCustomRules != CustomRules) {
        printf("\033[0;31mError: Accepted values are Y or N ! Input : %c", inputCustomRules);
        printf("\033[0m");
        exit(1);
    }

    //defaults values = those of the instructions
    if (inputCustomRules == NoCustomRules) {
        printf("\033[0;34m");

        rule.bypassWalls = false;
        sim.rules = rule;
        sim.nbPucerons = 20;
        sim.nbCoccinelles = 0;
        if (sim.levelSimulation == LevelSimulationTwo) {
            sim.nbCoccinelles = 10;
        }

        printf("Default values are chosen :\n");
        printf("\tLevel : %d\n", sim.levelSimulation);
        printf("\tBypass wall : false\n");
        printf("\tNumber aphid : %d\n", sim.nbPucerons);
        printf("\tNumber ladybug : %d\n", sim.nbCoccinelles);
        printf("\033[0m");

    } else {
        printf("\033[0;34m");
        printf("Choose different values for the simulation:\n");
        printf("You must set the values of :\n");

        printf("\033[0;34m");
        printf("\t Bypass Wall : \n");
        printf("\033[0m");

        printf("\t(Y)es or (N)o : ");
        scanf(" %c", &inputBypassWall);

        if (inputBypassWall != 'Y' && inputBypassWall != 'N') {
            printf("\033[0;31mError: Accepted values are Y or N ! Input: %c", inputBypassWall);
            printf("\033[0m");
            exit(1);
        }

        //by default, it's false
        rule.bypassWalls = false;
        if (inputBypassWall == 'Y') {
            rule.bypassWalls = true;
        }

        printf("\033[0;34m");
        printf("\t Number of Aphid : \n");
        printf("\033[0m");
        printf("\tBetween 1 and 900: ");
        scanf("%s", inputNbAhpid);
        valueNbAphid = strtol(inputNbAhpid, NULL, 10);
        if (valueNbAphid < 1 || valueNbAphid > 900) {
            printf("\033[0;31mError: Accepted values are 1 and 900 ! Input: %s", inputNbAhpid);
            printf("\033[0m");
            exit(1);
        }
        sim.nbPucerons = (int) valueNbAphid;

        sim.nbCoccinelles = 0;
        if (sim.levelSimulation == LevelSimulationTwo) {
            printf("\033[0;34m");
            printf("\t Number of Laydbug : \n");
            printf("\033[0m");
            printf("\tBetween 1 and 900: ");
            scanf("%s", inputNbLadybug);
            valueNbLadybug = strtol(inputNbLadybug, NULL, 10);
            if (valueNbLadybug < 1 || valueNbLadybug > 900) {
                printf("\033[0;31mError: Accepted values are between 1 and 900 ! Input: %s", inputNbLadybug);
                printf("\033[0m");
                exit(1);
            }
            sim.nbCoccinelles = (int) valueNbLadybug;
        }


        sim.rules = rule;
    }

    return sim; //the rules are returned via the simulation type to execute the simulation
}

//display of the initialization of ladybirds: displays the matrix with the ladybirds and the aphids
void showTurnCoccinelleInvasionCUI(Potager pot, Puceron pucerons[], int nbPucerons, Coccinelle cocci[], int nbCocci) {
    printf("##############################################################\n");
    printf("################## COCCINELLE INVASION TURN ##################\n");
    printf("##############################################################\n");
    showPotagerCUI(pot, pucerons, nbPucerons, cocci, nbCocci);
}

//display of the initialization of aphids: displays the matrix with the aphids
void showTurnPuceronInvasionCUI(Potager pot, Puceron pucerons[], int nbPucerons) {
    printf("##############################################################\n");
    printf("################### PUCERONS INVASION TURN ###################\n");
    printf("##############################################################\n");
    showPotagerCUI(pot, pucerons, nbPucerons, 0, 0);
}

//display of the initialization of the empty matrix with the tomatos
void showInitialTurnCUI(Potager pot) {
    printf("##############################################################\n");
    printf("################### INITIAL TURN #############################\n");
    printf("##############################################################\n");
    showPotagerCUI(pot, 0, 0, 0, 0);
}

//delimitation to recognise the turns in the terminal
void showTurnDelimiterCUI(int nbTurn) {
    printf("##############################################################\n");
    printf("########################### TURN %2d ##########################\n", nbTurn);
    printf("##############################################################\n");
}

// show the potager in terminal with the tomato, aphids and ladybugs
//input : potager, aphids, ladybugs & their number
void showPotagerCUI(Potager potager, Puceron pucerons[], int sizePuceron, Coccinelle coccinelles[], int sizeCoccinelle){
    int i, j, k;
    char *colorTomato;
    Puceron p;
    Coccinelle c;

    // top limit
    printf("x\n");

    printf("   +");
    for (j=0; j<NB_ELEM_POTAGER; j++){
        printf("---");
    }
    printf("+");

    printf("\n");
    for (i=NB_ELEM_POTAGER-1; i>=0; i--){
        //index x
        printf("\033[0;31m%2d\033[0m | ", i); //print coord
        for (j=0; j<NB_ELEM_POTAGER; j++){

            //workaround because cannot way to reset as null strict
            p.isDead = true;
            c.isDead = true;
            for (k = 0; k < sizePuceron; k++) {
                if (pucerons[k].coord.x == i && pucerons[k].coord.y == j ) {
                    p = pucerons[k];

                    break;
                }
            }
            for (k = 0; k < sizeCoccinelle; k++) {
                if (coccinelles[k].coord.x == i && coccinelles[k].coord.y == j ) {
                    c = coccinelles[k];

                    break;
                }
            }

            colorTomato = "[0m"; //default = no color
            if (getLifeState(potager.tomatos[i][j]) == StateMiddleLife) {
                colorTomato = "[0;36m"; //cyan
            } else if (getLifeState(potager.tomatos[i][j]) == StateEndLife) {
                colorTomato = "[0;33m"; //orange
            }

            //display aphid/ladybug
            //if there is an aphid
            if (p.isDead == false) {
                printf("\033%s%s\033[0;32m%s\033[0m",colorTomato, TomatoToString(potager.tomatos[i][j]), PuceronToString(p));
            } else if (c.isDead == false) {
                //if there is an ladybug
                printf("\033%s%s\033[0;31m%s\033[0m",colorTomato, TomatoToString(potager.tomatos[i][j]), CoccinelleToString(c));
            } else {
                //else = no aphid/ladybug
                printf("\033%s%-2s\033[0m",colorTomato, TomatoToString(potager.tomatos[i][j]));
            }


            if (j != NB_ELEM_POTAGER -1) {
                printf(" ");
            }
        }
        printf("|\n"); //delimitations
    }

    // bottom limit
    printf("   +");
    for (j=0; j<NB_ELEM_POTAGER; j++){
        printf("---"); //delimitations
    }
    printf("+");

    // index y
    printf("    \n");
    printf("     ");
    for (j=0; j<NB_ELEM_POTAGER; j++){
        printf("\033[0;31m%-3d\033[0m",j); //print coord

    }
    printf(" y");
    printf("\n");
}
