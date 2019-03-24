#include <iostream>
#include <string>
#include <functional>
#include "types.h"

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game(unsigned int x, unsigned int y, std::string board, Location initialState, Location target, std::function<double(Location, Location)> heuristic);
	virtual ~Game();
	int a;
private:
	Location state;
	Location target;
	std::function<double(Location, Location)> heuristic;
};

#endif /* GAME_H_ */
