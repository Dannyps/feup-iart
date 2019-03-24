#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "types.h"
#include "Node.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game(std::string mapBlueprint, Location initialState, Location target, std::function<uint32_t(Location, Location)> heuristic);
	virtual ~Game();
private:
	std::vector<std::vector<MapItem>> map;
	Location state;
	Location target;
	std::function<uint32_t(Location, Location)> heuristic;

	void readMap(std::string mapBlueprint);
	std::vector<Node> getChildren();
};

#endif /* GAME_H_ */
