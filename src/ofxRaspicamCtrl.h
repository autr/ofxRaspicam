#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include "raspicam/raspicam.h"
#include "ofMain.h"

using namespace std;

class ofxRaspicam;

class ofxRaspicamCtrl {
public: 

    ofParameterGroup ui;
    ofParameterGroup groupA, groupB, groupC, groupD; // sensor ctrls / camera ctrls / processing ctrls

    bool sendMode, sendWidth, sendHeight, sendFPS;
    string initialPreset;

    ofParameter<bool> enable; // open / close
    ofParameter<bool> send; // send all controls
    ofParameter<bool> receive; // sync all controls
    ofParameter<int> format; // cannot be changed after open
    ofParameter<int> mode;  // cannot be changed after open
    ofParameter<int> width; // cannot be changed after open
    ofParameter<int> height; // cannot be changed after open

    ofParameter<int> model; // presets for misc / v1 / v2 / HiQ
    ofParameter<int> presets; // preset index
    ofParameter<bool> apply;

    ofParameter<int> fps; // cannot be changed after open
    ofParameter<int> metering;
    ofParameter<int> shutter;
    ofParameter<int>  iso;
    ofParameter<int> exposure;
    ofParameter<int> awb;
    ofParameter<float> red;
    ofParameter<float> blue;

    ofParameter<int> rotation;
    ofParameter<bool> horz;
    ofParameter<bool> vert;
    ofParameter<int> brightness;
    ofParameter<int> contrast;
    ofParameter<int> saturation;
    ofParameter<int> sharpness;
    ofParameter<int> effect;

    ofxRaspicam * ptr = nullptr;
    bool isManualEnabling = false;

    ofxRaspicamCtrl();
    void setPtr( ofxRaspicam * cam ); // init

    void initSensor();

    void onGroupAChange( ofAbstractParameter & param );
    void onGroupBChange( ofAbstractParameter & param );
    void onGroupCChange( ofAbstractParameter & param );
    void onGroupDChange( ofAbstractParameter & param );


    void sendAll(); // resent
    void receiveAll(); // sync

    bool isReceiving;

};

#include "ofxRaspicam.h"