/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTDISPLAYSTATE_HPP
#define BB_DEVICE_MIRACASTDISPLAYSTATE_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile MiracastDisplayState.hpp <bb/device/MiracastDisplayState>
 *
 * @brief The current streaming state to the target Miracast device.
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
class BB_DEVICE_EXPORT MiracastDisplayState
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The current streaming state to the target Miracast device.
	 *
	 * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The state of the stream to the target Miracast device could not be determined.
		 *
		 * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The stream is no longer being sent to the target Miracast device.
		 *
		 * @since BlackBerry 10.2.0
         */
        Stopped = 1,

        /*!
         * @brief The stream is being sent to the target Miracast device.
		 *
		 * @since BlackBerry 10.2.0
         */
        Playing = 2,

        /*!
         * @brief The stream to the target Mircast device is temporarily suspended.
		 *
		 * @since BlackBerry 10.2.0
         */
        Paused = 3
    };

private:
    //!@cond PRIVATE
    MiracastDisplayState();
    ~MiracastDisplayState();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::MiracastDisplayState)
#endif // BB_DEVICE_MIRACASTDISPLAYSTATE_HPP
