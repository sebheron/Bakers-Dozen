#include <string>
#include "ofxAssimpModelLoader.h"
#include "ofVec3f.h"
#include "Transform.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
private:
	ofxAssimpModelLoader model;
	Transform* camera;
public:
	Renderer(std::string url);

	void draw(ofVec3f& position, ofVec3f& rotation, float& angle, ofVec3f& scale);

	bool show;
};

#endif // RENDERER_H