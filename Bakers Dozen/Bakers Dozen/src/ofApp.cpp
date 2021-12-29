#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableDepthTest();

	ofLoadImage(floorImage, "floor.png");
	floorImage.setTextureWrap(GL_REPEAT, GL_REPEAT);
	floorImage.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	ofLoadImage(blockImage, "crate.png");
	blockImage.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	auto center = glm::vec3(0, 1, 0);

	ground.set(32, 32, 8, 8);
	ground.rotateDeg(90, 1, 0, 0);
	ground.setPosition(center);
	ground.mapTexCoords(0, 0, 16, 16);

	cam.setNearClip(0);
	cam.setFarClip(500);
	cam.setPosition(0, -22, 27);
	cam.lookAt(center);
	cam.setVFlip(true);

	ofDisableArbTex();

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			if (y == 0 | x == 0 |
				y == 15 | x == 15) {
				blocks[y * 16 + x].set(x, y, true);
			}
			else if (y % 2 == 0 &&
				x % 2 == 0) {
				blocks[y * 16 + x].set(x, y, true);
			}
		}
	}

	bakers[0].transform.setPosition();
	bakers[0].transform.setPosition();
	bakers[0].transform.setPosition();

	light.enable();
	light.setPosition(0, -30, 0);
	light.lookAt(center);

	ofResetElapsedTimeCounter();
}

void ofApp::update(){
	float deltaTime = ofGetLastFrameTime();
}

void ofApp::draw(){
	ofClear(255, 255, 255);
	cam.begin();
	ofPushMatrix();
	
	floorImage.bind();
	ground.draw();
	floorImage.unbind();
	
	blockImage.bind();
	for (int i = 0; i < 256; i++) {
		blocks[i].draw();
	}
	blockImage.unbind();

	ofPopMatrix();
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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