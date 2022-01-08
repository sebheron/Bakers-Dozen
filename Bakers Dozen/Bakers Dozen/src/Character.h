#pragma once

#include <string>
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Board.h"
#include "GridItem.h"
#include "Pickup.h"

#ifndef CHARACTER_H
#define CHARACTER_H

struct PocketBomb {
	int power, piercing;
};

class Character : public Point {
protected:
	ofxAssimpModelLoader p_model, r_model;
	glm::vec3 position;
	float angle;
	bool moving, living;
	Board* board;
	std::stack<PocketBomb*> bombs;
	int id, power, piercing, startX, startY;
	ofSoundPlayer* walkSound;
	ofSoundPlayer* powerupSound;
	ofSoundPlayer* refillSound;
public:
	Character(std::string file, Board* board);

	void setup(int x, int y);
	void setSounds(ofSoundPlayer* walkSound, ofSoundPlayer* powerupSound, ofSoundPlayer* refillSound);
	virtual void update(float deltaTime);
	void draw();
	void kill();
	void jumpTo(glm::vec3 b, float t);
	bool sendMove(int x, int y);
	void placeBomb();
	void takePickup(Pickup* pickup);

	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);

	bool getLiving();
	glm::vec3 getPosition();
	int getId();
	int getBombsAvailable();
	int getPower();
	int getPiercing();
	
	static std::vector<Character*> players;
};

#endif // CHARACTER_H