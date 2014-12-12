/*
 * $QNXLicenseC:
 * Copyright 2012-2013, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable
 * license fees to QNX Software Systems before you may reproduce,
 * modify or distribute this software, or any work that includes
 * all or part of this software. Free development licenses are
 * available for evaluation and non-commercial purposes. For more
 * information visit http://licensing.qnx.com or email
 * licensing@qnx.com.
 *
 * This file may contain contributions from others. Please review
 * this entire file for other proprietary rights or license notices,
 * as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

/**
 * @file camera_api.h
 *
 * @brief Functions to take images and record videos with one or more cameras
 *        on a device.
 */

/**
 * @mainpage Camera library overview
 *
 * @section camera_intro_sec About the Camera service
 *
 * The Camera library provides an application with a consistent interface to
 * interact with one or more cameras connected to a device, as well as work with
 * metadata stored with images and videos.
 *
 * Depending on the camera hardware capabilities, you control the camera in the
 * following manner:
 *  - Connect and disconnect from a camera.
 *  - Start and stop the photo viewfinder and video viewfinder.
 *  - Use features on the camera, such as scene modes, change zoom, autofocus,
 *    auto white balance, and auto exposure.
 *  - Take pictures individually or in burst mode.
 *  - Encode video and save recordings to file.
 *  - Modify focus and access focus regions.
 *  - Turn flash and video-lights on and off.
 *
 * The Camera library @b does @b not automatically play audible shutter sounds
 * when a picture is taken or a video is recorded. Camera applications must
 * supply their own sound when a photo is captured or a video recording begins
 * and ends. While you can choose to not have a shutter sound when taking a
 * picture or shooting a video - you are responsible to ensure that
 * the application adheres to the local laws of the regions in which you wish to
 * distribute the application.
 *
 * For example, it is illegal to mute or modify the shutter sound of a camera
 * application in Japan and Korea. Ensure that you comply with the laws and
 * regulations for the countries in which you distribute your application.
 * For more information, see the BlackBerry World Vetting Criteria at
 * https://appworld.blackberry.com/isvportal/home.do.
 *
 * @section camapi_buffer_access Camera image buffer access
 * The camera service provides read access to image data from different
 * stages in the imaging datapath (image buffers). Applications access buffers
 * by binding callback functions or events to a particular stage of the imaging
 * datapath.
 *
 * The camera API is widely adaptable to the specific design patterns of your
 * application due to the option of using either threaded callbacks
 * (@e callback @e mode) or events received in an event-loop (@e event @e mode).
 * Using events does not preclude you from also using callbacks.
 * The two are interoperable and the camera API internally implements
 * callback threads using events.
 *
 * @subsection camapi_event_mode About event mode
 * Camera events are used asynchronously to notify an application when the
 * camera service has some data or status information available that can be
 * acted upon.  For example, a status event may indicate that a change in focus
 * has occurred, that the shutter has fired, or that a video recording has run
 * out of disk space.
 *
 * Status events do not have buffers associated with them, but instead carry
 * just enough data to convey the necessary status information.  In comparison,
 * an imaging event signals to the application that a data buffer has become
 * available and can be retrieved and processed.  An example of an imaging event
 * would be a viewfinder buffer or a still image buffer becoming available.
 *
 * When an imaging event is received, the application can then safely call one
 * of the get-buffer functions. For example, the @c
 * camera_get_viewfinder_buffers() function processes the data appropriately,
 * and then releases the buffer back to the camera service using @c
 * camera_return_buffer() function.
 *
 * To bind an event to a given point in the camera datapath, use one of the
 * following functions:
 * - @c camera_enable_image_event()
 * - @c camera_enable_postview_event()
 * - @c camera_enable_shutter_event()
 * - @c camera_enable_status_event()
 * - @c camera_enable_video_event()
 * - @c camera_enable_viewfinder_event()
 *
 * Multiple events can be bound to the same point in the datapath, but this may
 * be less efficient than dispatching multiple tasks after receiving a single
 * event in your application.
 *
 * To unbind an event from a given point in the camera datapath, use the @c
 * camera_disable_event() function.
 *
 * When a non-status event occurs, such as  a shutter or status event, your
 * application can retrieve the buffer associated with this event by calling
 * the corresponding get function:
 * - @c camera_get_image_buffers()
 * - @c camera_get_postview_buffers()
 * - @c camera_get_video_buffers()
 * - @c camera_get_viewfinder_buffers()
 *
 * When your application is finished processing the buffer, (e.g. when you save
 * the image buffer to disk) the buffer must be returned to the camera service
 * using the @c camera_return_buffer() function. No additional buffers are made
 * available to your application until you return the previously acquired
 * buffer. Since some events happen more frequently than others (e.g.
 * saving the image buffer to disk) it may be necessary to dispatch tasks using
 * separate threads to keep your event loop suitably serviced.
 *
 * For example, if you are using an algorithm to detect a smile, the algorithm
 * searches through multiple viewfinder frames until a still image is acquired.
 * Since it is possible to take more time to save this image to disk than the
 * inter-frame period of the viewfinder frames, it is best to process the
 * image-saving task on a different thread than the viewfinder-processing task.
 * This problem is also resolved by using the available callback threads.
 *
 * @subsection camapi_callback_mode About callback mode
 * Callbacks are one mechanism of asynchronously accessing camera image data
 * as well as status information. You provide custom code to be executed as a
 * callback when performing camera operations such as taking a picture or
 * encoding video. Using callbacks provide you a great amount of flexibility
 * to control what occurs in your application when a function executes. For
 * example, you can use callbacks to perform image processing or to save data
 * to disk. Callback functions execute in a separate thread, so you need to be
 * sure that your code is thread-safe through the use of appropriate thread
 * synchronization primitives (mutexes, semaphores, condvars, etc.).
 *
 * Unlike events, which can be explicitly bound to a specific location in the
 * image datapath, callbacks are implicitly registered only when invoking the
 * following functions:
 *  - @c camera_start_video_viewfinder()
 *  - @c camera_start_photo_viewfinder()
 *  - @c camera_take_photo()
 *  - @c camera_take_burst()
 *  - @c camera_start_burst()
 *  - @c camera_start_video()
 *  - @c camera_start_encode()
 *
 * Callbacks are deregistered when the operation started by one of the above
 * functions completes.  For example, when the @c camera_stop_photo_viewfinder()
 * function is invoked, any callbacks registered during the @c
 * camera_start_photo_viewfinder() function call are deregistered.
 *
 * These are the callback signatures for various Camera library functions:
 *
 * - image_callback: The callback is invoked when the final image data becomes
 *                   available. You can choose to save the image to disk or
 *                   perform other post-processing algorithms on the image.
 *                   The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the image data.  This data is
 *                              guaranteed to be valid only while your callback
 *                              function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * - postview_callback: The callback is invoked when the postview image data is
 *                      available. The image data provided is a
 *                      preview-sized version of the captured still image. For
 *                      example, you could display the preview-size image
 *                      instead of down-scaling and decompressing the final
 *                      image. The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                              which describes the postview frame.  This data
 *                              is only guaranteed to be valid while your
 *                              callback function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * - raw_callback: This callback is reserved for future use. Do not use.
 *
 * - shutter_callback: The callback is invoked when the shutter activates on the
 *                     camera. It's your responsibility to play audible shutter
 *                     sounds when a picture is taken or a video is recorded.
 *                     While you can choose to not have a shutter sound when
 *                     taking a picture - you are responsible to ensure that
 *                     the application adheres to the local laws of the regions
 *                     in which you wish to distribute the application.
 *                     For example, it is illegal to mute or modify the shutter
 *                     sound of a camera application in Japan and Korea. Ensure
 *                     that you comply with the laws and regulations for the
 *                     countries in which you distribute your application. For
 *                     more information, see the BlackBerry World Vetting
 *                     Criteria at
 *                     https://appworld.blackberry.com/isvportal/home.do.
 *                     If you use burst mode to capture images in rapid
 *                     succession, choose an appropriate moment to play the
 *                     shutter sound rather than play the shutter sound
 *                     repeatedly.
 *
 *
 *                     The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     void*)
 *  @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * - status_callback: The callback is invoked when additional data relevant to
 *                    the state of the camera is being reported. For example,
 *                    the time remaining on disk for a disk space warning event.
 *                    The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_devstatus_t,
 *                     uint16_t,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_dev_status_t: The status event that occurred.
 *          - uint16_t: Any extra data associated with the status event that
 *                      occurred.
 *          - void*: The user-specified argument in the @c arg argument.
 *                   The function is a callback that gets invoked when
 *                   status events occur.
 *
 * - video_callback: The callback is invoked when an uncompressed video frame
 *                   becomes available. The callback has the following
 *                   signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_buffer_t*: A pointer to a @c ::camera_buffer_t structure
 *                                which describes the video frame.  This data is
 *                                only guaranteed to be valid while your callback
 *                                function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 *    @b Note: On platforms that advertise the @c #CAMERA_FEATURE_PREVIEWISVIDEO
 *             feature, video frames are not explicitly available.
 *             Instead, use the frames returned by the viewfinder_callback.
 *
 * - viewfinder_callback: The callback is invoked when a viewfinder buffer
 *                        becomes available. The viewfinder is rendered to a
 *                        screen window by the camera service. You are not
 *                        required to add display code, unless you need to
 *                        perform custom output using some other mechanism.
 *                        The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_buffer_t*: A pointer to a @c #camera_buffer_t structure
 *                                which describes the viewfinder frame. This
 *                                data is only guaranteed to be valid while your
 *                                callback function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * - enc_video_callback: The callback is invoked when an encoded video frame
 *                       becomes available.
 *                       The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_buffer_t*: A pointer to a @c #camera_buffer_t structure
 *                                which describes the encoded frame.  This data
 *                                is only guaranteed to be valid while your
 *                                callback function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * - enc_audio_callback: The callback is invoked when an encoded audio frame
 *                       becomes available.
 *                       The callback has the following signature:
 * @code
 * void function_name( camera_handle_t,
 *                     camera_buffer_t*,
 *                     void*)
 * @endcode
 *          - ::camera_handle_t: The handle of the camera invoking the callback.
 *          - ::camera_buffer_t*: A pointer to a @c #camera_buffer_t structure
 *                                which describes the encoded frame.  This data
 *                                is only guaranteed to be valid while your
 *                                callback function is executing.
 *          - void*: The user-specified argument in the @c arg argument.
 *
 * @section camapi_manual_settings Manual camera settings
 *
 * You can configure various manual settings (i.e., ISO, shutter
 * speed, white white balance, and aperture) after you start the
 * viewfinder on the camera. Changes in settings may not be visible for several
 * frames due to latency in the image processing pipeline.
 *
 * For example, when you use an exposure mode (@c #camera_exposuremode_t) that
 * has a manual component such as @c #CAMERA_EXPOSUREMODE_ISO_PRIORITY and you
 * change the ISO setting (@c camera_set_manual_iso()), you may not see the
 * results of the ISO change until several frames later.
 *
 */

#ifndef __CAMERA_API_H__
#define __CAMERA_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <screen/screen.h>
#include <sys/siginfo.h>

/**
 * The version of the Camera library. The version is used for IPC handshaking
 * and communication between the application and the camera service.
 * You can compare @c #CAMERA_API_VERSION with the value returned by the @c
 * camera_get_api_version() function to determine if the runtime library is
 * different from the version your application was compiled with. Differences
 * may indicate potential incompatibilities.
 */
#define CAMERA_API_VERSION    2

/**
 * Error codes for the Camera library.
 */
typedef enum {
    /**
     * The function call to the camera completed successfully.
     */
    CAMERA_EOK = EOK,
    /**
     * The function call failed because the specified camera was not available.
     * Try to call the function again.
     */
    CAMERA_EAGAIN = EAGAIN,
    /**
     * The function call failed because of an invalid argument.
     */
    CAMERA_EINVAL = EINVAL,
    /**
     * The function call failed because the specified camera was not found.
     */
    CAMERA_ENODEV = ENODEV,
    /**
     * The function call failed because of a file table overflow.
     */
    CAMERA_EMFILE = EMFILE,
    /**
     * The function call failed because an invalid handle to a @c
     * #camera_handle_t value was used.
     */
    CAMERA_EBADF = EBADF,
    /**
     * The function call failed because the necessary permissions to access
     * the camera are not available.
     */
    CAMERA_EACCESS = EACCES,
    /**
     * The function call failed because an invalid file descriptor was used.
     */
    CAMERA_EBADR = EBADR,
    /**
     * The function call failed because the requested data does not
     * exist.
     */
    CAMERA_ENODATA = ENODATA,
    /**
     * The function call failed because the specified file or directory does
     * not exist.
     */
    CAMERA_ENOENT = ENOENT,
    /**
     * The function call failed because memory allocation failed.
     */
    CAMERA_ENOMEM = ENOMEM,
    /**
     * The function call failed because the requested operation is not
     * supported.
     */
    CAMERA_EOPNOTSUPP = EOPNOTSUPP,
    /**
     * The function call failed due to communication problem or time-out with
     * the camera.
     */
    CAMERA_ETIMEDOUT = ETIMEDOUT,
    /**
     * The function call failed because an operation on the camera is already in
     * progress. In addition, this error can indicate that a call could not be
     * completed because it was invalid or completed already. For example,
     * if you called the @c camera_stop_video() function but the camera had
     * already stopped recording video, this error code would be returned.
     */
#ifdef EALREADY_NEW
    CAMERA_EALREADY = EALREADY_NEW,
#else
    CAMERA_EALREADY = EALREADY,
#endif
    /**
     * The function call failed because the camera is busy.  Typically you
     * receive this error when you try to open a camera while the camera or
     * its required resources are in use.
     */
    CAMERA_EBUSY = EBUSY,
    /**
     * The function call failed because the disk is full.  This typically
     * happens when you are trying to start a video recording and less than
     * the system-reserved amount of disk space remains.
     */
    CAMERA_ENOSPC = ENOSPC,

    /**
     * The function call failed because the Camera library has not been
     * initialized.
     */
    CAMERA_EUNINIT = 0x1000,
    /**
     * The function call failed because the registration of a callback failed.
     */
    CAMERA_EREGFAULT,
    /**
     * The function call failed because the microphone is already in use.
     */
    CAMERA_EMICINUSE,
    /**
     * The function call failed because the operation cannot be completed while
     * the camera @c #CAMERA_UNIT_DESKTOP is in use.
     */
    CAMERA_EDESKTOPCAMERAINUSE,
    /**
     * The function call failed because the camera is in the power down state.
     */
    CAMERA_EPOWERDOWN,
    /**
     * The function call failed because the 3A have been locked.
     */
    CAMERA_3ALOCKED

    /*...*/
} camera_error_t;


/**
 * @brief The enumerated type specifies the image properties list.
 *
 * These properties are used as keys for the following functions:
 * - @c camera_set_photo_property()
 * - @c camera_set_photovf_property()
 * - @c camera_set_video_property()
 * - @c camera_set_videovf_property()
 * - @c camera_get_photo_property()
 * - @c camera_get_photovf_property()
 * - @c camera_get_video_property()
 * - @c camera_get_videovf_property()
 *
 * Each key has a type associated with it.
 */
typedef enum {
    /**
     * @internal
     * End-of-list identifier.
     */
    CAMERA_IMGPROP_END = -1,
    /**
     * The image format as a @c ::camera_frametype_t value.
     */
    CAMERA_IMGPROP_FORMAT = 0,
    /**
     * The width of image as an @c unsigned @c int value.
     */
    CAMERA_IMGPROP_WIDTH,
    /**
     * The height of the image as an @c unsigned @c int value.
     */
    CAMERA_IMGPROP_HEIGHT,
    /**
     * The frame rate of the image sequence as a @c double value.
     * When @c #CAMERA_IMGPROP_VARIABLEFRAMERATE is set to a
     * value of 1, it indicates the maximum frame rate to use for the image
     * sequence.
     */
    CAMERA_IMGPROP_FRAMERATE,
    /**
     * @deprecated Do not use this property. Instead, use the appropriate
     *             bitrate property that corresponds to the video codec. For
     *             example, if you configure an H.264/AVC video recording, use
     *             the @c camera_set_videoencoder_parameter() function
     *             to set the @c #CAMERA_H264AVC_BITRATE parameter.
     *
     * The units are in bits per second as an @c unsigned @c int
     * value.
     */
    CAMERA_IMGPROP_BITRATE,
    /**
     * @deprecated Do not use this property. Instead, use the appropriate
     *             bitrate property that corresponds to the video codec. For
     *             example, if you configure an H.264/AVC video recording, use
     *             the @c camera_set_videoencoder_parameter() function
     *             to set the @c #CAMERA_H264AVC_KEYFRAMEINTERVAL parameter.
     *
     * The interval (in frames) between the generation of each
     * keyframe as an @c unsigned @c int value.
     */
    CAMERA_IMGPROP_KEYFRAMEINTERVAL,
    /**
     * The image rotations (in degrees) as an @c unsigned @c int
     * value. Rotations occur clockwise.
     */
    CAMERA_IMGPROP_ROTATION,
    /**
     * Enable built-in stabilization algorithms to help avoid a
     * blurry image. The value is specified as an @c unsigned @c int value. A
     * value of 0 indicates that stabilization is off and a value of 1
     * indicates that stabilization is on.  Note that @c #CAMERA_IMGPROP_MAXFOV
     * must be set to 0 when starting the viewfinder before stabilization can
     * be enabled.  To enable stabilization for video, @c
     * #CAMERA_FEATURE_VIDEOSTABILIZATION must be available on the camera.  To
     * enable stabilization for photo, @c #CAMERA_FEATURE_PHOTOSTABILIZATION
     * must be available on the camera.
     */
    CAMERA_IMGPROP_STABILIZATION,
    /**
     * Zoom factor is used as an @c unsigned @c int value.
     * The zoom level is a value supported by the camera hardware and
     * represents digital zoom or optical zoom. Optical zoom is
     * only supported if the camera supports it. Most digital cameras
     * support digital zoom.
     */
    CAMERA_IMGPROP_ZOOMFACTOR,
    /**
     * The viewfinder can use hardware acceleration for @e blitting.
     * To use this feature, the hardware acceleration for the blitting feature
     * must be available (@c #CAMERA_FEATURE_VFHWOVERLAY). Use
     * the @c camera_can_feature() function to determine whether the camera
     * supports the feature.
     *
     * Blitting is an operation where you copy the viewfinder buffer
     * to the video display. For more information, see @c
     * SCREEN_USAGE_OVERLAY used in the @c screen_set_window_property_iv()
     * function in the Screen and Windowing Library. When you use this value,
     * the viewfinder window uses @c SCREEN_USAGE_OVERLAY when it is available.
     */
    CAMERA_IMGPROP_HWOVERLAY,
    /**
     * The JPEG quality setting of the camera as an @c int value.
     * The value represents a percentage.
     */
    CAMERA_IMGPROP_JPEGQFACTOR,
    /**
     * The window group ID the viewfinder should be created in, as a @c const
     * @c char* value. For more information, see the Screen and Windowing
     * library.
     */
    CAMERA_IMGPROP_WIN_GROUPID,
    /**
     * The window ID to apply to the viewfinder window that is created
     * as a @c const @c char* value.
     */
    CAMERA_IMGPROP_WIN_ID,
    /**
     * Burst mode should be used as an @c int value. A value
     * of 0 indicates to disable burst capture mode while a value of 1 indicates
     * to enable burst capture mode.
     */
    CAMERA_IMGPROP_BURSTMODE,
    /**
     * The frame rate divisor to apply when operating in burst capture
     * mode.  A value of 1 will yield a capture frame rate equal to the
     * viewfinder frame rate divided by 1.  A value of 2 will yield a capture
     * frame rate equal to the viewfinder frame rate divided by 2. For example,
     * every second frame is captured.  Fractional values are allowed.
     */
    CAMERA_IMGPROP_BURSTDIVISOR,
    /**
     * @deprecated Do not use this property. Instead, use the appropriate
     *             slice size property that corresponds to the video codec. For
     *             example, if you configure an H.264/AVC video recording, use
     *             the @c camera_set_videoencoder_parameter() function
     *             to set the @c #CAMERA_H264AVC_SLICESIZE parameter.
     *
     * The maximum slice size (in bytes) to use for video encoding
     * that supports slice encoding. Slice encoding is the encoding of a frame
     * into multiple slices for error resilience.
     */
    CAMERA_IMGPROP_SLICESIZE,
    /**
     * The variable frame rate should be enabled for this
     * image sequence. To use this feature, variable frame rate must be
     * supported for the viewfinder (@c
     * #CAMERA_FEATURE_PHOTOVFVARIABLEFRAMERATE). The use of variable frame
     * rate mode allows the camera to decrease the frame rate in order to
     * increase exposure time to compensate for poor lighting conditions.
     * You can use variable frame rate to vary the frame rate based on the
     * lighting conditions in a range defined as follows:
     * @code
     * CAMERA_IMGPROP_FRAMERATE >= frame rate >= CAMERA_IMGPROP_MINFRAMERATE
     * @endcode
     * The value of this property is specified as an @c unsigned @c int value.
     * A value of 0 indicates that variable frame rate is disabled (frame rate
     * is fixed as specified by @c #CAMERA_IMGPROP_FRAMERATE)
     * and a value of 1 indicates that variable frame rate is enabled.
     */
    CAMERA_IMGPROP_VARIABLEFRAMERATE,
    /**
     * The minimum frame rate of the image sequence is a @c double
     * value.
     * @b Note: If variable frame rate mode is enabled, be sure to change @c
     * #CAMERA_IMGPROP_FRAMERATE and @c #CAMERA_IMGPROP_MINFRAMERATE at the same
     * time via a single call to the @c camera_set_photovf_property() function.
     * Doing so ensures that range checks can be properly performed.
     */
    CAMERA_IMGPROP_MINFRAMERATE,
    /**
     * An embedded window will be created (see Screen and Windowing
     * API on window-types). If the viewfinder is being created as a child of an
     * existing child window, then this flag must be set.
     */
    CAMERA_IMGPROP_ISEMBEDDED,
    /**
     * A window will be created (see Screen and Windowing
     * API on window-types). This flag must be set to true in order to have a
     * @c ::camera_frametype_t image buffer posted to a viewfinder window.
     */
    CAMERA_IMGPROP_CREATEWINDOW,
    /**
     * Whether automatic embedding of metadata orientation hints is enabled.
     * This flag should be set to true in cases where the desired
     * @c #CAMERA_IMGPROP_ROTATION value cannot be selected due to limitations
     * in available rotation values reported by @c camera_get_photo_rotations().
     */
    CAMERA_IMGPROP_METAORIENTATIONHINT,
    /**
     * Indicates that the FOV (field of view) of the viewfinder should not be
     * cropped when the viewfinder is started.  A value of 0 indicates that
     * the viewfinder may be started with cropping applied in order to support
     * use of the @c #CAMERA_IMGPROP_STABILIZATION property.  A value of 1
     * indicates that the viewfinder will provide the widest possible field of
     * view at startup and will disallow attempts to use the @c
     * #CAMERA_IMGPROP_STABILIZATION property.
     */
    CAMERA_IMGPROP_MAXFOV,
    /**
     * The video codec used when generating compressed video files or streams
     * using @c camera_start_video() or @c camera_start_encode().  The video
     * codec value is of type @c ::camera_videocodec_t.
     */
    CAMERA_IMGPROP_VIDEOCODEC,
    /**
     * The audio codec used when generating compressed video files or streams
     * using @c camera_start_video() or @c camera_start_encode().  The audio
     * codec value is of type @c ::camera_audiocodec_t.
     */
    CAMERA_IMGPROP_AUDIOCODEC

} camera_imgprop_t;


