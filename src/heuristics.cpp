#include "heuristics.h"

uint32_t heuristicDiagonalDistance(Location state, Location target) {
    return sqrt(pow(state.x-target.x,2)+pow(state.y-target.y,2));
}

uint32_t heuristicZero(Location state, Location target) {
    return 0;
}