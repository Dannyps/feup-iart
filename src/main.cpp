#include <iostream>
#include "types.h"
#include "heuristics.h"
#include "Game.h"

int main() {
	Location state = {
			0,	// x
			0,	// y
	};

	Location target = {
			55,	// x
			6,	// y
	};

	std::cout << "This close to the target: " << heuristicDiagonalDistance(state, target) << std::endl;

	try {
		Game *g = new Game(4,5,"123");
		g->a++;
	} catch (std::exception *e) {
		std::cout << e->what();
	}

	return 0;
}

