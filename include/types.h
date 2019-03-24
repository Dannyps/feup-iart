#ifndef LABYRINTHROBOTS_TYPES_H
#define LABYRINTHROBOTS_TYPES_H

#include <iostream>

struct Location {
    uint8_t x = 0;
    uint8_t y = 0;

    Location(uint8_t x, uint8_t y){
        this->x = x;
        this->y = y;
    }

    bool operator== (Location rhs){
        return (this->x == rhs.x) && (this->y == rhs.y);
    }

    bool operator!= (Location rhs){
        return !(*this==rhs);
    }
};

enum Direction{
    right = 0,
    left = 1,
    up = 2,
    down = 3
};

enum MapItem{
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