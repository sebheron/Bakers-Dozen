#pragma once

#include "Block.h"
#include "Bomb.h"
#include "Explosion.h"

#ifndef BOARD_H
#define BOARD_H
#define BOARD_SIZE 17
#define BOARD_SIZE_SQUARED 289

class Board {
private:
	GridItem* blocks[BOARD_SIZE_SQUARED];
	Explosion* explosions[BOARD_SIZE_SQUARED];
public:
	void reset(ofTexture* breakableTexture, ofTexture* solidTexture);
	void update(float deltaTime);
	void draw();

	void calculateExplosion(Bomb* bomb, int x, int y);
	void explodeLine(int x, int y, int dx, int dy, int power, int piercing);
	void destroyBlock(int x, int y);
	bool checkPlaceBlocked(int x, int y);

	void addBomb(int x, int y, Bomb* bomb);
};

#endif // BOARD_H