#include <iostream>
#include <vector>
#include "types.h"

class Node {
public:
    Location position;
    uint8_t cost = 0;
    std::vector<Node> previousNodes;
    
    Node(Location pos, uint8_t cost);
    Node(Location pos, uint8_t cost, std::vector<Node> previousNodes);
};