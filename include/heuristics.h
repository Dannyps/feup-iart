#ifndef LABYRINTHROBOTS_HEURISTICS_H
#define LABYRINTHROBOTS_HEURISTICS_H

#include <cmath>
#include "types.h"

uint32_t heuristicDiagonalDistance(Location state, Location target);
uint32_t heuristicZero(Location state, Location target);
uint32_t heuristicManhattanDistance(Location state, Location target);
#endif