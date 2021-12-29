#pragma once

#include "ofMain.h"
#include "ofVec3f.h"
#include "GridItem.h"

#ifndef BLOCK_H
#define BLOCK_H

class Block : public GridItem {
public:
	void draw();
};

#endif // BLOCK_H