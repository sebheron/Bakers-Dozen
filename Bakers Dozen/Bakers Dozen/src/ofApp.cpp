#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableDepthTest();

	ground.set(34, 34, 8, 8);
	ground.rotateDeg(90, 1, 0, 0);
	ground.setPosition(0, 1, 0);
	ground.mapTexCoords(0, 0, 17, 17);

	cam.setNearClip(0);
	cam.setFarClip(500);
	cam.setPosition(1, -27.5, 10);
	cam.lookAt(glm::vec3(1, 1, 2.75));
	cam.setVFlip(true);

	ofDisableArbTex();

	ofLoadImage(floorImage, "floor.png");
	floorImage.setTextureWrap(GL_REPEAT, GL_REPEAT);
	floorImage.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	ofLoadImage(blockImage, "crate.png");
	blockImage.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	board = new Board();
	board->reset(&blockImage, &floorImage);

	players[0] = new Character("player1.obj", board);
	players[1] = new Character("player2.obj", board);
	players[2] = new Character("player3.obj", board);
	players[3] = new Character("player4.obj", board);
	players[0]->setup(1, 1, true);
	players[1]->setup(14, 14, true);
	players[2]->setup(1, 14, true);
	players[3]->setup(14, 1, true);

	exp = new Explosion();

	light.enable();
	light.setPosition(0, -30, 0);
	light.lookAt(glm::vec3(0, 1, 0));

	ofResetElapsedTimeCounter();
}

void ofApp::update(){
	float deltaTime = ofGetLastFrameTime();

	int x = keys[OF_KEY_RIGHT] - keys[OF_KEY_LEFT];
	int y = keys[OF_KEY_DOWN] - keys[OF_KEY_UP];
	bool bomb = keys[OF_KEY_RIGHT_SHIFT];

	players[0]->sendMove(x, y);
	if (bomb) {
		players[0]->placeBomb();
	}

	exp->update(deltaTime);

	players[0]->update(deltaTime);
	players[1]->update(deltaTime);
	players[2]->update(deltaTime);
	players[3]->update(deltaTime);

	board->update(deltaTime);
}

void ofApp::draw(){
	ofClear(50, 50, 50);
	cam.begin();
	ofPushMatrix();
	
	floorImage.bind();
	ofSetColor(255);
	ground.draw();
	floorImage.unbind();
	
	board->draw();
	exp->draw();

	players[0]->draw();
	players[1]->draw();
	players[2]->draw();
	players[3]->draw();

	ofPopMatrix();
	cam.end();
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
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	exp->setup(0, 0);
	exp->explode();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
