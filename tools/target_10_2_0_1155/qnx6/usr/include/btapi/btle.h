/*
 * $QNXLicenseC:
 * Copyright 2012, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software. Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

/**
 * @file btle.h
 *
 * @brief This file contains functions and structures for using the
 *        Bluetooth low energy functionality
 *
 *
 */

#ifndef _BTLE_H_
#define _BTLE_H_

#include <stdint.h>

/**
 * Bluetooth low energy API version.
 * For example, the value @c 0x00010000 translates to 0001.00.00 or v1.0.0.
 */
#define BT_LE_VERSION         0x00010000

/**
 * A value that represents all Bluetooth addresses. This value is useful when
 * you want to receive data from any Bluetooth-enabled devices.
 */
#define BT_LE_BDADDR_ANY  "00:00:00:00:00:00"

/**
 * A value used to run advertisements for an indefinite amount of time.
 */
#define BT_LE_TIME_INFINITY      0xFFFFFFFF

/**
 * The reason why the advertising completed.
 */
typedef enum {

    /**
     * Internal stack terminated advertisements.
     */
    BT_LE_ADVERT_REASON_INTERNAL_TERMINATED        = 0x00,

    /**
     * Advertisement timed interval elapsed.
     */
    BT_LE_ADVERT_REASON_INTERVAL_TIMEOUT           = 0x01,

    /**
     * Advertisements terminated due to an incoming or outgoing connection.
     */
    BT_LE_ADVERT_REASON_CONNECTION_TERMINATED      = 0x02,

    /**
     * Reserved for future use.
     */
    BT_LE_ADVERT_REASON_RESERVED                   = 0x03,

    /**
     * Advertisments terminated due to radio shutdown
     */
    BT_LE_ADVERT_REASON_RADIO_SHUTDOWN             = 0x04,

} bt_le_advert_complete_reason_t;

/**
 * Advertising scan type.
 */
typedef enum {

    /**
     * Passive advertisment scanning - no scan request packets will be sent.
     */
    BT_LE_ADVERT_SCAN_PASSIVE                       = 0x00,

    /**
     * Active advertisment scanning - scan request packets will be sent.
     */
    BT_LE_ADVERT_SCAN_ACTIVE                        = 0x01,

} bt_le_advert_scan_type_t;

/**
 * The callback prototype to indicate an incoming advertisement event has occurred.
 *
 * @param bdaddr The address of the Bluetooth-enabled device.
 * @param rssi The Received Signal Strength Indication (RSSI) for the
 *             advertisement.
 * @param data The data sent in the advertisement.
 * @param len The length of data sent.
 * @param userData Pointer to the user data defined when adding the listener.
 */
typedef void (*bt_le_advertisement_cb) (const char *bdaddr, int8_t rssi, const char *data, int len, void *userData);

/**
 * The callback prototype to indicate the advertisement interval has changed.
 *
 * @param intervalMin The current minimum advertisement interval. Time = N * 0.625 msec.
 * @param intervalMax The current maximum advertisement interval. Time = N * 0.625 msec.
 */
typedef void (*bt_le_advertisement_change_cb) (uint16_t intervalMin, uint16_t intervalMax);

/**
 * The callback prototype to indicate the advertisement has completed.
 *
 * @param reason The reason why the advertisements completed.
 */
typedef void (*bt_le_advertisement_complete_cb) (bt_le_advert_complete_reason_t reason);

/**
 * The structure that contains the control manager callback.
 */
typedef struct {
    /**
     * Callback function for received advertisement data.
     */
    bt_le_advertisement_cb advert;

    /**
     * Callback function to indicate a change in advertisement parameters.
     */
    bt_le_advertisement_change_cb changed;

    /**
     * Callback function to indicate advertisements have completed.
     */
    bt_le_advertisement_complete_cb complete;

} bt_le_callbacks_t;

/**
 * Structure for parameters that applications may request for low energy advertisements.
 * Ranges of values are specified for advertisement intervals. Application-requested values must
 * fall within the specified range. If different values are requested by multiple applications,
 * the lowest value that is within the range will be used as the advertising value.
 */
typedef struct {
    /**
     * The minimum initial advertising interval used when no connection exists.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t minAdvertInterval1;

    /**
     * The maximum initial advertisement interval used when either a connection exists or
     * advertising.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t maxAdvertInterval1;

    /**
     * The time (in msec) to perform the initial advertisements. Use @c GATT_TIME_INFINITY
     * to run until the connection is created or disconnected.  If @c time1 is set to @c 0, then the initial interval
     * is disabled and the second interval is used instead for power saving when fast advertising is not required.
     */
    uint32_t time1;

    /**
     * The minimum second advertisement interval, used after @c time1 has expired or when a connection exists.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t minAdvertInterval2;
    /**
     * The maximum second advertisement interval, used after @c time1 has expired or when a connection exists.
     * - Range: 0x0020 to 0x4000
     * - Time = N * 0.625 msec
     * - Time Range: 20 msec to 10.24 seconds
     */
    uint16_t maxAdvertInterval2;
    /**
     * The time (in msec) to perform the second stage of the advertisting process.
     * Use @c 0 to disable the second stage or @c GATT_TIME_INFINITY to run until advertisement is stopped.
     */
    uint32_t time2;

} bt_le_advert_parm_t;


__BEGIN_DECLS

