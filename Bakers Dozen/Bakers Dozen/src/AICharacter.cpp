#include "AICharacter.h"

AICharacter::AICharacter(std::string file, Board * board, AStar* astar) : astar(astar), Character::Character(file, board)
{
	intelligence = (int)Random::Range(6, 9);
	state = Thinking;
	lastState = Thinking;
	waitX = 0;
	waitY = 0;
	waitTime = 1.5 / this->intelligence;
}

void AICharacter::update(float deltaTime)
{
	Character::update(deltaTime);
	
	if (!living)
		return;
	if (state == Thinking && waitTime <= 0) {
		std::vector<Pickup*> pickups = checkForRelativePickups();
		if (checkForBombs(x, y)) {
			waitX = x;
			waitY = y;
			currentPath = findPathToSafePosition((int)Random::Range(0, 8));
			if (currentPath.size() > 0)
				state = Hiding;
		}
		else if (getIsPlayerAt(x, y)) {
			currentPath = findPathToSafePosition(2);
			if (currentPath.size() > 0)
				state = Seeking;
		}
		else if (pickups.size() > 0) {
			objective = pickups.at(0);
			currentPath = astar->getPath(x, y, objective->getX(), objective->getY(), id);
			if (currentPath.size() > 0) {
				state = Seeking;
			}
		}
		else if (getBombsAvailable() > 0) {
			objective = getNearestPlayer();
			if (objective > 0) {
				currentPath = astar->getBreakablePath(x, y, objective->getX(), objective->getY());
				if (currentPath.size() > 0) {
					state = Seeking;
				}
			}
		}
		else {
			currentPath = astar->getPath(x, y, startX, startY, id);
			if (currentPath.size() > 0) {
				state = Seeking;
			}
		}
		lastState = state;
	}
	else if (state == Bombing) {
		if (getBombsAvailable() > 0) {
			placeBomb();
			state = Thinking;
			waitTime = 1 / intelligence;
		}
		else {
			state = Thinking;
			waitTime = 1.5f / intelligence;
		}
	}
	else if (state == Seeking) {
		if (currentPath.size() > 0) {
			int bombs = getBombsAvailable();
			Node* node = currentPath.top();
			if (x == node->x && y == node->y) {
				currentPath.pop();
			}
			else {
				float dis = getDistance(node->x, node->y, x, y);
				if (dis > 1) {
					state = Thinking;
					waitTime = 1.5f / intelligence;
				}
				if (checkForBombs(x, y)) {
					state = Thinking;
				}
				else if (!checkForPlayers(x, y) || bombs <= 0) {
					sendMove(node->x - x, node->y - y);
					if (bombs > 0 && objective != getNearestPlayer()) {
						state = Thinking;
						waitTime = 1.5f / intelligence;
					}
					else if (bombs > 0 && !moving) {
						state = Bombing;
					}
				}
				else {
					state = Bombing;
				}
			}
		}
		else {
			state = Thinking;
			waitTime = 1.5f / intelligence;
		}
	}
	else if (state == Hiding) {
		if (currentPath.size() > 0) {
			Node* node = currentPath.top();
			if (node->x == x && node->y == y) {
				currentPath.pop();
			}
			else {
				float dis = getDistance(x, y, node->x, node->y);
				if (dis > 1) {
					state = Thinking;
					waitTime = 1.5f / intelligence;
				}
				if (!getIsPlayerAt(x, y)) {
					sendMove(node->x - x, node->y - y);
				}
				if (!moving) {
					state = Thinking;
					waitTime = 1 / intelligence;
				}
			}
		}
		else {
			state = Waiting;
		}
	}
	else if (state == Waiting) {
		if (!checkForBombs(x, y) && !board->checkPlaceBomb(waitX, waitY))
		{
			state = Thinking;
			waitTime = 1.5f / intelligence;
		}
	}
	waitTime -= deltaTime;
}

std::stack<Node*> AICharacter::findPathToSafePosition(int skip)
{
	std::set<Path> paths;
	for (int xx = 0; xx < BOARD_SIZE; xx++) {
		for (int yy = 0; yy < BOARD_SIZE; yy++) {
			if (!(x == xx && y == yy) && !board->checkPlaceBlocked(xx, yy) && !checkForBombs(xx, yy) && !checkForPlayers(xx, yy)) {
				std:stack<Node*> path = astar->getPath(x, y, xx, yy, id);
				paths.insert(Path
					{ 
						path.size(), path
					}
				);
			}
		}
	}
	int i = 0;
	while (!paths.empty()) {
		Path path = *paths.begin();
		if (i > skip || paths.size() == 1) {
			return path.path;
		}
		i++;
		paths.erase(path);
	}
	return std::stack<Node*>();
}

std::vector<Pickup*> AICharacter::checkForRelativePickups()
{
	std::vector<Pickup*> pickups;
	for (int xx = 0; xx < BOARD_SIZE; xx++) {
		for (int yy = 0; yy < BOARD_SIZE; yy++) {
			if (board->checkPlacePickup(xx, yy)) {
				size_t pathSize = astar->getPath(x, y, xx, yy, id).size();
				if (pathSize > 0 && pathSize < 8) {
					pickups.push_back((Pickup*)board->getGridItem(xx, yy));
				}
			}
		}
	}
	return pickups;
}

bool AICharacter::checkForBombs(int x, int y) {
	std::vector<Bomb*> bombs;
	for (int yy = 0; yy < BOARD_SIZE; yy++) {
		for (int xx = 0; xx < BOARD_SIZE; xx++) {
			if ((xx == x || y == yy) && board->checkPlaceBomb(xx, yy)) {
				float dis = getDistance(x, y, xx, yy);
				Bomb* bomb = (Bomb*)board->getGridItem(xx, yy);
				if (bomb->power >= dis) {
					return true;
				}
			}
		}
	}
	return false;
}

bool AICharacter::checkForPlayers(int x, int y) {
	glm::vec3 startPos = glm::vec3(x, 0, y);
	for (Character* player : players) {
		glm::vec3 playerPos = player->getPosition();
		float dis = getDistance(playerPos.x, playerPos.z, startPos.x, startPos.z);
		if (player->getId() != id && (playerPos.x == position.x || playerPos.z == position.z) && dis <= power - Random::Range(0, 2)) {
			return true;
		}
	}
	return false;
}

bool AICharacter::getIsPlayerAt(int x, int y) {
	glm::vec3 startPos = glm::vec3(x, 0, y);
	for (Character* player : players) {
		glm::vec3 playerPos = player->getPosition();
		float dis = getDistance(playerPos.x, playerPos.z, startPos.x, startPos.z);
		if (player->getId() != id && dis <= 0) {
			return true;
		}
	}
	return false;
}

Character* AICharacter::getNearestPlayer() {
	Character* bestTarget = 0;
	float closest = INFINITY;
	for(Character* potentialTarget : players) {
		glm::vec3 targetPos = potentialTarget->getPosition();
		float dis = getDistance(targetPos.x, targetPos.z, position.x, position.z);
		if (dis > 0 && dis < closest) {
			closest = dis;
			bestTarget = potentialTarget;
		}
	}
	return bestTarget;
}

float AICharacter::getDistance(int x1, int y1, int x2, int y2)
{
	float a = x2 - x1;
	float aa = a * a;

	float b = y2 - y1;
	float bb = b * b;

	return sqrt(aa + bb);
}