/**
 * @brief This enumerated type specifies the camera physical properties list
 *
 *        These properties are used as keys for the @c
 *        camera_get_physical_property() function. Each key is associated with
 *        a value of the type specified for each enumerator.
 */
typedef enum {
    /**
     * @internal
     * end-of-list identifier.
     */
    CAMERA_PHYSPROP_END = -1,
    /**
     * The focal length of the camera in millimeters as a @c double value.
     */
    CAMERA_PHYSPROP_FOCALLENGTH = 0,
    /**
     * The horizontal field of view of the camera when set to its minimum zoom
     * factor and at its full-frame resolution. The value (in degrees) is a @c
     * double value. The horizontal axis is defined as the axis running
     * from left to right of the device when held in its default orientation
     * (e.g., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_HORIZONTALFOV,
    /**
     * The vertical field of view of the camera when set to its minimum zoom
     * factor and its full-frame resolution. The value (in degrees) is a @c
     * double value. The vertical axis is defined as the axis running
     * from top to bottom of the device when held in its default orientation
     * (e.g., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_VERTICALFOV,
    /**
     * The full-frame width of the imaging sensor in millimeters as a
     * @c double value. The width corresponds to the sensor axis which runs
     * from left to right of the device when held in its default orientation
     * (e.g., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORWIDTH,
    /**
     * The full-frame height of the imaging sensor in millimeters as a @c double
     * value.  The height corresponds to the sensor axis which runs from top
     * to bottom of the device when held in its default orientation
     * (e.g., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORHEIGHT,
    /**
     * The magnification ratio between the maximum zoom factor
     * and the minimum zoom factor as a @c double value.
     * For example, a ratio of 3.0 indicates that a fully zoomed-in image
     * is expanded by a magnification factor of 3.0 times when compared with the
     * fully zoomed-out version of the image.
     */
    CAMERA_PHYSPROP_MAXZOOMRATIO,
    /**
     * The full-frame width of the imaging sensor in pixels as a
     * @c uint32_t value. The width corresponds to the sensor axis which runs
     * from left to right of the device when held in its default orientation
     * (e.g., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORWIDTHPIXELS,
    /**
     * The full-frame height of the imaging sensor in pixels as a @c uint32_t
     * value.  The height corresponds to the sensor axis which runs from top
     * to bottom of the device when held in its default orientation
     * (e.g., the BlackBerry logo is upright).
     */
    CAMERA_PHYSPROP_SENSORHEIGHTPIXELS
} camera_physprop_t;


/**
 * The status of the camera. The values are returned in callback
 * functions that you register. The purpose of the callback functions is to
 * provide notifications about changes in the state to the camera service. For
 * example, the changes to the state of the camera service can include:
 * - whether the viewfinder was started
 * - whether recording was stopped
 */
typedef enum {
    /**
     * The status of the camera is not known.
     */
    CAMERA_STATUS_UNKNOWN = 0,
    /**
     * No user is connected to the camera.
     */
    CAMERA_STATUS_DISCONNECTED,
    /**
     * A user is connected to the camera but the camera is in the
     * idle state.
     */
    CAMERA_STATUS_CONNECTED,
    /**
     * The camera is not powered. This is typical when the device is going into
     * a standby state.
     */
    CAMERA_STATUS_POWERDOWN,
    /**
     * The photo viewfinder has started.
     */
    CAMERA_STATUS_PHOTOVF,
    /**
     * The video viewfinder has started.
     */
    CAMERA_STATUS_VIDEOVF,
    /**
     * The recording has stopped due to a memory error or multimedia
     * framework error (used by the video encoder). The error is received from
     * the encoding graph.
     */
    CAMERA_STATUS_MM_ERROR,
    /**
     * A file has exceeded the maximum size. Recordings
     * will stop with this error when the size is getting too close to the
     * limit.
     */
    CAMERA_STATUS_FILESIZE_ERROR,
    /**
     * The recording has stopped because there is no more disk space
     * available.
     */
    CAMERA_STATUS_NOSPACE_ERROR,
    /**
     * The capture of a still image failed and was aborted.
     */
    CAMERA_STATUS_CAPTURE_ABORTED,
    /**
     * The user-configurable time-remaining threshold has been
     * exceeded while recording video. The default is 60 seconds, but you can
     * change the time-remaining threshold using the @c
     * camera_set_video_filesize_warning() function.
     */
    CAMERA_STATUS_FILESIZE_WARNING,
    /**
     * The focus changed on the camera.
     */
    CAMERA_STATUS_FOCUS_CHANGE,
    /**
     * A warning that the camera is about to free resources
     * due to a power-down or arbitration event (resources needed elsewhere).
     * You should release camera resources, such as stopping recordings,
     * stopping viewfinders, and releasing buffers.  This event happens when
     * the device is about to enter standby mode or a higher-priority process
     * needs access to resources that are shared with the camera service.
     */
    CAMERA_STATUS_RESOURCENOTAVAIL,
    /**
     * Video encoding has been paused.  This pause is due to
     * resources needed for video encoding not being currently available
     * (needed elsewhere), but in the future this pause may occur for other
     * reasons.  Once resources are available again, @c
     * #CAMERA_STATUS_VIDEO_RESUME status change will be sent.
     */
    CAMERA_STATUS_VIDEO_PAUSE,
    /**
     * Video encoding has resumed again following a pause or has
     * started encoding for the first time.
     */
    CAMERA_STATUS_VIDEO_RESUME,
    /**
     * Still capture has completed and you may now take another picture.
     * This occurs at the end of a @c camera_take_photo() or
     * @c camera_take_burst() cycle, or when @c camera_stop_burst() is called.
     */
    CAMERA_STATUS_CAPTURECOMPLETE,
    /**
     * The camera has been repowered. This status typically occurs when the
     * device returns from the standby (i.e., @c #CAMERA_STATUS_POWERDOWN)
     * state.
     */
    CAMERA_STATUS_POWERUP,
    /**
     * For system privacy reasons, the viewfinder has been frozen.  When the
     * viewfinder is frozen, the same frame is continually sent until the
     * @c #CAMERA_STATUS_VIEWFINDER_UNFREEZE status is sent.
     */
    CAMERA_STATUS_VIEWFINDER_FREEZE,
    /**
     * The viewfinder that was previously frozen has resumed the display of
     * frames.  This status can only be received after the
     * @c #CAMERA_STATUS_VIEWFINDER_FREEZE status has been received previously.
     */
    CAMERA_STATUS_VIEWFINDER_UNFREEZE,
    /**
     * This indicates that the low light status has changed. The status callback
     * extra data will be 1 when the camera enters the low light state, and 0
     * when it exits the low light state.
     */
    CAMERA_STATUS_LOWLIGHT
} camera_devstatus_t;

/**
 * The reason that the camera was turned off or was shutdown.
 *
 * When you use @e event mode, you can use @c camera_get_status_details()
 * to retrieve the reason the camera was turned off. The @c devstatusextra
 * argument is one of the listed enumerations from this enumerated type.
 * For information about the event mode, see @ref camapi_event_mode.
 *
 * When you are in @e callback mode, you can retrieve the reason using the third
 * argument from the status callback. For information about the callback
 * arguments, see @ref @ref camapi_callback_mode.
 */

typedef enum {
    /**
     * The camera was turned off for an unknown reason.
     */
    CAMERA_POWERDOWNREASON_UNKNOWN = 0,

    /**
     * The camera was turned off because the device went into standby mode.
     */
    CAMERA_POWERDOWNREASON_STANDBY,

    /**
     * The camera was turned off because the shared resources used by the camera
     * were required by another component of the operating system.
     */
    CAMERA_POWERDOWNREASON_RESOURCEARBITRATION,

    /**
     * The camera was turned off to prevent damage due to excessive heat.
     */
    CAMERA_POWERDOWNREASON_THERMAL,
} camera_powerdownreason_t;

/**
 * Represents the cameras on the device. Cameras can be
 * physically located on the front and rear of a device. It is possible for
 * devices to have more than two cameras.
 */
typedef enum {
    /**
     * No camera is available on the device.
     */
    CAMERA_UNIT_NONE = 0,
    /**
     * The camera on the front of the device.
     */
    CAMERA_UNIT_FRONT,
    /**
     * The camera on the rear of the device.
     */
    CAMERA_UNIT_REAR,
    /**
     * The virtual @e desktop camera used for sharing your desktop.
     * Sharing your desktop is a capability that's available for some devices.
     */
    CAMERA_UNIT_DESKTOP,
    /**
     * The virtual @e secondary desktop camera used for sharing your secondary
     * screen desktop output.
     * Sharing your secondary desktop is a capability that's available for some
     * devices.
     */
    CAMERA_UNIT_SECONDARY_DESKTOP,
    /**
     * For internal use only. The value is used to size the array for the
     * maximum number of cameras supported.
     */
    CAMERA_UNIT_NUM_UNITS
} camera_unit_t;


/**
 * A 32-bit value representing a handle used to identify an open instance of
 * a logical camera unit on a device. A handle to the camera is returned by
 * functions such as the @c camera_open() function and is released by the @c
 * camera_close() function. A handle, when available, is basically a file
 * descriptor that the user can use, provided they have the proper permissions
 * to access the camera. Various Camera library calls use the handle to interact
 * with the camera.
 */
typedef int32_t camera_handle_t;
/**
 * A safe-initializer value for @c camera_handle_t values. Use this value to
 * check that correct initialization occurred and whether a call to the @c
 * camera_open() function was successful. A camera handle should be set
 * to this value during initialization or when the handle is closed.
 */
#define CAMERA_HANDLE_INVALID  (-1)

/**
 * The camera capabilities or features available on the camera. The enumerated type
 * is used with the @c camera_has_feature() and @c camera_can_feature()
 * functions.
 */
typedef enum {
    /**
     * The camera supports queries from the @c
     * camera_can _feature() and @c camera_has_feature() functions.
     */
    CAMERA_FEATURE_FBM = 0,
    /**
     * It is possible to take photos (still images).
     */
    CAMERA_FEATURE_PHOTO = 1,
    /**
     * It is possible to encode video.
     */
    CAMERA_FEATURE_VIDEO = 2,
    /**
     * Zoom is available in photo viewfinder mode.
     */
    CAMERA_FEATURE_PHOTOZOOM = 3,
    /**
     * Zoom is available in the video viewfinder mode.
     */
    CAMERA_FEATURE_VIDEOZOOM = 4,
    /**
     * Zero-shutter lag is available.
     */
    CAMERA_FEATURE_ZSL = 5,
    /**
     * Burst mode is available for taking multiple photos
     * consecutively.
     *
     * @b Note: When @c #CAMERA_FEATURE_BURST is available, but @c
     * #CAMERA_FEATURE_CONTINUOUSBURST isn't, then only the @c
     * camera_take_burst() function can be used. The @c camera_start_burst()
     * function will not work
     */
    CAMERA_FEATURE_BURST = 6,
    /**
     * Exposure bracketing is available in burst capture mode.
     */
    CAMERA_FEATURE_EVBRACKETING = 7,
    /**
     * Flash is available.
     */
    CAMERA_FEATURE_FLASH = 8,
    /**
     * An on-board light source is available for use with video
     * capture.
     */
    CAMERA_FEATURE_VIDEOLIGHT = 9,
    /**
     * There is no standalone video buffer stream available.
     * Preview buffers are used for both viewfinder and video encoding.
     */
    CAMERA_FEATURE_PREVIEWISVIDEO = 10,
    /**
     * Autofocus is available.
     */
    CAMERA_FEATURE_AUTOFOCUS = 11,
    /**
     * Manual focus is available.
     */
    CAMERA_FEATURE_MANUALFOCUS = 12,
    /**
     * It is possible to focus on a specific region
     * in the photo.
     */
    CAMERA_FEATURE_REGIONFOCUS = 13,
    /**
     * Macro focus mode is available. Macro mode allows you to
     * focus on objects that are close to the camera, such as 10 centimeters
     * away.
     */
    CAMERA_FEATURE_MACROFOCUS = 14,
    /**
     * Focus-assist mode is available. Focus assist turns on the
     * light before taking a picture in low-light conditions. Turning on the
     * light improves focus performance in low-light conditions.
     */
    CAMERA_FEATURE_FOCUSASSIST = 15,
    /**
     * The viewfinder can use hardware acceleration for
     * blitting. Blitting is an operation where you copy the viewfinder buffer
     * to the video display. For more information, see @c SCREEN_USAGE_OVERLAY
     * in the @c screen_set_window_property_iv() function from the Screen and
     * Windowing API.
     */
    CAMERA_FEATURE_VFHWOVERLAY = 16,
    /**
     * Region exposure is available. Region exposure allows you
     * to perform spot and partial metering to regions of an image.
     */
    CAMERA_FEATURE_REGIONEXPOSURE = 17,
    /**
     * Region white balance is available. Region white balance uses the image
     * data in the user-specified region to make white balance adjustment
     * (color correction) computations.
     */
    CAMERA_FEATURE_REGIONWHITEBALANCE = 18,
    /**
     * Continuous-burst mode is available. Continuous burst
     * allows for multiple images to be taken over an indefinite time-frame.
     *
     * @b Note: When @c #CAMERA_FEATURE_BURST is available, but @c
     * #CAMERA_FEATURE_CONTINUOUSBURST isn't, then only the @c
     * camera_take_burst() function can be used. The @c camera_start_burst()
     * function will not work.
     */
    CAMERA_FEATURE_CONTINUOUSBURST = 19,
    /**
     * Face detection is available in the viewfinder image
     * stream. Face detection permits you retrieve the coordinates of the faces
     * detected in the scene via the accompanying preview metadata.
     */
    CAMERA_FEATURE_VFFACEDETECT = 20,
    /**
     * Face detection is available in the still image
     * stream. Face detection permits you retrieve the coordinates of the faces
     * detected in the scene via the accompanying still image metadata.
     */
    CAMERA_FEATURE_FACEDETECT = 21,
    /**
     * Variable frame rate is supported for photo viewfinder.
     * For more information, see the description for the @c
     * #CAMERA_IMGPROP_VARIABLEFRAMERATE.
     */
    CAMERA_FEATURE_PHOTOVFVARIABLEFRAMERATE = 22,
    /**
     * Auto exposure is available.
     */
    CAMERA_FEATURE_AUTOEXPOSURE = 23,
    /**
     * Auto white balance is available.
     */
    CAMERA_FEATURE_AUTOWHITEBALANCE = 24,
    /**
     * Manual exposure is available.
     */
    CAMERA_FEATURE_MANUALEXPOSURE = 25,
    /**
     * Manual white balance is available.
     */
    CAMERA_FEATURE_MANUALWHITEBALANCE = 26,
    /**
     * Premap of camera buffers is available.
     */
    CAMERA_FEATURE_PREMAPBUFFERS = 27,
    /**
     * Low light notification available.
     */
    CAMERA_FEATURE_LOWLIGHT_STATUS = 28,
    /**
     * Histogram feature availability
     */
    CAMERA_FEATURE_VFHISTOGRAM = 29,
    /**
     * Video stabilization is available on the camera.  For more information,
     * see @c #CAMERA_IMGPROP_STABILIZATION.
     */
    CAMERA_FEATURE_VIDEOSTABILIZATION = 30,
    /**
     * Photo stabilization is available on the camera.  For more information,
     * see @c #CAMERA_IMGPROP_STABILIZATION.
     */
    CAMERA_FEATURE_PHOTOSTABILIZATION = 31,
    /**
     * An end-of-list identifier. Also indicates the total number of features
     * recognized by the Camera library.
     */
    CAMERA_FEATURE_NUMFEATURES
} camera_feature_t;

/**
 * The maximum length of a filename returned by camera-roll functions. The value
 * is useful for you to determine the largest @c char* buffer to allocate. The
 * camera roll is a directory where photo and video files can be saved.
 */
#define CAMERA_ROLL_NAMELEN  (256)

/**
 * The frame types identifiers for an image buffer. Frame types are used to
 * distinguish between frame descriptors within a @c camera_buffer_t structure.
 */
typedef enum {
    /**
     * The frame type has no associated format, recognized
     * format, or is unformatted.
     */
    CAMERA_FRAMETYPE_UNSPECIFIED = 0,
    /**
     * The frame type is NV12 formatted data. The @c
     * ::camera_frame_nv12_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_NV12,
    /**
     * The frame type is 32-bit ARBG data. The @c
     * ::camera_frame_rgb8888_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_RGB8888,
    /**
     * The frame type is 24-bit RGB data. The @c
     * ::camera_frame_rgb888_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_RGB888,
    /**
     * The frame type is JPEG image data. The @c
     * ::camera_frame_jpeg_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_JPEG,
    /**
     * The frame type is 8-bit gray-scale image data. The @c
     * ::camera_frame_gray8_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_GRAY8,
    /**
     * The frame type is metadata. The @c
     * ::camera_frame_meta_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_METADATA,
    /**
     * The image is a 10-bit Bayer frame type. This
     * frame type contains uncompressed Bayer image data. The @c
     * ::camera_frame_bayer_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_BAYER,
    /**
     * The image is a YCbCr 4:2:2 packed frame type. This frame
     * type contains an uncompressed cbycry format. The @c
     * ::camera_frame_cbycry_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_CBYCRY,
    /**
     * The frame consists of compressed video data.  The @c
     * ::camera_frame_compressedvideo_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_COMPRESSEDVIDEO,
    /**
     * The frame consists of compressed audio data.  The @c
     * ::camera_frame_compressedaudio_t structure represents this frame type.
     */
    CAMERA_FRAMETYPE_COMPRESSEDAUDIO,
    /**
     * The frame type is 16-bit RGB data (5-bit Red Component, 6-bit Green
     * Component, 5-bit Blue Component). The @c ::camera_frame_rgb565_t
     * structure represents this frame type.
     */
    CAMERA_FRAMETYPE_RGB565,
    /**
     * An end-of-list identifier.
     */
    CAMERA_FRAMETYPE_NUMFRAMETYPES
} camera_frametype_t;


/**
 * The video compression formats used by the video encoder.
 */
typedef enum {
    /**
     * No compression.
     */
    CAMERA_VIDEOCODEC_NONE = 0,
    /**
     * AVC1 compression (NALU).
     */
    CAMERA_VIDEOCODEC_AVC1,
    /**
     * H264 compression (Annex B).
     */
    CAMERA_VIDEOCODEC_H264
} camera_videocodec_t;


/**
 * The audio compression formats used by the video encoder.
 */
typedef enum {
    /**
     * No compression.
     */
    CAMERA_AUDIOCODEC_NONE = 0,
    /**
     * MPEG-2/4 AAC compression.
     */
    CAMERA_AUDIOCODEC_AAC,
    /**
     * Uncompressed PCM audio samples.
     */
    CAMERA_AUDIOCODEC_RAW
} camera_audiocodec_t;


/**
 * The maximum size, in bytes, of the frame descriptor.
 */
#define CAMERA_MAX_FRAMEDESC_SIZE  (256)


/**
 * A camera event key that is used to identify an event that is enabled.
 */
typedef int32_t camera_eventkey_t;

/**
 * @brief Event buffering modes
 * @details The event buffering mode dictates the behavior of the @c inbuffer
 *          and @c outbuffer arguments of the buffer retrieval functions.
 *          The enumerated values are for use with the following functions:
 *          - @c camera_enable_image_event()
 *          - @c camera_enable_postview_event()
 *          - @c camera_enable_status_event()
 *          - @c camera_enable_shutter_event()
 *          - @c camera_enable_video_event()
 *          - @c camera_enable_viewfinder_event()
 *
 *         You use the following functions to retrieve the buffers:
 *         - @c camera_get_image_buffers()
 *         - @c camera_get_postview_buffers()
 *         - @c camera_get_video_buffers()
 *         - @c camera_get_viewfinder_buffers()
 */
typedef enum {
    /**
     * Read-only access to buffers is requested.  This is the same buffer access
     * mode employed when a callback function is used. The @c inbuffer argument
     * is read-only.
     */
    CAMERA_EVENTMODE_READONLY,
    /**
     * Read-write access to buffers is requested.  Using this mode allows you to
     * modify buffers prior to delivery to callback functions or read-only event
     * consumers. The @c inbuffer and @c outbuffer arguments refer to the same
     * image data in physical memory however, @c outbuffer is modifiable, while
     * @c inbuffer remains read-only.
     */
    CAMERA_EVENTMODE_READWRITE,
} camera_eventmode_t;


/**
 * A frame descriptor that holds only data. Use this frame descriptor when the
 * @c #CAMERA_FRAMETYPE_UNSPECIFIED is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * An array representing the frame data. The size of the array is
     * the size indicated by the @c #CAMERA_MAX_FRAMEDESC_SIZE value. This
     * placeholder value ensures that the file descriptor is always padded for
     * future compatibility.
     */
     uint8_t  framedata[CAMERA_MAX_FRAMEDESC_SIZE];
} camera_frame_unspecified_t;


/**
 * A frame descriptor used for NV12 frame types. Use this file descriptor when
 * @c #CAMERA_FRAMETYPE_NV12 is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
     uint32_t height;
    /**
     * The width of the frame in pixels.
     */
     uint32_t width;
    /**
     * The number of bytes from one row of pixels in memory to the next row of
     * pixels in memory. Stride is often called @e pitch.  The stride applies to
     * the luminance (Y) plane only.
     */
     uint32_t stride;
    /**
     * The offset from the start of the @c Y plane to the start of @c UV plane
     * in this format. Typically, the offset is equal to the height multiplied
     * by the stride, but may differ depending on the device.
     */
     int64_t uv_offset;
    /**
     * The number of bytes from one row of pixels in memory to the next row of
     * pixels in memory.  The uv_stride applies to the chrominance (UV) plane
     * only.
     */
     int64_t uv_stride;
} camera_frame_nv12_t;


/**
 * A frame descriptor used for RGB8888 frame types. Use this file descriptor
 * when @c #CAMERA_FRAMETYPE_RGB8888 is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
       /**
    * The width of the frame in pixels.
    */
    uint32_t width;
    /**
     * The number of bytes from one row of pixels in memory to the next row of
     * pixels in memory. Stride is often referred to as @e pitch.
     */
    uint32_t stride;
} camera_frame_rgb8888_t;


/**
 * A frame descriptor used for RGB888 frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_RGB888 is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame in pixels.
     */
    uint32_t width;
    /**
    * The number of bytes from one row of pixels in memory to the next row of
    * pixels in memory. Stride is often referred to as @e pitch.
    */
    uint32_t stride;
} camera_frame_rgb888_t;


