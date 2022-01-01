#include "Pickup.h"

Pickup::Pickup() : GridItem::GridItem(true, false, true)
{
	model.loadModel("bomb.obj", 20);
	model.setScaleNormalization(false);
	float r = Random::Range(0, 3);
	if (r < 1) {
		type = bomb;
	}
	else if (r < 2) {
		type = powerup;
	}
	else if (r < 3) {
		type = pierce;
	}
}

void Pickup::setup(int x, int y, bool active)
{
	model.setPosition(x * 2 - 15, -0.5, y * 2 - 15);
	GridItem::setup(x, y, active);
}

void Pickup::update(float deltaTime)
{
	rotation += deltaTime;
}

void Pickup::draw()
{
	if (active) {
		model.setRotation(0, rotation, 0, 1, 0);
		model.setScale(0.5, 0.5, 0.5);
		model.drawFaces();
	}
}

PickupType Pickup::getType()
{
	return type;
}
