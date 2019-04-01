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
		std::vector<Location> mapRow;
		for(uint8_t j = 0; j< line.length();j++){
			char c = line[j];
			Location l(i, j, c);
			mapRow.push_back(l);
		}
		map.push_back(mapRow);
	}

	file.close();

	if (map.size()==0){
		throw std::invalid_argument("The provided map is empty");
	}
	
	// calc nextLocation for each location
	for(uint8_t i = 0; this->map.size(); i++){
		std::vector<Location> mapRow = this->map.at(i);
		for(uint8_t j = 0; j< mapRow.size();j++){
			// ignore walls
			if(this->map.at(i).at(j).item == MapItem::wall) continue;

			for (int direction = 0; direction < 4 ; direction++){
				uint8_t y=i, x=j;
				while(map.at(y).at(x).item != MapItem::wall){
					switch (direction) {
						case Direction::right:
							x++;
							break;
						case Direction::left:
							x--;
							break;
						case Direction::up:
							y--;
							break;
						case Direction::down:
							y++;
							break;
						default:
							break;
					}
					if(y >= map.size() || x >= map[0].size()){
						break;
					}
				}
				switch (direction) {
					case Direction::right:
						this->map.at(i).at(j).right = &this->map.at(y).at(x);
						break;
					case Direction::left:
						this->map.at(i).at(j).left = &this->map.at(y).at(x);
						break;
					case Direction::up:
						this->map.at(i).at(j).up = &this->map.at(y).at(x);
						break;
					case Direction::down:
						this->map.at(i).at(j).down = &this->map.at(y).at(x);
						break;
					default:
						break;
				}

				std::cout << "direction: " << direction << "\t Original node: " << this->map.at(i).at(j).toString() << "\t Wall: " << this->map.at(y).at(x).toString() << std::endl;
			}

		}
	}

}

std::vector<Node> Game::getChildren(Node parentNode){
	std::vector<Node> children;

	for (int direction = 0; direction < 4 ; direction++){
		Location mapLocation = parentNode.position;
		Location lastMapLocation= mapLocation;
		while(map.at(mapLocation.y).at(mapLocation.x).item == MapItem::empty || map.at(mapLocation.y).at(mapLocation.x).item == MapItem::target1 || map.at(mapLocation.y).at(mapLocation.x).item == MapItem::robot1 || mapLocation == lastMapLocation){ // TODO: Find a cleaner way to do this!
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
			if(mapLocation.y >= map.size() || mapLocation.x >= map[0].size()){
				break;
			}
		}
		//std::cout << "parent: " << parentNode.position.toString() << ", lastMapLocation: " << lastMapLocation.toString() << std::endl;
		if(parentNode.position != lastMapLocation){
			std::vector<Node> previousNodes = parentNode.previousNodes;
			previousNodes.insert(previousNodes.end(), parentNode);
			uint16_t cost = parentNode.cost*2;
			children.push_back(Node(lastMapLocation, cost, previousNodes));
		}	
	}
	//std::cout << "csize: " << children.size() << std::endl;
	return children;
}

Location Game::findMapItem(MapItem mapItem){
	for(uint8_t y = 0; y < map.size(); y++){
		std::vector<Location> mapLine = map.at(y);
		for(uint8_t x = 0; x < mapLine.size(); x++){
			if(mapLine.at(x).item == mapItem){
				return Location(x, y);
			}
		}
	}
	return Location(0, 0);
}

void Game::printBoard() {
    std::cout << "Current state: \n";
    size_t line_size = map[0].size();

    std::cout << "╔";  //
    for (size_t i = 0; i < line_size * 2 - 1; i++) {
        if (i % 2)
            std::cout << "╦";
        else
            std::cout << "═";
    }
    std::cout << "╗" << std::endl;

    for (size_t i = 0; i < map.size(); i++) {
		std::vector<Location> mapRow = map[i];
        std::cout << "║";
        for (Location item : mapRow) {
            printItem(item.item);
            std::cout << "║";
        }
        std::cout << std::endl;
        if (i != map.size()-1) {
            for (size_t i = 0; i < line_size * 2 - 1; i++) {
                if (i == 0) {
                    std::cout << "╠";
                }
                if (i % 2)
                    std::cout << "╬";
                else
                    std::cout << "═";
            }
            std::cout << "╣" << std::endl;
        }
    }

    std::cout << "╚";  //
    for (size_t i = 0; i < line_size * 2 - 1; i++) {
        if (i % 2)
            std::cout << "╩";
        else
            std::cout << "═";
    }
    std::cout << "╝" << std::endl;
}

void Game::printItem(MapItem t){
	switch (t)
	{
		case wall:
			std::cout << "█";
			break;
		case empty:
			std::cout << " ";
			break;
		case robot1:
		case robot2:
		case robot3:
		case robot4:
		case robot5:
		case target1:
		case target2:
		case target3:
		case target4:
		case target5:
		 	std::cout << (char) t;
			break;
		default:
			std::cout << (char) t;
			break;
	}
}

std::vector<Location> Game::findSolution(){
	Location target = findMapItem(MapItem::target1);
	Node currentNode(findMapItem(MapItem::robot1), 0);
	std::vector<Node> expandedNodes;
	
	// std::cerr << "Start is: " << currentNode.position.toString() << std::endl;
	// std::cerr << "Goal is: " << target.toString() << std::endl;
	
	bool solutionFound = 0;
	expandedNodes.push_back(currentNode);
	while(!solutionFound){
		Node nodeToExapandNext(expandedNodes.at(0));
		uint32_t tempScore = UINT32_MAX;
		uint32_t nodeIndex = 0;
		for(uint32_t i = 0; i < expandedNodes.size(); i++){
			uint32_t evaluatedScore = heuristic(expandedNodes.at(i).position, target) + expandedNodes.at(i).cost;
			if(evaluatedScore < tempScore){
				tempScore = evaluatedScore;
				nodeToExapandNext = expandedNodes.at(i);
				nodeIndex = i;
			}
		}
		// std::cout << "Let's find something better than: " << nodeToExapandNext.position.toString() << " -> ";
		// for(Node previousN : nodeToExapandNext.previousNodes){
		// 	std::cout << previousN.position.toString();
		// }
		//std::cout << std::endl;

		expandedNodes.erase(expandedNodes.begin() + nodeIndex);
		std::vector<Node> nodesToInsert = getChildren(nodeToExapandNext);
				
		// std::cout << "Curent expanded nodes:" << std::endl;
		for(auto n : nodesToInsert){
			if (n.position == target){
				solutionFound = true;
				currentNode = n;
			}
			// std::cout << n.position.toString() << " h = " << heuristic(n.position, target) + n.cost << std::endl;
		}

		expandedNodes.insert(expandedNodes.end(), nodesToInsert.begin(), nodesToInsert.end());
	}

	std::vector<Location> path;
	for(Node node : currentNode.previousNodes){
		path.push_back(node.position);
	}
	path.push_back(currentNode.position);

	return path;
}