#include "Board.h"

void Board::reset(ofTexture* breakableTexture, ofTexture* solidTexture)
{
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			int i = y * BOARD_SIZE + x;
			explosions[i] = new Explosion();
			explosions[i]->setup(x, y);
			if (y == 0 | x == 0 |
				y == BOARD_SIZE - 1 | x == BOARD_SIZE - 1) {
				blocks[i] = new Block(false, solidTexture);
				blocks[i]->setup(x, y, true);
			}
			else if (y % 2 == 0 &&
				x % 2 == 0) {
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
			if (blocks[i]->triggerExplosion) {
				blocks[i]->hide();
				explosions[i]->explode();
				//Down casting to bomb and pass across. Noting previous trigger check we can ensure safety.
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
			break;

		if (blocks[i]->breakable) {
			blocks[i]->hide();
			blocks[i] = new GridItem();
			piercing--;
		}
		else if (!blocks[i]->canTraverse()) {
			break;
		}
		explosions[i]->explode();
	}
}

void Board::destroyBlock(int x, int y)
{
	if (x <= BOARD_SIZE - 1 & y <= BOARD_SIZE - 1 & x >= 0 & y >= 0) {
		int i = y * BOARD_SIZE + x;
		blocks[i]->hide();
		explosions[i]->explode();
		blocks[i] = new GridItem();
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

void Board::addBomb(int x, int y, Bomb* bomb)
{
	if (x > BOARD_SIZE - 1 | y > BOARD_SIZE - 1 | x < 0 | y < 0)
		return;
	int i = y * BOARD_SIZE + x;
	blocks[i] = bomb;
	blocks[i]->setup(x, y, true);
}