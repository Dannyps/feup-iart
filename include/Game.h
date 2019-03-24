#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include "types.h"
#include "Node.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game(std::string mapBlueprint, std::function<uint32_t(Location, Location)> heuristic);
	virtual ~Game();
private:
	std::vector<std::vector<MapItem>> map;
	std::function<uint32_t(Location, Location)> heuristic;

	void readMap(std::string mapBlueprint);
	std::vector<Node> getChildren(Node node);
	Location getInitialPosition();
};

#endif /* GAME_H_ */
