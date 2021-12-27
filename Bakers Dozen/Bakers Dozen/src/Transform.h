#include "ofVec3f.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform {
public:
	Transform(ofVec3f startPosition);

	void setPosition(ofVec3f position);
	void setRotation(ofVec3f rotation);
	void setScale(ofVec3f scale);

	ofVec3f position, rotation, scale;
	float angle;
};

#endif // TRANSFORM_H