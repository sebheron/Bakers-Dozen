#include "PanelButtons.h"

void PanelButtons::mouseMoved(ofMouseEventArgs & mouse)
{
	mpos = mouse;
}

void PanelButtons::mousePressed(ofMouseEventArgs & mouse)
{
	if (mouse.x > x && mouse.x < x + w) {
		int i = 0;
		for (std::unordered_map<string, bool>::iterator iter = buttons.begin(); iter != buttons.end(); ++iter) {
			if (mouse.y > y + i * h && mouse.y < y + (i + 1) * h && mouse.button == 0) {
				iter->second = true;
			}
			i++;
		}
	}
}

void PanelButtons::mouseReleased(ofMouseEventArgs & mouse)
{
	for (std::unordered_map<string, bool>::iterator iter = buttons.begin(); iter != buttons.end(); ++iter) {
		iter->second = false;
	}
}

void PanelButtons::setup(ofxCenteredTrueTypeFont* font, float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->font = font;

	ofAddListener(ofEvents().mouseMoved, this, &PanelButtons::mouseMoved);
	ofAddListener(ofEvents().mousePressed, this, &PanelButtons::mousePressed);
	ofAddListener(ofEvents().mouseReleased, this, &PanelButtons::mouseReleased);
}

void PanelButtons::draw()
{
	int i = 0;
	for (std::unordered_map<string, bool>::iterator iter = buttons.begin(); iter != buttons.end(); ++iter) {
		if (mpos.x > x && mpos.x < x + w && mpos.y > y + i * h && mpos.y < y + (i + 1) * h) {
			ofSetColor(50, 50, 100);
		}
		else {
			ofSetColor(100, 100, 150);
		}
		ofDrawRectangle(x, y + i * h, w, h - 2);
		ofSetColor(50);
		font->drawStringCentered(iter->first, ofVec2f(x + w / 2, y + (i + 0.5) * h + 2));
		i++;
	}
}

void PanelButtons::add(string title)
{
	buttons.insert(std::pair<string, bool>(title, false));
}

bool PanelButtons::get(string title)
{
	return buttons.at(title);
}

PanelButtons::~PanelButtons()
{
	ofRemoveListener(ofEvents().mouseMoved, this, &PanelButtons::mouseMoved);
	ofRemoveListener(ofEvents().mousePressed, this, &PanelButtons::mousePressed);
	ofRemoveListener(ofEvents().mouseReleased, this, &PanelButtons::mouseReleased);
}
