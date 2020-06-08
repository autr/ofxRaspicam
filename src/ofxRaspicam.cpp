#include "ofxRaspicam.h"


// static void ofxRaspicam::callback(void *arg) {

// 	ofxRaspicam * self = (ofxRaspicam *) arg;
// }


void ofxRaspicam::threadedFunction() {

    // start

    while(isThreadRunning()) {


		if (camera.grab()) {
	        lock();
			// camera.retrieve ( data, raspicam::RASPICAM_FORMAT_IGNORE );
		    image.setFromPixels( camera.getImageBufferData(), camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);
	    	newFrame = true;
	        unlock();
	    }
    }

    // done
}
void ofxRaspicam::open( int w, int h) {
	if ( !camera.open()) {
		ofLogError("ofxRaspicam") << "error opening...";
		return;
	} else {
		inited = true;
	}
	newFrame = false;
	// camera.setUserCallback(callback, this);
	camera.setFrameRate( 30 );
	camera.setCaptureSize(w, h);

	/*
		TODO: 

		SENSOR_MODES

		?



	*/
	width = w;
	height = h;
	camera.setSensorMode(4);

	camera.setFormat( raspicam::RASPICAM_FORMAT_BGR );
	data = new unsigned char[  camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
	ofLogNotice("ofxRaspicam") << "sleeping for 3 seconds...";
	sleep(3);

	ofLogNotice("ofxRaspicam") << "starting thread...";
	setThreadName("ofxRaspicam");
	startThread(true);

}