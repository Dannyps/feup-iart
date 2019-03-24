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
	Location initialPosition = getInitialPosition();
	std::vector<Node> childs = getChildren(Node(initialPosition,0));
	std::cout << "From the initial position (x = " << unsigned(initialPosition.x) << " and y = " << unsigned(initialPosition.y) << ")" << std::endl;
	std::cout << "Next node left is at: \nx: " << unsigned(childs.at(0).position.x) << "\ny: " << unsigned(childs.at(0).position.y) << "\nheuristic: " << heuristic(childs.at(0).position, Location(12,1)) << std::endl;
	std::cout << "Next node up is at: \nx: " << unsigned(childs.at(1).position.x) << "\ny: " << unsigned(childs.at(1).position.y) << "\nheuristic: " << heuristic(childs.at(1).position, Location(12,1)) << std::endl;
	std::cout << "Next node down is at: \nx: " << unsigned(childs.at(2).position.x) << "\ny: " << unsigned(childs.at(2).position.y) << "\nheuristic: " << heuristic(childs.at(2).position, Location(12,1)) << std::endl;
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