#pragma once

#include "ofMain.h"
#include "ofVec3f.h"

#ifndef PARTICLE_H
#define PARTICLE_H

enum ParticleColor { red, yellow };

class Particle {
private:
	glm::vec3 position;
	float fx, fy, fz, lifetime;
	int g;
public:
	Particle();
	void setup(float x, float y, ParticleColor color, float fx, float fy, float fz, float lifetime);
	void update(float deltaTime);
	void draw();
};

#endif PARTICLE_H
