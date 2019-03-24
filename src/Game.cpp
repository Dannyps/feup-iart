#include "Game.h"

using namespace std;

Game::Game(unsigned int x, unsigned int y, string board, Location initialState, Location target, std::function<double(Location, Location)> heuristic) :
			state(initialState), target(target), heuristic(heuristic){
	a = 0;
	if (board.length() != x * y) {
		string err= "Board string has " + to_string(board.length()) + " characters, expected " + to_string(x) + "*" + to_string(y) + "=" + to_string(x*y) + ".";
		throw runtime_error(err);
	}
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}
