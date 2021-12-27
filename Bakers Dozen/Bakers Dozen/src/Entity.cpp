#include "Entity.h"

Entity::Entity(std::string url) : renderer(Renderer(url)), transform(ofVec3f()) {}

void Entity::start() {}

void Entity::update(float deltaTime) {}

void Entity::draw() {
	renderer.draw(transform.position, transform.rotation, transform.angle, transform.scale);
}