/**
 * @brief Set up the desired scan interval when searching for device
 *        advertisements
 *
 * @param interval The scan interval used when no connections exist.
 *         Range (N * 0.625 msec): 0x0004 to 0x4000
 * @param window The scan window used during the scan.
 *         Range (N * 0.625 msec): 0x0004 to 0x4000
 * @param type The scan type used when listening for advertisements.
 *         Default: Passive scan.
 *
 * @return @c EOK on successful registration of scan parameters, @c -1 if an error
 *         occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EINVAL: The parameters provided are out of range.
 *         - @c ENOMEM: Insufficient memory was available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_set_scan_params(uint16_t interval, uint16_t window, bt_le_advert_scan_type_t type);

/**
 * @brief Add the Bluetooth address of the remote device to the advertisement
 *        filter list, such as <tt>12:03:40:60:11:21</tt>
 * @details Adding the address allows your application to receive device
 *          advertisement data. The advertisement data is in binary form,
 *          which you will need to parse in your application logic.
 *          If an error is returned from the function call, the @c errno is
 *          set with reason of failure.
 *
 * @param bdaddr The address of the specific Bluetooth-enabled device. You can
 *               use the value of @c BT_LE_BDADDR_ANY to receive advertisements
 *               from all Bluetooth-enabled devices.
 * @param userData  (Optional) A pointer to user data.
 *
 * @return @c EOK on successful addition of a device to the filter list,
 *         @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c EBUSY: The requested service is already in use.
 *         - @c EINVAL: The Bluetooth MAC address provided is NULL or invalid.
 *         - @c ENOMEM: Insufficient memory was available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_add_scan_device(const char *bdaddr, void *userData);

/**
 * @brief Remove the device from the advertisement filter list
 * @details If an error is returned from the function call, the @c errno is
 *          set with reason.
 *
 * @param bdaddr The address of the Bluetooth-enabled device to remove from the
 *               filter list.
 *
 * @return @c EOK on successful removal of a device from the filter list,
 *         @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c ENODEV: Bluetooth stack is unavailable.
 *         - @c EINVAL: The Bluetooth MAC address provided is NULL or invalid.
 *         - @c ENOMEM: Insufficient memory was available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_remove_scan_device(const char *bdaddr);

/**
 * @brief Start low energy advertisements
 *
 * @param advertParm (Optional) The advertisement parameters. Use
 *                            this argument when you require specific
 *                            advertisement parameters; set to @c NULL otherwise
 *                            to use the following default values.
 *                              - minAdvertInterval1 = 20ms
 *                              - maxAdvertInterval1 = 30ms
 *                              - time1              = 30sec
 *                              - minAdvertInterval2 = 1sec
 *                              - maxAdvertInterval2 = 2.5sec
 *                              - time2              = 60sec
 * @param intervalMin (Optional) Returns the minimum current advertisement interval.
 * @param intervalMax (Optional) Returns the maximum current advertisement interval.
 *
 * @return @c EOK on successful start of low energy advertisements,
 *         @c -1 if an error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c EBUSY: The stack is currently busy or there is an active
 *                     connection or connection request.
 *         - @c EMLINK: Advertising cannot be performed as there is already an
 *                      existing low energy connection.
 *         - @c EINVAL: Advertisement parameters provided were invalid.
 *         - @c ENOMEM: Insufficient memory was available to perform the
 *                      request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_start_advertisement(bt_le_advert_parm_t *advertParm, uint16_t *intervalMin, uint16_t *intervalMax);

/**
 * @brief Stop low energy advertisements
 *
 * @return @c EOK on successful stop of low energy advertisements, @c -1 if an
 *         error occurred with the @c errno value set.
 *         These are some of the error codes that can be returned:
 *         - @c EAGAIN: The link to the Bluetooth stack is unavailable. You
 *                      can try again.
 *         - @c EBUSY: The stack is currently busy or there is an active
 *                     connection or connection request.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_stop_advertisement();


/**
 * @brief Initialize the low energy functionality and allocate the required
 *        resources for the library
 * @details This function also starts a new thread for low energy functionality.
 *          The callback is invoked in the new thread and is thread safe. If an
 *          error is returned from this function call, the @c errno is set to
 *          indicate reason of failure.
 *
 * @param cb The list of callbacks to be used for low energy connection manager
 *           callbacks.
 *
 * @return @c EOK on successful initialization, @c -1 with the @c errno value
 *         set otherwise. The error codes that can be returned are as follows:
 *         - @c EACCES: Insufficient permissions to initialize the low energy
 *           functionality.
 *         - @c ENODEV: Bluetooth stack is unavailable.
 *         - @c ENOMEM: Insufficient memory was available to perform the
 *                      request.
 *         - @c ENOTSUP: The currently library version is not supported.
 *         - @c ESRVRFAULT: An internal error has occurred.
 */
int bt_le_init(bt_le_callbacks_t *cb);

/**
 * @brief Deallocate resources that were allocated to use low energy
 *        functionality
 * @details This function also stops the event loop that was created to work with
 *          the low energy functionality provided by this library.
 */
void bt_le_deinit();

/**
 * @cond
 * For internal use only. Do not use.
 *
 * The following prototypes are used as initialization functions for
 * various callbacks. The callbacks pass the version to indicate which
 * version an application is compiled against.
 */
int _bt_le_init(bt_le_callbacks_t *cb, uint32_t version);
#define bt_le_init(callbacks) _bt_le_init(callbacks, BT_LE_VERSION)
/** @endcond */


__END_DECLS

#endif /* _BTLE_H_ */


#include <sys/srcversion.h>
__SRCVERSION( "$URL$ $Rev$" )
