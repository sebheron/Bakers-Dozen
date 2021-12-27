#include "Baker.h"

Baker::Baker(std::string url) : Entity(url) {}

void Baker::start()
{
	transform.setPosition(ofVec3f(500, 500));
	transform.setRotation(ofVec3f(0, 0, 0));
}

void Baker::update(float deltaTime)
{
	transform.setRotation(ofVec3f(0, transform.rotation.y + deltaTime, 0));
}