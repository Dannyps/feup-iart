#include <iostream>
#include "types.h"
#include "heuristics.h"
#include "Game.h"

int main() {
	Location initialPosition = {
			0,	// x
			0,	// y
	};

	Location target = {
			55,	// x
			6,	// y
	};

	try {
		Game *g = new Game(1,3,"123", initialPosition, target, heuristicDiagonalDistance);
		g->a++;
	} catch (std::exception *e) {
		std::cout << e->what();
	}

	return 0;
}

