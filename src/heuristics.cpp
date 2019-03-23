#include "heuristics.h"

double heuristicDiagonalDistance(Location state, Location target) {
    return sqrt(pow(state.x-target.x,2)+pow(state.y-target.y,2));
}