/**
 * A frame descriptor used for RGB565 frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_RGB565 is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame in pixels.
     */
    uint32_t width;
    /**
    * The number of bytes from one row of pixels in memory to the next row of
    * pixels in memory. Stride is often referred to as @e pitch.
    */
    uint32_t stride;
} camera_frame_rgb565_t;


/**
 * A frame descriptor used for JPEG frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_JPEG is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the JPEG buffer in bytes.
     */
    uint64_t bufsize;
    /*...*/
} camera_frame_jpeg_t;


/**
 * A frame descriptor for 8-bits per pixel grayscale frame types. Use this
 * frame descriptor when @c #CAMERA_FRAMETYPE_GRAY8 is used for the @c
 * ::camera_frametype_t.
 */
typedef struct {
    /**
     * The height of the frame in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame in pixels.
     */
    uint32_t width;
    /**
    * The number of bytes from one row of pixels in memory to
    * the next row of pixels in memory. Stride is often called @e pitch.
    */
    uint32_t stride;
} camera_frame_gray8_t;


/**
 * A frame descriptor for metadata frame types. Use this frame descriptor
 * when @c #CAMERA_FRAMETYPE_METADATA is used for the @c ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the frame in bytes.
     */
    uint64_t bufsize;
    /*...*/
} camera_frame_meta_t;


/**
 * The Bayer array pixel component format. See @c ::camera_frame_bayer_t for
 * details about the Bayer frame format.
 *
 */
typedef enum {
    /**
     * Camera Bayer array format is unknown or unspecified.
     */
    CAMERA_BAYERFORMAT_UNSPECIFIED,

    /**
     * Cameras that use Bayer array format as follows:
     * @code
     *  G R
     *  B G
     * @endcode
     */
    CAMERA_BAYERFORMAT_GRBG,

    /**
     * Cameras that use Bayer array format as follows:
     * @code
     *  R G
     *  G B
     * @endcode
     */
    CAMERA_BAYERFORMAT_RGGB,

    /**
     * Cameras that use Bayer array format as follows:
     * @code
     *  B G
     *  G R
     * @endcode
     */
    CAMERA_BAYERFORMAT_BGGR,

    /**
     * Cameras that use Bayer array format as follows:
     * @code
     *  G B
     *  R G
     * @endcode
     */
    CAMERA_BAYERFORMAT_GBRG,

} camera_bayerformat_t;

/**
 * A frame descriptor for a Bayer frame type. Use this frame
 * descriptor when @c #CAMERA_FRAMETYPE_BAYER is used for the @c
 * ::camera_frametype_t.
 *
 * Each pixel in the Bayer frame is part of a Bayer @e macro-pixel. Each Bayer
 * macro-pixel is made up of four color components: one red, one blue, and two
 * green. We refer to the color components as @e pixels, and the group of four
 * as a macro-pixel.
 *
 * Each macro-pixel is stored across two lines in the frame. The first two
 * pixels are stored contiguously on the first line. The @c stride separates the
 * first pixel from the third, and the second pixel from the fourth.
 *
 * Each pixel of the Bayer macro-pixel is stored in @c packing bits. If @c le
 * is true, the lower @c bpp bits of @c packing contain color information, if
 * @c le is false, the higher @c bpp bits of @c packing contain color
 * information.
 *
 * For example, @c le = true, @c bpp = 10, and @c packing = 16 describes a
 * 10-bit Bayer frame such that each color component is stored in the lower
 * ten bits of a 16-bit pixel. If @c format were @c #CAMERA_BAYERFORMAT_RGGB,
 * the Bayer macro-pixel would be stored like so:
 * @code
 * Bit:          0123456789ABCDEF 0123456789ABCDEF
 * Scanline n:   RRRRRRRRRR000000 GGGGGGGGGG000000 = 32 bits
 * Scanline n+1: GGGGGGGGGG000000 BBBBBBBBBB000000 = 32 bits
 * @endcode
 *
 */
typedef struct {
    /**
     * The size of the frame, in bytes.
     */
    uint64_t bufsize;
    /**
     * The height of the frame, in pixels.
     */
    uint32_t height;
    /**
     * The width of the frame, in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes from one row of pixels in memory to the next row of
     * pixels in memory. Stride is often called @e pitch.
     */
    uint32_t stride;
    /**
     * The format of the Bayer macro-pixel.
     */
    camera_bayerformat_t format;
    /**
     * The inter-pixel distance, in bytes.
     */
    uint32_t packing;
    /**
     * The bits per pixel component inside the packing size.
     */
    uint32_t bpp;
    /**
     * Whether little-endian used to pack the frame. When @c le is true,
     * the bytes are packed in little-endian, otherwise when @c le is false,
     * the bytes are packed using big-endian.
     */
    bool le;
    /*...*/
} camera_frame_bayer_t;


/**
 * A frame descriptor for a YCbCr 4:2:2 packed frame type. Use this frame
 * descriptor when @c #CAMERA_FRAMETYPE_CBYCRY is used for the @c
 * camera_frametype_t.
 *
 * Each pixel in the CBYCRY frame is part of a macro-pixel. Each CBYCRY
 * macro-pixel is made up of four color components: one U (CR, or
 * red-difference chroma), one V (CB, or blue-difference chroma), and two Y
 * (luma) components. We refer to the color components as @e pixels, and the
 * group of four color components as a @e macro-pixel.
 *
 * Each macro-pixel is stored contiguously on the same line, unlike @c
 * camera_frame_bayer_t, where each macro-pixel is divided into two lines.
 *
 * Each pixel of the CBYCRY macro-pixel is stored in @c packing bits. If @c le
 * is true, the lower @c bpp bits of @c packing contain color information, if
 * @c le is false, the higher @c bpp bits of @c packing contain color
 * information.
 *
 * For example, @c le = true, @c bpp = 8, and @c packing = 8 describes an 8-bit
 * CBYCRY frame such that each color component is stored in the lower 8 bits of
 * a 8-bit pixel. Thus, the macro-pixel would be stored like so:
 * @code
 * Bit:          01234567 01234567 01234567 01234567
 * Scanline n:   UUUUUUUU YYYYYYYY VVVVVVVV YYYYYYYY = 32 bits
 * @endcode
 */
typedef struct {
    /**
     * The size of the buffer as a 64-bit integer.
     */
    uint64_t bufsize;
    /**
     * The height of the image, in pixels.
     */
    uint32_t height;
    /**
     * The width of the image, in pixels.
     */
    uint32_t width;
    /**
     * The number of bytes per line in the image.
     */
    uint32_t stride;
    /**
     * The inter-pixel distance, in bytes
     */
    uint32_t packing;
    /**
     * The bits per pixel component inside the packing size.
     */
    uint32_t bpp;
    /**
     * The endian order used for packing the data. A value of @c true indicates
     * that the bytes are packed using little-endian order, otherwise, a value
     * value @c false indicates that the bytes are packed using big-endian
     * order.
     */
    bool le;
    /*...*/
} camera_frame_cbycry_t;


/**
 * A frame descriptor for compressed video frame types. Use this
 * frame descriptor when @c #CAMERA_FRAMETYPE_COMPRESSEDVIDEO is used for the @c
 * ::camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the buffer as a 64-bit integer.
     */
    uint64_t bufsize;
    /**
     * The format of the compressed video.
     */
    camera_videocodec_t codec;
    /**
     * A flag indicating whether this frame is a keyframe.
     */
    bool keyframe;
    /**
     * Bitrate expressed in bits per second.
     */
    uint64_t bitrate;
} camera_frame_compressedvideo_t;


/**
 * A frame descriptor for compressed audio frame types. Use this
 * frame descriptor when @c #CAMERA_FRAMETYPE_COMPRESSEDAUDIO is used for the @c
 * camera_frametype_t.
 */
typedef struct {
    /**
     * The size of the buffer as a 64-bit integer.
     */
    uint64_t bufsize;
    /**
     * The format of the compressed audio.
     */
    camera_audiocodec_t codec;
    /**
     * A flag indicating whether this frame is a keyframe.
     */
    bool keyframe;
    /**
     * Number of channels in the audio stream.
     */
    uint32_t channels;
    /**
     * Number of bits per sample per channel.
     */
    uint32_t bits;
    /**
     * Uncompressed sample rate in hertz (Hz).
     */
    uint32_t samplerate;
    /**
     * Bitrate expressed in bits per second.
     */
    uint64_t bitrate;
} camera_frame_compressedaudio_t;


/**
 * A union that contains all supported available frame descriptors for the
 * Camera library.
 */
typedef union {
    /**
     * An unknown frame type or unspecified frame type.
     */
    camera_frame_unspecified_t      unspecified;
    /**
     * The @c camera_frame_nv12_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_NV12 enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_nv12_t             nv12;
    /**
     * The @c camera_frame_rgb8888_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_RGB8888 enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_rgb8888_t          rgb8888;
    /**
     * The @c camera_frame_rgb888_t member corresponds to the
     * #CAMERA_FRAMETYPE_RGB888 enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_rgb888_t           rgb888;
    /**
     * The @c camera_frame_jpeg_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_JPEG enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_jpeg_t             jpeg;
    /**
     * The @c camera_frame_gray8_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_GRAY8 enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_gray8_t            gray8;
    /**
     * The @c camera_frame_meta_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_METADATA enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_meta_t             meta;
    /**
     * The @c camera_frame_bayer_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_BAYER enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_bayer_t            bayer;
    /**
     * The @c camera_frame_cbycry_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_CBYCRY enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_cbycry_t           cbycry;
    /**
     * The @c camera_frame_compressedvideo_t member corresponds to the @c
     * #CAMERA_FRAMETYPE_COMPRESSEDVIDEO enumerator in the @c
     * #camera_frametype_t type.
     */
    camera_frame_compressedvideo_t  compvid;
    /**
     * The @c camera_frame_compressedaudio_t member corresponds to the
     * #CAMERA_FRAMETYPE_COMPRESSEDAUDIO enumerator in the @c
     * #camera_frametype_t type.
     */
    camera_frame_compressedaudio_t  compaud;
    /**
     * The @c camera_frame_rgb565_t member corresponds to the
     * #CAMERA_FRAMETYPE_RGB565 enumerator in the @c #camera_frametype_t type.
     */
    camera_frame_rgb565_t           rgb565;
    /*...*/
} camera_framedesc_t;




/**
 * The structure is used to convey image data between the API
 * and an application. This task can include handling buffers in callbacks and
 * all functions that utilize buffers.
 */
typedef struct {
    /**
     * The type of frame descriptor that is used to distinguish between members
     * of the @c ::camera_framedesc_t union.
     */
    camera_frametype_t      frametype;
    /**
     * The size of the @c ::camera_buffer_t.
     */
    uint64_t                framesize;
    /**
     * A pointer to the frame data.
     */
    uint8_t                *framebuf;
    /**
     * The size of the metadata frame.
     */
    uint64_t                framemetasize;
    /**
     * A pointer to the metadata frame.
     */
    void                   *framemeta;
    /**
     * The timestamp when the buffer was filled. The timestamp is referenced to
     * the system monotonic clock (CLOCK_MONOTONIC).
     */
    int64_t                 frametimestamp;
    /**
     * The rotation delta from the default device orientation. The rotation
     * is measured in degrees, clockwise.
     */
    int32_t                 frameorientation;
    /**
     * For internal use. Do not use.
     */
    uint32_t                reserved[4];
    /**
     * The union which describes the geometry of the image data being reported
     * by the @c framebuf field in this structure.
     */
    camera_framedesc_t      framedesc;
} camera_buffer_t;


/**
 * The resolution (height and width of the image) in pixels. Use this structure
 * to query supported resolutions.
 *
 */
typedef struct {
    /**
     * The width of the image in pixels.
     */
    unsigned int            width;
    /**
     * The height of the image in pixels.
     */
    unsigned int            height;
} camera_res_t;


/**
 * The type of scene mode to use for the camera. Scene modes specify the
 * camera settings to use, effects, and predefined visual styles applied by the
 * camera hardware to achieve a specific image result. For example,
 * you can use a faster shutter speed for fast-moving objects.
 * You can use the @c camera_get_scene_modes() function to determine which modes
 * are supported for the current platform and camera.
 *
 */
typedef enum {
    /**
     * The camera default scene mode.
     */
    CAMERA_SCENE_DEFAULT = 0,
    /**
     * The system determines the best settings to use to take the picture.
     */
    CAMERA_SCENE_AUTO,
    /**
     * Use a faster shutter speed. A fast shutter speed allows
     * you to capture images with less motion blur where the subjects are
     * quickly moving, such as sports shots.
     */
    CAMERA_SCENE_SPORTS,
    /**
     * Drop the mid-range tones in an image.
     */
    CAMERA_SCENE_WHITEBOARD,
    /**
     * Produce a soft-effect when photographing people.
     */
    CAMERA_SCENE_CLOSEUP,
    /**
     * The image is a piece of paper with text on it.
     */
    CAMERA_SCENE_BUSINESSCARD,
    /**
     * The image is a barcode. The camera is optimized by the system to
     * recognize the barcode image.
     */
    CAMERA_SCENE_BARCODE,
    /**
     * Use a faster shutter speed. A fast shutter speed allows
     * you to capture images with less motion blur where the subjects are
     * quickly moving, such as action shots.
     */
    CAMERA_SCENE_ACTION,
    /**
     * Don't apply any post-processing effects. In test
     * mode, pixels are untouched by the image signal processor (ISP) as image
     * optimizations are turned off. This mode is used for factory testing
     * and calibration.
     */
    CAMERA_SCENE_TEST,
    /**
     * Compensate exposure for bright scenes.
     */
    CAMERA_SCENE_BEACHANDSNOW,
    /**
     * Compensate exposure for dark scenes.
     */
    CAMERA_SCENE_NIGHT,
    /**
     * The total number of supported scene modes.
     */
    CAMERA_SCENE_NUMSCENEMODES
} camera_scenemode_t;


/**
 * The status of the flash that is used by set mode functions
 * in the Camera library.
 */
typedef enum {
    /**
     * Force the flash not to fire.
     */
    CAMERA_FLASH_OFF = 0,
    /**
     * Force the flash to fire.
     */
    CAMERA_FLASH_ON,
    /**
     * Force the flash to fire as required.
     */
    CAMERA_FLASH_AUTO
} camera_flashmode_t;


/**
 * The status of the video light that is used by set-mode functions
 * in the Camera library.
 */
typedef enum {
    /**
     * Turn off the video light.
     */
    CAMERA_VIDEOLIGHT_OFF = 0,
    /**
     * Turn on the video light.
     */
    CAMERA_VIDEOLIGHT_ON
} camera_videolightmode_t;

/**
 * The state of the autofocus algorithm on the camera.
 */
typedef enum {
    /**
     * Autofocus is disabled or not available.
     */
    CAMERA_FOCUSSTATE_NONE = 0,
   /**
    * The system is waiting for the scene to stabilize before trying to focus.
    * Not all platforms may support this intermediate state.
    */
    CAMERA_FOCUSSTATE_WAITING,
   /**
    * The system is searching for an object to focus on.
    */
    CAMERA_FOCUSSTATE_SEARCHING,
   /**
    * The system has failed to focus.
    */
    CAMERA_FOCUSSTATE_FAILED,
   /**
    * The focus is locked.
    */
    CAMERA_FOCUSSTATE_LOCKED,
   /**
     * The system detected a significant change in the scene and
     * that running a new focus cycle would be recommended. Not all
     * platforms support this state and it only applies to single
     * focus modes.
     */
     CAMERA_FOCUSSTATE_SCENECHANGE
} camera_focusstate_t;


/**
 * The focus mode of the camera. Use @c camera_get_focus_modes() to determine
 * the focus modes that are supported for the current platform and camera.
 */
typedef enum {
    /**
     * focus mode is off.
     */
    CAMERA_FOCUSMODE_OFF = 0,
    /**
     * The camera is using extended depth of field (EDoF) focus
     * mode.
     */
    CAMERA_FOCUSMODE_EDOF,
    /**
     * The camera is using manual focus mode.
     */
    CAMERA_FOCUSMODE_MANUAL,
    /**
     * The camera is using single-cycle autofocus. Single-cycle
     * focus occurs once and then stops.
     */
    CAMERA_FOCUSMODE_AUTO,
    /**
     * The camera is using single-cycle macro autofocus.
     * Single-cycle focus occurs once and then stops.
     */
    CAMERA_FOCUSMODE_MACRO,
    /**
     * The camera is using continuous autofocus mode. The
     * autofocus algorithm restarts if the scene goes out of focus.
     */
    CAMERA_FOCUSMODE_CONTINUOUS_AUTO,
    /**
     * The camera is using continuous autofocus mode while
     * in macro view. The autofocus algorithm restarts if the scene goes out
     * of focus.
     */
    CAMERA_FOCUSMODE_CONTINUOUS_MACRO,
    /**
     * The total number of supported focus modes.
     */
    CAMERA_FOCUSMODE_NUMFOCUSMODES
} camera_focusmode_t;


/**
 * The exposure mode of the camera. You can use the @c
 * camera_get_exposure_modes() function to determine which modes are supported
 * for the current platform and camera.
 */
typedef enum {
    /**
     * The default auto exposure mode.
     */
    CAMERA_EXPOSUREMODE_DEFAULT,

    /**
     * Auto exposure is off.
     */
    CAMERA_EXPOSUREMODE_OFF,

    /**
     * Exposure is automatically adjusted by the camera.
     */
    CAMERA_EXPOSUREMODE_AUTO,

    /**
     * Manual exposure mode.
     * All exposure controls must be manually set.
     */
    CAMERA_EXPOSUREMODE_MANUAL,

    /**
     * The ISO value must be manually set. The camera automatically adjusts
     * the other exposure controls.
     */
    CAMERA_EXPOSUREMODE_ISO_PRIORITY,

    /**
     * Shutter speed must be manually set. The camera automatically adjusts
     * the other exposure controls.
     */
    CAMERA_EXPOSUREMODE_SHUTTER_PRIORITY,

    /**
     * Aperture value must be manually set. The camera automatically adjusts
     * the other exposure controls.
     */
    CAMERA_EXPOSUREMODE_APERTURE_PRIORITY,

    /**
     * The ISO value and shutter speed must be manually set. The camera
     * automatically adjusts the other exposure controls.
     */
    CAMERA_EXPOSUREMODE_ISO_SHUTTER_PRIORITY,

    /**
     * The ISO value and aperture value must be manually set. The camera
     * automatically adjusts the other exposure controls.
     */
    CAMERA_EXPOSUREMODE_ISO_APERTURE_PRIORITY,

    /**
     * Shutter speed and aperture value must be manually set.
     * Other exposure controls are automatically adjusted by the camera.
     */
    CAMERA_EXPOSUREMODE_SHUTTER_APERTURE_PRIORITY,

    /**
     * The total number of exposure modes.
     */
    CAMERA_EXPOSUREMODE_NUMEXPOSUREMODES
} camera_exposuremode_t;


/**
 * The white balance mode of the camera. You can use the @c
 * camera_get_whitebalance_modes() function to determine which modes are
 * supported for the current platform and camera.
 */
typedef enum {
    /**
     * White balance is automatically adjusted by the platform.
     */
    CAMERA_WHITEBALANCEMODE_DEFAULT,

    /**
     * Auto white balance is off.
     */
    CAMERA_WHITEBALANCEMODE_OFF,

    /**
     * Auto white balance is on and will be set automatically.
     */
    CAMERA_WHITEBALANCEMODE_AUTO,

    /**
     * White balance must be manually set.
     */
    CAMERA_WHITEBALANCEMODE_MANUAL,

    /**
     * The total number of white balance modes.
     */
    CAMERA_WHITEBALANCEMODE_NUMWHITEBALANCEMODES
} camera_whitebalancemode_t;


/**
 * The autofocus, auto exposure, and auto white balance, or simply 3A.
 */
typedef enum {
    /**
     * The camera is not using automatic settings for
     * focus, exposure, or white balance.
     */
    CAMERA_3A_NONE = 0,
    /**
     * The camera is using autofocus.
     */
    CAMERA_3A_AUTOFOCUS =        1<<0,
    /**
     * The camera is using automatic settings for exposure.
     */
    CAMERA_3A_AUTOEXPOSURE =     1<<1,
    /**
     * The camera is using automatic settings for white balance.
     */
    CAMERA_3A_AUTOWHITEBALANCE = 1<<2
} camera_3a_t;


/**
 * This structure is used to identify a subset of pixels in an image.
 * Regions are used to report focus lock positions and to configure
 * region-dependent focus, exposure, and white balance operations.
 */
typedef struct {
    /**
     * The left coordinate of the region. A value of 0 refers to the leftmost
     * column of the image.
     */
    uint32_t left;
    /**
     * The top coordinate of the region. A value of 0 refers to the topmost
     * column of the image.
     */
    uint32_t top;
    /**
     * The width of the region in pixels.
     */
    uint32_t width;
    /**
     * The height of the region in pixels.
     */
    uint32_t height;
    /**
     * An addition value that can be used to configure exposure, focus, or
     * white balance. Typically, the additional values can be a weighting,
     * ranking, or other application-specific value.
     */
    uint32_t extra;
} camera_region_t;


/**
 * The camera access mode flags that are passed to the @c camera_open() function
 * to indicate the type of access that is required.
 * @anonenum camapi_camera_modeflags Camera access mode flags
 */
enum {
    /**
     * Read-access to the camera configuration.
     */
    CAMERA_MODE_PREAD =      1<<0,
    /**
     * Write-access to the camera configuration.
     */
    CAMERA_MODE_PWRITE =     1<<1,
    /**
     * Read-access to the camera imaging datapath (image buffers).
     */
    CAMERA_MODE_DREAD =      1<<2,
    /**
     * Write access to the camera imaging datapath (image buffers).
     */
    CAMERA_MODE_DWRITE =     1<<3,
    /**
     * Access to the filename generator from the camera roll.
     * The filename generator creates unique file names and also creates files
     * on the camera roll.
     */
    CAMERA_MODE_ROLL =       1<<4,
    /**
     * For internal use only.
     */
    CAMERA_MODE_PRIVILEGED = 1<<5,
    /**
     * The application has read-only access to the camera configuration and the
     * camera imaging datapath.
     */
    CAMERA_MODE_RO =         (CAMERA_MODE_PREAD | CAMERA_MODE_DREAD),
    /**
     * The application has read-access and write-access to camera
     * configuration and the camera imaging datapath. Use this as an alias for @c
     * #CAMERA_MODE_PREAD, @c #CAMERA_MODE_PWRITE, @c #CAMERA_MODE_DREAD, and @c
     * #CAMERA_MODE_DWRITE.
     */
    CAMERA_MODE_RW =         (CAMERA_MODE_PREAD | CAMERA_MODE_PWRITE |
                              CAMERA_MODE_DREAD | CAMERA_MODE_DWRITE),
};


/**
 * The supported image formats on the camera roll.
 */
