#include <iostream>
#include "types.h"
#include "heuristics.h"
#include "Game.h"

int main(int argc, char *argv[]) {
	if (argc < 2){
		std::cout << "Give a map file" << std::endl;
		return -1;
	}

	try {
		Game game(argv[1], heuristicDiagonalDistance);
	} catch (std::exception *e) {
		std::cout << e->what();
	}
	return 0;
}

