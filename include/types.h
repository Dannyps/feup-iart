#ifndef LABYRINTHROBOTS_TYPES_H
#define LABYRINTHROBOTS_TYPES_H

#include <iostream>

typedef struct {
    uint8_t x = 0;
    uint8_t y = 0;
} Location;

enum class Direction{
    right,
    left,
    up,
    down
};

enum class MapItems{
    r1 = 'a',
    r2 = 'b',
    r3 = 'c',
    r4 = 'd',
    r5 = 'e',
    wall = 'x',
    empty = 'y',
    target = 'z'
};

#endif //LABYRINTHROBOTS_TYPES_H