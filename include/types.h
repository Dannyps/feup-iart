#ifndef LABYRINTHROBOTS_TYPES_H
#define LABYRINTHROBOTS_TYPES_H

#include <iostream>
#include <string>


enum MapItem {
    robot1 = 'a',
    robot2 = 'b',
    robot3 = 'c',
    robot4 = 'd',
    robot5 = 'e',
    wall = 'x',
    empty = 'y',
    target1 = '1',
    target2 = '2',
    target3 = '3',
    target4 = '4',
    target5 = '5',
};

struct Location;
struct Location {
    uint8_t x = 0;
    uint8_t y = 0;

    Location();
    Location(uint8_t x, uint8_t y) {
        this->x = x;
        this->y = y;
    }

    Location(uint8_t x, uint8_t y, char i) {
        Location(x, y);
        this->item = (MapItem) i;
    }

    bool operator==(Location rhs) {
        return (this->x == rhs.x) && (this->y == rhs.y);
    }

    bool operator!=(Location rhs) {
        return !(*this == rhs);
    }

    std::string toString() {
        return std::string("(" + std::to_string(x) + "," + std::to_string(y) + ")");
    }

    public:
        Location *left;
        Location *right;
        Location *up;
        Location *down;
        MapItem item;
};

enum Direction {
    right = 0,
    left = 1,
    up = 2,
    down = 3
};

#endif  //LABYRINTHROBOTS_TYPES_H