#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.open(720,576);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.draw(0,0,ofGetWidth(),ofGetHeight());
	ofDrawBitmapStringHighlight( ofToString(ofGetFrameRate()), 10, 10 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}