# Hilfe

Some stuff for making life EZ'r:

```
export DISPLAY=:0:0 make run
sudo apt-get install xvfb
xvfb-run ./bin/example
scp -r ofxRaspicam pi@raspberrypi.local:~/openFrameworks/addons/ofxRaspicam # copy the 1st time around
scp -prq ofxRaspicam/* pi@raspberrypi.local:~/openFrameworks/addons/ofxRaspicam/ # recursive copying
```


# Install AVA raspivid

```
make
sudo make install
sudo ldconfig
```

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

Then copied those includes into the repo (with .so linked via addon_config flag -lraspicam)

# High Quality Camera

Raspivid is using MMAL from 4 years ago - not picking up latest camera... official specs:

```
Sensor size definition = cropped sensor

Version 1 [OV5647]

Mode	Size	Aspect Ratio	Frame rates	FOV	Binning
0	automatic selection				
1	1920x1080	16:9	1-30fps	Partial	None
2	2592x1944	4:3	1-15fps	Full	None
3	2592x1944	4:3	0.1666-1fps	Full	None
4	1296x972	4:3	1-42fps	Full	2x2
5	1296x730	16:9	1-49fps	Full	2x2
6	640x480	4:3	42.1-60fps	Full	2x2 plus skip
7	640x480	4:3	60.1-90fps	Full	2x2 plus skip

Version 2 [IMX219]

Mode	Size	Aspect Ratio	Frame rates	FOV	Binning
0	automatic selection				
1	1920x1080	16:9	0.1-30fps	Partial	None
2	3280x2464	4:3	0.1-15fps	Full	None
3	3280x2464	4:3	0.1-15fps	Full	None
4	1640x1232	4:3	0.1-40fps	Full	2x2
5	1640x922	16:9	0.1-40fps	Full	2x2
6	1280x720	16:9	40-90fps	Partial	2x2
7	640x480	4:3	40-200fps1	Partial	2x2
1For frame rates over 120fps, it is necessary to turn off automatic exposure and gain control using -ex off. Doing so should achieve the higher frame rates, but exposure time and gains will need to be set to fixed values supplied by the user.

HQ Camera

Mode	Size	Aspect Ratio	Frame rates	FOV	Binning
0	automatic selection				
1	2028x1080	169:90	0.1-50fps	Partial	2x2
2	2028x1520	4:3	0.1-50fps	Full	2x2
3	4056x3040	4:3	0.005-10fps	Full	None
4	1012x760	4:3	50.1-120fps	Full	4x4
```

Glitchy pixels when trying to send sensor_mode to highqual camera... so:

# Update MMAL and VCOS libs

Compile and install raspberrypi/userland (sudo make && sudo make install)

