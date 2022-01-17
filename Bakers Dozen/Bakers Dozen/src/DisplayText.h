#pragma once

#include "ofMain.h"

#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

class DisplayText {
private:
	int size;
	float offsetX, offsetY;
	int r1, g1, b1, r2, g2, b2;
	ofTrueTypeFont font;
public:
	void setup(string path, int size);
	void setFirstColor(int r, int g, int b);
	void setSecondColor(int r, int g, int b);
	void drawText(string text, float x, float y);
};

#endif // DISPLAYTEXT_H
