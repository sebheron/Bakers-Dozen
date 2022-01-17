#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofVec2f.h"
#include "ofxCenteredTrueTypeFont.h"

#ifndef PANELBUTTONS_H
#define PANELBUTTONS_H

class PanelButtons {
private:
	void mouseMoved(ofMouseEventArgs & mouse);
	void mousePressed(ofMouseEventArgs & mouse);
	void mouseReleased(ofMouseEventArgs & mouse);
	float x, y, w, h;
	glm::vec2 mpos;
	std::unordered_map<string, bool> buttons;
	ofxCenteredTrueTypeFont* font;
public:
	void setup(ofxCenteredTrueTypeFont* font, float x, float y, float w, float h);
	void draw();
	void add(string title);
	bool get(string title);

	~PanelButtons();
};

#endif // PANELBUTTONS_H