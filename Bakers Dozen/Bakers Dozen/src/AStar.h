#pragma once

#include "Board.h"

#ifndef ASTAR_H
#define ASTAR_H

struct Node {
	int x, y;
	bool walkable, breakable;
	float distance, cost, weight;
	Node* parent = 0;

	bool operator< (const Node& right) const { return distance + cost < right.distance + right.cost; }
	bool operator> (const Node& right) const { return distance + cost > right.distance + right.cost; }
	bool operator== (const Node& right) const { return distance + cost == right.distance + right.cost; }
	bool operator!= (const Node& right) const { return distance + cost != right.distance + right.cost; }
};

struct Path {
	size_t length;
	std::stack<Node*> path;

	bool operator< (const Path& right) const { return length < right.length; }
	bool operator> (const Path& right) const { return length > right.length; }
	bool operator== (const Path& right) const { return length == right.length; }
	bool operator!= (const Path& right) const { return length != right.length; }
};

class AStar {
private:
	Board* board;
	Node* nodes[BOARD_SIZE_SQUARED];
public:
	AStar(Board* board);

	void readBoard();
	Node* getNodeAt(int x, int y, bool forcewalk = false);
	std::vector<Node*> getNodes(Node* node);
	std::stack<Node*> getPath(int x1, int y1, int x2, int y2);
	std::stack<Node*> getBreakablePath(int x1, int y1, int x2, int y2);
};

#endif // ASTAR_H