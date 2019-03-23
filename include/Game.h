/*
 * Game.h
 *
 *  Created on: Mar 23, 2019
 */

#include <iostream>
#include <string>

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	Game(unsigned int x, unsigned int y, std::string board);
	virtual ~Game();
	int a;
};

#endif /* GAME_H_ */
