#include <iostream>
#include "types.h"

class Node {
public:
    Node(Location pos, uint8_t cost);
    Location position;
    uint8_t cost = 0;
};