#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include "raspicam/raspicam.h"
#include "raspicam/raspicamrawbuffer.h"
#include "ofMain.h"

class ofxRaspicam;
#include "ofxRaspicamDef.h"
#include "ofxRaspicamCtrl.h"

using namespace std;


class ofxRaspicam : ofThread {

public:

    // use this to control ofxRaspiCam, for example:

    ofxRaspicamCtrl ctrl; 

    /*
        ofxRaspicam cam;
        cam.ctrl.width = 1280;
        cam.ctrl.height = 720;
        cam.ctrl.shutter = 1;
        cam.ctrl.enable = true;

        or

        ofxRaspicam cam;
        ofxPanel gui;
        gui.setup( cam.ctrl.ui );

    */


    ofxRaspicam();
    ~ofxRaspicam();

    // core funcs

    void open();
    void close();
    ofTexture & syncToTexture( ofTexture & texture );

    // utility functions

    raspicam::RaspiCam & getInternal();
    
    int getActualFPS() {
        return actualFPS;
    }

    bool isFrameNew() {

    	if (newFrame) {
    		newFrame = false;
    		return true;
    	} else {
    		return false;
    	}
    }

    int getWidth();

    int getHeight();

	bool isOpen();

    void printInfo() {

        ofLogNotice("ofxRaspicam") << getInfoString();
    }


    static string humanShutterSpeed( int microseconds ) {
        float v = (1000000.0 / (float)microseconds);
        if (v < 0.0) {
            v = 60 / 60 / v;
            return ofToString(v)+"s";
        } else {
            return "1/"+ofToString(v)+"s";
        }
    }

    string getInfoString();

    // settings strings...

    static string RASPICAM_FORMAT_STR(int i);
    static string RASPICAM_EXPOSURE_STR(int i);
    static string RASPICAM_AWB_STR(int i);
    static string RASPICAM_IMAGE_EFFECT_STR(int i);
    static string RASPICAM_METERING_STR(int i);
    static string RASPICAM_ENCODING_STR(int i);

    // presets info...

    static string RASPICAM_MODEL_STR(int i);
    static string RASPICAM_PRESETS_STR(int i, int ii);
    static vector<int> RASPICAM_PRESETS_DEF(int i, int ii);
    static int RASPICAM_PRESETS_SIZE(int i);

    int width, height;

    bool debugNoGrab;


private:

    void threadedFunction();

    raspicam::RaspiCamRawBuffer rawbuffer;
    raspicam::RaspiCam obj;
    ofPixels pixels;
    unsigned char * buffer;

    float timer; // timestamp
    float actualFPS; // how fast is it actually grabbing?

    bool newFrame; // once buffer has been copied

    static bool isClosing();
    static void setClosingFlag( bool b);
    // core functions...

    static void onRawBufferCallback(const raspicam::RaspiCamRawBuffer& _buffer, void* _thisVoid);
    static void onCaptureBufferCallback(void *arg);
    void processCallback(unsigned char * _buffer);

    ofTexture * texturePtr;

    void init();
    void release();
};


