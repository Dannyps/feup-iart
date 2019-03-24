#include "Game.h"

Game::Game(std::string mapBlueprint, std::function<uint32_t(Location, Location)> heuristic) : heuristic(heuristic){
	readMap(mapBlueprint);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::readMap(std::string mapBlueprint){
	std::ifstream file(mapBlueprint);

	if(!file.is_open()){
		throw std::invalid_argument("The map file provided doesn't exist");
	}

	std::string line;
	for(uint8_t i = 0; getline(file, line); i++){
		std::vector<MapItem> mapRow;
		for(char item : line){
			mapRow.push_back((MapItem)item);
		}
		map.push_back(mapRow);
	}

	file.close();

	if (map.size()==0){
		throw std::invalid_argument("The map provided is empty");
	}
}

std::vector<Node> Game::getChildren(Node parentNode){
	std::vector<Node> children;

	for (int direction = 0; direction < 4 ; direction++){
		Location mapLocation = parentNode.position;
		Location lastMapLocation= mapLocation;
		while(map.at(mapLocation.y).at(mapLocation.x) == MapItem::empty || mapLocation == lastMapLocation){
			lastMapLocation = mapLocation;
			switch (direction)
			{
				case Direction::right:
					mapLocation.x++;
					break;
				case Direction::left:
					mapLocation.x--;
					break;
				case Direction::up:
					mapLocation.y--;
					break;
				case Direction::down:
					mapLocation.y++;
					break;
					
				default:
					break;
			}
		}
		if(parentNode.position != lastMapLocation){
			children.push_back(Node(lastMapLocation, parentNode.cost++));
		}	
	}
	return children;
}

Location Game::getInitialPosition(){
	for(uint8_t y = 0; y < map.size(); y++){
		auto mapLine = map.at(y);
		for(uint8_t x = 0; x < mapLine.size(); x++){
			if(mapLine.at(x) == MapItem::r1){
				return Location(x, y);
			}
		}
	}
	throw std::runtime_error("Initial Position not found");
}

void Game::printBoard(){
	std::cout << "Current state: \n";
	for(size_t i = 0; i < map.size(); i++)
	{
		std::vector<MapItem> miv = map[i];
		for(size_t j = 0; j < miv.size(); j++)
		{
			std::cout << (char) miv[j];
		}

		std::cout << std::endl;
		
	}
	
}