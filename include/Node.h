#include <iostream>
#include "types.h"

class Node {
public:
    Node(Location pos);
private:
    Location position;
    uint8_t cost = 0;
};