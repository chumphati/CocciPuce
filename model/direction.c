#include "coordonnee.h"
#include "direction.h"

//allows the change of coordinate (shift of 1) according to a direction
//returns the value of a new coordinate
Coordonnees NextCoordFromDirection(enum Direction direction, Coordonnees c) {
    Coordonnees newCoord = c;

    switch (direction) {
        case North:
            newCoord.x = c.x + 1;
            break;
        case South:
            newCoord.x = c.x - 1;
            break;
        case East:
            newCoord.y = c.y + 1;
            break;
        case West:
            newCoord.y = c.y - 1;
            break;
        case North_west:
            newCoord.y = c.y - 1;
            newCoord.x = c.x + 1;
            break;
        case North_east:
            newCoord.y = c.y + 1;
            newCoord.x = c.x + 1;
            break;
        case South_east:
            newCoord.y = c.y + 1;
            newCoord.x = c.x - 1;
            break;
        case South_west:
            newCoord.x = c.x - 1;
            newCoord.y = c.y - 1;
            break;
    }

    return newCoord;
}

//determines the direction in which an entity should move in order to reach a target based on their coordinates
enum Direction GetDirectionBetweenCoordonnes(Coordonnees origin, Coordonnees target) {
    enum Direction dir;

    if (origin.x == target.x) {
        if (origin.y > target.y) {
            dir = West;
        } else {
            dir = East;
        }
    }
    if (origin.y == target.y) {
        if (origin.x > target.x) {
            dir = South;
        } else {
            dir = North;
        }
    }

    if (origin.y > target.y && origin.x > target.x) {
        dir = South_west;
    }
    if (origin.y > target.y && origin.x < target.x) {
        dir = North_west;
    }
    if (origin.y < target.y && origin.x > target.x) {
        dir = South_east;
    }
    if (origin.y < target.y && origin.x < target.x) {
        dir = North_east;
    }

    return dir; //return the direction
}
