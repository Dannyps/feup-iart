#include "Node.h"

Node::Node(Location pos, uint8_t cost) : position(pos), cost(cost) {
    
}

Node::Node(Location pos, uint8_t cost, std::vector<Node> previousNodes) : position(pos), cost(cost), previousNodes(previousNodes){
    
}