```
Install the project...
-- Install configuration: ""
-- Up-to-date: /opt/vc/src/hello_pi
-- Up-to-date: /opt/vc/src/hello_pi/libs
-- Up-to-date: /opt/vc/src/hello_pi/libs/revision
-- Installing: /opt/vc/src/hello_pi/libs/revision/revision.h
-- Installing: /opt/vc/src/hello_pi/libs/revision/revision.c
-- Installing: /opt/vc/src/hello_pi/libs/revision/Makefile
-- Up-to-date: /opt/vc/src/hello_pi/libs/ilclient
-- Installing: /opt/vc/src/hello_pi/libs/ilclient/ilclient.c

# etc etc etc

# ...

# oh hello...

-- Up-to-date: /opt/vc/include/interface/vcos
-- Installing: /opt/vc/include/interface/vcos/vcos_mutex.h
-- Installing: /opt/vc/include/interface/vcos/vcos_event_flags.h
-- Installing: /opt/vc/include/interface/vcos/vcos_event.h
-- Installing: /opt/vc/include/interface/vcos/vcos_stdint.h
-- Installing: /opt/vc/include/interface/vcos/vcos_atomic_flags.h
-- Installing: /opt/vc/include/interface/vcos/vcos_blockpool.h
-- Installing: /opt/vc/include/interface/vcos/vcos_msgqueue.h
-- Installing: /opt/vc/include/interface/vcos/vcos_inttypes.h
-- Installing: /opt/vc/include/interface/vcos/vcos_thread.h
-- Installing: /opt/vc/include/interface/vcos/vcos_reentrant_mutex.h
-- Installing: /opt/vc/include/interface/vcos/vcos_semaphore.h
-- Installing: /opt/vc/include/interface/vcos/vcos_lowlevel_thread.h
-- Installing: /opt/vc/include/interface/vcos/vcos_queue.h
-- Installing: /opt/vc/include/interface/vcos/vcos_quickslow_mutex.h
-- Installing: /opt/vc/include/interface/vcos/vcos_ctype.h
-- Installing: /opt/vc/include/interface/vcos/vcos_cfg.h
-- Installing: /opt/vc/include/interface/vcos/vcos_dlfcn.h
-- Installing: /opt/vc/include/interface/vcos/vcos_assert.h
-- Installing: /opt/vc/include/interface/vcos/vcos_timer.h
-- Up-to-date: /opt/vc/include/interface/vcos/pthreads
-- Installing: /opt/vc/include/interface/vcos/pthreads/vcos_platform_types.h
-- Installing: /opt/vc/include/interface/vcos/pthreads/vcos_futex_mutex.h
-- Installing: /opt/vc/include/interface/vcos/pthreads/vcos_platform.h
-- Installing: /opt/vc/include/interface/vcos/vcos_string.h
-- Installing: /opt/vc/include/interface/vcos/vcos_isr.h
-- Installing: /opt/vc/include/interface/vcos/vcos.h
-- Installing: /opt/vc/include/interface/vcos/vcos_cmd.h
-- Installing: /opt/vc/include/interface/vcos/vcos_attr.h
-- Installing: /opt/vc/include/interface/vcos/vcos_mem.h
-- Installing: /opt/vc/include/interface/vcos/vcos_thread_attr.h
-- Installing: /opt/vc/include/interface/vcos/vcos_build_info.h
-- Installing: /opt/vc/include/interface/vcos/vcos_once.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_deprecated.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_thread_reaper.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_joinable_thread_from_plain.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_generic_reentrant_mtx.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_latch_from_sem.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_generic_quickslow_mutex.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_mem_from_malloc.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_common.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_generic_named_sem.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_mutexes_are_reentrant.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_generic_blockpool.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_generic_event_flags.h
-- Installing: /opt/vc/include/interface/vcos/generic/vcos_generic_tls.h
-- Installing: /opt/vc/include/interface/vcos/user_nodefs.h
-- Installing: /opt/vc/include/interface/vcos/vcos_logging_control.h
-- Installing: /opt/vc/include/interface/vcos/glibc
-- Installing: /opt/vc/include/interface/vcos/vcos_init.h
-- Installing: /opt/vc/include/interface/vcos/vcos_logging.h
-- Installing: /opt/vc/include/interface/vcos/vcos_legacy_isr.h
-- Installing: /opt/vc/include/interface/vcos/build
-- Installing: /opt/vc/include/interface/vcos/build/pthreads
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/CMakeFiles
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/CMakeFiles/vcos.dir
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/CMakeFiles/vcos.dir/__
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/CMakeFiles/vcos.dir/__/generic
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/CMakeFiles/vcos.dir/__/glibc
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/generic
-- Installing: /opt/vc/include/interface/vcos/build/pthreads/generic/CMakeFiles
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles/3.13.4
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles/3.13.4/CompilerIdCXX
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles/3.13.4/CompilerIdCXX/tmp
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles/3.13.4/CompilerIdC
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles/3.13.4/CompilerIdC/tmp
-- Installing: /opt/vc/include/interface/vcos/build/CMakeFiles/CMakeTmp
-- Installing: /opt/vc/include/interface/vcos/vcos_stdbool.h
-- Installing: /opt/vc/include/interface/vcos/vcos_types.h
-- Installing: /opt/vc/include/interface/vcos/vcos_named_semaphore.h
-- Installing: /opt/vc/include/interface/vcos/vcos_tls.h
-- Installing: /opt/vc/include/interface/vcos/vcos_mempool.h

# etc etc 

# mmm

-- Installing: /opt/vc/lib/pkgconfig/mmal.pc
-- Installing: /opt/vc/lib/libvcos.so
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_common.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_generic_blockpool.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_generic_event_flags.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_generic_named_sem.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_generic_quickslow_mutex.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_generic_reentrant_mtx.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_generic_tls.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_joinable_thread_from_plain.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_latch_from_sem.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_mem_from_malloc.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_mutexes_are_reentrant.h
-- Up-to-date: /opt/vc/include/interface/vcos/generic/vcos_thread_reaper.h
-- Installing: /opt/vc/lib/libmmal.so
-- Set runtime path of "/opt/vc/lib/libmmal.so" to ""
-- Installing: /opt/vc/include/interface/mmal/mmal.h
-- Installing: /opt/vc/include/interface/mmal/mmal_buffer.h
-- Installing: /opt/vc/include/interface/mmal/mmal_clock.h
-- Installing: /opt/vc/include/interface/mmal/mmal_common.h
-- Installing: /opt/vc/include/interface/mmal/mmal_component.h
-- Installing: /opt/vc/include/interface/mmal/mmal_encodings.h
-- Installing: /opt/vc/include/interface/mmal/mmal_events.h
-- Installing: /opt/vc/include/interface/mmal/mmal_format.h
-- Installing: /opt/vc/include/interface/mmal/mmal_logging.h
-- Installing: /opt/vc/include/interface/mmal/mmal_parameters.h
-- Installing: /opt/vc/include/interface/mmal/mmal_parameters_audio.h
-- Installing: /opt/vc/include/interface/mmal/mmal_parameters_camera.h
-- Installing: /opt/vc/include/interface/mmal/mmal_parameters_clock.h
-- Installing: /opt/vc/include/interface/mmal/mmal_parameters_common.h
-- Installing: /opt/vc/include/interface/mmal/mmal_parameters_video.h
-- Installing: /opt/vc/include/interface/mmal/mmal_pool.h
-- Installing: /opt/vc/include/interface/mmal/mmal_port.h
-- Installing: /opt/vc/include/interface/mmal/mmal_queue.h
-- Installing: /opt/vc/include/interface/mmal/mmal_types.h
-- Installing: /opt/vc/lib/libmmal_core.so
-- Set runtime path of "/opt/vc/lib/libmmal_core.so" to ""
-- Installing: /opt/vc/include/interface/mmal/core/mmal_buffer_private.h
-- Installing: /opt/vc/include/interface/mmal/core/mmal_clock_private.h
-- Installing: /opt/vc/include/interface/mmal/core/mmal_component_private.h
-- Installing: /opt/vc/include/interface/mmal/core/mmal_core_private.h
-- Installing: /opt/vc/include/interface/mmal/core/mmal_port_private.h
-- Installing: /opt/vc/include/interface/mmal/core/mmal_events_private.h
-- Installing: /opt/vc/lib/libmmal_util.so
-- Set runtime path of "/opt/vc/lib/libmmal_util.so" to ""
-- Installing: /opt/vc/include/interface/mmal/util/mmal_component_wrapper.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_connection.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_default_components.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_graph.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_il.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_list.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_param_convert.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_util.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_util_params.h
-- Installing: /opt/vc/include/interface/mmal/util/mmal_util_rational.h
-- Installing: /opt/vc/bin/mmal_vc_diag
-- Set runtime path of "/opt/vc/bin/mmal_vc_diag" to ""
-- Installing: /opt/vc/lib/libmmal_vc_client.so
-- Set runtime path of "/opt/vc/lib/libmmal_vc_client.so" to ""
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_api.h
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_api_drm.h
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_client_priv.h
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_msgnames.h
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_msgs.h
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_opaque_alloc.h
-- Installing: /opt/vc/include/interface/mmal/vc/mmal_vc_shm.h
-- Installing: /opt/vc/lib/libmmal_components.so
-- Set runtime path of "/opt/vc/lib/libmmal_components.so" to ""

# noice.

```

Then recompile AVA raspivid...

```
make
sudo make install
# nana na na na 
sudo ldconfig
# boop
```

And thassit - RPi HiQuality Camera working perfectly :-D :-D :-D

# But that wasn't easy...

Next time around... possibly could've just done this:

```
sudo apt install libraspberrypi-bin
sudo apt install libraspberrypi-dev
```

Take a looky:

```
dpkg-query -L libraspberrypi-dev 
# looks about right

```

So maybe bash-script install_libs.sh, or subfolder

