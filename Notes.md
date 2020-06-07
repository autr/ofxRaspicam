```
-- Install configuration: "Release"
-- Installing: /usr/local/lib/cmake/Findraspicam.cmake
-- Installing: /usr/local/lib/cmake/raspicamConfig.cmake
-- Installing: /usr/local/lib/libraspicam.so.0.1.2
-- Installing: /usr/local/lib/libraspicam.so.0.1
-- Set runtime path of "/usr/local/lib/libraspicam.so.0.1.2" to ""
-- Installing: /usr/local/lib/libraspicam.so
-- Installing: /usr/local/lib/libraspicam_cv.so
-- Set runtime path of "/usr/local/lib/libraspicam_cv.so" to ""
-- Installing: /usr/local/include/raspicam/raspicamtypes.h
-- Installing: /usr/local/include/raspicam/raspicam.h
-- Installing: /usr/local/include/raspicam/raspicam_cv.h
-- Installing: /usr/local/include/raspicam/raspicam_still_cv.h
-- Installing: /usr/local/bin/raspicam_test
-- Set runtime path of "/usr/local/bin/raspicam_test" to ""
-- Installing: /usr/local/bin/raspicam_still_test
-- Set runtime path of "/usr/local/bin/raspicam_still_test" to ""
-- Installing: /usr/local/bin/raspicam_cv_test
-- Set runtime path of "/usr/local/bin/raspicam_cv_test" to ""
-- Installing: /usr/local/bin/raspicam_cv_still_test
-- Set runtime path of "/usr/local/bin/raspicam_cv_still_test" to ""
```

```
scp -r ofxRaspicam pi@raspberrypi.local:~/openFrameworks/addons/ofxRaspicam
scp -prq ofxRaspicam/* pi@raspberrypi.local:~/openFrameworks/addons/ofxRaspicam/
```