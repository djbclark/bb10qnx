/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTRESULT_HPP
#define BB_DEVICE_MIRACASTRESULT_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile MiracastResult.hpp <bb/device/MiracastResult>
 *
 * @brief Indicates the result of a Miracast operation.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * <qml>
 *    <class register="enum-only" />
 * </qml>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT MiracastResult
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Indicates the result of the Miracast operation.
	 *
	 * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief An error occurred in the processing of the request that is
         * not recoverable.
         *
         * @details Whatever operation had been attempted should be considered
         * incomplete or otherwise impossible.
         *
         * @since BlackBerry 10.2.0
         */
        InternalError = 0,

        /*!
         * @brief The operation was successful
		 *
		 * @since BlackBerry 10.2.0
         */
        Success = 1,

        /*!
         * @brief The connection attempt requires a PIN.
         *
         * @details The device requires a PIN in order for a connection
         * to be established.
		 *
		 * @since BlackBerry 10.2.0
         */
        PinRequired = 2,

        /*!
         * @brief The supplied PIN was incorrect.
         *
         * @details The PIN supplied to the device was not the expected value.
         * The PIN should be corrected and the attempt made again.
		 *
		 * @since BlackBerry 10.2.0
         */
        PinIncorrect = 3,

        /*!
         * @brief The target device did not accept the connection attempt.
         *
         * @details The connection attempt can fail due to a timeout,
         * refusal by the target device, or other conditions.
         *
         * @since BlackBerry 10.2.0
         */
        ConnectionFailed = 4,

        /*!
         * @brief The request was made at an invalid stage.
         *
         * @details This error is saying that the request was made at a time
         * when it was not valid to do so.  It is possible to re-try the request
         * at a later time.
         *
         * @since BlackBerry 10.2.0
         */
        InvalidRequest = 5,

        /*!
         * @brief Request cancelled due to status changes or other requests.
         *
         * @details This error is saying that request was rejected because of
         * the current state of the device.  One example might be making a
         * connection request while in the middle of processing a connection request.
         *
         * @since BlackBerry 10.2.0
         */
        RequestCancelled = 6,

        /*!
         * @brief The request was unable to be completed due to the WiFi system.
         *
         * @details This is commonly raised when a request is made while WiFi
         * is turned off.
         *
         * @since BlackBerry 10.2.0
         */
        WiFiFailure = 7,

        /*!
         * @brief The Miracast service is disabled by IT policy.
         *
         * @since BlackBerry 10.2.0
         */
        DisabledByPolicy = 8,

        /*!
         * @brief The specified device was not found.
         *
         * @since BlackBerry 10.2.0
         */
        DeviceNotFound = 9,

        /*!
         * @brief The request could not be completed due to a failure in the Miracast system.
         *
         * @details This failure could be on this device or on the target device.
         *
         * @since BlackBerry 10.2.0
         */
        MiracastFailure = 10
    };

private:
    //!@cond PRIVATE
    MiracastResult();
    ~MiracastResult();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::MiracastResult)
#endif // BB_DEVICE_MIRACASTRESULT_HPP
