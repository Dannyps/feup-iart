#include <iostream>
#include "types.h"
#include "heuristics.h"

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
	return 0;
}

