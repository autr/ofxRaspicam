#include "ofxRaspicam.h"
#include "ofxRaspicamCtrl.h"

void ofxRaspicamCtrl::setPtr( ofxRaspicam * cam ) {
    ptr = cam;
}


ofxRaspicamCtrl::ofxRaspicamCtrl() {

    isReceiving = false;
    sendMode = false;
    sendWidth = false;
    sendHeight = false;
    sendFPS = false;


    groupA.add( enable.set( "enable", false ));
    groupA.add( channel.set( "threaded", 1, 0, 2 ));
    groupA.add( send.set( "send", false ));
    groupA.add( receive.set( "receive", false ));

    groupA.add( mode.set( "mode", 0, 0, 7 )); // auto mode
    groupA.add( width.set( "width", 1280, 0, 4056 )); // based on HiQ sensor
    groupA.add( height.set( "height", 960, 0, 3040 )); // based on HiQ sensor
    groupA.add( format.set( "format", 3, 0, 4 )); // RGB format


    groupA.add( model.set( "model", 0, 0, 4)); // presets for misc / v1 / v2 / HiQ 
    groupA.add( presets.set( "presets", 0, 0, ofxRaspicam::RASPICAM_PRESETS_SIZE(0) )); // preset index

    groupB.add( fps.set( "fps", 30, 0, 120 ));
    groupB.add( metering.set( "metering", 0, 0, 3 )); // average

    /*
        1000000/shutter = shutterFPS
        1000000/shutterFPS = shutter
        60 / shutterFPS = milliseconds
        60 / 60 / shutterFPS = seconds

        According to docs: 200000000 max shutterspeed
        According to HiQ MMAL reporting: 330000 max shutterspeed
    */

    groupB.add( shutter.set( "shutter", 1, 1, 330000 ));
    groupB.add( iso.set( "iso", 400, 100, 800 ));
    groupB.add( exposure.set( "exposure", 0, 0, 12 )); // 0 is off / 1 is auto exposure / 10 is fixed fps)
    groupB.add( awb.set( "awb", 1, 0, 9 )); // 1 is auto white balance
    groupB.add( red.set( "red", 2.5, 0, 5 ));
    groupB.add( blue.set( "blue", 2.5, 0, 5 ));

    groupC.add( rotation.set( "rotation", 0, 0, 4 )); 
    groupC.add( horz.set( "horz", false ));
    groupC.add( vert.set( "vert", false ));
    groupC.add( brightness.set( "brightness", 50, 0, 100 ));
    groupC.add( contrast.set( "contrast", 1, -100, 100 ));
    groupC.add( saturation.set( "saturation", 1, -100, 100 ));
    groupC.add( sharpness.set( "sharpness", 1, -100, 100 ));
    groupC.add( effect.set( "effect", 1, 0, 19 ));

    ui.add( groupA );
    ui.add( groupB );
    ui.add( groupC );
    ui.add( groupD );

    ofAddListener( groupA.parameterChangedE(), this, &ofxRaspicamCtrl::onGroupAChange);
    ofAddListener( groupB.parameterChangedE(), this, &ofxRaspicamCtrl::onGroupBChange);
    ofAddListener( groupC.parameterChangedE(), this, &ofxRaspicamCtrl::onGroupCChange);
    ofAddListener( groupD.parameterChangedE(), this, &ofxRaspicamCtrl::onGroupDChange);

}

