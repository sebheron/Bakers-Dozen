#include "Character.h"

Character::Character() : scale(glm::vec3(1, 1, 1))
{
	model.loadModel("bear.obj", 20);
	model.setScaleNormalization(false);
}

void Character::update(float deltaTime) {}

void Character::draw() {
	model.setPosition(position.x, position.y, position.z);
	model.setRotation(0, angle, rotation.x, rotation.y, rotation.z);
	model.setScale(scale.x, scale.y, scale.z);
	model.drawFaces();
}

void Character::setPosition(float x, float y, float z)
{
	//Set the position.
	position = glm::vec3(x, y, z);
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
		this->rotation = glm::vec3(x / angle, y / angle, z / angle);
	}
	else {
		this->rotation = glm::vec3(x, y, z);
	}
}

void Character::setScale(float x, float y, float z)
{
	//Half the scale.
	this->scale = glm::vec3(x * 0.5f, y * 0.5f, z * 0.5f);
}