/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTCONNECTIONSTATE_HPP
#define BB_DEVICE_MIRACASTCONNECTIONSTATE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile MiracastConnectionState.hpp <bb/device/MiracastConnectionState>
 *
 * @brief The current state of the connection to the target Miracast device.
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
class BB_DEVICE_EXPORT MiracastConnectionState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The current state of the connection to the target Miracast device.
	 *
	 * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The state of the connection to the target Miracast device could not be determined.
		 *
		 * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The device is connected to a Miracast device.
		 *
		 * @since BlackBerry 10.2.0
         */
        Connected = 1,

        /*!
         * @brief The device is attempting to connect to a Miracast device.
		 *
		 * @since BlackBerry 10.2.0
         */
        Connecting = 2,

        /*!
         * @brief The device is not connected to a Miracast device.
		 *
		 * @since BlackBerry 10.2.0
         */
        Disconnected = 3
    };

private:
    //!@cond PRIVATE
    MiracastConnectionState();
    ~MiracastConnectionState();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::MiracastConnectionState)
#endif // BB_DEVICE_MIRACASTCONNECTIONSTATE_HPP
