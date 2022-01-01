#pragma once

#ifndef GRIDITEM_H
#define GRIDITEM_H

class GridItem {
protected:
	bool active, traversable, triggerExplosion, breakable, canExplode;
	int x, y;
public:
	GridItem(bool traversable = true, bool triggerExplosion = false, bool breakable = false);

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