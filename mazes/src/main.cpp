#include <iostream>
#include <string>
#include "../include/dsets.h"
#include "../include/maze.h"
#include "../include/PNG.h"

using namespace std;

int main(int argc, char ** argv)
{
    // using the two integer arguments as width & height
    int width = 0, height = 0;
    if (argc == 3) {
        width = stoi(argv[1]);
        height = stoi(argv[2]);
    } else {
        width = 50;
        height = 50;
    }
    // generate a random maze
    SquareMaze maze;
    maze.makeMaze(width, height);
    PNG* canvas = maze.drawMaze();
    canvas->writeToFile("generated_mazes/maze.png");
    delete canvas;
    canvas = NULL;
    // generate the solution of the random maze
    canvas = maze.drawMazeWithSolution();
    canvas->writeToFile("generated_mazes/solution.png");
    delete canvas;
    return 0;
}
