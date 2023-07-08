#include "rule.h"

//return if a direction is possible according to the animal position
//depends on the rule chosen (bypass wall or not)
bool SpawnDirectionIsPossible(Rule rule, Coordonnees coord, enum Direction direction) {
    if (rule.bypassWalls) {
        return true;
    }

    if ( coord.x < 0 || coord.y < 0 ||
        coord.y >= NB_ELEM_POTAGER || coord.x >= NB_ELEM_POTAGER
        ){
        return false;
    }

    if (coord.x == (NB_ELEM_POTAGER - 1) && (direction == East || direction == North_east || direction == South_east)) {
        return false;
    }

    if (coord.x == 0 && (direction == West || direction == North_west || direction == South_west)) {
        return false;
    }

    if (coord.y == (NB_ELEM_POTAGER - 1) && (direction == North || direction == North_west || direction == South_west)) {
        return false;
    }

    if (coord.y == 0 && (direction == South || direction == South_west || direction == South_east)) {
        return false;
    }


    return true;
}
