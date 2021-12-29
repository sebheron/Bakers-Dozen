#include "GridItem.h"

GridItem::GridItem() : x(0), y(0), active(false) {}

void GridItem::setup(int x, int y, bool active)
{
	this->x = x;
	this->y = y;
	this->active = active;
}

bool GridItem::getActive()
{
	return active;
}
