#include "Board.h"

void Board::reset(ofTexture* breakableTexture, ofTexture* solidTexture)
{
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			int i = y * BOARD_SIZE + x;
			explosions[i] = new Explosion();
			explosions[i]->setup(x, y);

			//Skip certain board positions to avoid smothering players.
			if (x == 1 || x == BOARD_SIZE - 2) {
				if (y == 1 || y == BOARD_SIZE - 2) {
					blocks[i] = new GridItem();
					continue;
				}
				else if (y == 2 || y == BOARD_SIZE - 3) {
					blocks[i] = new GridItem();
					continue;
				}
			}
			else if (x == 2 || x == BOARD_SIZE - 3) {
				if (y == 1 || y == BOARD_SIZE - 2) {
					blocks[i] = new GridItem();
					continue;
				}
			}
			if (y == 0 | x == 0 | y == BOARD_SIZE - 1 | x == BOARD_SIZE - 1
				| (y % 2 == 0 && x % 2 == 0)) {
				blocks[i] = new Block(false, solidTexture);
				blocks[i]->setup(x, y, true);
			}
			else if (Random::Range(0,1) > 0.5) {
				blocks[i] = new Block(true, breakableTexture);
				blocks[i]->setup(x, y, true);
			}
			else {
				blocks[i] = new GridItem();
			}
		}
	}
}

void Board::update(float deltaTime) {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			int i = y * BOARD_SIZE + x;
			explosions[i]->update(deltaTime);
			blocks[i]->update(deltaTime);
			//Checking whether an explosion should be triggered.
			if (blocks[i]->isExploding()) {
				blocks[i]->smash();
				explosions[i]->explode();
				explosionSound->play();
				//Explicit down casting to bomb and pass across.
				//Noting previous trigger check we can ensure safety of casting.
				calculateExplosion((Bomb*)blocks[i], x, y);
				blocks[i] = new GridItem();
			}
		}
	}
}

void Board::draw()
{
	ofSetColor(255);
	for (int i = 0; i < BOARD_SIZE_SQUARED; i++) {
		explosions[i]->draw();
		ofSetColor(255);
		blocks[i]->draw();
	}
}

void Board::setSounds(ofSoundPlayer* explosionSound) {
	this->explosionSound = explosionSound;
}

void Board::calculateExplosion(Bomb* bomb, int x, int y)
{
	int power = bomb->power;
	int piercing = bomb->piercing;

	explodeLine(x, y, 1, 0, power, piercing);
	explodeLine(x, y, 0, 1, power, piercing);
	explodeLine(x, y, -1, 0, power, piercing);
	explodeLine(x, y, 0, -1, power, piercing);
}

void Board::explodeLine(int x, int y, int dx, int dy, int power, int piercing)
{
	for (int j = 0; j < power; j++) {
		x += dx;
		y += dy;
		int i = y * BOARD_SIZE + x;

		if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0 | piercing < 0)
			return;

		if (blocks[i]->getExplosive()) {
			blocks[i]->explode();
			explosionSound->play();
			return;
		}

		bool traversable = blocks[i]->canTraverse();
		if (blocks[i]->isBreakable()) {
			blocks[i]->smash();
			if (!traversable) {
				if (Random::Range(0, 1) > 0.5) {
					blocks[i] = new Pickup();
					blocks[i]->setup(x, y, true);
				}
				piercing--;
			}
		}
		else if (!traversable) {
			return;
		}

		explosions[i]->explode();
	}
}

bool Board::checkPlaceBlocked(int x, int y)
{
	if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0)
		return true;
	int i = y * BOARD_SIZE + x;
	bool active = blocks[i]->getActive();
	return active ? !blocks[i]->canTraverse() : active;
}

bool Board::checkPlaceBomb(int x, int y)
{
	if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0)
		return false;
	int i = y * BOARD_SIZE + x;
	return blocks[i]->getExplosive() && blocks[i]->getActive();
	return false;
}

bool Board::checkPlacePickup(int x, int y)
{
	if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0)
		return false;
	int i = y * BOARD_SIZE + x;
	if (!checkPlaceBlocked(x, y) && blocks[i]->getActive()) {
		return blocks[i]->isBreakable();
	}
	return false;
}

bool Board::checkPlaceBreakableBlocked(int x, int y)
{
	if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0)
		return true;
	int i = y * BOARD_SIZE + x;
	bool active = blocks[i]->getActive();
	active = active ? !blocks[i]->canTraverse() : active;
	return active ? blocks[i]->isBreakable() : active;
}

Explosion* Board::getExplosionAt(int x, int y)
{
	return explosions[y * BOARD_SIZE + x];
}

GridItem * Board::getGridItem(int x, int y)
{
	int i = y * BOARD_SIZE + x;
	if (blocks[i]->getActive()) {
		return blocks[i];
	}
	return 0;
}

bool Board::addBomb(int x, int y, int power, int piercing, float angle)
{
	if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0)
		return false;
	int i = y * BOARD_SIZE + x;
	if (!blocks[i]->getActive()) {
		blocks[i] = new Bomb(power, piercing, angle);
		blocks[i]->setup(x, y, true);
		return true;
	}
	return false;
}
