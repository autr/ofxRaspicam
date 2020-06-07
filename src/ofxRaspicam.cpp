#include "ofxRaspicam.h"

void ofxRaspicam::open( int w, int h) {
	if ( !camera.open()) {
		ofLogError("ofxRaspicam") << "error opening...";
		return;
	}
	data = new unsigned char[  camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
	ofLogNotice("ofxRaspicam") << "sleeping for 3 seconds...";
	sleep(3);

}


void ofxRaspicam::update() {

	camera.grab();
	camera.retrieve ( data, raspicam::RASPICAM_FORMAT_RGB ); 
    image.setFromPixels( data, camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);

}