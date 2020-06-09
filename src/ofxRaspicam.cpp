#include "ofxRaspicam.h"

bool closing = false;

bool ofxRaspicam::isClosing() {
    return closing;
}
void ofxRaspicam::setClosingFlag( bool b) {
    closing = b;
}

// ---------------------------------------------------------------------------------------------------

ofxRaspicam::ofxRaspicam() {

    objPtr = new raspicam::RaspiCam();
    bufferPtr = new raspicam::RaspiCamRawBuffer;
    ctrl.setPtr(this);
}

ofxRaspicam::~ofxRaspicam() {
    close();
}

void ofxRaspicam::onRawBufferCallback(const raspicam::RaspiCamRawBuffer& _buffer, void* _thisVoid) {

    if (ofxRaspicam::isClosing()) return;

    auto _t = static_cast<ofxRaspicam*>(_thisVoid);
    auto & t = *_t;

    // find actual FPS...

    float f = ofGetElapsedTimef();
    t.actualFPS = 1.0/(f-t.timer);
    t.timer = f;

    // copy raw buffer...

    if (t.bufferPtr != nullptr) {
        t.buffer() = _buffer; // COPY
    } else {
        ofLogError("ofxRaspicam") << "buffer not defined...";
    }

    t.needsGrab = true;
    t.newFrame = true;

}

void ofxRaspicam::init( ) {

    ofLogNotice("ofxRaspicam") << "opening...\n------------------";

    if (objPtr == nullptr) objPtr = new raspicam::RaspiCam();
    if (bufferPtr == nullptr) bufferPtr = new raspicam::RaspiCamRawBuffer;

    printInfo(); // default settings
    ctrl.initSensor();
    printInfo(); // ofxRaspicam settings

    newFrame = false;
    needsGrab = false;
    ofxRaspicam::setClosingFlag(false);

    obj().setRawBufferCallback( onRawBufferCallback, this );
    if ( !obj().open()) {
        ofLogError("ofxRaspicam") << "error opening...\n------------------";
        return;
    }

    ofLogNotice("ofxRaspicam") << "sleeping for 500 milliseconds...\n------------------";
    sleep(500);
}

void ofxRaspicam::syncToTexture( ofTexture & texture ) {
    if (ofxRaspicam::isClosing() || !newFrame || !isOpen()) return;
    if (texture.getWidth() != getWidth() && texture.getHeight() != getHeight() ) {
        texture.allocate(getWidth(), getHeight(), GL_RGB);
        // GLint f;
        // if (obj().getFormat() == raspicam::RASPICAM_FORMAT::RASPICAM_FORMAT_RGB) {
        // }
    }
    texture.loadData( getData(), getWidth(), getHeight(), GL_RGB );
    newFrame = true;
}

void ofxRaspicam::open() {
    ctrl.isManualEnabling = true;
    ctrl.enable = true;
    if (!isOpen()) init();
    ctrl.isManualEnabling = false;
}

void ofxRaspicam::close() {
    ctrl.isManualEnabling = true;
    ctrl.enable = false;
    if (isOpen()) release();
    ctrl.isManualEnabling = false;
}


void ofxRaspicam::release() { 
    ofxRaspicam::setClosingFlag(true);
    ofLogNotice("ofxRaspicam") << "closing 1...";
    obj().setRawBufferCallback( onRawBufferCallback, nullptr );
    sleep(1000);
    ofLogNotice("ofxRaspicam") << "closing 2...";
    delete bufferPtr;
    bufferPtr = nullptr;
    sleep(1000);
    ofLogNotice("ofxRaspicam") << "closing 3...";
    sleep(1000);
    ofLogNotice("ofxRaspicam") << "closing 4...";
    delete objPtr;
    objPtr = nullptr;
    sleep(1000);
    ofLogNotice("ofxRaspicam") << "closing 5...";
    sleep(1000);
    ofLogNotice("ofxRaspicam") << "closing 6...";

    ofxRaspicam::setClosingFlag(false);
}

// ---------------------------------------------------------------------------------------------------


int ofxRaspicam::getWidth() {
    if (objPtr == nullptr) return 0;
    return obj().getWidth();
}

int ofxRaspicam::getHeight() {
    if (objPtr == nullptr) return 0;
    return obj().getHeight();
}

bool ofxRaspicam::isOpen() {
    if (objPtr == nullptr) return false;
    return obj().isOpened();
}

raspicam::RaspiCam & ofxRaspicam::getInternal() {
    return obj();
}

const unsigned char * ofxRaspicam::getData() {
    if (bufferPtr == nullptr) return {};
    return (unsigned char *)buffer().getBuffer();
}


string ofxRaspicam::getInfoString() {

    if (objPtr == nullptr) return "NOT INITED";

    string info = "ID: " + obj().getId();
    info += "\n----------------\n";
    string o = (obj().isOpened()) ? "OPEN" : "CLOSED";
    info += "status: " + o + "\n";
    info += "format: " + ofToString( obj().getFormat() ) + ":" + RASPICAM_FORMAT_STR((int)obj().getFormat()) + "\n";
    info += "width: " + ofToString( obj().getWidth() ) + "\n";
    info += "height: " + ofToString( obj().getHeight() ) + "\n";
    info += "rotation: " + ofToString( obj().getRotation() ) + "\n";
    info += "horz: " + ofToString( obj().isHorizontallyFlipped() ) + "\n";
    info += "vert: " + ofToString( obj().isVerticallyFlipped() ) + "\n";
    info += ".................\n";
    info += "metering: " + ofToString( obj().getMetering() ) + ":" + RASPICAM_METERING_STR((int)obj().getMetering()) + "\n";
    info += "shutter: " + ofToString( obj().getShutterSpeed() ) + " (" + humanShutterSpeed((int)obj().getShutterSpeed() ) + ") \n";
    info += "ISO: " + ofToString( obj().getISO() ) + "\n";
    info += "exposure: " + ofToString( obj().getExposure() ) + ":" + RASPICAM_EXPOSURE_STR((int)obj().getExposure()) + "\n";
    info += "AWB: " + ofToString( obj().getAWB() ) + ":" + RASPICAM_AWB_STR((int)obj().getAWB()) + "\n";
    info += "red: " + ofToString( obj().getAWBG_red() ) + "\n";
    info += "blue: " + ofToString( obj().getAWBG_blue() ) + "\n";
    info += ".................\n";
    info += "brightness: " + ofToString( obj().getBrightness() ) + "\n";
    info += "contrast: " + ofToString( obj().getContrast() ) + "\n";
    info += "saturation: " + ofToString( obj().getSaturation() ) + "\n";
    info += "sharpness: " + ofToString( obj().getSharpness() ) + "\n";
    info += "effect: " + ofToString( obj().getImageEffect() ) + ":" + RASPICAM_IMAGE_EFFECT_STR((int)obj().getImageEffect()) + "\n";
    info += ".................\n";
    info += "target FPS: " + ofToString( obj().getFrameRate() ) + "\n";
    info += "actual FPS: " + ofToString( actualFPS ) + "\n";
    info += "ofApp FPS: " + ofToString( ofGetFrameRate() ) + "\n";
    info += "----------------\n";

    return info;
}

// ---------------------------------------------------------------------------------------------------



