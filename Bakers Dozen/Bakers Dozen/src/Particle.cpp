#include "Particle.h"

Particle::Particle() {}

void Particle::setup(float x, float y, ParticleColor color, float fx, float fy, float fz, float lifetime)
{
	position = glm::vec3(x * 2 - 15, -0.5, y * 2 - 15);
	switch (color) {
	case red:
		g = 0;
		break;
	case yellow:
		g = 255;
		break;
	}
	this->fx = fx;
	this->fy = fy;
	this->fz = fz;
	this->lifetime = lifetime;
}

void Particle::update(float deltaTime)
{
	lifetime -= deltaTime;
	position.x += fx * deltaTime;
	position.y += fy * deltaTime;
	position.z += fz * deltaTime;
}

void Particle::draw()
{
	ofSetColor(255, g, 0);
	ofDrawSphere(position, 0.75 * lifetime);
}
