#include "heuristics.h"

uint32_t heuristicDiagonalDistance(Location state, Location target) {
    return sqrt(pow(state.x-target.x,2)+pow(state.y-target.y,2));
}

uint32_t heuristicManhattanDistance(Location state, Location target) {
    return pow(state.x-target.x,2)+pow(state.y-target.y,2);
}

uint32_t heuristicZero(__attribute__ ((unused)) Location state, __attribute__ ((unused)) Location target) {
    return 0;
}