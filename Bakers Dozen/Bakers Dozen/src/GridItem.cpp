#include "GridItem.h"

GridItem::GridItem(bool traversable, bool canExplode, bool breakable)
	: active(false), traversable(traversable), triggerExplosion(false), breakable(breakable), canExplode(canExplode), Point::Point() {}

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
	return traversable;
}

bool GridItem::getActive()
{
	return active;
}

bool GridItem::isExploding()
{
	return triggerExplosion;
}

bool GridItem::isBreakable()
{
	return breakable;
}

bool GridItem::getExplosive()
{
	return canExplode;
}

void GridItem::smash()
{
	active = false;
	breakable = false;
	traversable = true;
}

void GridItem::explode(bool reset)
{
	triggerExplosion = !reset;
}