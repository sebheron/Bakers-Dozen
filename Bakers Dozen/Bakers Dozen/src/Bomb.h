#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "GridItem.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb : public GridItem {
private:
	ofxAssimpModelLoader model;
	float scale;
public:
	Bomb();

	void setup(int x, int y, bool active) override;
	void update(float deltaTime) override;
	void draw() override;

	bool canTraverse() override;

	int power, piercing;
};

#endif // BOMB_H