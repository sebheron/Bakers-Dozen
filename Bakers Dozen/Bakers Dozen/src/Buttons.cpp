#include "Buttons.h"

void Buttons::mouseMoved(ofMouseEventArgs & mouse)
{
	mpos = mouse;
}

void Buttons::mousePressed(ofMouseEventArgs & mouse)
{
	if (mouse.button == 0) {
		if (mouse.x > x && mouse.x < x + w) {
			int i = 0;
			for (std::unordered_map<string, ofEvent<ofEventArgs>*>::iterator iter = buttons.begin(); iter != buttons.end(); ++iter) {
				if (mouse.y > i * h && mouse.y < (i + 1) * h) {
					iter->second->notify(ofEventArgs());
				}
			}
		}
	}
}

void Buttons::setup(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y - 5;
	this->w = w;
	this->h = h;

	ofAddListener(ofEvents().mouseMoved, this, &Buttons::mousePressed);
	ofAddListener(ofEvents().mousePressed, this, &Buttons::mousePressed);
}

void Buttons::draw()
{
	int i = 0;
	for (std::unordered_map<string, ofEvent<ofEventArgs>*>::iterator iter = buttons.begin(); iter != buttons.end(); ++iter) {
		if (mpos.x > x && mpos.x < x + w && mpos.y > i * h && mpos.y < (i + 1) * h) {
			ofSetColor(255);
		}
		else {
			ofSetColor(120);
		}
		ofDrawRectangle(x, y * i + 5, w, h);
	}
}

void Buttons::add(string title, ofEvent<ofEventArgs>* e)
{
	buttons.insert(std::pair<string, ofEvent<ofEventArgs>*>(title, e));
}