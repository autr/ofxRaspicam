#include "ofxRaspicam.h"


string ofxRaspicam::RASPICAM_MODEL_STR(int i) {
    string v[4] = { "MISC", "V1", "V2", "HIQ" };
    return v[i];
};


// ---------------------------------------------------------------------------------------------------


vector<vector<string>> raspicamPresetStrings = { 
    {
        "MISC_AUTO", 
        "MISC_ML_320_240",
        "MISC_ML_640_480", 
        "MISC_PAL_720_576", 
        "MISC_NTSE_720_480", 
        "MISC_720P_1280_720", 
        "MISC_1080P_1920_1080"
    }, { 
        "V1_MODE_AUTO", 
        "V1_MODE_1080P_30FPS", 
        "V1_MODE_2592_1944_15FPS", 
        "V1_MODE_2592_1944_1FPS", 
        "V1_MODE_1296_972_42FPS", 
        "V1_MODE_1296_730_49FPS", 
        "V1_MODE_640_380_60FPS", 
        "V1_MODE_640_380_90FPS"
    }, { 
        "V2_MODE_AUTO", 
        "V2_MODE_1080P_30FPS", 
        "V2_MODE_3280_2464_15FPS_A", 
        "V2_MODE_3280_2464_15FPS_B", 
        "V2_MODE_1640_1232_40FPS", 
        "V2_MODE_1640_922_40FPS", 
        "V2_MODE_1280_720_90FPS", 
        "V2_MODE_640_480_200FPS"
    }, { 
        "HIQ_MODE_AUTO", 
        "HIQ_MODE_2028_1080_50FPS", 
        "HIQ_MODE_2028_1520_50FPS", 
        "HIQ_MODE_4056_3040_10FPS", 
        "HIQ_MODE_1012_760_120FPS"
    }
};

string ofxRaspicam::RASPICAM_PRESETS_STR(int i, int ii) {
    return raspicamPresetStrings[i][ii];
};

// ---------------------------------------------------------------------------------------------------

vector<vector<vector<int>>> raspicamPresetSettings = {
    {
        {0,0,0}, // auto
        {320,240,60},
        {640,480,60},
        {720,576,60},
        {720,480,60},
        {1280,720,30},
        {1920,1080,30}
    }, {
        {0,0,0}, // auto
        {1920,1080,30},
        {2592,1944,15},
        {2592,1944,1},
        {1296,972,42},
        {1296,730,49},
        {640,380,60},
        {640,380,90}
    }, {
        {0,0,0}, // auto
        {1920,1080,30},
        {3280,2464,15},
        {3280,2464,15},
        {1640,1232,40},
        {1640,922,40},
        {1280,720,90},
        {640,480,200}
    }, {
        {0,0,0}, // auto
        {2028,1080,50},
        {2028,1520,50},
        {4056,3040,10},
        {1012,760,120}
    }
};

vector<int> ofxRaspicam::RASPICAM_PRESETS_DEF(int i, int ii) {
    return raspicamPresetSettings[i][ii];
};

int ofxRaspicam::RASPICAM_PRESETS_SIZE(int i) {
    return raspicamPresetSettings[i].size();
};

// ---------------------------------------------------------------------------------------------------



// Pixel types

string ofxRaspicam::RASPICAM_FORMAT_STR( int i ) {
    vector<string> v = {
    "YUV420",
    "GRAY",
    "BGR",
    "RGB",
    "IGNORE"
    };
    return v[i];
};

// Exposure types

string ofxRaspicam::RASPICAM_EXPOSURE_STR( int i ) {
    vector<string> v = {
    "OFF",
    "AUTO",
    "NIGHT",
    "NIGHTPREVIEW",
    "BACKLIGHT",
    "SPOTLIGHT",
    "SPORTS",
    "SNOW",
    "BEACH",
    "VERYLONG",
    "FIXEDFPS",
    "ANTISHAKE",
    "FIREWORKS"
    };
    return v[i];
};

// Auto white balance types

vector<string> raspicamAWBStrings = {
    "OFF",
    "AUTO",
    "SUNLIGHT",
    "CLOUDY",
    "SHADE",
    "TUNGSTEN",
    "FLUORESCENT",
    "INCANDESCENT",
    "FLASH",
    "HORIZON"
};
string ofxRaspicam::RASPICAM_AWB_STR( int i ) {
    return raspicamAWBStrings[i];
};

// Image effects

string ofxRaspicam::RASPICAM_IMAGE_EFFECT_STR( int i ) {
    vector<string> v = {
    "NONE",
    "NEGATIVE",
    "SOLARIZE",
    "SKETCH",
    "DENOISE",
    "EMBOSS",
    "OILPAINT",
    "HATCH",
    "GPEN",
    "PASTEL",
    "WATERCOLOR",
    "FILM",
    "BLUR",
    "SATURATION",
    "COLORSWAP",
    "WASHEDOUT",
    "POSTERISE",
    "COLORPOINT",
    "COLORBALANCE",
    "CARTOON"
    };
    return v[i];
};

// Metering types

string ofxRaspicam::RASPICAM_METERING_STR( int i ) {
    vector<string> v = {
    "AVERAGE",
    "SPOT",
    "BACKLIT",
    "MATRIX"
    };
    return v[i];
};

// Encoding types

string ofxRaspicam::RASPICAM_ENCODING_STR( int i ) {
    vector<string> v = {
    "JPEG",
    "BMP",
    "GIF",
    "PNG",
    "RGB"
    };
    return v[i];
};
