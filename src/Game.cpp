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
	/*Location initialPosition = initialPosition();
	std::vector<Node> childs = getChildren(Node(initialPosition,0));
	std::cout << "From the initial position (x = " << unsigned(initialPosition.x) << " and y = " << unsigned(initialPosition.y) << ")" << std::endl;
	std::cout << "Next node left is at: \nx: " << unsigned(childs.at(0).position.x) << "\ny: " << unsigned(childs.at(0).position.y) << "\nheuristic: " << heuristic(childs.at(0).position, Location(12,1)) << std::endl;
	std::cout << "Next node up is at: \nx: " << unsigned(childs.at(1).position.x) << "\ny: " << unsigned(childs.at(1).position.y) << "\nheuristic: " << heuristic(childs.at(1).position, Location(12,1)) << std::endl;
	std::cout << "Next node down is at: \nx: " << unsigned(childs.at(2).position.x) << "\ny: " << unsigned(childs.at(2).position.y) << "\nheuristic: " << heuristic(childs.at(2).position, Location(12,1)) << std::endl;
	*/
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
			std::vector<Node> previousNodes = parentNode.previousNodes;
			previousNodes.insert(previousNodes.end(), parentNode);
			children.push_back(Node(lastMapLocation, parentNode.cost++, previousNodes));
		}	
	}
	return children;
}

Location Game::findMapItem(MapItem mapItem){
	for(uint8_t y = 0; y < map.size(); y++){
		std::vector<MapItem> mapLine = map.at(y);
		for(uint8_t x = 0; x < mapLine.size(); x++){
			if(mapLine.at(x) == mapItem){
				return Location(x, y);
			}
		}
	}
	return Location(0, 0);
}

void Game::printBoard() {
    std::cout << "Current state: \n";
    //size_t line_size = map[0].size();

    // std::cout << "╔";  //
    // for (size_t i = 0; i < line_size * 2 - 1; i++) {
    //     if (i % 2)
    //         std::cout << "╦";
    //     else
    //         std::cout << "═";
    // }
    // std::cout << "╗" << std::endl;

    for (size_t i = 0; i < map.size(); i++) {
		std::vector<MapItem> mapRow = map[i];
        // std::cout << "║";
        for (MapItem item : mapRow) {
            printItem(item);
            // std::cout << "║";
        }
        std::cout << std::endl;
        // if (i != map.size()-1) {
        //     for (size_t i = 0; i < line_size * 2 - 1; i++) {
        //         if (i == 0) {
        //             std::cout << "╠";
        //         }
        //         if (i % 2)
        //             std::cout << "╬";
        //         else
        //             std::cout << "═";
        //     }
        //     std::cout << "╣" << std::endl;
        // }
    }

    // std::cout << "╚";  //
    // for (size_t i = 0; i < line_size * 2 - 1; i++) {
    //     if (i % 2)
    //         std::cout << "╩";
    //     else
    //         std::cout << "═";
    // }
    // std::cout << "╝" << std::endl;
}

void Game::printItem(MapItem t){
	switch (t)
	{
		case wall:
			std::cout << "███";
			break;
		case empty:
			std::cout << "▏▔▔";
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
		 	std::cout << "▏" << (char) t;
			break;
		default:
			std::cout << (char) t;
			break;
	}
}

std::vector<Location> Game::findSolution(){
	Location target(findMapItem(MapItem::target1));
	Node currentNode(findMapItem(MapItem::robot1), 0);
	std::vector<Node> expandedNodes;
	
	expandedNodes.push_back(currentNode);
	while(currentNode.position != target){
		Node nodeToExapandNext(expandedNodes.at(0));
		uint32_t tempScore = UINT32_MAX;
		uint8_t nodeIndex = 0;
		for(uint8_t i = 0; i < expandedNodes.size(); i++){
			uint32_t evaluatedScore = heuristic(expandedNodes.at(i).position, target) + expandedNodes.at(i).cost;
			if(evaluatedScore < tempScore){
				tempScore = evaluatedScore;
				nodeToExapandNext = expandedNodes.at(i);
				nodeIndex = i;
			}
		}
		expandedNodes.erase(expandedNodes.begin() + nodeIndex);
		std::vector<Node> nodesToInsert = getChildren(nodeToExapandNext);
		expandedNodes.insert(expandedNodes.end(), nodesToInsert.begin(), nodesToInsert.end());
	}

	std::vector<Location> path;
	for(Node node : currentNode.previousNodes){
		path.push_back(node.position);
	}
	path.push_back(currentNode.position);

	return path;
}