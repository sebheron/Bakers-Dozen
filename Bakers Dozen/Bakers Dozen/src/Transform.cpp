#include "Transform.h"

Transform::Transform(ofVec3f startPosition) : position(startPosition), scale(0.5, 0.5, 0.5) {}

void Transform::setPosition(ofVec3f position)
{
	//Set the position.
	this->position = position;
}

void Transform::setRotation(ofVec3f rotation)
{
	//Find largest angle.
	if (rotation.x > rotation.y) {
		angle = rotation.x;
	}
	else {
		angle = rotation.y;
	}
	if (rotation.z > angle) {
		angle = rotation.z;
	}

	//If we need to set an angle.
	if (angle > 0){
		//Calculate rotation according to angle.
		this->rotation = ofVec3f(rotation.x / angle, rotation.y / angle, rotation.z / angle);
	}
	else {
		this->rotation = rotation;
	}
}

void Transform::setScale(ofVec3f scale)
{
	//Half the scale.
	this->scale = scale * 0.5;
}
