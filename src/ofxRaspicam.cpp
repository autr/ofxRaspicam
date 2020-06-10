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

    // bufferPtr = new raspicam::RaspiCamRawBuffer;
    ctrl.setPtr(this);
    debugNoGrab = false;
}

ofxRaspicam::~ofxRaspicam() {
    close();
}

void ofxRaspicam::processCallback(unsigned char * _buffer) {

    if (ofxRaspicam::isClosing()) return;

    float f = ofGetElapsedTimef();
    actualFPS = 1.0/(f-timer);
    timer = f;

    // copy raw buffer...
    ofLog() << "t";
    lock();
    pixels.setFromPixels( _buffer, width, height, 3);
    unlock();

    newFrame = true;
}


void ofxRaspicam::onCaptureBufferCallback(void *arg) {

    if (ofxRaspicam::isClosing()) return;
    ofxRaspicam * t = (ofxRaspicam *) arg;
    if ((int)t->ctrl.channel != 0) return;
    t->processCallback( t->obj.getImageBufferData() );
}


void ofxRaspicam::onRawBufferCallback(const raspicam::RaspiCamRawBuffer& _buffer, void* _thisVoid) {
    if (ofxRaspicam::isClosing()) return;
    auto t = static_cast<ofxRaspicam*>(_thisVoid);
    if ((int)t->ctrl.channel != 1) return;
    t->processCallback( (unsigned char *)_buffer.getBuffer() );


}

void ofxRaspicam::threadedFunction()  {

    while(isThreadRunning()) {
        if ((int)ctrl.channel == 2) {
            obj.grab();
            lock();
            pixels.setFromPixels( (unsigned char *)obj.getImageBufferData(), width, height, 3);
            newFrame = true;
            float f = ofGetElapsedTimef();
            actualFPS = 1.0/(f-timer);
            timer = f;
            unlock();
        }
    }
}

void ofxRaspicam::init( ) {

    ofLogNotice("ofxRaspicam") << "opening...\n------------------";

    printInfo(); // default settings
    ctrl.initSensor();
    printInfo(); // ofxRaspicam settings

    newFrame = false;
    ofxRaspicam::setClosingFlag(false);

    width = obj.getWidth();
    height = obj.getHeight();

    if ( !obj.open()) {
        ofLogError("ofxRaspicam") << "error opening...\n------------------";
        return;
    }


    obj.setUserCallback( onCaptureBufferCallback, this );
    obj.setRawBufferCallback( onRawBufferCallback, this );
    if (!isThreadRunning()) startThread(true);


}

ofTexture & ofxRaspicam::syncToTexture( ofTexture & texture ) {
    if (ofxRaspicam::isClosing() || !newFrame || !isOpen()) return texture;
    if ((int)texture.getWidth() != (int)getWidth() && (int)texture.getHeight() != (int)getHeight() ) {
        texture.allocate((int)getWidth(), (int)getHeight(), GL_RGB);
        ofLogError("ofxRaspicam") << "allocating texture...\n------------------";
        // GLint f;
        // if (obj.getFormat() == raspicam::RASPICAM_FORMAT::RASPICAM_FORMAT_RGB) {
        // }
    }
    if (texturePtr == nullptr) texturePtr = &texture;
    lock();
    texture.loadData( pixels );
    unlock();
    return texture;
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
    // obj.setRawBufferCallback( onRawBufferCallback, nullptr );
    // obj.setUserCallback( onCaptureBufferCallback, nullptr );
    if (texturePtr != nullptr) texturePtr->clear();
    stopThread();
    sleep(500);
    obj.release();
    sleep(500);
    ofxRaspicam::setClosingFlag(false);
}

// ---------------------------------------------------------------------------------------------------


int ofxRaspicam::getWidth() {
    return width;
}

int ofxRaspicam::getHeight() {
    return height;
}

bool ofxRaspicam::isOpen() {
    return obj.isOpened();
}

raspicam::RaspiCam & ofxRaspicam::getInternal() {
    return obj;
}


string ofxRaspicam::getInfoString() {

    string info = "ID: " + obj.getId();
    info += "\n----------------\n";
    string o = (obj.isOpened()) ? "OPEN" : "CLOSED";
    info += "status: " + o + "\n";
    info += "format: " + ofToString( obj.getFormat() ) + ":" + RASPICAM_FORMAT_STR((int)obj.getFormat()) + "\n";
    info += "width: " + ofToString( obj.getWidth() ) + "\n";
    info += "height: " + ofToString( obj.getHeight() ) + "\n";
    info += "rotation: " + ofToString( obj.getRotation() ) + "\n";
    info += "horz: " + ofToString( obj.isHorizontallyFlipped() ) + "\n";
    info += "vert: " + ofToString( obj.isVerticallyFlipped() ) + "\n";
    info += ".................\n";
    info += "metering: " + ofToString( obj.getMetering() ) + ":" + RASPICAM_METERING_STR((int)obj.getMetering()) + "\n";
    info += "shutter: " + ofToString( obj.getShutterSpeed() ) + " (" + humanShutterSpeed((int)obj.getShutterSpeed() ) + ") \n";
    info += "ISO: " + ofToString( obj.getISO() ) + "\n";
    info += "exposure: " + ofToString( obj.getExposure() ) + ":" + RASPICAM_EXPOSURE_STR((int)obj.getExposure()) + "\n";
    info += "AWB: " + ofToString( obj.getAWB() ) + ":" + RASPICAM_AWB_STR((int)obj.getAWB()) + "\n";
    info += "red: " + ofToString( obj.getAWBG_red() ) + "\n";
    info += "blue: " + ofToString( obj.getAWBG_blue() ) + "\n";
    info += ".................\n";
    info += "brightness: " + ofToString( obj.getBrightness() ) + "\n";
    info += "contrast: " + ofToString( obj.getContrast() ) + "\n";
    info += "saturation: " + ofToString( obj.getSaturation() ) + "\n";
    info += "sharpness: " + ofToString( obj.getSharpness() ) + "\n";
    info += "effect: " + ofToString( obj.getImageEffect() ) + ":" + RASPICAM_IMAGE_EFFECT_STR((int)obj.getImageEffect()) + "\n";
    info += ".................\n";
    info += "target FPS: " + ofToString( obj.getFrameRate() ) + "\n";
    info += "actual FPS: " + ofToString( actualFPS ) + "\n";
    info += "ofApp FPS: " + ofToString( ofGetFrameRate() ) + "\n";
    info += "----------------\n";

    return info;
}

// ---------------------------------------------------------------------------------------------------



