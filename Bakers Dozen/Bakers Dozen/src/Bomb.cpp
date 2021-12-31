#include "Bomb.h"

Bomb::Bomb() : scale(1), power(2), piercing(0)
{
	breakable = true;
	triggerExplosion = true;
	model.loadModel("bomb.obj", 20);
	model.setScaleNormalization(false);
}

void Bomb::setup(int x, int y, bool active)
{
	scale = 1;
	GridItem::setup(x, y, active);
}

void Bomb::update(float deltaTime)
{
	if (active) {
		scale += deltaTime/2.5;
		if (scale > 2) {
			triggerExplosion = true;
		}
	}
}

void Bomb::draw()
{
	if (active) {
		model.setScale(scale, scale, scale);
		float flatScale = (scale - 1) * (scale - 1) * (scale - 1);
		//Creating pseudo-random shake.
		//Formula 'y = sin(axxx)/b' provides an exponential scaled to '1/b'.
		float shakeX = sin(40 * flatScale) / 6;
		//Changing 'a' slightly will transform values enough to create visible difference in x/y shake.
		float shakeY = sin(42 * flatScale) / 6;
		model.setPosition(x * 2 - 15 + shakeX, 0, y * 2 - 15 + shakeY);
		model.drawFaces();
	}
}

bool Bomb::canTraverse()
{
	return false;
}