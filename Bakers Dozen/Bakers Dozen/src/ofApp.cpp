#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofDisableArbTex();

	ground.set(34, 34, 8, 8);
	ground.rotateDeg(90, 1, 0, 0);
	ground.setPosition(0, 1, 0);
	ground.mapTexCoords(0, 0, 17, 17);

	cam.setNearClip(0);
	cam.setFarClip(500);
	cam.setPosition(1, -27.5, 10);
	cam.lookAt(glm::vec3(1, 1, 2.75));
	cam.setVFlip(true);

	ofLoadImage(floorImage, "floor.png");
	floorImage.setTextureWrap(GL_REPEAT, GL_REPEAT);
	floorImage.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	ofLoadImage(blockImage, "crate.png");
	blockImage.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	board = new Board();

	astar = new AStar(board);

	players[0] = new Character("player1.obj", board);
	players[1] = new AICharacter("player2.obj", board, astar);
	players[2] = new AICharacter("player3.obj", board, astar);
	players[3] = new AICharacter("player4.obj", board, astar);

	light.setPosition(0, -30, 0);
	light.lookAt(glm::vec3(0, 1, 0));

	text.load("pixels.ttf", 65, false);
	instructions.load("pixels.ttf", 40, false);
	ending.load("pixels.ttf", 80, false);

	logo.load("logo.png");
	bread.load("bread.png");

	buttons.setup(&instructions, ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() - 180, 600, 60);
	buttons.add("Play");
	buttons.add("Quit");

	retry.setup(&instructions, ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() - 300, 600, 60);
	retry.add("Retry");
	retry.add("Back");

	deathSound.load("death.mp3");
	deathSound.setMultiPlay(true);
	explosionSound.load("explosion.mp3");
	explosionSound.setMultiPlay(true);
	powerupSound.load("powerup.mp3");
	powerupSound.setMultiPlay(true);
	walkSound.load("walk.mp3");
	walkSound.setMultiPlay(true);
	refillSound.load("refill.mp3");
	refillSound.setMultiPlay(true);

	themeMusic.load("theme.mp3");
	themeMusic.setLoop(INFINITE);
	themeMusic.setVolume(0.85);
	gameMusic.load("game.mp3");
	gameMusic.setLoop(INFINITE);
	gameMusic.setVolume(0.85);

	board->setSounds(&explosionSound);
	players[0]->setSounds(&walkSound, &powerupSound, &refillSound);
	players[1]->setSounds(&walkSound, &powerupSound, &refillSound);
	players[2]->setSounds(&walkSound, &powerupSound, &refillSound);
	players[3]->setSounds(&walkSound, &powerupSound, &refillSound);

	start();
}

void ofApp::start()
{
	light.disable();
	ofDisableLighting();
	currentScene = Menu;
	ofResetElapsedTimeCounter();
	themeMusic.play();
}

void ofApp::begin()
{
	df = 0;
	won = false;
	ofEnableLighting();
	light.enable();
	board->reset(&blockImage, &floorImage);
	players[0]->setup(1, 1);
	players[1]->setup(15, 15);
	players[2]->setup(1, 15);
	players[3]->setup(15, 1);
	themeMusic.stop();
	gameMusic.play();
	currentScene = Game;
	ofResetElapsedTimeCounter();
}

void ofApp::death(bool won)
{
	gameMusic.stop();
	ofResetElapsedTimeCounter();
	this->won = won;
	endText = won ? "SUCCESS\nYou now hold the monopoly for baked goods!" : "FAILED\nNow all the other bakers\nwill be taking your business!";
	currentScene = End;
}

