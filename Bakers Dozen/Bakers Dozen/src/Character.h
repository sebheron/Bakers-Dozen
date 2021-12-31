#pragma once

#include <string>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Board.h"
#include "GridItem.h"
#include "Bomb.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character: public GridItem {
private:
	ofxAssimpModelLoader model;
	glm::vec3 position;
	float angle;
	bool moving;
	Board* board;
	std::list<Bomb*> bombs;
	int prevX, prevY;
public:
	Character(std::string file, Board* board);

	void setup(int x, int y, bool active) override;
	void update(float deltaTime) override;
	void draw() override;
	void jumpTo(glm::vec3 b, float t);
	void sendMove(int x, int y);
	void placeBomb();

	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
};

#endif // CHARACTER_H