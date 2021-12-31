#include "GridItem.h"

GridItem::GridItem() : x(0), y(0), active(false), triggerExplosion(false), breakable(false) {}

void GridItem::setup(int x, int y, bool active)
{
	this->x = x;
	this->y = y;
	this->active = active;
}

void GridItem::update(float deltaTime) {}

void GridItem::draw() {}

bool GridItem::canTraverse()
{
	return true;
}

bool GridItem::getActive()
{
	return active;
}

void GridItem::hide()
{
	active = false;
}
