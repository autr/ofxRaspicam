#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofLog::setAutoSpace(true);
	of.listDevices();
	// cam.open();
	showGui = false;
	// texture.allocate(cam.getWidth(), cam.getHeight(), GL_RGB);
	drawTexture = true;
}

//--------------------------------------------------------------
void ofApp::update(){

	cam.syncToTexture( texture );
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	if (texture.isAllocated() && drawTexture) texture.draw(0,0,ofGetWidth(),ofGetHeight());
	// ofDrawBitmapString( "f = fullscreen, p = print info, g = toggle gui", 10, 10 );
	// ofDrawBitmapString( "1 = grab ctrls, 2 = cam ctrls, 3 = extra ctrls", 10, 30 );
	ofDrawBitmapString( cam.getInfoString(), 10, 15 );
	ofDrawBitmapString( cam.debugNoGrab, 10, 30 );
	if (showGui) {
		gui.draw();
	}
}

void ofApp::exit() {
	cam.close(); // zehr wichtig
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') ofToggleFullscreen();
	if (key == 'p') cam.printInfo();
	if (key == '1'||key == '2'||key == '3'||key=='4') {
		gui.clear();
		if (key=='1') gui.setup( cam.ctrl.groupA );
		if (key=='2') gui.setup( cam.ctrl.groupB );
		if (key=='3') gui.setup( cam.ctrl.groupC );
		if (key=='4') gui.setup( cam.ctrl.groupD );
		gui.setPosition( ofGetWidth() - 200 , 0 );
		showGui = true;
	}
	if (key == '5') showGui = false;
	if (key == 'd') cam.debugNoGrab = !cam.debugNoGrab;
	if (key == 's') drawTexture = !drawTexture;
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