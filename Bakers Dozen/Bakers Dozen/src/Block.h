#pragma once

#include "ofMain.h"
#include "ofVec3f.h"
#include "GridItem.h"

#ifndef BLOCK_H
#define BLOCK_H

class Block : public GridItem {
private:
	ofTexture* texture;
public:
	Block(bool breakable, ofTexture* texture);

	void draw() override;
};

#endif // BLOCK_H