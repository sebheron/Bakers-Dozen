#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Random.h"

#ifndef EXPLOSION_H
#define EXPLOSION_H
#define PARTICLE_COUNT 5
#define PARTICLE_EMISSION_TIME 0.25
#define PARTICLE_SPEED 10

class Explosion {
private:
	Particle* particles[PARTICLE_COUNT];
	int x, y;
	float time;
public:
	Explosion();

	void setup(int x, int y);
	void explode();
	void update(float deltaTime);
	void draw();

	bool exploded;
};

#endif EXPLOSION_H
