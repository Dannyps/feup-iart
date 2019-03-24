#include <iostream>
#include "types.h"
#include "heuristics.h"
#include "Game.h"

int main(int argc, char *argv[]) {
	if (argc < 1){
		std::cout << "Give a map file" << std::endl;
		return -1;
	}

	Location initialPosition = {
			0,	// x
			0,	// y
	};

	Location target = {
			55,	// x
			6,	// y
	};

	try {
		Game game(argv[0], initialPosition, target, heuristicDiagonalDistance);
	} catch (std::exception *e) {
		std::cout << e->what();
	}

	return 0;
}

