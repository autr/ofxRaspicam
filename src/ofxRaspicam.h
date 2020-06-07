#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <raspicam/raspicam.h>
#include "ofMain.h"

using namespace std;

class ofxRaspicam {
public:

	bool inited = false;
	ofParameterGroup group;
	ofParameter<bool> useTexture;

	raspicam::RaspiCam camera;
	ofImage image;
    unsigned char * data;
    ofPixels pixels;

    ofxRaspicam() {
    	group.add( useTexture.set("useTexture", true) );
    }

    ~ofxRaspicam() {
    }

	void open( int w, int h);

	void close() {
		inited = false;
	}

	bool isOpen() {
		return inited;
	}

	unsigned char & getData() {
		return * data;
	}

	ofTexture & getTexture() {
		return image.getTexture();
	}
	ofPixels & getPixels() {
		return image.getPixels();
	}


	void update();

	void draw( ofRectangle rect ) {
		image.draw(rect);
	}
	void draw( int x, int y, int w, int h ) {
		image.draw(x,y,w,h);
	}
};