#include "heuristics.h"

uint32_t heuristicDiagonalDistance(Location state, Location target) {
    return pow(state.x-target.x,2)+pow(state.y-target.y,2);
}
