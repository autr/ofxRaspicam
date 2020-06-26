/**********************************************************
 Software developed by AVA ( Ava Group of the University of Cordoba, ava  at uco dot es)
 Main author Rafael Munoz Salinas (rmsalinas at uco dot es)
 This software is released under BSD license as expressed below
-------------------------------------------------------------------
Copyright (c) 2013, AVA ( Ava Group University of Cordoba, ava  at uco dot es)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:

   This product includes software developed by the Ava group of the University of Cordoba.

4. Neither the name of the University nor the names of its contributors
   may be used to endorse or promote products derived from this software
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AVA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL AVA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************/

#ifndef _RASPICAM_TYPES_H
#define _RASPICAM_TYPES_H

namespace raspicam {

    /**Image formats
     */
    enum RASPICAM_FORMAT{
        RASPICAM_FORMAT_YUV420 = 0,
        RASPICAM_FORMAT_GRAY = 1,
        RASPICAM_FORMAT_BGR = 2,
        RASPICAM_FORMAT_RGB = 3,
        RASPICAM_FORMAT_RGBA = 4,
        RASPICAM_FORMAT_IGNORE = 5 //do not use
    };

    /**Exposure types
     */
    enum RASPICAM_EXPOSURE {
        RASPICAM_EXPOSURE_OFF = 0,
        RASPICAM_EXPOSURE_AUTO = 1,
        RASPICAM_EXPOSURE_NIGHT = 2,
        RASPICAM_EXPOSURE_NIGHTPREVIEW = 3,
        RASPICAM_EXPOSURE_BACKLIGHT = 4,
        RASPICAM_EXPOSURE_SPOTLIGHT = 5,
        RASPICAM_EXPOSURE_SPORTS = 6,
        RASPICAM_EXPOSURE_SNOW = 7,
        RASPICAM_EXPOSURE_BEACH = 8,
        RASPICAM_EXPOSURE_VERYLONG = 9,
        RASPICAM_EXPOSURE_FIXEDFPS = 10,
        RASPICAM_EXPOSURE_ANTISHAKE = 11,
        RASPICAM_EXPOSURE_FIREWORKS = 12
    }  ;

    /**Auto white balance types
     */
    enum RASPICAM_AWB {
        RASPICAM_AWB_OFF = 0,
        RASPICAM_AWB_AUTO = 1,
        RASPICAM_AWB_SUNLIGHT = 2,
        RASPICAM_AWB_CLOUDY = 3,
        RASPICAM_AWB_SHADE = 4,
        RASPICAM_AWB_TUNGSTEN = 5,
        RASPICAM_AWB_FLUORESCENT = 6,
        RASPICAM_AWB_INCANDESCENT = 7,
        RASPICAM_AWB_FLASH = 8,
        RASPICAM_AWB_HORIZON = 9
    }  ;

    /**Image effects
     */
    enum RASPICAM_IMAGE_EFFECT {
        RASPICAM_IMAGE_EFFECT_NONE = 0,
        RASPICAM_IMAGE_EFFECT_NEGATIVE = 1,
        RASPICAM_IMAGE_EFFECT_SOLARIZE = 2,
        RASPICAM_IMAGE_EFFECT_SKETCH = 3,
        RASPICAM_IMAGE_EFFECT_DENOISE = 4,
        RASPICAM_IMAGE_EFFECT_EMBOSS = 5,
        RASPICAM_IMAGE_EFFECT_OILPAINT = 6,
        RASPICAM_IMAGE_EFFECT_HATCH = 7,
        RASPICAM_IMAGE_EFFECT_GPEN = 8,
        RASPICAM_IMAGE_EFFECT_PASTEL = 9,
        RASPICAM_IMAGE_EFFECT_WATERCOLOR = 10,
        RASPICAM_IMAGE_EFFECT_FILM = 11,
        RASPICAM_IMAGE_EFFECT_BLUR = 12,
        RASPICAM_IMAGE_EFFECT_SATURATION = 13,
        RASPICAM_IMAGE_EFFECT_COLORSWAP = 14,
        RASPICAM_IMAGE_EFFECT_WASHEDOUT = 15,
        RASPICAM_IMAGE_EFFECT_POSTERISE = 16,
        RASPICAM_IMAGE_EFFECT_COLORPOINT = 17,
        RASPICAM_IMAGE_EFFECT_COLORBALANCE = 18,
        RASPICAM_IMAGE_EFFECT_CARTOON = 19
    }  ;

    /**Metering types
     */
    enum RASPICAM_METERING {
        RASPICAM_METERING_AVERAGE = 0,
        RASPICAM_METERING_SPOT = 1,
        RASPICAM_METERING_BACKLIT = 2,
        RASPICAM_METERING_MATRIX = 3
    }  ;
    /*Econdig modes (for still mode)
     */

    typedef enum RASPICAM_ENCODING {
        RASPICAM_ENCODING_JPEG = 0,
        RASPICAM_ENCODING_BMP = 1,
        RASPICAM_ENCODING_GIF = 2,
        RASPICAM_ENCODING_PNG = 3,
        RASPICAM_ENCODING_RGB = 4
    } RASPICAM_ENCODING;

}
#endif

