#pragma once

#include "ofxAssimpModelLoader.h"
#include "ofMain.h"
#include "GridItem.h"
#include "Random.h"

#ifndef PICKUP_H
#define PICKUP_H

enum PickupType {powerup, pierce};

class Pickup : public GridItem {
private:
	ofxAssimpModelLoader model;
	float rotation;
	PickupType type;
public:
	Pickup();

	void setup(int x, int y, bool active) override;
	void draw() override;

	PickupType getType();
};

#endif // PICKUP_H