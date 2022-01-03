#pragma once

#include "Character.h"
#include "Random.h"
#include "AStar.h"

#ifndef AICHARACTER_H
#define AICHARACTER_H

enum AIState { Thinking, Bombing, Seeking, Hiding, Waiting, Retreating };

class AICharacter : public Character {
private:
	AStar* astar;
	std::stack<Node*> currentPath;
	AIState state, lastState;
	float intelligence;
	float waitTime;
	int index;
	Point* objective;
	int waitX, waitY;
public:
	AICharacter(std::string file, Board* board, AStar* astar);

	void update(float deltaTime) override;

	std::stack<Node*> findPathToSafePosition(int skip = 0);
	std::vector<Pickup*> checkForRelativePickups();
	bool checkForBombs(int x, int y);
	bool checkForPlayers(int x, int y);
	bool getIsPlayerAt(int x, int y);
	bool isPlayerThreat(Character* player);
	Character* getNearestPlayer();
	int getBombsAvailable();
	float getDistance(int x1, int y1, int x2, int y2);
};


#endif // AICHARACTER_H