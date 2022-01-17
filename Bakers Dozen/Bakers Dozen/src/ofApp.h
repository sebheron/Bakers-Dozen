#pragma once

#include "ofMain.h"
#include "ofVec3f.h"
#include "Block.h"
#include "AICharacter.h"
#include "Board.h"
#include "Explosion.h"
#include "AStar.h"
#include "ofxCenteredTrueTypeFont.h"
#include "PanelButtons.h"

#ifndef OFAPP_H
#define OFAPP_H

enum Scene { Menu, Game, End };

class ofApp : public ofBaseApp{
	private:
		bool won;
		std::string endText;
		float df;
	public:
		void setup();
		void start();
		void begin();
		void death(bool won);
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

		Scene currentScene;

		//Menu
		ofImage logo;
		ofxCenteredTrueTypeFont instructions, ending;
		PanelButtons buttons, retry;

		//Game
		ofCamera cam;
		ofPlanePrimitive ground;
		ofTexture blockImage, floorImage;
		ofLight light;
		ofImage bread;
		ofTrueTypeFont text;
		ofSoundPlayer deathSound, explosionSound, refillSound, powerupSound, walkSound,
			themeMusic, gameMusic;

		AStar* astar;
		Board* board;
		Character* players[4];

		unsigned int keys[65536];
};

#endif // OFAPP_H