typedef enum {
    /**
     * Images are saved in the system-specified default format on the camera
     * roll.
     */
    CAMERA_ROLL_PHOTO_FMT_DEFAULT = 0,
    /**
     * Images are saved in JPEG format on the camera roll.
     */
    CAMERA_ROLL_PHOTO_FMT_JPG,
    /**
     * Images are saved in PNG format on the camera roll.
     */
    CAMERA_ROLL_PHOTO_FMT_PNG,
} camera_roll_photo_fmt_t;

/**
 * The camera roll video file formats.
 */
typedef enum {
    /**
     * Video is saved in the default camera format.
     */
    CAMERA_ROLL_VIDEO_FMT_DEFAULT = 0,
    /**
     * Video is saved in the MP4 format.
     */
    CAMERA_ROLL_VIDEO_FMT_MP4,
} camera_roll_video_fmt_t;


/**
 * @brief Retrieve the current build version of the Camera library
 * @details The API version is useful to ensure that certain calls are
 *          available. You can use the returned value to compare to the @c
 *          #CAMERA_API_VERSION to determine if the runtime library is different
 *          from the version your application was compiled with. Differences
 *          may indicate potential incompatibilities.
 *
 * @return A value representing the version of the Camera library.
 */
int
camera_get_api_version(void);


/**
 * @brief Request a handle to access a logical camera unit
 * @details If the camera is available, a handle for exclusive access to the
 *          camera unit is returned. You must pass in a @c ::camera_handle_t
 *          value to store the handle. You must also have access permissions to
 *          use the camera.
 *
 * @param unit The logical camera unit to open.
 * @param mode The access mode of the camera, which is comprised of the
 *             @c CAMERA_MODE_xxx flags ORed together.
 * @param handle A pointer to the returned camera handle if access is granted.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_open(camera_unit_t unit,
            uint32_t mode,
            camera_handle_t *handle);


/**
 * @brief Discontinue use of a logical camera on the device
 *
 * @details Any internal resources associated with a previously
 *          opened camera unit are freed.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_close(camera_handle_t handle);




/**
 * @brief Retrieve an enumerated list of cameras available on the device
 * @details An array of camera units is returned in the @c cameras
 *          argument.
 *
 *          Ensure that the @c cameras argument points to an array which has at
 *          least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          cameras argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *
 * @param numasked The requested number of camera units to return in the
 *                 array.
 * @param numsupported A pointer to the number of camera units that you have
 *                     access to. The argument is updated when the function
 *                     completes successfully.
 * @param cameras A pointer to the first element in a @c camera_unit_t array.
 *                The array is updated with the cameras that you have access
 *                to when the function completes successfully.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_cameras(unsigned int numasked,
                             unsigned int *numsupported,
                             camera_unit_t *cameras);


/**
 * @brief Determine whether a feature is available on the camera
 * @details The availability of a feature does not mean that the feature is
 *         usable. For example, this function may indicate that physical
 *         flash is available, but the feature actually may not be used
 *         until the viewfinder is active. To determine if a feature can be
 *         used in the camera's current state, use the @c camera_can_feature()
 *         function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param feature The specific feature to query.
 * @return @c true when the specified feature is supported by the device,
 *         otherwise a value of @c false.
 */


bool
camera_has_feature(camera_handle_t handle,
                   camera_feature_t feature);


/**
 * @brief Determine whether a feature is available on the camera in its
 *        current state
 * @details The difference between this function and the @c
 *          camera_has_feature() function is that this function indicates the
 *          features on the camera are available for use in the current
 *          camera state rather than just available.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param feature The specific feature to query.
 * @return @c true when the specified feature is currently available,
 *         otherwise, a value of @c false.
 */
bool
camera_can_feature(camera_handle_t handle,
                   camera_feature_t feature);


/**
 * @brief Find the cameras that have the specified features.
 * @details You can use this function find cameras with features required for
 *          your application. For example, you can use it to find cameras which
 *          have flash or only cameras that face the front.
 *          This function is used to iterate through a list of cameras and
 *          is returned in the @c nextunit argument.
 *
 *          For example, to start iterating through the cameras, you set the @c
 *          prevunit argument to @c #CAMERA_UNIT_NONE.  Doing so, returns @c
 *          nextunit found on this iteration. If you wanted to continue
 *          iterating through the list of cameras, you would pass the value
 *          returned by the @c nextunit argument as the @c prevunit argument
 *          in your next call of the this function. When the end of the list is
 *          reached, @c nextunit returns with a value of @c #CAMERA_UNIT_NONE.
 *
 * @param features A pointer that lists the features to search for.
 * @param nfeatures The number of features specified in the first argument.
 * @param prevunit The previous unit that was queried or @c #CAMERA_UNIT_NONE
 *                 if this is the first call to this function.
 * @param nextunit A pointer to a @c ::camera_unit_t value where the function
 *                 returns the next unit which supports all requested
 *                 features.
 * @return @c #CAMERA_EOK when the function successfully completes.
 *         @c #CAMERA_ENODEV indicates that the end of list was reached.
 */
camera_error_t
camera_find_capable(camera_feature_t *features,
                    int nfeatures,
                    camera_unit_t prevunit,
                    camera_unit_t *nextunit);


/**
 * @brief Retrieve the supported output resolutions for a photo
 * @details After you use this function to retrieve the resolutions that are
 *          supported by the camera on the device, you can configure the
 *          viewfinder properties.
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param outputformat The frame type that the viewfinder supports.
 * @param numasked The requested number of resolutions to return in the
 *                 resolutions array. You can use a value of 0 to
 *                 determine the maximum number of supported resolutions
 *                 on the camera.
 * @param numsupported The number of resolutions supported for the specified
 *                     camera.
 * @param resolutions The pointer the first element of a @c camera_res_t array.
 *                    The array is updated with the viewfinder resolutions.
 *                    available on the camera. Ensure that you create an array
 *                    with the same or greater number of elements as specified
 *                    in the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_output_resolutions(camera_handle_t handle,
                                    camera_frametype_t outputformat,
                                    unsigned int numasked,
                                    unsigned int *numsupported,
                                    camera_res_t *resolutions);


/**
 * @brief Retrieve the supported output resolutions for video
 * @details After you use this function to retrieve the resolutions that are
 *          supported by the camera, you can configure the viewfinder
 *          argument.
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of resolutions to return in the
 *                 resolutions array. You can use a value of 0 to determine
 *                 the maximum number of supported resolutions to the camera.
 * @param numsupported The number of resolutions supported for the specified
 *                     camera.
 * @param resolutions The pointer the first element of a @c resolutions array.
 *                    The array is updated with the viewfinder resolutions
 *                    available on the camera. Ensure that you create an array
 *                    with the same or greater number of elements as specified
 *                    in the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_output_resolutions(camera_handle_t handle,
                                    unsigned int numasked,
                                    unsigned int *numsupported,
                                    camera_res_t *resolutions);


/**
 * @brief Retrieve the viewfinder output resolutions for photos
 * @details After you use this function to retrieve the resolutions that are
 *          supported by the camera, you can configure the viewfinder
 *          properties.
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument. You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of resolutions to return in the
 *                 resolutions array. You can use a value of 0 to
 *                 determine the maximum number of supported viewfinder
 *                 resolutions on the camera.
 * @param numsupported The number of resolutions supported for the specified
 *                     camera.
 * @param resolutions The pointer to a @c camera_res_t array. The array
 *                    is updated with the viewfinder resolutions supported by
 *                    the camera. Ensure that you create an array with the same
 *                    or greater number of elements as specified in the
 *                    @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the call
 *         failed.
 */
camera_error_t
camera_get_photo_vf_resolutions(camera_handle_t handle,
                                unsigned int numasked,
                                unsigned int *numsupported,
                                camera_res_t *resolutions);


/**
 * @brief Retrieve the viewfinder resolutions for video
 * @details After you use this function to retrieve the resolutions that are
 *          supported by the camera, you can configure the viewfinder
 *          argument.
 *
 *          Ensure that the @c resolutions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          resolutions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of resolutions to return in the
 *                 resolutions array. You can use a value of 0 to
 *                 determine the maximum number of supported viewfinder
 *                 resolutions on the camera.
 * @param numsupported The number of resolutions supported for the specified
 *                     camera.
 * @param resolutions The pointer to a @c ::camera_res_t array. The array
 *                    is updated with the viewfinder resolutions supported by
 *                    the camera. Ensure that you create an array with the same
 *                    or greater number of elements as specified in the
 *                    @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_vf_resolutions(camera_handle_t handle,
                                unsigned int numasked,
                                unsigned int *numsupported,
                                camera_res_t *resolutions);


/**
 * @brief Configure one or more settings in the photo viewfinder
 *
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using ::camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTMODE
 *           - @c #CAMERA_IMGPROP_VARIABLEFRAMERATE
 *           - @c #CAMERA_IMGPROP_MINFRAMERATE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property-value pair matches the expected data
 *                    type. Data type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 * @code
 * property1, value1, property2, value2,...
 * @endcode
 *
 * For example, you can set values in the following manner:
 * @code
 * camera_set_photovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIN_GROUPID, "mygroup",
 *                              CAMERA_IMGPROP_WIN_ID, "vfwindow",
 *                              CAMERA_IMGPROP_WIDTH, 1024,
 *                              CAMERA_IMGPROP_HEIGHT, 576,
 *                              CAMERA_IMGPROP_ROTATION, 90,
 *                              CAMERA_IMGPROP_BURSTMODE, 1,
 *                              CAMERA_IMGPROP_FRAMERATE, (double)15.0,
 *                              CAMERA_IMGPROP_HWOVERLAY, 0,
 *                              CAMERA_IMGPROP_ZOOMFACTOR, 20 );
 * @endcode
 *
 * @b Note: The following properties can't be changed after the
 *      viewfinder has started:
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_BURSTMODE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *      You can change these properties after stopping the
 *      viewfinder. When the viewfinder is running then
 *      @c #CAMERA_IMGPROP_WIN_GROUPID can only be set if the
 *      current value is an empty string.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_photovf_property(handle, args...) \
        _camera_set_photovf_property(handle, args, CAMERA_IMGPROP_END)

/**
 * @internal
 * For internal use only. Use the @c camera_set_photovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_photovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief Retrieve one or more properties of the photo viewfinder
 *
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTMODE
 *           - @c #CAMERA_IMGPROP_VARIABLEFRAMERATE
 *           - @c #CAMERA_IMGPROP_MINFRAMERATE
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 *         For example, you can get values in the following manner:
 * @code
 * camera_get_photovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIDTH, &vf_width,
 *                              CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                              CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                              CAMERA_IMGPROP_BURSTMODE, &burstmode,
 *                              CAMERA_IMGPROP_FRAMERATE, &framerate,
 *                              CAMERA_IMGPROP_HWOVERLAY, &hwoverlay,
 *                              CAMERA_IMGPROP_ZOOMFACTOR, &zoomfactor );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_photovf_property(handle, args...) \
        _camera_get_photovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the @c camera_get_photovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_photovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief Configure one or more settings in the video viewfinder
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIN_GROUPID
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 * @code
 * property1, value1, property2, value2,...
 * @endcode
 *
 * For example, you can set values in the following manner:
 * @code
 * camera_set_videovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIN_GROUPID, "GroupID",
 *                              CAMERA_IMGPROP_WIN_ID, "WindowID",
 *                              CAMERA_IMGPROP_WIDTH, 1024,
 *                              CAMERA_IMGPROP_HEIGHT, 576,
 *                              CAMERA_IMGPROP_ROTATION, 90,
 *                              CAMERA_IMGPROP_FRAMERATE, (double)30.0 );
 * @endcode
 *
 * @b Note: The following properties can't be changed after the
 *      viewfinder has started:
 *           - @c #CAMERA_IMGPROP_WIN_ID
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *      You can change these properties after stopping the
 *      viewfinder. When the viewfinder is running then
 *      @c #CAMERA_IMGPROP_WIN_GROUPID can only be set if the
 *      current value is an empty string.
 *
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_videovf_property(handle, args...) \
        _camera_set_videovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_set_videovf_property() function
 * instead which auto-terminates the ... varargs list.
 *
 */
camera_error_t
_camera_set_videovf_property(camera_handle_t handle,
                             ...);


/**
 * @brief Retrieve one or more properties from the video viewfinder
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_HWOVERLAY
 *           - @c #CAMERA_IMGPROP_ZOOMFACTOR
 *           - @c #CAMERA_IMGPROP_MAXFOV
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 *
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 * For example, you can get values in the following manner:
 * @code
 * camera_get_videovf_property( camera_handle,
 *                              CAMERA_IMGPROP_WIDTH, &vf_width,
 *                              CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                              CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                              CAMERA_IMGPROP_FRAMERATE, &vf_framerate );
 * @endcode
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_videovf_property(handle, args...) \
        _camera_get_videovf_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_set_videovf_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_videovf_property(camera_handle_t handle,
                             ...);



/**
 * @brief Start the photo viewfinder on the camera
 * @details This function can only be called if the @c #CAMERA_FEATURE_PHOTO
 *          is available. You can determine whether the feature is available by
 *          calling the @c camera_can_feature() function.
 *
 *          Before calling this function, ensure that you:
 *           - Use the @c camera_set_photovf_property() function to configure
 *              the photo viewfinder.
 *           - Use the @c camera_set_photo_property()  function to set any photo
 *              properties.
 *           - Create a screen window to be the parent of the child viewfinder
 *              window that will be created by this call.
 *
 *         Once the photo viewfinder is running, the user can take photos,
 *         and configure scene modes. In addition, you can reposition or resize
 *         their viewfinder windows using the Screen and Windowing API. In order
 *         to retrieve a window handle to the viewfinder window that is created,
 *         you must listen for the appropriate screen event. After receiving the
 *         window handle, you can then use the screen API to manipulate the
 *         window.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param viewfinder_callback A function pointer to a function with the
 *                            following signature:
 *
 *                            @c void @c function_name ( @c camera_handle_t,
 *                                                       @c camera_buffer_t*,
 *                                                       @c void*)
 *                            The function is a callback that gets invoked
 *                            when a raw viewfinder buffer becomes available.
 *                            Set the argument to @c NULL when no function
 *                            needs to be called.
 *                            For information about the callback arguments, see
 *                            @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 *                        void @c function_name( @c camera_handle_t,
 *                                                  @c camera_devstatus_t,
 *                                                  @c uint16_t, @c void*)
 *                        The function is a callback that gets invoked when
 *                        status events occur. Set the argument to @c NULL
 *                        when no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_start_photo_viewfinder(camera_handle_t handle,
                              void (*viewfinder_callback)
                                   (camera_handle_t, camera_buffer_t*, void*),
                              void (*status_callback)
                                   (camera_handle_t, camera_devstatus_t,
                                    uint16_t, void*),
                              void *arg);


/**
 * @brief Start the video viewfinder on the camera
 * @details This function can only be called if the @c #CAMERA_FEATURE_VIDEO
 *          is available. You can determine whether the feature is available by
 *          calling the @c camera_can_feature() function.
 *
 *          Before you call this function, ensure you:
 *           - Use the @c camera_set_videovf_property() function to configure
 *             the video viewfinder.
 *           - Use the @c camera_set_video_property() function to set any video
 *             properties.
 *           - Create a screen window to hold the video viewfinder buffers.
 *
 *         Once the video viewfinder is running, the user can encode video
 *         and configure scene modes. In addition, the you can reposition or
 *         resize their viewfinder window using the Screen and Windowing API. In
 *         order to retrieve a window handle to the viewfinder window that is
 *         created, you must listen for the appropriate screen event. After
 *         receiving the window handle, you can then use the screen API to
 *         manipulate the window.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param viewfinder_callback A function pointer to a function with the
 *                            following signature:
 *                            @c void @c function_name( @c camera_handle_t,
 *                                                      @c camera_buffer_t*,
 *                                                      @c void*).
 *                            The function is a callback that gets invoked when
 *                            a raw viewfinder buffer becomes available. Set
 *                            the argument to @c NULL when no function needs to
 *                            be called.
 *                            For information about the callback arguments, see
 *                            @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 *                        @c void @c function_name( @c camera_handle_t,
 *                                                  @c camera_devstatus_t,
 *                                                  @c uint16_t, @c void*).
 *                        The function is a callback that gets invoked when
 *                        status events occur. Set the argument to @c NULL when
 *                        no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the last
 *            argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_start_video_viewfinder(camera_handle_t handle,
                              void (*viewfinder_callback)
                                   (camera_handle_t, camera_buffer_t*, void*),
                              void (*status_callback)
                                   (camera_handle_t, camera_devstatus_t,
                                    uint16_t, void*),
                              void *arg);


/**
 * @brief Stop using the photo viewfinder
 * @details You can only stop the viewfinder after you have successfully
 *          started it. After you stop running the photo viewfinder, you
 *          cannot take photos.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_photo_viewfinder(camera_handle_t handle);

/**
 * @brief Stop using the video viewfinder
 * @details  You can only stop the viewfinder after you have successfully
 *          started it. After you stop running the video viewfinder,
 *          you cannot encode video.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_video_viewfinder(camera_handle_t handle);


/**
 * @brief Configure the current output properties for a photo
 * @details Ensure that you call this function before you start the viewfinder
 *          because the photo format is necessary to configure the hardware
 *          correctly.
 *
 *          As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_STABILIZATION
 *           - @c #CAMERA_IMGPROP_JPEGQFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTDIVISOR
 *           - @c #CAMERA_IMGPROP_METAORIENTATIONHINT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 * For example, you can set the values in the following manner:
 * @code
 * camera_set_photo_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, 1024,
 *                            CAMERA_IMGPROP_HEIGHT, 576,
 *                            CAMERA_IMGPROP_ROTATION, 90);
 * @endcode
 *
 * @b Note: The following properties can't be changed after the
 *      viewfinder has started:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_JPEGQFACTOR
 *      You can change these properties after stopping the
 *      viewfinder.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. If you pass a value that does not match the type
 *         required for the property, the return value does not clearly
 *         indicate the problem.
 */
#define camera_set_photo_property(handle, args...) \
    _camera_set_photo_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_set_photo_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_photo_property(camera_handle_t handle,
                           ...);


/**
 * @brief Retrieve the output properties for a photo
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_FORMAT
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_STABILIZATION
 *           - @c #CAMERA_IMGPROP_JPEGQFACTOR
 *           - @c #CAMERA_IMGPROP_BURSTDIVISOR
 *           - @c #CAMERA_IMGPROP_METAORIENTATIONHINT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 *
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 * For example, you can retrieve the values in the following manner:
 * @code
 * camera_get_photo_property( camera_handle,
 *                              CAMERA_IMGPROP_WIDTH, &vf_width,
 *                              CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                              CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                              CAMERA_IMGPROP_STABILIZATION, &stable,
 *                              CAMERA_IMGPROP_FRAMERATE, &framerate,
 *                              CAMERA_IMGPROP_JPEGQFACTOR, &jpeq,
 *                              CAMERA_IMGPROP_BURSTDIVISOR, &burstdiv );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. If you pass a value that does not match the type
 *         required for the property, the return value does not clearly
 *         indicate the problem.
 */
#define camera_get_photo_property(handle, args...) \
        _camera_get_photo_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_get_photo_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_photo_property(camera_handle_t handle,
                           ...);


