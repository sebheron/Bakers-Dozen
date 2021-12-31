#pragma once

#ifndef GRIDITEM_H
#define GRIDITEM_H

class GridItem {
protected:
	bool active;
	int x, y;
public:
	GridItem();

	virtual void setup(int x, int y, bool active);
	virtual void update(float deltaTime);
	virtual void draw();

	virtual bool canTraverse();
	bool getActive();
	void hide();

	bool triggerExplosion, breakable;
};

#endif // GRIDITEM_H