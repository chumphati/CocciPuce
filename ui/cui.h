#ifndef COCCIPUCE_CUI_H
#define COCCIPUCE_CUI_H

#include "../model/puceron.h"
#include "../model/tomato.h"
#include "../rule.h"
#include "../model/potager.h"
#include "../model/coccinelle.h"
#include "../simulation.h"
#include "../rule.h"

Simulation customizeRulesCUI();
void showTurnCoccinelleInvasionCUI(Potager potager, Puceron pucerons[], int sizePuceron, Coccinelle coccinelles[], int sizeCoccinelle);
void showTurnPuceronInvasionCUI(Potager potager, Puceron pucerons[], int sizePuceron);
void showInitialTurnCUI(Potager pot);
void showTurnDelimiterCUI(int nbTurn);
void showPotagerCUI(Potager potager, Puceron pucerons[], int sizePuceron, Coccinelle coccinelles[], int sizeCoccinelle);

#endif //COCCIPUCE_CUI_H