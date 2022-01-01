#pragma once

#include "ofMain.h"
#include "Board.h"

boolean[][] maze = new boolean[width][height]; // The maze
boolean[][] wasHere = new boolean[width][height];
boolean[][] correctPath = new boolean[width][height]; // The solution to the maze
int startX, startY; // Starting X and Y values of maze
int endX, endY;     // Ending X and Y values of maze

public void solveMaze() {
	maze = generateMaze(); // Create Maze (false = path, true = wall)
	for (int row = 0; row < maze.length; row++)
		// Sets boolean Arrays to default values
		for (int col = 0; col < maze[row].length; col++) {
			wasHere[row][col] = false;
			correctPath[row][col] = false;
		}
	boolean b = recursiveSolve(startX, startY);
	// Will leave you with a boolean array (correctPath) 
	// with the path indicated by true values.
	// If b is false, there is no solution to the maze
}

struct Node { int x, y, d; };

std::vector<Node> getEmptyNodes(Board* board) {
	std::vector<Node> nodes;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			if (!board->checkPlaceBlocked(x, y)) {
				nodes.push_back(Node{ x,y,0 });
			}
		}
	}
}

std::vector<Node> getPathFromTo(int sx, int sy, int ex, int ey) {

}

public boolean recursiveSolve(int x, int y) {
	if (x == endX && y == endY) return true; // If you reached the end
	if (maze[x][y] || wasHere[x][y]) return false;
	// If you are on a wall or already were here
	wasHere[x][y] = true;
	if (x != 0) // Checks if not on left edge
		if (recursiveSolve(x - 1, y)) { // Recalls method one to the left
			correctPath[x][y] = true; // Sets that path value to true;
			return true;
		}
	if (x != width - 1) // Checks if not on right edge
		if (recursiveSolve(x + 1, y)) { // Recalls method one to the right
			correctPath[x][y] = true;
			return true;
		}
	if (y != 0)  // Checks if not on top edge
		if (recursiveSolve(x, y - 1)) { // Recalls method one up
			correctPath[x][y] = true;
			return true;
		}
	if (y != height - 1) // Checks if not on bottom edge
		if (recursiveSolve(x, y + 1)) { // Recalls method one down
			correctPath[x][y] = true;
			return true;
		}
	return false;
}