void ofApp::update(){
	float deltaTime = ofGetLastFrameTime();
	switch (currentScene) {
	case Menu:
		if (ofGetElapsedTimeMillis() > 100) {
			if (buttons.get("Play")) {
				begin();
			}
			else if (buttons.get("Quit")) {
				ofExit();
			}
		}
		break;
	case End:
		df += deltaTime;
		if (df > 4.2) {
			if (retry.get("Retry")) {
				begin();
			}
			else if (retry.get("Back")) {
				start();
				return;
			}
		}
		deltaTime /= 15;
	case Game:
		players[0]->sendMove(keys[OF_KEY_RIGHT] - keys[OF_KEY_LEFT], keys[OF_KEY_DOWN] - keys[OF_KEY_UP]);
		if (keys[32]) {
			players[0]->placeBomb();
			keys[32] = false;
		}

		board->update(deltaTime);

		//Brute force player deaths.
		for (int y = 0; y < BOARD_SIZE; y++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				Explosion* explosion = board->getExplosionAt(x, y);
				if (explosion->exploded) {
					for (Character* player : players) {
						glm::vec3 pos = player->getPosition();
						if (round(pos.x) == x && round(pos.z) == y) {
							player->kill();
							deathSound.play();
						}
					}
					explosion->exploded = false;
				}
			}
		}

		players[0]->update(deltaTime);
		players[1]->update(deltaTime);
		players[2]->update(deltaTime);
		players[3]->update(deltaTime);

		if (players[0]->getLiving()
			&& !players[1]->getLiving()
			&& !players[2]->getLiving()
			&& !players[3]->getLiving()) {
			death(true);
		}
		else if (!players[0]->getLiving()) {
			death(false);
		}
		break;
	}
}

void ofApp::draw(){
	switch (currentScene) {
	case Menu:
		ofBackground(0);
		ofSetColor(80, 80, 100);
		instructions.drawStringCenteredHorizontally("Baking is a competitive industry and desperate times call for desperate measures...\nBake up some bread bombs to take down your baker foes\nRemember to stock up by revisiting your oven.\nUse the arrows keys to move and spacebar to place a bomb.\nCollect sugar to increase power and yeast to break through more blocks.",
			ofGetWindowWidth() / 2 + 1, ofGetWindowHeight() / 2 + 1);
		ofSetColor(100, 100, 150);
		instructions.drawStringCenteredHorizontally("Baking is a competitive industry and desperate times call for desperate measures...\nBake up some bread bombs to take down your baker foes\nRemember to stock up by revisiting your oven.\nUse the arrows keys to move and spacebar to place a bomb.\nCollect sugar to increase power and yeast to break through more blocks.",
			ofGetWindowWidth()/2, ofGetWindowHeight()/2);
		ofSetColor(255);
		logo.draw(ofGetWindowWidth() / 2 - 283, 50 + sin(ofGetElapsedTimeMillis() / 1000.0) * 20);
		buttons.draw();
		break;
	case End:
	case Game:
		ofClear(0);
		cam.begin();
		ofEnableDepthTest();
		ofPushMatrix();

		floorImage.bind();
		ofSetColor(150);
		ground.draw();
		floorImage.unbind();

		board->draw();

		players[0]->draw();
		players[1]->draw();
		players[2]->draw();
		players[3]->draw();

		ofPopMatrix();
		ofDisableDepthTest();
		cam.end();

		ofSetColor(30);
		text.drawString("BOMBS:", 55, 102);
		text.drawString("SUGAR: " + std::to_string(players[0]->getPower()), 55, 172);
		text.drawString("YEAST: " + std::to_string(players[0]->getPiercing()), 55, 242);
		ofSetColor(255);
		text.drawString("BOMBS:", 50, 107);
		text.drawString("SUGAR: " + std::to_string(players[0]->getPower()), 50, 177);
		text.drawString("YEAST: " + std::to_string(players[0]->getPiercing()), 50, 247);
		for (int i = 0; i < players[0]->getBombsAvailable(); i++) {
			bread.draw(260 + 70 * i, 50, 60, 60);
		}
		break;
	}
	if (currentScene == End) {
		ofSetColor(0, 0, 0, 255 * (df <= 3 ? df / 3 : 1));
		ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		ofSetColor(80, 80, 100, 255 * (df <= 3 ? df / 3 : 1));
		ending.drawStringCentered(endText,
			ofGetWindowWidth() / 2 + 4, ofGetWindowHeight() / 2 + 4);
		ofSetColor(100, 100, 150, 255 * (df <= 3 ? df / 3 : 1));
		ending.drawStringCentered(endText,
			ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
		if (df > 4.2) {
			retry.draw();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	keys[key] = 1;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	keys[key] = 0;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	buttons.setup(&instructions, ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() - 180, 600, 60);
	retry.setup(&instructions, ofGetWindowWidth() / 2 - 300, ofGetWindowHeight() - 300, 600, 60);
}
