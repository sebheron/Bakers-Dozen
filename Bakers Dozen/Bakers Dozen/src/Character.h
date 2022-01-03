#pragma once

#include <string>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Board.h"
#include "GridItem.h"
#include "Bomb.h"
#include "Pickup.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public Point {
protected:
	ofxAssimpModelLoader model;
	glm::vec3 position;
	float angle;
	bool moving, living;
	Board* board;
	std::list<Bomb*> bombs;
	int power, piercing;
	int id;
public:
	Character(std::string file, Board* board);

	void setup(int x, int y);
	virtual void update(float deltaTime);
	void draw();
	void jumpTo(glm::vec3 b, float t);
	void sendMove(int x, int y);
	void placeBomb();
	void takePickup(Pickup* pickup);

	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	glm::vec3 getPosition();
	float getPowerLevel();

	int getId();
	
	static std::vector<Character*> players;
};

#endif // CHARACTER_H