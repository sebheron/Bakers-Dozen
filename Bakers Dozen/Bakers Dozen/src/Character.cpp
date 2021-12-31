#include "Character.h"

Character::Character(std::string file, Board* board)
{
	this->board = board;
	model.loadModel(file, 20);
	model.setScaleNormalization(false);
	model.setScale(2.5, 2.5, 2.5);
}

void Character::setup(int x, int y, bool active)
{
	GridItem::setup(x, y, active);
	position = glm::vec3(x, 0, y);
	bombs.push_front(new Bomb());
	moving = false;
}

void Character::update(float deltaTime)
{
	if (moving) {
		jumpTo(glm::vec3(x, 0, y), deltaTime * 10);
	}
}

void Character::sendMove(int x, int y) {
	if (!moving && (x != 0 || y != 0) && abs(x) + abs(y) < 2) {
		if (board->checkPlaceBlocked(this->x + x, this->y + y))
			return;

		prevX = this->x;
		prevY = this->y;

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
	for (Bomb* bomb : bombs) {
		//Check for the unlikely event that a bomb has been placed below the characters feet.
		if (!board->checkPlaceBlocked(prevX, prevY)
			&& bomb->triggerExplosion) {
			bomb->triggerExplosion = false;
			board->addBomb(prevX, prevY, bomb);
		}
	}
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
		position = glm::vec3(x, 0, y);
		prevX = x;
		prevY = y;
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
