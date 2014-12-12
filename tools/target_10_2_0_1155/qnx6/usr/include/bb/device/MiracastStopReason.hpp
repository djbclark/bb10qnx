/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTSTOPREASON_HPP
#define BB_DEVICE_MIRACASTSTOPREASON_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile MiracastStopReason.hpp <bb/device/MiracastStopReason>
 *
 * @brief The reason why the Miracast service was stopped.
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
class BB_DEVICE_EXPORT MiracastStopReason
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The reason why the Miracast service was stopped.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The reason for the current state of the Miracast service is not known.
         *
         * @since BlackBerry 10.2.0
         */
    	Unknown = 0,

        /*!
         * @brief The service is still running.
         *
         * @since BlackBerry 10.2.0
         */
        NotStopped = 1,

        /*!
         * @brief An application requested for the service to be shutdown.
         *
         * @since BlackBerry 10.2.0
         */
        Application = 2,

        /*!
         * @brief Miracast is not supported on this device.
         *
         * @since BlackBerry 10.2.0
         */
        NotSupported = 3,

        /*!
         * @brief Miracast was disabled by IT policy.
         *
         * @since BlackBerry 10.2.0
         */
        ItPolicy = 4,

        /*!
         * @brief The P2P profile or module experienced a failure.
         *
         * @since BlackBerry 10.2.0
         */
        P2PFailure = 5,

        /*!
         * @brief Miracast was stopped due to system error or other internal reasons.
         *
         * @since BlackBerry 10.2.0
         */
        Internal = 6
    };

private:
    //!@cond PRIVATE
    MiracastStopReason();
    ~MiracastStopReason();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::MiracastStopReason)
#endif // BB_DEVICE_MIRACASTSTOPREASON_HPP
