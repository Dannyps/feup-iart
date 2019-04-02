#include <iostream>
#include <vector>
#include "types.h"

class Node {
public:
    Location position;
    uint32_t cost = 1;
    std::vector<Node> previousNodes;
    
    Node(Location &pos, uint32_t cost);
    Node(Location &pos, uint32_t cost, std::vector<Node> previousNodes);
};