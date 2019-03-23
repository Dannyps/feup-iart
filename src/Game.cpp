/*
 * Game.cpp
 *
 *  Created on: Mar 23, 2019
 */

#include "Game.h"
using namespace std;

Game::Game(unsigned int x, unsigned int y, string board) {
	a = 0;
	if (board.length() != x * y) {
		string err= "Board string has " + to_string(board.length()) + " characters, expected " + to_string(x) + "*" + to_string(y) + "=" + to_string(x*y) + ".";
		throw runtime_error(err);
	}
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}
