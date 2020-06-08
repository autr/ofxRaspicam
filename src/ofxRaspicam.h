#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <raspicam/raspicam.h>
#include "ofMain.h"

using namespace std;


/*

	TODO:

	RASPICAM_FORMAT_IGNORE - thread races

*/

class ofxRaspicam : public ofThread {
public:

	bool inited = false;
	ofParameterGroup group;
	int width, height;


	raspicam::RaspiCam camera;
	ofImage image;
    unsigned char * data;
    ofPixels pixels;
    ofTexture texture;
    bool newFrame;

    void threadedFunction();

    ofxRaspicam() {
    }

    ~ofxRaspicam() {
    	close();
    }

    void printInfo() {

        ofLogNotice("ofxRaspicam") << "format:" << camera.getFormat();
        ofLogNotice("ofxRaspicam") << "width:" << camera.getWidth();
        ofLogNotice("ofxRaspicam") << "height:" << camera.getHeight();
        ofLogNotice("ofxRaspicam") << "brightness:" << camera.getBrightness();
        ofLogNotice("ofxRaspicam") << "rotation:" << camera.getRotation();
        ofLogNotice("ofxRaspicam") << "ISO:" << camera.getISO();
        ofLogNotice("ofxRaspicam") << "sharpness:" << camera.getSharpness();
        ofLogNotice("ofxRaspicam") << "contrast:" << camera.getContrast();
        ofLogNotice("ofxRaspicam") << "saturation:" << camera.getSaturation();
        ofLogNotice("ofxRaspicam") << "shutter:" << camera.getShutterSpeed();
        ofLogNotice("ofxRaspicam") << "exposure:" << camera.getExposure();
        ofLogNotice("ofxRaspicam") << "AWB:" << camera.getAWB();
        ofLogNotice("ofxRaspicam") << "red:" << camera.getAWBG_red();
        ofLogNotice("ofxRaspicam") << "blue:" << camera.getAWBG_blue();
        ofLogNotice("ofxRaspicam") << "effect:" << camera.getImageEffect();
        ofLogNotice("ofxRaspicam") << "metering:" << camera.getMetering();
        ofLogNotice("ofxRaspicam") << "FPS:" << camera.getFrameRate();
        ofLogNotice("ofxRaspicam") << "horz:" << camera.isHorizontallyFlipped();
        ofLogNotice("ofxRaspicam") << "vert:" << camera.isVerticallyFlipped();
    }

    bool isFrameNew() {

    	// ofLog() << "???" << camera.getFormat() << camera.getWidth() << camera.getHeight() << width << height;
    	if (newFrame) {
    		newFrame = false;
    		return true;
    	} else {
    		return false;
    	}
    }

	void open( int w, int h);

	void close() {
		stopThread();
    	camera.release();
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

	void draw( ofRectangle rect ) {
		image.draw(rect);
	}
	void draw( int x, int y, int w, int h ) {
		image.draw(x,y,w,h);
	}
};