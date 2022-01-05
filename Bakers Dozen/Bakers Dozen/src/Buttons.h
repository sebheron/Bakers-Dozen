#pragma once

#include "ofMain.h"
#include "ofEvents.h"

#ifndef BUTTONS_H
#define BUTTONS_H

class Buttons {
private:
	void mouseMoved(ofMouseEventArgs & mouse);
	void mousePressed(ofMouseEventArgs & mouse);

	float x, y, w, h;

	glm::vec2 mpos;

	std::unordered_map<string, ofEvent<ofEventArgs>*> buttons;
public:
	void setup(float x, float y, float w, float h);
	void draw();
	void add(string title, ofEvent<ofEventArgs>* e);
};

#endif // BUTTONS_H