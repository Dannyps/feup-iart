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
    int x = 0;
    int y = 0;

    Location(int x, int y) : x(x), y(y) {}

    Location(int x, int y, char i) : x(x), y(y), item((MapItem)i) {}

    bool operator==(Location rhs) {
        return (this->x == rhs.x) && (this->y == rhs.y);
    }

    bool operator!=(Location rhs) {
        return !(*this == rhs);
    }

    std::string toString() {
        return std::string("(" + std::to_string(+x) + "," + std::to_string(+y) + ") -> " + (char)item);
    }

    Location *left = NULL;
    Location *right = NULL;
    Location *up = NULL;
    Location *down = NULL;
    MapItem item;
};

enum Direction {
    right = 0,
    left = 1,
    up = 2,
    down = 3
};

#endif  //LABYRINTHROBOTS_TYPES_H