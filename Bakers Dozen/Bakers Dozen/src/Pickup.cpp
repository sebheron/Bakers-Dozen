#include "Pickup.h"

Pickup::Pickup() : GridItem::GridItem(true, false, true)
{
	float r = Random::Range(0, 2);
	if (r < 1) {
		model.loadModel("yeast.obj", 20);
		type = pierce;
	}
	else if (r < 2) {
		model.loadModel("sugar.obj", 20);
		type = powerup;
	}
	model.setScaleNormalization(false);
	model.setScale(1.1, 1.1, 1.1);
}

void Pickup::setup(int x, int y, bool active)
{
	model.setPosition(x * 2 - 15, -0.8, y * 2 - 15);
	rotation = Random::Range(0, 360);
	GridItem::setup(x, y, active);
}

void Pickup::draw()
{
	if (active) {
		model.setRotation(0, rotation + ofGetElapsedTimeMillis() / 50, 0, 1, 0);
		model.drawFaces();
	}
}

PickupType Pickup::getType()
{
	return type;
}
