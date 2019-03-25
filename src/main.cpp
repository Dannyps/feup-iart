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
		game.printBoard();
		std::vector<Location> sol = game.findSolution();
		for(Location p : sol){
			std::cout << p.toString() << std::endl;
		}

	} catch (std::exception *e) {
		std::cout << e->what();
	}
	return 0;
}

