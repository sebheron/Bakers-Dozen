#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "GridItem.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character: public GridItem {
private:
	ofxAssimpModelLoader model;
	glm::vec3 position, rotation, scale;
	float angle;
public:
	Character();

	virtual void update(float deltaTime);
	void draw();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
};

#endif // CHARACTER_H