#pragma once

#include "ofMain.h"
#include "ofVec3f.h"
#include "Block.h"
#include "AICharacter.h"
#include "Board.h"
#include "Explosion.h"
#include "AStar.h"

#ifndef OFAPP_H
#define OFAPP_H

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);

		ofCamera cam;
		ofPlanePrimitive ground;
		ofTexture blockImage, floorImage;
		ofLight light;

		AStar* astar;

		Board* board;

		Character* players[4];

		Explosion* exp;

		unsigned int keys[65536];
};

#endif // OFAPP_H