#ifndef COCCIPUCE_DIRECTION_H
#define COCCIPUCE_DIRECTION_H

//all possible directions
enum Direction {
    North=1,
    South=2,
    East=3,
    West=4,
    North_west=5,
    North_east=6,
    South_east=7,
    South_west=8,
};

static const int DIRECTION_POSSIBLE = 8; //number of possible directions
static const int MIN_DIRECTION = 1; //value of the min direction

Coordonnees NextCoordFromDirection(enum Direction direction, Coordonnees c);
enum Direction GetDirectionBetweenCoordonnes(Coordonnees origin, Coordonnees target);
#endif //COCCIPUCE_DIRECTION_H
