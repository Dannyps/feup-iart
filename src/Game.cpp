#include "Game.h"

Game::Game(std::string mapBlueprint, Location initialState, Location target, std::function<uint32_t(Location, Location)> heuristic) : state(initialState), target(target), heuristic(heuristic){
	readMap(mapBlueprint);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

std::vector<Node> Game::getChildren(){
	std::vector<Node> children;

	return children;
}

void Game::readMap(std::string mapBlueprint){
	std::cout << "reading map: " << mapBlueprint << std::endl;
	// in the end
	if (map.size()==0){
		throw std::invalid_argument("The map provided is empty");
	}
}
