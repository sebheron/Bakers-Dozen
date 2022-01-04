#pragma once

#include "Point.h"

#ifndef GRIDITEM_H
#define GRIDITEM_H

class GridItem : public Point {
protected:
	bool active, traversable, triggerExplosion, breakable, canExplode;
public:
	GridItem(bool traversable = true, bool canExplode = false, bool breakable = false);

	virtual void setup(int x, int y, bool active);
	virtual void update(float deltaTime);
	virtual void draw();

	bool canTraverse();
	bool getActive();
	bool isExploding();
	bool isBreakable();
	bool getExplosive();
	void smash();
	void explode(bool reset = false);
};

#endif // GRIDITEM_H