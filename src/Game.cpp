/*
 * Game.cpp
 *
 *  Created on: Mar 23, 2019
 */

#include "Game.h"
using namespace std;

Game::Game(int x, int y, string board) {
	int a = x + y + board.length();
	a++;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

