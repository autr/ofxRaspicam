#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);
    ofLog::setAutoSpace(true);
	grabber.listDevices();
	// ofSetFrameRate(60);
	cam.open(1280, 760);
	gui.setup( cam.group );
}

//--------------------------------------------------------------
void ofApp::update(){

	if (cam.isFrameNew()) {
		float t = ofGetElapsedTimef();
		cam.lock();
		copy = cam.image;
		cam.unlock();
		ofLog() << "FPS " << 1.0/(t-stamp);
		stamp = t;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	copy.draw(0,0,ofGetWidth(),ofGetHeight());
	ofDrawBitmapStringHighlight( ofToString(ofGetFrameRate()), 240, 20 );
	gui.draw();
}

void ofApp::exit() {
	cam.close(); // zehr wichtig
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') ofToggleFullscreen();
	if (key == 'p') cam.printInfo();
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