/**
 * @brief Configure the output properties for video
 * @details Ensure that you call this function before you start the viewfinder
 *          in video mode is necessary to configure the hardware correctly.
 *
 *          As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and the correct type for the value such as an
 *          @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *          - @c #CAMERA_IMGPROP_WIDTH
 *          - @c #CAMERA_IMGPROP_HEIGHT
 *          - @c #CAMERA_IMGPROP_FRAMERATE
 *          - @c #CAMERA_IMGPROP_ROTATION
 *          - @c #CAMERA_IMGPROP_STABILIZATION
 *          - @c #CAMERA_IMGPROP_VIDEOCODEC
 *          - @c #CAMERA_IMGPROP_AUDIOCODEC
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 *
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 * For example, you can set the values in the following manner:
 * @code
 * camera_set_video_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, 1024,
 *                            CAMERA_IMGPROP_HEIGHT, 576,
 *                            CAMERA_IMGPROP_ROTATION, 90
 *                            CAMERA_IMGPROP_FRAMERATE, (double)30.0);
 *
 * @endcode
 *          On platforms that do not provide independent video and viewfinder
 *          image streams, the @c #CAMERA_IMGPROP_WIDTH, @c
 *          #CAMERA_IMGPROP_HEIGHT and @c #CAMERA_IMGPROP_ROTATION properties
 *          should match values supplied to the @c camera_set_videovf_property()
 *          function. The viewfinder frame rate (the value used for the @c
 *          @c #CAMERA_IMGPROP_FRAMERATE property in the @c
 *          camera_set_videovf_property() function) must be an integer multiple
 *          of the video frame rate used in this function.
 *
 *          You should determine whether the @c #CAMERA_FEATURE_PREVIEWISVIDEO
 *          property is declared using the @c camera_has_feature() function
 *          before configuring the video output properties.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_set_video_property(handle, args...) \
        _camera_set_video_property(handle, args, CAMERA_IMGPROP_END)


/**
 * @internal
 * For internal use only. Use the camera_set_video_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_set_video_property(camera_handle_t handle,
                           ...);


/**
 * @brief Retrieve the current output properties for video
 *
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c #camera_imgprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value. The following @c
 *          #camera_imgprop_t can be used with this function:
 *           - @c #CAMERA_IMGPROP_WIDTH
 *           - @c #CAMERA_IMGPROP_HEIGHT
 *           - @c #CAMERA_IMGPROP_FRAMERATE
 *           - @c #CAMERA_IMGPROP_ROTATION
 *           - @c #CAMERA_IMGPROP_STABILIZATION
 *           - @c #CAMERA_IMGPROP_VIDEOCODEC
 *           - @c #CAMERA_IMGPROP_AUDIOCODEC
 *
 *           @b Note: There is no type-checking performed by the compiler,
 *                    therefore, you must ensure that the value you provide
 *                    for each property matches the expected data type. Data
 *                    type mismatches can result in undefined
 *                    behavior and may cause your application to crash.
 *
 *         You can specify multiple property-value pairs by delimiting them
 *         with a comma as follows:
 *
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 * For example, you can retrieve the values in the following manner:
 * @code
 * camera_get_video_property( camera_handle,
 *                            CAMERA_IMGPROP_WIDTH, &vf_width,
 *                            CAMERA_IMGPROP_HEIGHT, &vf_height,
 *                            CAMERA_IMGPROP_ROTATION, &vf_rotation,
 *                            CAMERA_IMGPROP_FRAMERATE, &vf_framerate );
 * @endcode
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_video_property(handle, args...) \
        _camera_get_video_property(handle, args, CAMERA_IMGPROP_END)

/**
 * @internal
 * For internal use only. Use the camera_get_video_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_video_property(camera_handle_t handle,
                           ...);


/**
 * @brief Take a photo
 * @details Before you take a photo, ensure that you have configured the
 *          viewfinder, set the output properties for the photo, and started
 *          the viewfinder. This function can only be called if the @c
 *          #CAMERA_FEATURE_PHOTO is available. You can determine whether
 *          the feature is available by calling the @c camera_can_feature()
 *          function. Callbacks that are invoked by this function are called
 *          only once.
 *
 *          If you want an application to save the photo to a
 *          file, then this function should be invoked with the @c
 *          image_callback argument set. When the @c image_callback is set,
 *          the image buffer is provided as the second argument to the callback
 *          function. Then, in the image_callback function that is invoked, you
 *          can save the buffer to a file.
 *
 *          A @c #CAMERA_STATUS_CAPTURECOMPLETE status event is emitted once the
 *          photo capture is completed.
 *
 * Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded.  Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name( @c camera_handle_t,
 *                                                   @c void*).
 *                         The function is a callback that gets
 *                         invoked when the shutter activates. Typically, the
 *                         callback function plays a shutter sound. You can
 *                         use @c NULL if no function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param raw_callback Use @c NULL. Reserved for future use.
 * @param postview_callback A function pointer to a function with the
 *                          following signature:
 *                          @c void @c function_name( @c camera_handle_t,
 *                                                    @c camera_buffer_t*,
 *                                                    @c void*).
 *                          The function is  a callback that gets invoked when
 *                          the post-view (review) image data is available. This
 *                          callback is used to provide a preview-sized copy of
 *                          the photo. Typically, the preview-sized photo is
 *                          used to provide visual feedback by the UI before
 *                          the final image is available. You can use @c
 *                          NULL if no function needs to be called.
 *                          For information about the callback arguments, see
 *                          @ref camapi_callback_mode.
 * @param image_callback   A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name( @c camera_handle_t,
 *                                                   @c camera_buffer_t*,
 *                                                   @c void*).
 *                        The function that is called when the final
 *                         image, such as a JPEG, is available. You can
 *                        @c camera_set_photo_property() function to change the
 *                        @c #CAMERA_IMGPROP_FORMAT to another format other than
 *                        @c #CAMERA_FRAMETYPE_JPEG. You can also use @c NULL if
 *                        no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @param wait A boolean value that indicates whether the function blocks or
 *             not. If the value is set to @c true, this function is
 *             blocking and will return once all specified callbacks have
 *             returned. If the value is set to @c false, this function call is
 *             non-blocking and returns before all specified callbacks have
 *             returned.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_take_photo(camera_handle_t handle,
                  void (*shutter_callback)(camera_handle_t, void*),
                  void (*raw_callback)(camera_handle_t, camera_buffer_t*,
                                       void*),
                  void (*postview_callback)(camera_handle_t,
                                            camera_buffer_t*, void*),
                  void (*image_callback)(camera_handle_t, camera_buffer_t*,
                                         void*),
                  void *arg,
                  bool wait);


/**
 * @brief Take multiple photos in burst mode
 * @details Before you take a photo, ensure that you have configured the
 *          viewfinder, set the output properties for the photo, and started
 *          the viewfinder.  This function can only be called if the @c
 *          #CAMERA_FEATURE_BURST is available. You can determine whether
 *          the feature is available by calling the @c camera_can_feature()
 *          function.
 *
 *          If you want an application to save the photo to a
 *          file, then this function should be invoked with the @c
 *          image_callback argument set. When the @c image_callback is set,
 *          the image buffer is provided as the second argument to the callback
 *          function. Then, in the invoked @c image_callback function, you can
 *          save the buffer to a file. If an application wants to save burst
 *          photos to disk, then the @c image_callback argument should be set.
 *          When this callback is invoked, if the image cannot be saved to disk
 *          before the next frame arrives, then the user should buffer frames
 *          instead and save the buffers to disk after the entire burst is
 *          complete.
 *
 *          @b Note: While in burst mode, you should not save files in the
 *                   callback for performance reasons. Instead, you
 *                   should buffer the images and save them at later time.
 *
 *          The callbacks that you set for this function are called for each
 *          photo and therefore, are called multiple times.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded.  Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 *       Since burst mode captures images in rapid succession, you should choose
 *       an appropriate moment to play the shutter sound rather than play the
 *       shutter sound repeatedly.
 *
 *       A @c #CAMERA_STATUS_CAPTURECOMPLETE status event is emitted once the
 *       burst capture is completed.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param burst_count The number of frames to take in a single burst.
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name( @c camera_handle_t,
 *                                                   @c void*).
 *                         The function is a callback that gets invoked when
 *                         the shutter activates. Typically, the callback function
 *                         plays a shutter sound. You can use @c NULL if no
 *                         function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param raw_callback Use @c NULL. Reserved for future use.
 * @param postview_callback A function pointer to a function with the
 *                          following signature:
 *                          @c void @c function_name( @c camera_handle_t,
 *                                                    @c camera_buffer_t*,
 *                                                    @c void*).
 *                          The function is  a callback
 *                          that gets invoked when the postview (review) image
 *                          data is available. This callback is used to provide
 *                          a preview-sized copy of the photo. Typically, the
 *                          preview-sized photo is used to provide visual
 *                          feedback before the final image is available. You
 *                          can use @c NULL if no function needs to be called.
 *
 *                          For information about the callback arguments, see
 *                          @ref camapi_callback_mode.
 * @param image_callback   A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name(@c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                        The function that is called when the final
 *                        full-resolution image is available. You can use @c
 *                        NULL if no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @param wait A boolean value that indicates whether the function blocks or
 *             not. If set to @c true, this function is blocking and will
 *             return once all specified callbacks have returned. If set to
 *             @c false, this function call is non-blocking and returns before
 *             all specified callbacks have returned.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_take_burst(camera_handle_t handle,
                  int burst_count,
                  void (*shutter_callback)(camera_handle_t, void*),
                  void (*raw_callback)(camera_handle_t,
                                       camera_buffer_t*, void*),
                  void (*postview_callback)(camera_handle_t,
                                            camera_buffer_t*, void*),
                  void (*image_callback)(camera_handle_t, camera_buffer_t*,
                                        void*),
                  void *arg,
                  bool wait);


/**
 * @brief Start to take pictures in burst mode
 * @details Before you take a photo, ensure that you have configured the
 *          viewfinder, set the output properties for the photo, and started
 *          the viewfinder. This function can only be called if the @c
 *          #CAMERA_FEATURE_CONTINUOUSBURST is available. You can determine
 *          whether the feature is available by calling the @c
 *          camera_can_feature() function.
 *
 *          This function does not block. To terminate a continuous burst
 *          capture, call the @c camera_stop_burst() function.
 *
 *         Unlike the @c camera_take_burst function, there is no upper limit
 *         to the number of pictures you can take. Buffers are only valid for
 *         the duration of the callback to prevent memory exhaustion. To prevent
 *         memory exhaustion, you can:
 *         - Maintain a circular buffer in order to implement negative-shutter
 *           lag.
 *         - Maintain a growing heap of buffers after capture begins in order
 *           to select your favorite photo - after the fact.
 *         - Only capture images where certain criteria has been met. For
 *           example, capture images that contain only smiles or three faces are
 *           seen in the photo.
 *
 *         Burst runs as close as possible to the preview frame rate specified
 *         by in the @c camera_set_photovf_property() function divided by the
 *         burst divisor specified in the @c camera_set_photo_property()
 *         function. Use the @c camera_start_burst() function when image-capture
 *         latency is a concern or when your application cannot tolerate brief
 *         disruptions to the viewfinder. Brief disruptions can occur when using
 *         the @c camera_take_photo() function.
 *
 *         You should make copies of the frames as they arrive and exit the
 *         callback as quickly as possible. You should avoid saving the files
 *         within the @c image_callback function because writing to disk may
 *         take more time that is available before the next frame arrives.
 *         For this reason, buffers are only valid until the callback function
 *         returns. Memory that was valid before a callback started is
 *         unmapped from user's process when the callback completes. Attempts to
 *         access memory buffers after the end of a callback function yields
 *         undefined results, such as bus errors.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded.  Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 *       Since burst mode captures images in rapid succession, you should choose
 *       an appropriate moment to play the shutter sound rather than play the
 *       shutter sound repeatedly.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutter_callback A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name( @c camera_handle_t,
 *                                                   @c void*).
 *                         The function is a callback that gets invoked when
 *                         the shutter activates. Typically, the callback function
 *                         plays a shutter sound. You can use @c NULL if no
 *                         function needs to be called.
 *                         For information about the callback arguments, see
 *                         @ref camapi_callback_mode.
 * @param raw_callback Use @c NULL. Reserved for future use.
 * @param postview_callback A function pointer to a function with the
 *                          following signature:
 *                          @c void @c function_name(@c camera_handle_t,
 *                                                   @c camera_buffer_t*,
 *                                                   @c void*).
 *                          The function is  a callback that gets invoked when
 *                          the post-view (review) image data is available.
 *                          This callback is used to provide a preview-sized
 *                          copy of the photo. Typically, the preview-sized
 *                          photo is used to provide visual feedback before the
 *                          final image is available. You can use @c NULL if no
 *                          function needs to be called.
 *                          For information about the callback arguments, see
 *                          @ref camapi_callback_mode.
 * @param image_callback   A function pointer to a function with the following
 *                         signature:
 *                         @c void @c function_name(@c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                        The function that is called when the final
 *                        full-resolution image is available. You can use @c
 *                         NULL if no function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is
 *            the last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         callfailed.
 */
camera_error_t
camera_start_burst(camera_handle_t handle,
                   void (*shutter_callback)(camera_handle_t, void*),
                   void (*raw_callback)(camera_handle_t,
                                        camera_buffer_t*, void*),
                   void (*postview_callback)(camera_handle_t,
                                             camera_buffer_t*, void*),
                   void (*image_callback)(camera_handle_t, camera_buffer_t*,
                                          void*),
                   void *arg);


/**
 * @brief Stop taking photos in burst mode
 * @details Stops the camera from taking any more pictures in burst mode.
 *          Use this function to terminate a continuous burst capture after you
 *          called  the @c camera_start_burst() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_burst(camera_handle_t handle);


/**
 * @brief Performs optional initialization for video recording and encoding
 * @details Calling this function is optional, however, when called once, the
 *          first call to the @c camera_start_video() or @c camera_start_encode()
 *          functions take less time. If this function is not called, more
 *          initialization time is required when you call the @c
 *          camera_start_video() or @c camera_start_encode() functions the
 *          first time.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_init_video_encoder(void);


/**
 * @brief Start recording video
 * @details This function can only be called if the @c #CAMERA_FEATURE_VIDEO
 *          is available. You can determine whether the feature is available by
 *          calling the @c camera_can_feature() function.
 *
 *          Video is recorded based on the configured properties. You must
 *          use the @c camera_start_video_viewfinder() to start the viewfinder
 *          before you call this function. The audio track will be taken
 *          from the active audio input on the device.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded.  Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 * @b Note: Before calling this function, call the @c
 *      camera_set_video_property() function to ensure that all
 *      required properties are set.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param filename The name of the file to save the video to.
 * @param video_callback A function pointer to a function with the following
 *                       signature:
 *                        @c void @c function_name( @c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                       The function is a callback function to invoke
 *                       when the uncompressed video frame is available.
 *                       You can use @c NULL if no function needs to be called.
 *                       For information about the callback arguments, see
 *                       @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 *                        @c void @c function_name(@c camera_handle_t,
 *                                                 @c camera_devstatus_t,
 *                                                 @c uint16_t, @c void*).
 *                        The function is a callback that gets invoked when
 *                        status events occur. You can use @c NULL if no
 *                        function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. @c #CAMERA_EINVAL is returned if there
 *         is a mismatch in video properties set using @c
 *         camera_set_video_property() function.
 */
camera_error_t
camera_start_video(camera_handle_t handle,
                   const char *filename,
                   void (*video_callback)(camera_handle_t,
                                          camera_buffer_t*, void*),
                   void (*status_callback)(camera_handle_t, camera_devstatus_t,
                                           uint16_t, void*),
                   void *arg);


/**
 * @brief Stop recording video
 * @details Use this function to stop a video recording that has been started
 *          with the @c camera_start_video() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_video(camera_handle_t handle);



/**
 * @brief Start encoding video
 * @details This function can only be called if the @c #CAMERA_FEATURE_VIDEO
 *          is available. You can determine whether the feature is available by
 *          calling the @c camera_can_feature() function.
 *
 *          Video is encoded based on the configured properties. You must
 *          use the @c camera_start_video_viewfinder() to start the viewfinder
 *          before you call this function. The audio track will be taken
 *          from the active audio input on the device.
 *
 * @b Note: The Camera library @b does @b not automatically play audible shutter
 *       sounds when a picture is taken or a video is recorded.  Camera
 *       applications must supply their own sound when a photo is captured or a
 *       video recording begins and ends. While you can choose to not have a
 *       shutter sound when taking a picture - you are responsible to ensure
 *       that the application adheres to the local laws of the regions in which
 *       you wish to distribute the application.
 *
 *       For example, it is illegal to mute or modify the shutter sound of a
 *       camera application in Japan and Korea. Ensure that you comply with the
 *       laws and regulations for the countries in which you distribute your
 *       application. For more information, see the BlackBerry World Vetting
 *       Criteria at https://appworld.blackberry.com/isvportal/home.do.
 *
 * @b Note: Before calling this function, call the @c
 *          camera_set_video_property() function to ensure that all required
 *          properties are set.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param video_callback A function pointer to a function with the following
 *                       signature:
 *                        @c void @c function_name( @c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                       The function is a callback function to invoke
 *                       when the uncompressed video frame is available.
 *                       You can use @c NULL if no function needs to be called.
 *                       For information about the callback arguments, see
 *                       @ref camapi_callback_mode.
 * @param enc_video_callback A function pointer to a function with the following
 *                       signature:
 *                        @c void @c function_name( @c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                       The function is a callback function to invoke
 *                       when the encoded video frame is available.
 *                       This argument is mandatory and can't be a @c NULL
 *                       value.
 *                       For information about the callback arguments, see
 *                       @ref camapi_callback_mode.
 * @param enc_audio_callback A function pointer to a function with the following
 *                       signature:
 *                        @c void @c function_name( @c camera_handle_t,
 *                                                  @c camera_buffer_t*,
 *                                                  @c void*).
 *                       The function is a callback function to invoke
 *                       when the encoded audio frame is available.
 *                       You can use @c NULL if no function needs to be called.
 *                       For information about the callback arguments, see
 *                       @ref camapi_callback_mode.
 * @param status_callback A function pointer to a function with the following
 *                        signature:
 *                        @c void @c function_name(@c camera_handle_t,
 *                                                 @c camera_devstatus_t,
 *                                                 @c uint16_t, @c void*).
 *                        The function is a callback that gets invoked when
 *                        status events occur. You can use @c NULL if no
 *                        function needs to be called.
 *                        For information about the callback arguments, see
 *                        @ref camapi_callback_mode.
 * @param arg The argument passed to all callback functions, which is the
 *            last argument in the callback functions.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed. @c #CAMERA_EINVAL is returned if there
 *         is a mismatch in video properties set using @c
 *         camera_set_video_property() function.
 */
camera_error_t
camera_start_encode(camera_handle_t handle,
                    void (*video_callback)(camera_handle_t,
                                           camera_buffer_t*, void*),
                    void (*enc_video_callback)(camera_handle_t,
                                               camera_buffer_t*, void*),
                    void (*enc_audio_callback)(camera_handle_t,
                                               camera_buffer_t*, void*),
                    void (*status_callback)(camera_handle_t, camera_devstatus_t,
                                            uint16_t, void*),
                    void *arg);


/**
 * @brief Stop encoding video
 * @details Use this function to stop a video recording that has been started
 *          with the @c camera_start_encode() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_stop_encode(camera_handle_t handle);


/**
 * @brief Configure the zoom level on the camera for taking a photo
 * @details This function can be called if the @c #CAMERA_FEATURE_VIDEOZOOM
 *          or @c #CAMERA_FEATURE_PHOTOZOOM feature are available. You can
 *          determine whether the feature is available by calling the @c
 *          camera_can_feature() function. In addition, the photo or video
 *          viewfinder must be started using either the @c
 *          camera_start_photo_viewfinder() or @c
 *          camera_start_video_viewfinder() functions, respectively.
 *
 *          The value that you specify as the @c level argument sets the
 *          viewfinder zoom-level. The zoom level is a value supported by the
 *          camera hardware and can represent an optical or digital zoom
 *          depending on which the hardware supports.
 *
 *          You can specify whether to use smooth zooming using the
 *          @c smooth argument. You can use the @c camera_get_zoom_limits()
 *          function to determine the supported zoom levels and whether the
 *          camera supports smooth zooming.
 *
 *  @b Note: Changing the zoom level can interfere with existing settings
 *          which depend on coordinates within the viewfinder frame.
 *          For example, the @c camera_set_focus_regions() function can
 *          exhibit undefined behavior after the zoom level has changed.
 *          To resolve this issue, ensure that you reapply any region-dependent
 *          settings after a zoom level change.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param level An @c unsigned @c int value which falls within the minimum or
 *              maximum range returned by @c camera_get_zoom_limits() function.
 *              A value of 0 indicates not to use zoom. Values larger than 0
 *              indicate increasing magnification.
 * @param smooth A of @c true specifies to zoom to specified
 *               @c level value, while a value of @c false, specifies to jump
 *               to the specified zoom level.
 * @return @c #CAMERA_EOK when the function successfully sets the zoom level,
 *         otherwise another @c ::camera_error_t value that provides the reason
 *         that the call failed.
 */
camera_error_t
camera_set_zoom(camera_handle_t handle,
                unsigned int level,
                bool smooth);


