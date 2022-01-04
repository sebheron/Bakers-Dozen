#pragma once

#include "Block.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Random.h"
#include "Pickup.h"

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
	bool checkPlaceBlocked(int x, int y);
	bool checkPlaceBomb(int x, int y);
	bool checkPlacePickup(int x, int y);
	bool checkPlaceBreakableBlocked(int x, int y);
	bool checkExplosionOccured(int x, int y);
	GridItem* getGridItem(int x, int y);

	void addBomb(int x, int y, int power, int piercing, float angle);
};

#endif // BOARD_H