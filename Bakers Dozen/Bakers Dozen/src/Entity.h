#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "Transform.h"
#include "Renderer.h"
#include <string>

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity(std::string url);

	virtual void start();
	virtual void update(float deltaTime);
	void draw();

	Transform transform;
	Renderer renderer;
};

#endif // ENTITY_H