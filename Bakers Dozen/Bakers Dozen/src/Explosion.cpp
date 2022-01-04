#include "Explosion.h"

Explosion::Explosion() : exploded(false), time(0) {
	for (int i = 0; i < PARTICLE_COUNT; i++) {
		particles[i] = new Particle();
	}
}

void Explosion::setup(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Explosion::explode()
{
	for (int i = 0; i < PARTICLE_COUNT; i++) {
		float fx = Random::Range(-PARTICLE_SPEED, PARTICLE_SPEED);
		float fy = Random::Range(-PARTICLE_SPEED, PARTICLE_SPEED);
		float fz = Random::Range(-PARTICLE_SPEED, PARTICLE_SPEED);
		particles[i]->setup(x, y, i > PARTICLE_COUNT / 2 ? red : yellow, fx, fy, fz, PARTICLE_EMISSION_TIME);
	}
	exploded = true;
	time = PARTICLE_EMISSION_TIME;
}

void Explosion::update(float deltaTime)
{
	exploded = false;
	if (time > 0)
	{
		time -= deltaTime;
		for (int i = 0; i < PARTICLE_COUNT; i++) {
			particles[i]->update(deltaTime);
		}
	}
}

void Explosion::draw()
{
	if (time > 0) {
		for (int i = 0; i < PARTICLE_COUNT; i++) {
			particles[i]->draw();
		}
	}
}
