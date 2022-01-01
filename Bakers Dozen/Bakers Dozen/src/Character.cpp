#include "Character.h"

Character::Character(std::string file, Board* board)
{
	players.push_front(this);
	power = 1;
	piercing = 0;
	this->board = board;
	model.loadModel(file, 20);
	model.setScaleNormalization(false);
	model.setScale(2.5, 2.5, 2.5);
}

void Character::setup(int x, int y)
{
	this->x = x;
	this->y = y;
	position = glm::vec3(x, 0, y);
	bombs.push_front(new Bomb(&power, &piercing));
	moving = false;
	living = true;
}

void Character::update(float deltaTime)
{
	if (!living)
		return;
	if (moving) {
		jumpTo(glm::vec3(x, 0, y), deltaTime * 10);
	}
}

void Character::sendMove(int x, int y) {
	if (!living)
		return;
	if (!moving && (x != 0 || y != 0) && abs(x) + abs(y) < 2) {
		if (board->checkPlaceBlocked(this->x + x, this->y + y))
			return;

		if (x > 0) {
			setRotation(0, 270, 0);
		}
		else if (x < 0) {
			setRotation(0, 90, 0);
		}
		else if (y > 0) {
			setRotation(0, 0, 0);
		}
		else {
			setRotation(0, 180, 0);
		}

		this->x += x;
		this->y += y;
		moving = true;
	}
}

void Character::placeBomb()
{
	if (!living)
		return;
	for (Bomb* bomb : bombs) {
		//Round the positions to provide a fluid positioning of the bombs.
		int roundedX = round(x);
		int roundedY = round(y);
		//Check for the unlikely event that a bomb has been placed below the characters feet.
		if (!board->checkPlaceBlocked(roundedX, roundedY)
			&& bomb->isExploding()) {
			bomb->explode(true);
			board->addBomb(roundedX, roundedY, bomb);
		}
	}
}

void Character::takePickup(Pickup* pickup)
{
	PickupType type = pickup->getType();
	switch (type) {
	case bomb:
		bombs.push_front(new Bomb(&power, &piercing));
		break;
	case powerup:
		power++;
		break;
	case pierce:
		piercing++;
		break;
	}
	pickup->smash();
}

void Character::draw() {
	model.setPosition(position.x * 2 - 15, position.y + 0.2, position.z * 2 - 15);
	model.drawFaces();
}

void Character::jumpTo(glm::vec3 b, float t) {
	float currentX = position.x * (1.f - t) + b.x * t;
	float currentZ = position.z * (1.f - t) + b.z * t;
	float dx = b.x - currentX;
	float dz = b.z - currentZ;
	float distance = sqrt(dx * dx + dz * dz);

	float animCo = -(sin((distance - 0.25) * 2 * PI) + 1) / 2;
	float currentY = animCo;
	setScale(1, 1 - animCo / 4, 1);
	position = glm::vec3(currentX, currentY, currentZ);

	if (abs(dx) < 0.05f & abs(dz) < 0.05f) {
		if (board->checkPlacePickup(x, y)) {
			takePickup((Pickup*)board->getGridItem(x, y));
		}
		position = glm::vec3(x, 0, y);
		moving = false;
	}
}

void Character::setRotation(float x, float y, float z)
{
	if (x > y) {
		angle = x;
	}
	else {
		angle = y;
	}
	if (z > angle) {
		angle = z;
	}

	//If we need to set an angle.
	if (angle > 0) {
		//Calculate rotation according to angle.
		model.setRotation(0, angle, x / angle, y / angle, z / angle);
	}
	else {
		model.setRotation(0, angle, x, y, z);
	}
}

void Character::setScale(float x, float y, float z)
{
	//Half the scale.
	model.setScale(x * 2.5, y * 2.5, z * 2.5);
}

glm::vec3 Character::getPosition()
{
	return position;
}

float Character::getPowerLevel() {
	float level = piercing + power + bombs.size();
	return level;
}