/**
 * @brief Retrieve the supported range of zoom levels and whether smooth zooming
 *        is supported by the camera
 * @details Not all cameras support smooth zooming.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param min_level A pointer to an @c int value that will be updated with the
 *                  minimal zoom level supported by the camera.
 * @param max_level A pointer to an @c int value that will be updated with the
 *                  maximum zoom level supported by the camera.
 * @param smooth A pointer to a boolean value that will be updated when the call
 *               completes. A value of @c true indicates that smooth zooming is
 *               supported by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_zoom_limits(camera_handle_t handle,
                       unsigned int *min_level,
                       unsigned int *max_level,
                       bool *smooth);


/**
 * @brief Change the scene mode on the camera
 * @details You specify the scene mode to set using the @c mode
 *          argument. The viewfinder must be active prior to setting the scene
 *          mode. Use @c camera_get_scene_modes() to determine the focus modes
 *          that are supported for the current platform and camera.
 *
 * @b Note: Some scene modes override previously configured settings.  For
 *       example, if you set the scene mode to @c #CAMERA_SCENE_NIGHT, it may
 *       override the programmed frame rate in order to achieve better
 *       low-light performance.  In this situation, you can change the scene
 *       mode to another mode other than @c #CAMERA_SCENE_NIGHT to restore the
 *       frame rate back to its configured value.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired scene mode to set the camera to.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_scene_mode(camera_handle_t handle,
                      camera_scenemode_t mode);


/**
 * @brief Query the current scene mode of the camera
 * @details This function allows you to retrieve the currently configured scene
 *          mode for the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to a @c camera_scenemode_t value in which to return
 *        the currently configured scene mode.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_scene_mode(camera_handle_t handle,
                      camera_scenemode_t* mode);


/**
 * @brief Retrieve the scene modes available for the camera
 * @details The API allows you to retrieve the scene modes available given the
 *          current platform and camera.  A viewfinder must be active prior
 *          to retrieving supported scene modes or changing scene modes.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of scene modes to return in the @c modes
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported scene modes available on the camera.
 * @param numsupported The pointer to an integer that will be updated  with the
 *                     number of scene modes supported by the camera.
 * @param modes A pointer to a @c camera_scenemode_t array. The array is
 *              updated with the scene modes supported by the camera. Ensure
 *              that you create an array with the same number of elements as the
 *              @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_scene_modes(camera_handle_t handle,
                       int numasked,
                       int *numsupported,
                       camera_scenemode_t *modes);


/**
 * @brief Configure the flash mode for the camera
 * @details This function can be called if the @c #CAMERA_FEATURE_FLASH
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function. You
 *          specify the flash mode to set using the @c mode argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired flash mode to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_flash(camera_handle_t handle,
                    camera_flashmode_t mode);


/**
 * @brief Configure focus assist light
 * @details This function can be called if the @c #CAMERA_FEATURE_FOCUSASSIST
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable A flag that indicates whether or not to enable focus assist.
 *               To enable, set to @c true.  To disable, set to @c false.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_focus_assist(camera_handle_t handle,
                           bool enable);


/**
 * @brief Configure the video-light on the camera
 * @details This function can be called if the @c #CAMERA_FEATURE_VIDEOLIGHT
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *          You specify the video-light mode to set using the @c mode argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The desired video-light mode to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_videolight(camera_handle_t handle,
                         camera_videolightmode_t mode);


/**
 * @brief Configure the exposure bracketing settings
 * @details This function can be called if the @c #CAMERA_FEATURE_EVBRACKETING
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          An array of EV deltas can be configured when a burst is triggered.
 *          The exposure deltas will be applied to successive frames. For
 *          example, {-3.0, 0.0, +3.0} in conjunction with a three-shot burst
 *          would yield three images. The first underexposed by three stops,
 *          the second at nominal exposure, and the third would be overexposed
 *          by three stops.
 *
 *          Before you use this function, you must start the photo viewfinder.
 *          You can use the @c camera_get_ev_bracketing_limits()
 *          function to determine the exposure bracketing minimum and maximum
 *          values, as well as the maximum set in the @c num argument.
 *
 * @code
 * camera_error_t camretcode;
 * double ev_deltas[] = {-3.0, 0.0, +3.0};
 * retcode = camera_config_ev_bracketing( handle,
 *                                        sizeof(ev_deltas)/sizeof(double),
 *                                        ev_deltas );
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param num The number of exposure bracket delta values.
 * @param ev_deltas A pointer to an array of exposures deltas values.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_ev_bracketing(camera_handle_t handle,
                            uint32_t num,
                            double *ev_deltas);


/**
 * @brief Retrieve the exposure bracketing minimum and maximum values
 * @details Bracketing is a technique that involves taking several shots
 *          of the same subject using different exposure levels. To use this
 *          function, pass in pointers to the @c max_num, @c min_delta, @c and
 *          max_delta arguments to retrieve the appropriate limits supported
 *          by the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param max_num A pointer that will be updated  with the maximum number of
 *                bracketing deltas that are supported by the camera.
 * @param min_delta A pointer that will be updated  with the minimal EV
 *                  delta that is supported by the camera.
 * @param max_delta A pointer that will be updated  with the maximum EV
 *                  delta that are supported by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_ev_bracketing_limits(camera_handle_t handle,
                                uint32_t *max_num,
                                double *min_delta,
                                double *max_delta);


/**
 * @brief Retrieve the focus state of the camera
 * @details The focus state and the region of focus when the function
 *          completes successfully. Typically, you call this function when
 *          a status callback of type @c #CAMERA_STATUS_FOCUS_CHANGE is received.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param state A pointer that will be updated with the focus state of the camera.
 * @param region A pointer that will be updated with the region that the focus
 *               has locked to. Only valid when state is @c
 *               #CAMERA_FOCUSSTATE_LOCKED.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_state(camera_handle_t handle,
                       camera_focusstate_t *state,
                       camera_region_t *region);


/**
 * @brief Configure the focus mode on the camera
 * @details You can use the value of the @c camera_focusmode_t to set the
 *          focus mode on the camera. Use @c camera_get_focus_modes() to
 *          determine the focus modes that are supported for the current
 *          platform and camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The focus mode to use.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_focus_mode(camera_handle_t handle,
                      camera_focusmode_t mode);


/**
 * @brief Retrieve the focus mode from the camera
 * @details The focus mode of the camera is retrieved from the @c mode
 *          pointer that is passed to the function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer to a @c bool value that is updated with the current
 *             focus mode of the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_mode(camera_handle_t handle,
                      camera_focusmode_t *mode);


/**
 * @brief Retrieve the focus modes available on the camera
 * @details Use this function to retrieve the focus modes available given the
 *          current platform.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked element allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or @c
 *          modes argument set to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of focus modes to return in the @c modes
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported focus modes available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of focus modes supported by the camera.
 * @param modes A pointer to a @c camera_focusmode_t array. The array is updated
 *              with the focus modes supported by the camera. Ensure that
 *              you create an array with the same number of elements as the
 *              @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_modes(camera_handle_t handle,
                       int numasked,
                       int *numsupported,
                       camera_focusmode_t *modes);


/**
 * @brief Configure the focus regions on the camera
 * @details This function can be called if the @c #CAMERA_FEATURE_REGIONFOCUS
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The maximum number of focus regions that you can configure is
 *          returned by the @c numsupported argument of the
 *          @c camera_get_focus_regions() function.
 *
 *          After setting the regions, you must call the @c
 *          camera_set_focus_mode() function to commit the changes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numregions The number of regions to apply, which is the number of
 *                   elements in the @c regions array.
 * @param regions A pointer to an array of focus regions to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_focus_regions(camera_handle_t handle,
                         int numregions,
                         camera_region_t *regions);


/**
 * @brief Retrieve the focus regions configured on the camera
 * @details This function allows you to retrieve the configured autofocus
 *          grid from the camera.  See @c camera_set_focus_regions() for
 *          details on configuring this grid.  When regions are defined,
 *          the autofocus algorithm will give priority to focusing on
 *          objects in the defined areas.
 *
 *          The maximum number of supported focus regions is determined by
 *          checking the @c numsupported argument when the function completes
 *          successfully.
 *
 *          Ensure that the @c regions argument points to an array
 *          which has at least @c numasked element allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          regions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of regions to return in the @c regions
 *                 array. You can specify a value of 0 to determine the number
 *                 of supported focus regions available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of focus regions supported by the camera.
 * @param numreturned The pointer to an integer that will be updated with the
 *                    number of focus regions returned in the @c regions array.
 * @param regions A pointer to a @c ::camera_region_t array. The array is updated
 *                with the focus regions configured on the camera. Ensure that
 *                you create an array with the same number of elements as the
 *                @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_focus_regions(camera_handle_t handle,
                         int numasked,
                         int *numsupported,
                         int *numreturned,
                         camera_region_t *regions);


/**
 * @brief Configure the auto exposure regions on the camera
 * @details This function can be called if the @c #CAMERA_FEATURE_REGIONEXPOSURE
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          The maximum number of exposure regions that you can configure is
 *          returned by the @c numsupported argument of the
 *          @c camera_get_exposure_regions() function.
 *
 *          After setting the regions, you must call the @c
 *          camera_set_exposure_mode() function to commit the changes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numregions The number of regions to apply, which is the number of
 *                   elements in the @c regions array.
 * @param regions A pointer to an array of focus regions to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_exposure_regions(camera_handle_t handle,
                            int numregions,
                            camera_region_t *regions);


/**
 * @brief Retrieve the exposure regions configured on the camera
 * @details This function allows you to retrieve the configured auto exposure
 *          grid from the camera.  See @c camera_set_exposure_regions() for
 *          details on configuring this grid.  When regions are defined,
 *          the auto exposure algorithm will give exposure priority to
 *          objects in the defined areas.
 *
 *          The maximum number of supported exposure regions is determined by
 *          checking the @c numsupported argument when the function completes
 *          successfully.
 *
 *          Ensure that the @c regions argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          regions argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of regions to return in the @c regions
 *                 array. You can specify a value of 0 to determine the number
 *                 of supported exposure regions available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of exposure regions supported by the camera.
 * @param numreturned The pointer to an integer that will be updated with the
 *                    number of exposure regions returned in the @c regions array.
 * @param regions A pointer to a @c camera_region_t array. The array is updated
 *                with the exposure regions configured on the camera. Ensure that
 *                you create an array with the same number of elements as the
 *                @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_exposure_regions(camera_handle_t handle,
                            int numasked,
                            int *numsupported,
                            int *numreturned,
                            camera_region_t *regions);


/**
 * @brief Configure the auto white balance regions on the camera
 * @details This function can be called if the @c
 *          #CAMERA_FEATURE_REGIONWHITEBALANCE feature is available.
 *          Use the @c camera_can_feature() function to determine whether the
 *          feature is available.
 *
 *          The maximum number of white balance regions that you can configure
 *          is returned by the @c numsupported argument of the @c
 *          camera_get_whitebalance_regions() function.
 *
 *          After setting the regions, you must call the @c
 *          camera_set_whitebalance_mode() function to commit the changes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numregions The number of regions to apply, which is the number of
 *                   elements in the @c regions array.
 * @param regions A pointer to an array of focus regions to apply.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_whitebalance_regions(camera_handle_t handle,
                                int numregions,
                                camera_region_t *regions);


/**
 * @brief Retrieve the white balance regions configured on the camera
 * @details This function allows you to retrieve the configured auto-
 *          white balance grid from the camera.  See @c
 *          camera_set_whitebalance_regions() for details on configuring this
 *          grid. When regions are defined, the auto white balance algorithm
 *          gives auto whitebalancing priority to objects in the defined
 *          areas.
 *
 *          The maximum number of supported white balance regions is determined
 *          by checking the @c numsupported argument when the function completes
 *          successfully.
 *
 *          Ensure that the @c regions argument points to an array
 *          which has at least @c numasked elements allocated.To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or
 *          setting the regions argument to NULL. When the function is invoked
 *          in @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value that was returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of regions to return in the @c regions
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported white balance regions available on the
 *                 camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of white balance regions supported by the camera.
 * @param numreturned The pointer to an integer that will be updated with the
 *                    number of white balance regions returned in the @c regions
 *                    array.
 * @param regions A pointer to a @c ::camera_region_t array. The array is
 *                updated with the white balance regions configured on the
 *                camera. Ensure that you create an array with the same number
 *                of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_whitebalance_regions(camera_handle_t handle,
                                int numasked,
                                int *numsupported,
                                int *numreturned,
                                camera_region_t *regions);


/**
 * @brief Configures the autofocus, auto exposure, and auto white balance
 *        locks on the camera
 *
 * @details For the @c locks argument, you can specify the locks by ORing
 *          values from @c ::camera_3a_t enumerated type. The following are
 *          examples:
 *          - To unlock autofocus, auto exposure, and auto white balance, use
 *            the value of @c CAMERA_3A_NONE.
 *          - To lock autofocus and auto exposure and unlock
 *            auto white balance, use the value of @c
 *            CAMERA_3A_AUTOFOCUS|CAMERA_3A_AUTOEXPOSURE.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param locks The lock to configure on the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_3a_lock(camera_handle_t handle,
                   uint32_t locks);


/**
 * @brief Retrieve the list of supported lock modes on the camera
 *
 * @details The lock modes that are supported are returned as separate
 *          elements in an array. The following examples list the array elements
 *          that are returned:
 *
 *          For a camera where all three lock modes can be operated
 *          independently, the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_AUTOEXPOSURE
 *           - element 2: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 3: CAMERA_3A_NONE
 *          @endcode
 *          For a camera where autofocus and auto exposure need to be locked
 *          simultaneously, the array returned is as follows:
 *           @code
 *           - element 0: CAMERA_3A_AUTOFOCUS|CAMERA_3A_AUTOEXPOSURE
 *           - element 1: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *           @endcode
 *          For a camera where autofocus, auto exposure, and auto white balance
 *          needs to be locked together, the array returned is as follows:
 *          @code
 *           - element 0:
 *          CAMERA_3A_AUTOFOCUS|CAMERA_3A_AUTOEXPOSURE|
 *          CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *          For a camera that supports only autofocus, the array returned is
 *          as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of modes to retrieve from the camera
 *                 and should  be equal to the number of elements in the array
 *                 you pass as the @c modes argument.
 * @param numsupported A pointer to an @c int value that is updated with the
 *                     number of lock modes that are supported by the platform.
 * @param modes A pointer to an @c uint32_t array. The array is updated with the
 *              lock modes supported by the camera. Ensure that you create an
 *              array with the same number of elements as indicated by the @c
 *              numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_3a_lock_modes(camera_handle_t handle,
                         int numasked,
                         int *numsupported,
                         uint32_t *modes);

/**
 * @brief Configure 3A algorithm for face-detection priority
 *
 * @details For the @c priority argument, you can OR values from the @c
 *          #camera_3a_t enumerated type to enable or disable 3A face-detection
 *          priority. These are examples:
 *
 *          - Enable 3A face-detection priority for autofocus and auto exposure,
 *            but not auto white balance:
 *            @c CAMERA_3A_AUTOFOCUS|CAMERA_3A_AUTOEXPOSURE.
 *          - Disable face priority:
 *            @c CAMERA_3A_NONE
 *
 *          @b Note: Enabling 3A face-detection priority for a given mode will
 *                   clear any corresponding @c ::camera_region_t. For example,
 *                   if @c priority includes @c #CAMERA_3A_AUTOEXPOSURE, the
 *                   @c ::camera_region_t set by @c camera_set_exposure_regions()
 *                   is cleared.
 *
 *          After 3A face-priority algorithms are enabled, the camera will select
 *          a default face to track. You can explicitly select a different face
 *          using @c camera_set_3a_face_id().
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param priority The face priority mode to configure on the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_3a_face_priority(camera_handle_t handle,
                            uint32_t priority);

/**
 * @brief Retrieve the list of supported 3A face-detection priority modes
 *        on the camera
 *
 * @details The 3A face-detection priority modes that are supported are returned
 *          as separate elements in an array. The following examples list the
 *          array elements that are returned:
 *
 *          For a camera where all three 3A face-detection priority modes can be
 *          operated independently, the array returned is as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_AUTOEXPOSURE
 *           - element 2: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 3: CAMERA_3A_NONE
 *          @endcode
 *
 *          For a camera where autofocus and auto exposure need to be used
 *          simultaneously, the array returned is as follows:
 *
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS|CAMERA_3A_AUTOEXPOSURE
 *           - element 1: CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          For a camera where autofocus, auto exposure, and auto white balance
 *          needs to be used together, the array returned is as follows:
 *          @code
 *           - element 0:
 *          CAMERA_3A_AUTOFOCUS|CAMERA_3A_AUTOEXPOSURE|
 *          CAMERA_3A_AUTOWHITEBALANCE
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          For a camera that supports only autofocus, the array returned is
 *          as follows:
 *          @code
 *           - element 0: CAMERA_3A_AUTOFOCUS
 *           - element 1: CAMERA_3A_NONE
 *          @endcode
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of 3A face-detection priority modes
 *                 to retrieve from the camera and should be equal to the number
 *                 of elements in the array you pass as the @c modes argument.
 * @param numsupported A pointer to an @c int value that is updated with the
 *                     number of 3A face-detection priority modes that are
 *                     supported by the camera.
 * @param modes A pointer to an @c uint32_t array. The array is updated with the
 *              3A face-detection priority modes supported by the camera. Ensure
 *              that you create an array with the same number of elements as
 *              indicated by the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_3a_face_priority_modes(camera_handle_t handle,
                                  int numasked,
                                  int *numsupported,
                                  uint32_t *modes);


/**
 * @brief Select a face for the 3A face-priority algorithms to track
 *
 * @details Use this function to instruct the 3A face-priority algorithms
 *          to operate only on the face identified by the caller. The face ID
 *          must correspond to a valid face as reported by the face detection
 *          metadata and retrieved by a call to @c camera_meta_get_face_id().
 *          You can only use this function after face-priority 3A algorithms are
 *          enabled using @c camera_set_3a_face_priority().
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param id The face ID to operate on. Reported by @c camera_meta_get_face_id().
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_3a_face_id(camera_handle_t handle,
                      uint32_t id);


/**
 * @brief Deselect a face for the 3A face-priority algorithms to track
 *
 * @details Use this function to instruct the 3A face-priority algorithms
 *          to disregard a previously programmed face ID and to return to the
 *          default 3A face-priority behaviour. You can only use this
 *          function after face-priority 3A algorithms are enabled using
 *          @c camera_set_3a_face_priority().
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_clear_3a_face_id(camera_handle_t handle);


/**
 * @brief Retrieve the ID of the face that the 3A face-priority algorithms
 *        are currently tracking
 *
 * @details Use this function to query which face the 3A face-priority
 *          algorithms are currently operating on. If the user has previously
 *          selected a face to track using @c camera_set_3a_face_id(), then the
 *          returned ID will match the ID the user provided. If the user has
 *          not previously specified a face to track, then this function will
 *          return the ID of the face which the 3A face-priority algorithms
 *          have defaulted to tracking. You can only use this function after
 *          face-priority 3A algorithms are enabled using @c
 *          camera_set_3a_face_priority().
 *
 *          If no face is tracked, this function returns @c #CAMERA_ENODATA for
 *          one of these reasons:
 *          - There are no faces detected in the scene
 *          - The user-selected face is no longer present in the scene
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param id A pointer to a @c uint32_t value that is updated with the ID of the
 *           face that is currently being tracked.
 *
 * @return @c #CAMERA_EOK when the function successfully completes,
 *         @c #CAMERA_ENODATA when there is no face being tracked, otherwise
 *         another @c ::camera_error_t value that provides the reason
 *         that the call failed.
 */
camera_error_t
camera_get_3a_face_id(camera_handle_t handle,
                      uint32_t *id);


/**
 * @brief Change the manual focus to a desired level on the camera
 * @details This function can be called if the @c #CAMERA_FEATURE_MANUALFOCUS
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          Before you can change the focus, you need to set the
 *          camera to @c #CAMERA_FOCUSMODE_MANUAL using the @c
 *          camera_set_focus_mode() function.
 *
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param step The location  to set the focus. Use the @c
 *             camera_get_manual_focus_step() function to retrieve the details
 *             on the range accepted for this argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_focus_step(camera_handle_t handle,
                             int step);


/**
 * @brief Retrieve information regarding the manual focus step, including the
 *        currently configured step value and the maximum supported step value
 * @details Use this function when the @c #CAMERA_FEATURE_MANUALFOCUS
 *          feature is available. You can determine whether the feature is
 *          available by calling the @c camera_can_feature() function.
 *
 *          Before you can use this function to retrieve the range of accepted
 *          values, you need to set the camera to @c
 *          #CAMERA_FOCUSMODE_MANUAL using the @c camera_set_focus_mode()
 *          function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param maxstep A pointer to the maximum settable step value that can be used
 *                for manual focus. It also indicates infinity focus.
 * @param step A pointer to the current step value (position) of the lens.
 *             The minimum step value is 0 and the maximum step is the value
 *             returned by the @c maxstep argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_focus_step(camera_handle_t handle,
                             int *maxstep,
                             int *step);


/**
 * @brief Create and open the next available file on the camera roll for
 *        writing
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera service manages unique
 *          filenames on behalf of the user. Use this function to retrieve
 *          the next available file from the camera roll. You require @c
 *          #CAMERA_MODE_ROLL access mode when you call the @c camera_open()
 *          function to open the camera.
 *
 *          After you successfully call this function, a file is created and
 *          opened for writing. To close the file, you must call the @c
 *          camera_roll_close_photo() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param  fd A pointer to the file descriptor. The pointer that is returned
 *            pointers an open photo file on the camera roll.
 * @param  filename A pointer to returned name of the file on the camera roll.
 *                  Ensure that the array pointed to by filename is at least of
 *                  size @c #CAMERA_ROLL_NAMELEN.
 * @param  namelen The size of the buffer provided by the caller as the
 *                 filename. The maximum size is indicated by the value of @c
 *                 #CAMERA_ROLL_NAMELEN.
 * @param fmt The image file format to create.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_open_photo(camera_handle_t handle,
                       int *fd,
                       char *filename,
                       int namelen,
                       camera_roll_photo_fmt_t fmt);


/**
 * @brief Close the file descriptor for a file on the camera roll
 *
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera service manages unique filenames
 *          on behalf of the user. Use this function to close the file
 *          descriptor that was returned by calling the @c
 *          camera_roll_open_photo() function on the camera roll.
 *
 * @param fd The file descriptor to the open file on the camera roll.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_close_photo(int fd);


/**
 * @brief Create and open a new video file on the camera roll for writing
 *
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera service manages unique
 *          filenames on behalf of the user.
 *
 *          After you successfully call this function, a file is created and
 *          opened for writing. To close the file, you must call the @c
 *          camera_roll_close_video() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param  fd A pointer to the file descriptor. The pointer that is returned
 *            pointers an open video file on the camera roll.
 * @param  filename A pointer to returned name of the file on the camera roll.
 *                  Ensure that the array pointed to by filename is at least of
 *                  size @c #CAMERA_ROLL_NAMELEN.
 * @param  namelen The size of the buffer provided by the caller as the
 *                 filename.  The maximum size is indicated by the value of @c
 *                 #CAMERA_ROLL_NAMELEN.
 * @param fmt The video file format to create.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_open_video(camera_handle_t handle,
                       int *fd,
                       char *filename,
                       int namelen,
                       camera_roll_video_fmt_t fmt);


/**
 * @brief Close the file descriptor for a video file on a camera roll
 * @details The camera roll is a directory on the device where the camera
 *          application saves files. The camera service manages unique filenames
 *          on behalf of the user. Use this function to close the file
 *          descriptor that was returned by calling the @c
 *          camera_roll_open_video() function on the camera roll.
 *
 * @param fd The file descriptor to the open video file on the camera roll.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         @c #CAMERA_EINVAL if the @c size is not allocated, @c buf is invalid,
 *         or the frame type does not exist.
 */
camera_error_t
camera_roll_close_video(int fd);