void ofxRaspicamCtrl::onGroupAChange( ofAbstractParameter & param ) {

    if (isReceiving) return;

    string name = param.getName();
    ofLogNotice("ofxRaspicamCtrl") << "setting control paramter..." << name;

    if (name == "send" && (bool)send) {
        sendAll();
        send = false;
    }
    if (name == "receive" && (bool)receive) {
        isReceiving = true;
        receiveAll();
        receive = false;
        isReceiving = false;
    }
    if (name == "enable" && !isManualEnabling) {
        if ((bool)enable && ptr != nullptr) ptr->open();
        if (!(bool)enable && ptr != nullptr) ptr->close();
    }
    if (name == "model") {
        presets.setMax( ofxRaspicam::RASPICAM_PRESETS_SIZE((int)model) );
    }
    if (name == "presets") {

        ofLogNotice("ofxRaspicamCtrl") << "attempting preset..." << name;

        int i = (int)model;
        int ii = (int)presets;

        string m = ofxRaspicam::RASPICAM_MODEL_STR(i);
        int s = ofxRaspicam::RASPICAM_PRESETS_SIZE(i);

        if ( ii < 0 || ii >= s || ii == 0 ) {
            ofLogNotice("ofxRaspicamCtrl") << "error..." << s << m << ii << i;
            return;
        }

        string n = ofxRaspicam::RASPICAM_PRESETS_STR(i, ii);
        vector<int> d = ofxRaspicam::RASPICAM_PRESETS_DEF(i, ii);

        ofLogNotice("ofxRaspicamCtrl") << "setting preset..." << n << d[0] << d[1] << d[2];

        width = d[0];
        height = d[1];
        fps = d[2];

        apply = false;
        initialPreset = n;
    }

    if (ptr != nullptr) {

        if (name == "format") ptr->getInternal().setFormat( (raspicam::RASPICAM_FORMAT)(int)format );
        if (name == "mode") {
            ptr->getInternal().setSensorMode( (int)mode );
            sendMode = true;
        }
        if (name == "width") {
            ptr->getInternal().setWidth( (int)width );
            sendWidth = true;
        }
        if (name == "height") {
            ptr->getInternal().setHeight( (int)height );
            sendFPS = true;
        }

    }
}
void ofxRaspicamCtrl::onGroupBChange( ofAbstractParameter & param ) {

    if (isReceiving || ptr == nullptr) return;
    string name = param.getName();
    ofLogNotice("ofxRaspicamCtrl") << "setting control paramter..." << name;

    if (name == "fps") {
        ptr->getInternal().setFrameRate( (int)fps );
        sendFPS = true;
    }
    if (name == "metering") ptr->getInternal().setMetering( (raspicam::RASPICAM_METERING)(int)metering );
    if (name == "shutter") ptr->getInternal().setShutterSpeed( (int)shutter );
    if (name == "iso") ptr->getInternal().setISO( (int)iso );
    if (name == "exposure") ptr->getInternal().setExposure( (raspicam::RASPICAM_EXPOSURE)(int)exposure );
    if (name == "awb") ptr->getInternal().setAWB( (raspicam::RASPICAM_AWB)(int)awb );
    if (name == "red") ptr->getInternal().setAWB_RB( (float)red, (float)blue );
    if (name == "blue") ptr->getInternal().setAWB_RB( (float)red, (float)blue );

}
void ofxRaspicamCtrl::onGroupCChange( ofAbstractParameter & param ) {

    if (isReceiving || ptr == nullptr) return;
    string name = param.getName();
    ofLogNotice("ofxRaspicamCtrl") << "setting control paramter..." << name;

    if (name == "rotation") ptr->getInternal().setRotation( (int)rotation );
    if (name == "horz") ptr->getInternal().setHorizontalFlip( (bool)horz );
    if (name == "vert") ptr->getInternal().setVerticalFlip( (bool)vert );
    if (name == "brightness") ptr->getInternal().setBrightness( (int)brightness );
    if (name == "contrast") ptr->getInternal().setContrast( (int)contrast );
    if (name == "saturation") ptr->getInternal().setSaturation( (int)saturation );
    if (name == "sharpness") ptr->getInternal().setSharpness( (int)sharpness );
    if (name == "effect") ptr->getInternal().setImageEffect( (raspicam::RASPICAM_IMAGE_EFFECT)(int)effect );

}
void ofxRaspicamCtrl::onGroupDChange( ofAbstractParameter & param ) {

    if (isReceiving) return;
    string name = param.getName();
    ofLogNotice("ofxRaspicamCtrl") << "setting control paramter..." << name;

}

void ofxRaspicamCtrl::initSensor() {

    ptr->getInternal().setFormat( (raspicam::RASPICAM_FORMAT)(int)format );
    if (sendWidth) {
        ofLogNotice("ofxRaspicamCtrl") << "sending initial width..." << (int)width;
        ptr->getInternal().setWidth( (int)width );
    }
    if (sendHeight) { 
        ofLogNotice("ofxRaspicamCtrl") << "sending initial height..." << (int)height;
        ptr->getInternal().setHeight( (int)height );
    }
    if (sendFPS) { 
        ofLogNotice("ofxRaspicamCtrl") << "sending initial FPS..." << (int)fps;
        ptr->getInternal().setFrameRate( (int)fps );
    }
    if (sendMode) { 
        ofLogNotice("ofxRaspicamCtrl") << "sending initial sensor mode..." << (int)mode;
        ptr->getInternal().setSensorMode( (int)mode );
    }
}

void ofxRaspicamCtrl::sendAll() {

    if (ptr == nullptr) return;

    initSensor();

    ptr->getInternal().setRotation( (int)rotation );
    ptr->getInternal().setHorizontalFlip( (bool)horz );
    ptr->getInternal().setVerticalFlip( (bool)vert );

    ptr->getInternal().setMetering( (raspicam::RASPICAM_METERING)(int)metering );
    ptr->getInternal().setShutterSpeed( (int)shutter );
    ptr->getInternal().setISO( (int)iso );
    ptr->getInternal().setExposure( (raspicam::RASPICAM_EXPOSURE)(int)exposure );
    ptr->getInternal().setAWB( (raspicam::RASPICAM_AWB)(int)awb );
    ptr->getInternal().setAWB_RB( (int)red, (int)blue );

    ptr->getInternal().setBrightness( (int)brightness );
    ptr->getInternal().setContrast( (int)contrast );
    ptr->getInternal().setSaturation( (int)saturation );
    ptr->getInternal().setSharpness( (int)sharpness );
    ptr->getInternal().setImageEffect( (raspicam::RASPICAM_IMAGE_EFFECT)(int)effect );

};
void ofxRaspicamCtrl::receiveAll() {

    if (ptr == nullptr) return;

    format = ptr->getInternal().getFormat();
    width = ptr->getInternal().getWidth();
    height = ptr->getInternal().getHeight();
    rotation = ptr->getInternal().getRotation();
    horz = ptr->getInternal().isHorizontallyFlipped();
    vert = ptr->getInternal().isVerticallyFlipped();
    fps = ptr->getInternal().getFrameRate();

    metering = ptr->getInternal().getMetering();
    shutter = ptr->getInternal().getShutterSpeed();
    iso = ptr->getInternal().getISO();
    exposure = ptr->getInternal().getExposure();
    awb = ptr->getInternal().getAWB();
    red = ptr->getInternal().getAWBG_red();
    blue = ptr->getInternal().getAWBG_blue();

    brightness = ptr->getInternal().getBrightness();
    contrast = ptr->getInternal().getContrast();
    saturation = ptr->getInternal().getSaturation();
    sharpness = ptr->getInternal().getSharpness();
    effect = ptr->getInternal().getImageEffect();
}
