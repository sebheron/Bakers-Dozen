#pragma once

#include "Character.h"

#ifndef AICHARACTER_H
#define AICHARACTER_H

enum AIState { Thinking, Bombing, Seeking, Hiding, Waiting, Retreating };
struct Node { int x, y; };

class AICharacter : public Character {
private:
	AIState state = Thinking;
	float intelligence = 1;
	float waitTime;
	int index;
public:
	void update(float deltaTime) override;

	std::vector<int> findPathToSafePosition();
	std::vector<Pickup*> checkForRelativePickups();
	std::vector<Bomb*> checkForBombs(int x, int y);
	std::vector<Character*> checkForPlayers(int x, int y);
	bool isPlayerThreat(Character* player);
	Character* getNearestPlayer();
};


#endif // AICHARACTER_H