/**
 * @brief Determines how much space (in bytes) is available to save a photo
 *        to the camera roll
 * @details The @c size argument is updated with the amount of space in
 *          bytes.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param size A pointer that is updated with the number of bytes available
 *             for saving the photo.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_available_photo(camera_handle_t handle,
                            long long *size);


/**
 * @brief Determines how much space (in btyes) is available to save video
 *        files to the camera roll
 * @details The @c size argument is updated with the amount of space in
 *          bytes.
 *
 * @param  handle The handle to the camera.
 * @param  size A pointer that is updated with the number of bytes available
 *              for saving the video.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_available_video(camera_handle_t handle,
                            long long *size);


/**
 * @brief Inform the video encoder to generate a keyframe on demand when
 *        encoding video
 * @details Only call this function when video encoding is in progress.
 *          Typically, you would request a new keyframe when an error occurs
 *          while recording video, such as a network or system error. The new
 *          keyframe allows you to recover from the error as quickly as
 *          possible. Only use this function when video encoding is occurring.
 *          For instance, when the @c camera_start_video has been called
 *          successfully.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_force_video_keyframe(camera_handle_t handle);


/**
 * @brief Retrieve the rotation angles supported by the viewfinder
 *        in photo mode
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, the value of @c non-square should
 *          be set to @c false.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or @c
 *          rotations argument set to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument. You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frametype.
 * @param numasked The requested number rotations to retrieve from the camera.
 *                 If you provide a number larger than the maximum number of
 *                 rotations available on the camera, only the supported
 *                 rotations are returned.
 * @param numsupported A pointer to the number of rotations that are returned.
 *                     If the value of @c numasked is larger than the number
 *                     of rotations available on the camera, this is updated
 *                     to reflect the number rotations supported by the camera.
 * @param rotations A pointer to an @c uint32_t array. The array is updated with
 *                  the rotations supported by the camera. Ensure that you
 *                  create an array with the same number of elements as
 *                  indicated by the @c numasked argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of images that are not a square angle (or
 *                   multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_vf_rotations(camera_handle_t handle,
                              camera_frametype_t frametype,
                              int numasked,
                              int *numsupported,
                              uint32_t *rotations,
                              bool *nonsquare);


/**
 * @brief Retrieve rotation angles supported by the viewfinder in video mode
 *
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, the value of @c non-square
 *          should be set to @c false.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument. You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_videovf_property() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frametype.
 * @param numasked The requested number rotations to retrieve from the camera.
 *                 If you provide a number larger than the maximum number of
 *                 rotations available on the camera, only the supported
 *                 rotations are returned.
 * @param numsupported A pointer to the number of rotations that are returned.
 *                     If the value of @c numasked is larger than the number
 *                     of rotations available on the camera, this is updated
 *                     to reflect the number rotations supported by the camera.
 * @param rotations A pointer to an @c uint32_t array. The array is updated with
 *                  the viewfinder rotations supported by the camera.
 *                  Ensure that you create an array with the same number of
 *                  elements as indicated by the @c numasked argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of images that are not a square angle (or
 *                   multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_vf_rotations(camera_handle_t handle,
                              camera_frametype_t frametype,
                              int numasked,
                              int *numsupported,
                              uint32_t *rotations,
                              bool *nonsquare);


/**
 * @brief Retrieve the rotation angles supported for pictures by the camera
 *
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, the value of @c non-square should
 *          be set to @c false.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or @c
 *          rotations argument set to NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_photo_property() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frametype.
 * @param burst Whether the rotations should be valid for burst capture
 * @param numasked The requested number rotations to retrieve from the camera.
 *                 If you provide a number larger than the maximum number of
 *                 rotations available on the camera, only the supported
 *                 rotations are returned.
 * @param numsupported A pointer to the number of rotations that are returned.
 *                     If the value of @c numasked is larger than the number
 *                     of rotations available on the camera, this is updated
 *                     to reflect the number rotations supported by the camera.
 * @param rotations A pointer a @c uint32_t array. The array is updated with
 *                  the photo rotations supported by the camera. Ensure that
 *                  you create an array with the same number of elements as
 *                  indicated by the @c numasked argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of images that are not a square angle (or
 *                   multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_rotations(camera_handle_t handle,
                           camera_frametype_t frametype,
                           bool burst,
                           int numasked,
                           int *numsupported,
                           uint32_t *rotations,
                           bool *nonsquare);


/**
 * @brief Retrieve the configurable rotation angles supported for the encoded
 *        video produced by the camera
 * @details Typical rotations are multiples of 90 degrees (called square
 *          rotations), such as 0, 90, 180, and 270. For cameras that
 *          support only square rotations, the value of @c non-square should be
 *          set to @c false.
 *
 *          Ensure that the @c rotations argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          rotations argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_ROTATION property using the @c
 *          camera_set_video_property() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frame type to query supported rotations for. Using
 *                  @c #CAMERA_FRAMETYPE_UNSPECIFIED will return the supported
 *                  rotations for the currently configured frametype.
 * @param numasked The requested number rotations to retrieve from the camera.
 *                 If you provide a number larger than the maximum number of
 *                 rotations available on the camera, only the supported
 *                 rotations are returned.
 * @param numsupported A pointer to the number of rotations that are returned.
 *                     If the value of @c numasked is larger than the number
 *                     of rotations available on the camera, this is updated
 *                     to reflect the number rotations supported by the camera.
 * @param rotations A pointer an @c uint32_t array. The array is updated with the
 *                  video rotations supported by the camera. Ensure that you
 *                  create an array with the same number of elements as
 *                  indicated by the @c numasked argument.
 * @param nonsquare  The value updated to reflect whether the camera supports
 *                   rotation of images that are not a square angle (or
 *                   multiples of 90 degrees).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_rotations(camera_handle_t handle,
                           camera_frametype_t frametype,
                           int numasked,
                           int *numsupported,
                           uint32_t *rotations,
                           bool *nonsquare);


/**
 * @brief Instruct the camera of the current device orientation
 *
 * @details You can specify values such as 0, 90, 180 or 270 degrees, where 0
 *          degrees is the default orientation of the device. It is the
 *          responsibility of an application to update the camera when
 *          the device orientation changes.
 *
 *          Use this function to let the camera on the system know how the
 *          user is holding the device. This allows the camera to adjust
 *          internal settings, such as exposure weighting, face detection, or
 *          other orientation-dependent features to match the orientation of the
 *          device.  If the @c #CAMERA_IMGPROP_METAORIENTATIONHINT property
 *          is enabled for photo output, then the EXIF orientation hint
 *          will be computed using a combination of the orientation set using
 *          this function as well as the rotation angle indicated by
 *          @c #CAMERA_IMGPROP_ROTATION.
 *
 *          This function has no effect on the output image rotations.
 *          It is simply used to inform the camera hardware that the
 *          orientation of the scene has changed in order to optimize
 *          internal algorithms, such as metering and face detection.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param val The orientation value, such as 0, 90, 180, or 270. 0
 *            represents the default orientation (landscape or portrait), 90
 *            represents rotated to the right, and 180 degrees represents
 *            upside down based on the marking on the device.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_device_orientation(camera_handle_t handle,
                              uint32_t val);


/**
 * @brief Configure the threshold of recording time left on the
 *        device before a warning is issued
 * @details The device has a recording capacity measured in bytes, which can
 *          also be expressed as a number of seconds depending on the encoding
 *          bit-rate. The recording capacity is indicated as seconds of
 *          recording time, which is a reflection of the amount of time left to
 *          record the video. While encoding, there is a continual estimation
 *          of the how many seconds of recording time remains before the storage
 *          device is full.
 *
 *          The camera service invokes the @c status_callback with status
 *          set to #CAMERA_STATUS_FILESIZE_WARNING whenever the amount of
 *          time left to record video is less than the value set in the @c
 *          seconds_remaining argument. The @c status_callback is the callback
 *          function set when you call the @c camera_start_photo_viewfinder() or
 *          @c camera_start_video_viewfinder() functions.
 *
 *          @e Note: The time remaining that is calculated is an estimate based
 *          on the encoder's past performance and is subject to jitter. For this
 *          reason, the calculated time remaining may not be perfectly accurate.
 *
 *          Typically, an application would set this to five minutes (or 3000
 *          seconds). Once that threshold is crossed, an application would
 *          indicate a low-space warning. You can decide to adjust the threshold
 *          lower to receive additional warnings as the recording time
 *          approaches 0. For example, you could move the threshold to one
 *          minute (60 seconds) for the next warning.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param seconds_remaining The desired threshold (in seconds) before the
 *                          status call function is called when the amount of
 *                          time is less than the value specified by
 *                          this argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_video_filesize_warning(camera_handle_t handle,
                                  uint16_t seconds_remaining);


/**
 * @brief Retrieve the photo frame types available on the camera
 * @details Use this function to retrieve the photo frame types supported
 *          by the current camera. The returned formats can be applied to
 *          @c #CAMERA_IMGPROP_FORMAT via the @c camera_set_photo_property()
 *          function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of photo frame types to return in the @c
 *                 types array. You can specify a value of 0 to determine the
 *                 number of supported photo frame types available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of photo frame types supported by the camera.
 * @param types   A pointer to a @c ::camera_frametype_t array. The array is
 *                updated with the photo frame types supported by the camera.
 *                Ensure that you allocate an array with the same number of
 *                elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_frame_types(camera_handle_t handle,
                             int numasked,
                             int *numsupported,
                             camera_frametype_t *types);

/**
 * @brief Retrieve the photo viewfinder frame types available on the camera
 * @details Use this function to retrieve the photo viewfinder frame
 *          types supported by the current camera.
 *
 *          The returned formats can be applied to @c #CAMERA_IMGPROP_FORMAT
 *          via the @c camera_set_photovf_property() function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of photo viewfinder frame types to
 *                 return in the @c types array. You can specify a value of
 *                 0 to determine the number of supported photo viewfinder
 *                 frame types available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of photo viewfinder frame types supported by the
 *                     camera.
 * @param types   A pointer to a @c #camera_frametype_t array. The array is
 *                updated with the photo viewfinder frame types supported
 *                on the camera. Ensure that you allocate an array with the
 *                same number of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photovf_frame_types(camera_handle_t handle,
                               int numasked,
                               int *numsupported,
                               camera_frametype_t *types);

/**
 * @brief Retrieve the video viewfinder frame types available on the camera
 * @details Use this function to retrieve the video viewfinder frame types
 *          supported by the current camera.
 *
 *          The returned formats can be applied to @c #CAMERA_IMGPROP_FORMAT
 *           via the @c camera_set_videovf_property() function.
 *
 *          Ensure that the @c types argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          types argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of video viewfinder frame types to
 *                 return in the @c types array. You can specify a value of
 *                 0 to determine the number of supported video viewfinder
 *                 frame types available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of video viewfinder frame types supported by the
 *                     camera.
 * @param types A pointer to a @c #camera_frametype_t array. The array is
 *              updated with the video viewfinder frame types supported by the.
 *              camera. Ensure that you allocate an array with the same number
 *              of elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_videovf_frame_types(camera_handle_t handle,
                               int numasked,
                               int *numsupported,
                               camera_frametype_t *types);

/**
 * @brief Configure the exposure mode on the camera
 * @details You can use the value of the @c #camera_exposuremode_t to set the
 *          exposure mode on the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The exposure mode to use.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_exposure_mode(camera_handle_t handle,
                         camera_exposuremode_t mode);


/**
 * @brief Retrieve the exposure mode from the camera
 * @details The exposure mode of the camera is returned in the @c mode
 *          argument that you pass to this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer that is updated with the current exposure mode
 *             of the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_exposure_mode(camera_handle_t handle,
                         camera_exposuremode_t *mode);


/**
 * @brief Retrieve the exposure modes that are available on the camera
 * @details Use this function to retrieve the exposure modes that
 *          are available on the camera.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of exposure modes to return in the
 *                 @c modes array. You can specify a value of 0 to determine
 *                 the number of supported exposure modes available on the
 *                 camera.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of exposure modes supported by the camera.
 * @param modes   A pointer to a @c ::camera_exposuremode_t array. The array is
 *                updated with the exposure modes supported by the camera.
 *                Ensure that you allocate an array with the same number of
 *                elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_exposure_modes(camera_handle_t handle,
                          int numasked,
                          int *numsupported,
                          camera_exposuremode_t *modes);


/**
 * @brief Configure the white balance mode on the camera
 * @details Use the value of the @c camera_whitebalancemode_t to set the
 *          white balance mode on the camera.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The white balance mode to use.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_whitebalance_mode(camera_handle_t handle,
                             camera_whitebalancemode_t mode);


/**
 * @brief Retrieve the white balance mode from the camera
 * @details The white balance mode of the camera is returned in from the @c
 *          mode argument that you pass to this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer that is updated with the current white balance
 *             mode of the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_whitebalance_mode(camera_handle_t handle,
                             camera_whitebalancemode_t *mode);


/**
 * @brief Retrieve the white balance modes that are available on the camera
 * @details Use this function to retrieve the white balance modes
 *          that are available on the camera.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or
 *          setting the @c modes argument to @c NULL. When the function is
 *          invoked in @e presizing mode, the maximum array size required is
 *          returned in @c numsupported argument. You can then allocate
 *          an array of the appropriate size and invoke the function again with
 *          @c numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of white balance modes to return in
 *                 the @c modes array. You can specify a value of 0 to
 *                 determine the number  of supported white balance modes
 *                 available on the camera.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of white balance modes supported by the
 *                     camera.
 * @param modes A pointer to a @c #camera_whitebalancemode_t array. The array
 *              is updated with the white balance modes supported by the camera.
 *              Ensure that you allocate an array with the same number of
 *              elements as the @c numasked argument.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_whitebalance_modes(camera_handle_t handle,
                              int numasked,
                              int *numsupported,
                              camera_whitebalancemode_t *modes);


/**
 * @brief Change the manual white balance color temperature
 * @details Use this function to set the white balance color
 *          temperature. The white balance alters the color for the image.
 *          The value that you set using this function is only applied when the
 *          white balance mode has been set to manual white balance using the
 *          @c camera_set_whitebalance_mode() function with the @c
 *          #CAMERA_WHITEBALANCEMODE_MANUAL property.
 *
 *          For more information regarding when these manual settings take
 *          effect, see @ref camapi_manual_settings and
 *          @c #camera_exposuremode_t.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param value The manual white balance color temperature (in Kelvin).
 *              Use the @c camera_get_supported_manual_white_balance_values()
 *              function to determine the white balance color temperature values
 *              that can be set.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_white_balance(camera_handle_t handle,
                                unsigned whitebalancevalue);

/**
 * @brief Retrieve the manual white balance color temperature
 * @details Use this function to retrieve the current manual white balance
 *          color temperature. If no white balance value was set, a default
 *          white balance value is returned.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param whitebalancevalue A pointer to an integer value that will be updated
 *                          with the manual white balance color temperature
 *                          value (in Kelvin).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_white_balance(camera_handle_t handle,
                                unsigned *whitebalancevalue);


/**
 * @brief Retrieve the supported manual white balance color temperature values
 *
 * @details Use this function to retrieve the set of supported manual white
 *          balance color temperature values.
 *
 *          Ensure that the @c whitebalancevalues argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          whitebalancevalues argument to @c NULL. When you invoke this
 *          function in @e presizing mode, the maximum array size that is
 *          required is returned in the @c numsupported argument. Then,
 *          you can allocate an array of the appropriate size and invoke
 *          this function again with @c numasked set to the value from the
 *          @c numsupported argument that was returned from the previous call to
 *          this function.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_white_balance() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of white balance color temperature values
 *                 to return in the @c whitebalancevalues array. You can specify
 *                 a value of 0 to determine the number of supported white
 *                 balance color temperature values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported white balance color temperature
 *                     values.
 * @param whitebalancevalues A pointer to an @c int array. The array is updated
 *                           with the manual white balance color temperature
 *                           values supported. Ensure that you allocate an array
 *                           with the same number of elements as the @c numasked
 *                           argument. If the @c maxmin argument returns @c
 *                           true, then the first value returned in the @c
 *                           whitebalancevalues array is the maximum supported
 *                           white balance value, and the second value returned
 *                           is the minimum supported color temperature.
 * @param maxmin A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values
 *               only describe the discrete white balance colour temperature
 *               values supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_white_balance_values(camera_handle_t handle,
                                                 unsigned numasked,
                                                 unsigned *numsupported,
                                                 unsigned *whitebalancevalues,
                                                 bool *maxmin);


/**
 * @brief Change the manual ISO value on the camera
 * @details Use this function to set the manual ISO value. The value
 *          that you set using this function is only applied when the exposure
 *          mode has been set to allow manual ISO settings. You can use the
 *          @c camera_get_supported_manual_iso_values() function to determine
 *          the range of valid ISO values that you can use.
 *
 *          For more information regarding when these manual settings take
 *          effect, see @ref camapi_manual_settings and
 *          @c #camera_exposuremode_t.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param isovalue The ISO value to set on the camera.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_iso(camera_handle_t handle,
                      unsigned isovalue);


/**
 * @brief Retrieve the current manual ISO value
 * @details Use this function to retrieve the current manual ISO value.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param isovalue A pointer to an integer that is updated with the
 *                 ISO value when the function returns.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_iso(camera_handle_t handle,
                      unsigned *isovalue);


/**
 * @brief Retrieve the supported manual ISO values that are available for
 *        the camera
 * @details Use this function to retrieve the set of supported manual ISO
 *          values.
 *
 *          When you call this function, ensure that the @c isovalues argument
 *          points to an array which has at least the same number of elements
 *          allocated as specified in the @c numasked argument. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          isovalues argument to @c NULL. When the function is invoked in
 *          @e presizing mode, the maximum array size that is required is
 *          returned in @c numsupported argument. You can then allocate an array
 *          of the appropriate size and invoke the function again with @c
 *          numasked argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_iso() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of manual ISO values to return in the
 *                 @c isovalues array. You can specify a value of 0 to determine
 *                 the number of supported manual ISO values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported manual ISO values.
 * @param isovalues  A pointer to an array that will be updated
 *                   with the manual ISO values that are supported. Ensure that
 *                   you allocate the array with at least @c numasked elements.
 *                   If the @c maxmin argument returns @c true, then the first
 *                   value returned in the @c isovalues array is the maximum
 *                   supported manual ISO value, and the second value that is
 *                   returned is the minimum supported manual ISO value.
 * @param maxmin A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values
 *               only describes the discrete manual ISO values supported.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_iso_values(camera_handle_t handle,
                                       unsigned numasked,
                                       unsigned *numsupported,
                                       unsigned *isovalues,
                                       bool *maxmin);


/**
 * @brief Change the manual shutter speed
 * @details Use this function to set the manual shutter speed.
 *          The value that you set using this function is only applied when
 *          the setting is set to allow manual shutter speed. You can use the
 *          @c camera_get_supported_manual_shutter_speeds() function to
 *          determine the range of valid shutter speeds values that you can use.
 *
 *          For more information regarding when the value takes
 *          effect, see @ref camapi_manual_settings.
 *.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutterspeed The manual shutter speed (in seconds). Use the @c
 *                     camera_get_supported_manual_shutter_speeds() function
 *                     to determine what manual shutter speeds you can set.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_shutter_speed(camera_handle_t handle,
                                double shutterspeed);

/**
 * @brief Retrieve the current manual shutter speed
 * @details Use this function to retrieve the currently set manual shutter speed.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param shutterspeed A pointer to a double that will be updated with the
 *                     current manual shutter speed (in seconds).
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_shutter_speed(camera_handle_t handle,
                                double *shutterspeed);

/**
 * @brief Retrieve the supported manual shutter speeds
 * @details Use this function to retrieve the supported manual shutter
 *          speeds that you can use.
 *
 *          Ensure that the @c shutterspeeds argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c shutterspeeds argument to @c NULL. When the
 *          function is invoked in @e presizing mode, the maximum array size that
 *          is required is returned in @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with @c numasked argument set to the value returned previously
 *          in the @c numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_shutter_speed() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of manaul shutter speeds to return in
 *                 the @c shutterspeeds array. You can specify a value of 0 to
 *                 determine the number of supported manual shutter speeds
 *                 values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported shutter speeds.
 * @param shutterspeeds  A pointer to a double array (in seconds). The array is
 *                       updated with the manual shutter speeds supported.
 *                       Ensure that you allocate an array at least @c numasked
 *                       elements. If the @c maxmin argument returns @c true,
 *                       then the first value returned in the @c shutterspeeds
 *                       array is the maximum supported shutter speed, and the
 *                       second value returned is the minimum supported shutter
 *                       speed.
 * @param maxmin A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describes the discrete shutter speeds that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_shutter_speeds(camera_handle_t handle,
                                           unsigned numasked,
                                           unsigned *numsupported,
                                           double *shutterspeeds,
                                           bool *maxmin);


/**
 * @brief Change the manual aperture value (f-number)
 * @details Use this function to set the manual aperture value.
 *
 *          Setting a small f-number results in a reduced depth of field.
 *          Setting a large f-number results in an increased depth of field.
 *
 *          For more information regarding when manual settings take
 *          effect, see @ref camapi_manual_settings and
 *          @c #camera_exposuremode_t.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param aperturevalue The aperture value. See @c
 *                      camera_get_supported_manual_aperture_values() function
 *                      for how to determine what aperture values can be set.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_manual_aperture(camera_handle_t handle,
                           double aperturevalue);


/**
 * @brief Retrieve the manual aperture value (f-number)
 * @details Use this function to retrieve the current manual aperture
 *          value (f-number).
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param aperturevalue A pointer to a @c double that will be updated with the
 *                      current manual aperture value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_manual_aperture(camera_handle_t handle,
                           double *aperturevalue);


/**
 * @brief Retrieve the supported manual aperture values (f-numbers)
 * @details Use this function to retrieve the set of supported manual
 *          aperture values (f-numbers).
 *
 *          Ensure that the @c aperturevalues  argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c aperturevalues argument to @c NULL. When the
 *          function is invoked in @e presizing mode, the maximum array size that
 *          is required is returned in @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with @c numasked argument set to the value returned previously
 *          in the @c numsupported argument.
 *
 *          The values that you retrieve using this function can be set using
 *          the @c camera_set_manual_aperture() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of manual aperture values to return in
 *                 the @c aperturevalues array. You can specify a value of 0 to
 *                 determine the number of supported manual aperture values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported manual aperture values.
 * @param aperturevalues A pointer to a @c double array. The array is updated
 *                       with the manual aperture values supported. Ensure that
 *                       you allocate an array with the same number of elements
 *                       as the @c numasked argument. If the @c maxmin argument
 *                       returns @c true, then the first value returned in the
 *                       @c aperturevalues array is the maximum supported
 *                       manual aperture value, and the second value returned
 *                       is the minimum supported manual aperture value.
 * @param maxmin A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describes the discrete aperture values that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_manual_aperture_values(camera_handle_t handle,
                                            unsigned numasked,
                                            unsigned *numsupported,
                                            double *aperturevalues,
                                            bool *maxmin);


/**
 * @brief Set the EV offset (exposure compensation)
 * @details Use this function to set the EV offset to make pictures brighter
 *          or darker. The value set in this function @b does @b not take effect
 *          if the exposure mode (@c #camera_exposuremode_t) is set to one of
 *          these values:
 *            - @c #CAMERA_EXPOSUREMODE_MANUAL
 *            - @c #CAMERA_EXPOSUREMODE_OFF
 *
 *          You can call the @c camera_get_supported_ev_offsets() to determine
 *          the available EV offset values that can be used.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param offset The EV offset to set. Positive values, such as +1 indicates to
 *               make the picture brighter while negative values, such as -1
 *               make the pictures darker.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_ev_offset(camera_handle_t handle,
                     double offset);


/**
 * @brief Retrieve the current EV offset
 * @details Use this function to retrieve the current EV offset. The
 *          current EV offset is disabled when the exposure mode is one of:
 *            - @c CAMERA_EXPOSUREMODE_MANUAL
 *            - @c CAMERA_EXPOSUREMODE_OFF
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param offset A pointer to a @c double that will be updated with the EV offset.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_ev_offset(camera_handle_t handle,
                     double * offset);


/**
 * @brief Retrieve the supported EV offset values that are supported
 * @details Use this function to retrieve the EV offset values that are
 *          available on the camera.
 *
 *          Ensure that the @c offsets argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument
 *          to 0 or the @c offsets argument to @c NULL. When the
 *          function is invoked in @e presizing mode, the maximum array size that
 *          is required is returned in @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with @c numasked argument set to the value returned previously
 *          in the @c numsupported argument.
 *
 *          You can call the @c camera_set_ev_offset() function to determine
 *          the EV offset values that are set.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of EV offset values to return in the
 *                 @c offsets array. You can specify a value of 0 to
 *                 determine the number of supported EV offsets values.
 * @param numsupported A pointer to an integer that will be updated with the
 *                     number of supported EV offset values.
 * @param offsets A pointer to a @c double array. The array is updated
 *                with the EV offset values supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument.  If the @c maxmin argument returns true,
 *                then the first value returned in the @c offsets array is the
 *                maximum supported EV offset, and the second value returned is
 *                the minimum supported EV offset.
 * @param maxmin  A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values describes
 *               the discrete EV offset values that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_ev_offsets(camera_handle_t handle,
                                unsigned numasked,
                                unsigned *numsupported,
                                double *offsets,
                                bool *maxmin);


/**
 * @brief Retrieve the supported photo viewfinder frame rates
 * @details Use this function to retrieve the set of supported photo
 *          viewfinder frame rates.
 *
 *          Ensure that the @c rates argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c rates argument to @c NULL. When the function is
 *          invoked in @e presizing mode, the maximum array size that is required
 *          is returned in @c numsupported argument. You can then allocate an
 *          array of the appropriate size and invoke the function again with @c
 *          numasked argument set to the value returned previously
 *          in the @c numsupported argument.
 *
 *          You can call the @c camera_set_photovf_property() function to set
 *          the @c #CAMERA_IMGPROP_FRAMERATE property to one of the values
 *          retrieved using this function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param burst Whether the frame rates should be valid for burst viewfinder
 *              mode. To enable burst viewfinder mode, call the
 *              @c camera_set_photovf_property() function and set the
 *              @c CAMERA_IMGPROP_BURSTMODE property to 1.
 * @param numasked The requested number of frame rates to return in the @c rates
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported frame rates.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of supported frame rates.
 * @param rates   A pointer to a double array. The array is updated
 *                with the photo viewfinder frame rates supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument.  If the @c maxmin flag returns @c true,
 *                then the first value returned in the rates array is the
 *                maximum supported frame rate, and the second value returned is
 *                the minimum supported frame rate.
 * @param maxmin A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only
 *               describe the discrete frame rates that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_vf_framerates(camera_handle_t handle,
                               bool burst,
                               int numasked,
                               int *numsupported,
                               double *rates,
                               bool *maxmin);


/**
 * @brief Retrieve the supported photo output frame rates
 * @details Use this function to retrieve the set of supported photo
 *          output frame rates.
 *
 *          When calling this function, ensure that the @c rates argument
 *          points to an array which has at least the number of elements
 *          allocated as specified in the @c numasked argument. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or @c
 *          rates argument set to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 *          The values that you retrieve using this function can be written to
 *          @c #CAMERA_IMGPROP_FRAMERATE property using the @c
 *          camera_set_photo_property() function.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param frametype The frametype for which supported framerates are being requested.
 * @param numasked The requested number of frame rates to return in the @c rates
 *                 array. You can specify a value of zero to determine the
 *                 number of supported frame rates.
 * @param numsupported The pointer to an integer that is populated with the
 *                     number of supported frame rates.
 * @param rates   A pointer to a double array. The array is updated
 *                with the photo output frame rates supported. Ensure that
 *                you allocate an array with the same number of elements as the
 *                @c numasked argument.  If the @c maxmin flag returns @c true,
 *                then the first value returned in the rates array is the
 *                maximum supported frame rate, and the second value returned is
 *                the minimum supported frame rate.
 * @param maxmin  A pointer to a bool value which is set to @c true if the
 *                rates returned should be interpreted as a continuous range of
 *                framerates between a maximum and minimum, or set to @c false
 *                if the rates returned describe only the discrete frame rates
 *                supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_photo_output_framerates(camera_handle_t handle,
                                   camera_frametype_t frametype,
                                   int numasked,
                                   int *numsupported,
                                   double *rates,
                                   bool *maxmin);


/**
 * @brief Retrieve the supported video viewfinder frame rates
 * @details Use this function to retrieve the set of supported video
 *          viewfinder frame rates.
 *
 *          Ensure that the @c rates argument points to an array
 *          which has at least @c numasked elements allocated. To
 *          determine an appropriate size for this array, you can invoke this
 *          function in @e presizing mode by setting the @c numasked argument to
 *          to 0 or the @c rates argument to @c NULL. When the
 *          function is invoked in @e presizing mode, the maximum array size that
 *          is required is returned in @c numsupported argument. You can then
 *          allocate an array of the appropriate size and invoke the function
 *          again with @c numasked argument set to the value returned previously
 *          in the @c numsupported argument.
 *
 *          You can call the @c camera_set_videovf_property() function to set
 *          the @c #CAMERA_IMGPROP_FRAMERATE property to one of the values
 *          retrieved using this function
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of frame rates to return in the @c rates
 *                 array. You can specify a value of 0 to determine the
 *                 number of supported frame rates.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of supported frame rates.
 * @param rates   A pointer to a @c double array. The array is updated
 *                with the photo viewfinder frame rates that are supported.
 *                You must ensure that you allocate an array with the same
 *                number of elements as the value from the @c numasked argument.
 *                If the @c maxmin argument returns @c true, then the first
 *                value returned in the rates array is the maximum supported
 *                frame rate, and the second value returned is the minimum
 *                supported frame rate.
 * @param maxmin  A pointer to a @c boolean value which will be set to @c true
 *               if the values returned should be interpreted as a maximum and
 *               a minimum value, or set to @c false if the values only describe
 *               the discrete frame rates that are supported.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_vf_framerates(camera_handle_t handle,
                               int numasked,
                               int *numsupported,
                               double *rates,
                               bool *maxmin);

/**
 * @brief  Retrieve the native orientation of the camera relative to the default
 *         orientation of the device
 * @details The native orientation describes the installed clockwise angular
 *          offset of the camera sensor with respect to the screen when the
 *          device is held upright. When a camera is installed with a non-zero
 *          orientation offset relative to the rest of the device, the image
 *          data output by the camera must be rotated for correct presentation
 *          on the screen.
 *
 *          This concept is similar to taking a photo on a film which has
 *          been reoriented to take a portrait (tall) rather than a landscape
 *          (wide) photograph. The film is still landscape, and when printed,
 *          these photographs are printed in landscape (wide) format. It is
 *          the responsibility of the viewer to hold the finished photographic
 *          print in the correct orientation in order to recreate the captured
 *          scene. The value returned by this function indicates how far
 *          clockwise the camera hardware has been oriented from the viewer, and
 *          therefore indicates how far the user must rotate the output photo
 *          buffer clock-wise in order for it to appear upright on-screen.
 *
 * @b Note: Use this function only when the user needs to know
 *          details about how the camera is physically installed in the device.
 *          Since the camera hardware is able to render to rotated buffers on
 *          behalf of the user on most devices, it is sufficient to use the @c
 *          camera_get_photo_vf_rotations(), @c camera_get_video_vf_rotations(),
 *          and @c camera_get_photo_rotations() to cover common use cases.
 *
 *          It is important to understand that even though the camera hardware
 *          may be physically installed with a non-zero orientation, this API
 *          internally compensates for the native orientation offset when
 *          communicating rotation angles between the user and the hardware.
 *
 * The following are examples of how this function works in relation to
 * other functions available in this API:
 *  - Scenario 1: The @c camera_get_native_orientation() function reports an
 *                orientation of 90 degrees, such as for a smartphone.
 *                The @c camera_get_photo_vf_rotations() function reports
 *                that 0, 90, 180, 270 are supported capture rotation angles.
 *                The user configures the photo viewfinder using @c
 *                camera_set_photovf_property() and specifies a value of 0 for
 *                @c #CAMERA_IMGPROP_ROTATION to receive upright image buffers.
 *                In this scenario, the API will internally translate 0 to a
 *                physical rotation which is relative to the camera by adding
 *                the orientation (90) and yielding 90. This capability ensures
 *                that the buffers output from The Camera API are presentable
 *                upright on-screen as-is.
 *
 *  - Scenario 2: The @c camera_get_native_orientation() reports an orientation
 *                of 90 degrees, such as for a smartphone.The @c
 *                camera_get_photo_vf_rotations() reports that 270 is the only
 *                supported capture rotation angle.  This could be the case on
 *                a device which does not support capture rotation. The user has
 *                no choice but to configure the photo viewfinder using a value
 *                of 270 for @c #CAMERA_IMGPROP_ROTATION property.
 *                The API will internally translate 270 to a physical rotation,
 *                which is relative to the camera by adding the orientation (90)
 *                and yielding 0. The buffer being rendered to is now understood
 *                to be 0-degrees offset relative to the camera. Note that this
 *                is consistent with the fact that this particular physical
 *                camera does not support capture rotation.  Since we know that
 *                this camera has a non-zero native orientation (90),we know
 *                that rendering this buffer to the screen will result in a
 *                sideways image.  The user must rotate this buffer by 90
 *                degrees (the native orientation) prior to being displayed on
 *                the screen.
 *
 * For more information about capture buffer rotation, see the @c
 * camera_get_photo_vf_rotations(), @c camera_get_video_rotations(), and @c
 * camera_get_photo_rotations() functions.
 *
 * @param handle The handle returned by a call to the @c camera_open() function
 * @param orientation A pointer to an @c uint32_t value that will be updated with
 *                    the native orientation expressed in degrees clockwise.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_native_orientation(camera_handle_t handle, uint32_t *orientation);

/**
 * @brief Enable the final image data event
 * @details Use this function to enable the image event. The image event is sent
 *          when the final image data is available. Call this function when
 *          configuring the Camera API for @e event mode instead of @e callback
 *          mode.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode.
 * @param key A pointer to a ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This is the sigevent that will be sent back to the user
 *              when the event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_image_event(camera_handle_t handle,
                          camera_eventmode_t eventmode,
                          camera_eventkey_t *key,
                          struct sigevent* event);

/**
 * @brief Enable the postview review event
 * @details Use this function to enable the postview event, which is sent
 *          when there is a preview-sized version of a captured still image.
 *          Call this function when configuring the Camera API for @e event mode
 *          instead of @e callback mode.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode.
 * @param key A pointer to a ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This is the sigevent that will be sent back to the user
 *              when the event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_postview_event(camera_handle_t handle,
                             camera_eventmode_t eventmode,
                             camera_eventkey_t *key,
                             struct sigevent* event);

/**
 * @brief Reserved for future use
 * @details Do not use. Enable the raw event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode.
 * @param key A pointer to a ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This is the sigevent that will be sent back to the user
 *              when the event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_raw_event(camera_handle_t handle,
                        camera_eventmode_t eventmode,
                        camera_eventkey_t *key,
                        struct sigevent* event);

/**
 * @brief Enable the shutter event
 * @details Use this function to enable the shutter event, which is signalled
 *          when the shutter activates for a photo capture. Call this function when
 *          configuring the Camera API for @e event mode instead of @e callback
 *          mode.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key A pointer to a ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This is the sigevent that will be sent back to the user
 *              when the event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_shutter_event(camera_handle_t handle,
                            camera_eventkey_t *key,
                            struct sigevent* event);

/**
 * @brief Enable the status event
 * @details Use this function to enable the status event, which is signalled
 *          when there is additional data to be reported, relevant to the current
 *          mode. Call this function when configuring the Camera API for @e
 *          event mode instead of @e callback mode
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key A pointer to a ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This is the sigevent that will be sent back to the user
 *              when the event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_status_event(camera_handle_t handle,
                           camera_eventkey_t *key,
                           struct sigevent* event);

/**
 * @brief Enable the video event
 * @details Use this function to enable the video event, which is signalled
 *          when the uncompressed video frame becomes available. Call this
 *          function when configuring the Camera API for @e event mode instead
 *          of @e callback mode.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode.
 * @param key A pointer to a ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This sigevent is sent back to the user when the
 *              event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_video_event(camera_handle_t handle,
                          camera_eventmode_t eventmode,
                          camera_eventkey_t *key,
                          struct sigevent* event);

/**
 * @brief Enable the viewfinder event
 * @details Use this function to enable the viewfinder event, which is signalled
 *          when a raw viewfinder buffer is available. The viewfinder is
 *          rendered to a screen window by the camera service. It is not
 *          required to provide display code unless custom output is required
 *          using some other mechanism. Call this function when configuring the
 *          Camera API to use @e event mode instead of @e callback mode.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param eventmode The event buffering mode.
 * @param key A pointer to a @c ::camera_eventkey_t value. This argument is
 *            required for subsequent function calls to identify the proper
 *            event.
 * @param event A pointer to a sigevent. The sigevent must be initialized by the
 *              caller. This sigevent will be sent back to the user when the
 *              event occurs.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_enable_viewfinder_event(camera_handle_t handle,
                               camera_eventmode_t eventmode,
                               camera_eventkey_t *key,
                               struct sigevent* event);

/**
 * @brief Disable the event specified by key
 * @details Use this function to disable an event that was previously enabled,
 *          when these events are not longer required.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to an enable event
 *            function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_disable_event(camera_handle_t handle,
                     camera_eventkey_t key);

/**
 * @brief Retrieve a video buffer from the camera service
 * @details Use this function to retrieve a buffer with video data. Only call
 *          this function after receiving a video event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
  *           camera_enable_video_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera service.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera service.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_video_buffers(camera_handle_t handle,
                         camera_eventkey_t key,
                         camera_buffer_t *inbuffer,
                         camera_buffer_t *outbuffer);

/**
 * @brief Retrieve a viewfinder buffer from the camera service.
 * @details Use this function to retrieve a buffer with viewfinder data. Only
 *          call this function after you receive a viewfinder event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_viewfinder_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t struct returned
 *                 by the camera service.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t struct returned
 *                  by the camera service.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_viewfinder_buffers(camera_handle_t handle,
                              camera_eventkey_t key,
                              camera_buffer_t *inbuffer,
                              camera_buffer_t *outbuffer);

/**
 * @brief Retrieve an image buffer from the camera service.
 * @details Use this function to retrieve a buffer with image data. Only
 *          call this function after you receive an image event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_image_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t structure
 *                 returned by the camera service.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t structure
 *                  returned by the camera service.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_image_buffers(camera_handle_t handle,
                         camera_eventkey_t key,
                         camera_buffer_t *inbuffer,
                         camera_buffer_t *outbuffer);

/**
 * @brief Retrieve a postview buffer from the camera service.
 * @details Use this function to retrieve a buffer with postview data. Only
 *          call this function after you receive a video event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_postview_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t structure
 *                 returned by the camera service.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t structure
 *                  returned by the camera service.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_postview_buffers(camera_handle_t handle,
                            camera_eventkey_t key,
                            camera_buffer_t *inbuffer,
                            camera_buffer_t *outbuffer);

/**
 * @internal
 * @brief Reserved for future use
 * @details Do not use. Retrieve a raw buffer from the camera service.
 *          Use this function to retrieve a buffer with raw data. Only
 *          call this function after you receive a raw event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param key The key value that was returned by a call to the @c
 *            camera_enable_raw_event() function.
 * @param inbuffer A pointer to the input @c ::camera_buffer_t structure
 *                 returned by the camera service.
 * @param outbuffer A pointer to the output @c ::camera_buffer_t structure
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_raw_buffers(camera_handle_t handle,
                       camera_eventkey_t key,
                       camera_buffer_t *inbuffer,
                       camera_buffer_t *outbuffer);

/**
 * @brief Retrieve the status details from a status event.
 * @details Use this function to parse device status details from the sigval
 *          returned from a status event.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param value The sigval received from the status event.
 * @param devstatus The returned device status details.
 * @param devstatusextra The returned extra device status details.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_status_details(camera_handle_t handle,
                          union sigval value,
                          camera_devstatus_t *devstatus,
                          uint16_t *devstatusextra);

/**
 * @brief Return a buffer to the camera service
 * @details Use this function to return a buffer back to the camera service.
 *          The @c buffer value you provide must be acquired from the camera
 *          service using one of the following functions:
 *          - @c camera_get_video_buffers()
 *          - @c camera_get_viewfinder_buffers()
 *          - @c camera_get_image_buffers()
 *          - @c camera_get_postview_buffers()
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param buffer A pointer to a buffer acquired by a call to one of the above
 *              get-buffer functions
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_return_buffer(camera_handle_t handle,
                     camera_buffer_t *buffer);

/**
 * @brief Configure reporting of viewfinder histogram data
 * @details Use this function to enable viewfinder histogram reporting if
 *          supported on the camera. To determine whether histogram data is
 *          supported, call the @c camera_can_feature() function with the @c
 *          #CAMERA_FEATURE_VFHISTOGRAM.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable Enable histogram data reporting. Set to @c True to enable,
 *               @c false otherwise.
 *
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_vf_histogram(camera_handle_t handle,
                        bool enable);

/**
 * @brief Configure viewfinder face-detection metadata reporting
 * @details Use this function to enable the reporting of viewfinder
 *          face-detection metadata if the feature is supported on the camera.
 *          You can call the @c camera_can_feature() function with the @c
 *          #CAMERA_FEATURE_VFFACEDETECT to determine if your camera supports
 *          face-detection.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable Set to @c true to enable viewfinder face-detection metadata
 *               reporting, @c false otherwise.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_vf_face_detect(camera_handle_t handle,
                             bool enable);


/**
 * @brief Configure face-detection metadata reporting for still images
 * @details Use this function to enable the reporting of still image
 *          face-detection metadata if the feature is supported on the camera.
 *          You can call the the @c camera_can_feature() function with
 *          the @c #CAMERA_FEATURE_FACEDETECT property to determine if your
 *          camera supports the face-detection feature.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param enable Set to @c true to enable reporting of face-detection metadata
 *               for still images, @c false otherwise.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_config_photo_face_detect(camera_handle_t handle,
                                bool enable);

/**
 * @brief Retrieve the flash power level
 * @details Use this function to get the available flash power level, as a
 *          percentage of the maximum. A non-zero level indicates that there
 *          is sufficient power available to fire the flash (see @c
 *          camera_config_flash()).
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param percent A pointer to the returned percentage value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_flash_level(camera_handle_t handle,
                       uint32_t *percent);

/**
 * @brief Retrieve the video light power level
 * @details Use this function to get the available video light power level,
 *          as a percentage of the maximum. A non-zero level indicates that
 *          there is sufficient power available to turn on the video light
 *          (see @c camera_config_videolight()).
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param percent A pointer to the percentage value.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_videolight_level(camera_handle_t handle,
                            uint32_t *percent);


/**
 * @brief Set or clear the geolocation data for photo metadata
 * @details Use this function to specify or remove geolocation metadata
 *          to your images.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param latitude The desired latitude in degrees.
 * @param longitude The desired longitude in degrees.
 * @param altitude The desired altitude in meters.
 * @param valid A flag that sets or clears the geolocation data. Set to @c true
 *             to set the data, set to @c false to clear the data.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_set_geolocation(camera_handle_t handle,
                       double latitude,
                       double longitude,
                       double altitude,
                       bool valid);


/**
 * @brief Set the camera roll path
 * @details The value you set for the @c pathname argument must a
 *          NULL-terminated string and must not be larger than the @c
 *          #CAMERA_ROLL_NAMELEN.
 *
 *          The camera roll is the directory where video files and image files
 *          are stored.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param pathname The string represent the path to the camera roll.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_set_path(camera_handle_t handle, char* pathname);


/**
 * @brief Retrieve the camera roll path
 * @details The camera roll is the directory where video files and image files
 *          are stored.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param pathname A buffer to receive the NULL-terminated string specifying the
 *                 path to the camera roll.
 * @param pathlen The size of the path name buffer, should be set to @c
 *                #CAMERA_ROLL_NAMELEN.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_roll_get_path(camera_handle_t handle, char* pathname, int pathlen);


/**
 * @brief Register with the resource management component to let the
 *        camera service know that your application is ready to process buffers
 * @details At any point in time, it is possible that the resources used by the
 *          the camera viewfinder are required by a higher priority application.
 *          When this situation occurs, the viewfinder is stopped by the camera
 *          service. If buffers are in use by your application when the
 *          viewfinder is stopped, this can cause your application to crash when
 *          buffer memory is unmapped. Your application can call the @c
 *          camera_register_resource() function to request that the camera
 *          service defer the unmapping of buffer memory.
 *
 *          Whenever resources are needed elsewhere by higher priority
 *          applications, your application will receive a @c
 *          #CAMERA_STATUS_RESOURCENOTAVAIL status event. When your application
 *          receives this status event, you must immediately cease processing
 *          all camera buffers and then call the @c camera_deregister_resource()
 *          function to let the camera service know that it can proceed to unmap
 *          allocated resources. A timeout is in place that limits the amount
 *          of time your application has before resources will be
 *          forcefully revoked. For this reason, it is recommended that you
 *          call @c camera_deregister_resource() function as soon as possible
 *          when your application receives the @c
 *          #CAMERA_STATUS_RESOURCENOTAVAIL status event.
 *
 *  @b Note: You can call the @c camera_register_resource() function more than
 *          once if you wish to perform cleanup on multiple threads, but
 *          you must call the @c camera_deregister_resource() function the same
 *          number of times when cleaning up.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_register_resource(camera_handle_t handle);


/**
 * @brief Deregister from the resource management component of the camera
 *        service
 * @details Use this function to signal to the camera service that your
 *          application is no longer processing buffers from the camera service.
 *          See @c camera_register_resource() for usage.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_deregister_resource(camera_handle_t handle);


/**
 * @brief Retrieve one or more physical properties of the camera
 * @details As part of the @c args argument, you can provide one or more
 *          property-value pairs using @c ::camera_physprop_t values as the name
 *          of the property and a pointer to the correct type for the value such
 *          as an @c int or @c double value.
 *
 *          @b Note: There is no type-checking performed by the compiler,
 *                   therefore, you must ensure that the value you provide
 *                   for each property matches the expected data type. Data type
 *                   mismatches can result in undefined behavior and may cause
 *                   your application to crash.
 *
 *          You can specify multiple property-value pairs by delimiting them
 *          with a comma as follows:
 * @code
 * property1, &value1, property2, &value2,...
 * @endcode
 *
 *         For example, you can get values in the following manner:
 * @code
 * camera_get_physical_property(camera_handle,
 *                              CAMERA_PHYSPROP_FOCALLENGTH, &focalLength,
 *                              CAMERA_PHYSPROP_HORIZONTALFOV, &horizFov);
 * @endcode
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param args... A series of comma-delimited property-value pairs where each
 *                value must be a pointer a variable of the expected type.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
#define camera_get_physical_property(handle, args...)\
        _camera_get_physical_property(handle, args, CAMERA_PHYSPROP_END)


/**
 * @internal
 * For internal use only. Use the @c camera_get_physical_property() function
 * instead which auto-terminates the ... varargs list.
 */
