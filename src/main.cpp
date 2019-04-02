#include <iostream>
#include <string>

#include "Game.h"
#include "heuristics.h"
#include "types.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Give a map file" << std::endl;
        return -1;
    }

    try {
        Game game(argv[1], heuristicManhattanDistance);
        game.printBoard();
        std::vector<Location> sol = game.findSolution();
        for (size_t i = 1; i < sol.size(); i++) {
            Location p1 = sol[i - 1];
            Location p2 = sol[i];
            std::string d = "t";
            if (p1.x == p2.x) {
                if (p2.y < p1.y)
                    d = "up";
                else
                    d = "down";
            } else {
                if (p2.x > p1.x)
                    d = "right";
                else
                    d = "left";
            }

            std::cout << p1.toString() <<"\t"<< p2.toString() << "\t" << d << std::endl;
        }

    } catch (std::exception *e) {
        std::cout << e->what();
    }
    return 0;
}
