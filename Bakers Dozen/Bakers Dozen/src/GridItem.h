#pragma once

#ifndef GRIDITEM_H
#define GRIDITEM_H

class GridItem {
private:
	bool active;
	int x, y;
public:
	GridItem();

	void setup(int x, int y, bool active);

	bool getActive();
};

#endif // GRIDITEM_H