camera_error_t
_camera_get_physical_property(camera_handle_t handle,
                              ...);


/**
 * @brief Retrieve the low-light status
 * @details Use this function to determine if the camera considers the current
 *          conditions to be low in light.
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param lowlight A pointer to the low-light status.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_lowlight_status(camera_handle_t handle,
                           bool *lowlight);


/**
 * @brief Verify whether a given video codec is supported
 * @details Use this function to determine if a given video codec is supported
 *          on the device.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param codec The video codec to verify.
 * @return @c true when the specified video codec is supported by the device,
 *         otherwise a value of @c false.
 */
bool
camera_is_videocodec_supported(camera_handle_t handle,
                               camera_videocodec_t codec);

/**
 * The camera video viewfinder modes that are available.
 */
typedef enum {
    /**
     * Standard video viewfinder mode.
     */
    CAMERA_VIDEO_VF_MODE_VIDEO,

    /**
     * Video snapshot mode.
     */
    CAMERA_VIDEO_VF_MODE_VIDEO_SNAPSHOT,

    /**
     * The number of video viewfinder modes.
     */
    CAMERA_VIDEO_VF_NUMMODES,
} camera_video_vf_modes_t;

/**
 * @brief Change the video viewfinder mode
 * @details Use this function to change the video viewfinder mode.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode The video viewfinder mode.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 *
 */
camera_error_t
camera_set_video_vf_mode(camera_handle_t handle, camera_video_vf_modes_t mode);

/**
 * @brief Retrieve the current video viewfinder mode
 * @details Use this function to determine the current video viewfinder mode.
 *          The @c handle indicates the camera of which to determine videofinder
 *          mode.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param mode A pointer that will be updated with the current video viewfinder
 *             mode.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 *
 */
camera_error_t
camera_get_video_vf_mode(camera_handle_t handle, camera_video_vf_modes_t *mode);

/**
 * @brief Retrieve the supported video viewfinder modes
 * @details Use this function to query supported video viewfinder modes.
 *
 *          Ensure that the @c modes argument points to an array
 *          which has at least @c numasked elements allocated. To determine an
 *          appropriate size for this array, you can invoke this function in @e
 *          presizing mode by setting the @c numasked argument to 0 or the @c
 *          modes argument to @c NULL. When the function is invoked in
 *          this @e presizing mode, the maximum array size required is returned
 *          in @c numsupported argument.  You can then allocate an array of the
 *          appropriate size and invoke the function again with @c numasked
 *          argument set to the value returned previously in the @c
 *          numsupported argument.
 *
 * @param handle The handle returned by a call to the @c camera_open() function.
 * @param numasked The requested number of scene modes to return in the @c modes
 *                 array.
 * @param numsupported The pointer to an integer that will be updated with the
 *                     number of video viewfinder modes supported by the camera.
 * @param modes   A pointer to a @c ::camera_video_vf_modes_t array. The array
 *                 is updated with the scene modes supported by the camera.
 * @return @c #CAMERA_EOK when the function successfully completes, otherwise
 *         another @c ::camera_error_t value that provides the reason that the
 *         call failed.
 */
camera_error_t
camera_get_supported_video_vf_modes(camera_handle_t handle,
                                    unsigned int numasked,
                                    unsigned int *numsupported,
                                    camera_video_vf_modes_t *modes);

#ifdef __cplusplus
}
#endif
#endif   /* __CAMERA_API_H__ */

#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
