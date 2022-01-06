#include "Character.h"

std::vector<Character*> Character::players;

Character::Character(std::string file, Board* board) : Point::Point()
{
	players.push_back(this);
	id = players.size();
	this->board = board;
	p_model.loadModel(file, 20);
	p_model.setScaleNormalization(false);
	p_model.setScale(2.5, 2.5, 2.5);
	r_model.loadModel("oven.obj", 20);
	r_model.setScaleNormalization(false);
	r_model.setScale(0.9, 0.9, 0.9);
}

void Character::setup(int x, int y)
{
	power = 1;
	piercing = 0;
	startX = x;
	startY = y;
	this->x = startX;
	this->y = startY;
	r_model.setPosition(startX * 2 - 15, -0.75, startY * 2 - 15);
	position = glm::vec3(x, 0, y);
	moving = false;
	living = true;
}

void Character::setSounds(ofSoundPlayer * walkSound, ofSoundPlayer* powerupSound, ofSoundPlayer* refillSound)
{
	this->walkSound = walkSound;
	this->powerupSound = powerupSound;
	this->refillSound = refillSound;
}

void Character::update(float deltaTime)
{
	if (!living)
		return;
	if (moving) {
		jumpTo(glm::vec3(x, 0, y), deltaTime * 10);
	}
	else if (x == startX && y == startY && bombs.empty()) {
		bombs.push(new PocketBomb{ power, piercing });
		bombs.push(new PocketBomb{ power, piercing });
		bombs.push(new PocketBomb{ power, piercing });
		refillSound->play();
	}
}

bool Character::sendMove(int x, int y) {
	if (!living)
		return false;
	if (!moving && (x != 0 || y != 0) && abs(x) + abs(y) < 2) {
		if (board->checkPlaceBlocked(this->x + x, this->y + y))
			return false;

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
		walkSound->play();
		moving = true;
	}

	return true;
}

void Character::placeBomb()
{
	if (!living)
		return;
	if (!bombs.empty()) {
		PocketBomb* bomb = bombs.top();
		//Check for the unlikely event that a bomb has been placed below the characters feet.
		if (!board->checkPlaceBlocked(x, y)) {
			board->addBomb(x, y, bomb->power, bomb->piercing, p_model.getRotationAngle(0));
			bombs.pop();
		}
	}
}

void Character::takePickup(Pickup* pickup)
{
	PickupType type = pickup->getType();
	switch (type) {
	case powerup:
		power++;
		break;
	case pierce:
		piercing++;
		break;
	}
	powerupSound->play();
	pickup->smash();
}

void Character::draw() {
	if (living) {
		p_model.setPosition(position.x * 2 - 15, position.y + 0.2, position.z * 2 - 15);
		p_model.drawFaces();
		if (bombs.empty()) {
			r_model.setRotation(0, ofGetElapsedTimeMillis() / 150, 0, 1, 0);
			r_model.drawFaces();
		}
	}
}

void Character::kill()
{
	living = false;
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

	if (abs(dx) < 0.05f && abs(dz) < 0.05f) {
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
		p_model.setRotation(0, angle, x / angle, y / angle, z / angle);
	}
	else {
		p_model.setRotation(0, angle, x, y, z);
	}
}

void Character::setScale(float x, float y, float z)
{
	//Half the scale.
	p_model.setScale(x * 2.5, y * 2.5, z * 2.5);
}

bool Character::getLiving()
{
	return living;
}

glm::vec3 Character::getPosition()
{
	return position;
}

int Character::getId()
{
	return id;
}

int Character::getBombsAvailable()
{
	return bombs.size();
}
