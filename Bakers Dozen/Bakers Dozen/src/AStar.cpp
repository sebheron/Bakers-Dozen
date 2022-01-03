#include "AStar.h"

AStar::AStar(Board * board) : board(board)
{
	std::fill(nodes, nodes + BOARD_SIZE_SQUARED, (Node*)NULL);
}

void AStar::readBoard()
{
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			int i = y * BOARD_SIZE + x;
			bool breakable = board->checkPlaceBreakableBlocked(x, y);
			bool blocked = board->checkPlaceBlocked(x, y);
			if (nodes[i] == 0) {
				nodes[i] = new Node{
					x, y,
					!blocked, breakable,
					-1, 1, 1, 0 
				};
			}
			else {
				nodes[i]->x = x;
				nodes[i]->y = y;
				nodes[i]->walkable = !blocked;
				nodes[i]->breakable = breakable;
				nodes[i]->distance = -1;
				nodes[i]->cost = 1;
				nodes[i]->parent = 0;
			}
		}
	}
}

Node * AStar::getNodeAt(int x, int y, bool forcewalk)
{
	int i = y * BOARD_SIZE + x;
	if (forcewalk) {
		nodes[i]->walkable = true;
	}
	return nodes[i];
}

std::vector<Node*> AStar::getNodes(Node* n)
{
	static int dx[4] = { 1, 0, 0, -1 };
	static int dy[4] = { 0, -1, 1, 0 };

	std::vector<Node*> nodes;

	for (int i = 0; i < 4; i++) {
		int xx = n->x + dx[i];
		int yy = n->y + dy[i];

		if (xx < BOARD_SIZE - 1 && xx > 0 && yy < BOARD_SIZE - 1 && yy > 0) {
			nodes.push_back(getNodeAt(xx, yy));
		}
	}

	return nodes;
}


std::stack<Node*> AStar::getPath(int x1, int y1, int x2, int y2)
{
	if (nodes[0] == 0)
		readBoard();

	std::stack<Node*> path;

	std::list<Node*> open;
	std::list<Node*> closed;
	std::vector<Node*> adj;

	Node* start = getNodeAt(x1, y1);
	start->cost = 1;
	start->parent = 0;
	start->distance = 0;
	Node* end = getNodeAt(x2, y2);
	Node* current = start;
	open.push_back(start);

	while (open.size() > 0 && std::find(closed.begin(), closed.end(), end) == closed.end())
	{
		current = open.front();
		open.pop_front();
		closed.push_back(current);
		adj = getNodes(current);

		for(Node* n : adj)
		{
			if (std::find(closed.begin(), closed.end(), n) == closed.end() && n->walkable
				&& std::find(open.begin(), open.end(), n) == open.end())
			{
				n->parent = current;
				n->distance = abs(n->x - end->x) + abs(n->y - end->y);
				n->cost = n->weight + current->cost;
				open.push_back(n);
			}
		}
	}

	if (std::find(closed.begin(), closed.end(), end) == closed.end())
	{
		return path;
	}

	Node* prev = 0;
	Node* temp = current;
	if (temp < 0) {
		return path;
	}
	do
	{
		path.push(temp);
		prev = temp;
		temp = temp->parent;
	} while (prev != temp && temp != start && temp != 0);
	return path;
}

std::stack<Node*> AStar::getBreakablePath(int x1, int y1, int x2, int y2)
{
	if (nodes[0] == 0)
		readBoard();

	std::stack<Node*> path;

	std::list<Node*> open;
	std::list<Node*> closed;
	std::vector<Node*> adj;

	Node* start = getNodeAt(x1, y1, true);
	start->cost = 1;
	start->parent = 0;
	start->distance = 0;
	Node* end = getNodeAt(x2, y2);
	Node* current = start;
	open.push_back(start);

	while (open.size() > 0 && std::find(closed.begin(), closed.end(), end) == closed.end())
	{
		current = open.front();
		bool breakable = board->checkPlaceBreakableBlocked(current->x, current->y);
		bool blocked = board->checkPlaceBlocked(current->x, current->y);
		current->walkable = !blocked;
		current->breakable = breakable;
		open.pop_front();
		closed.push_back(current);
		adj = getNodes(current);

		for (Node* n : adj)
		{
			if (std::find(closed.begin(), closed.end(), n) == closed.end() && (n->walkable || n->breakable)
				&& std::find(open.begin(), open.end(), n) == open.end())
			{
				n->parent = current;
				n->distance = abs(n->x - end->x) + abs(n->y - end->y);
				n->cost = n->weight + current->cost + (n->breakable ? 0.5 : 0);
				open.push_back(n);
			}
		}
	}

	if (std::find_if(closed.begin(), closed.end(), compareN(end)) == closed.end())
	{
		return path;
	}

	Node* prev = 0;
	Node* temp = current;
	if (temp < 0) {
		return path;
	}
	do
	{
		path.push(temp);
		prev = temp;
		temp = temp->parent;
	} while (prev != temp && temp != start && temp != 0);
	return path;
}