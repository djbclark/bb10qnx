/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTSTATUS_HPP
#define BB_DEVICE_MIRACASTSTATUS_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile MiracastStatus.hpp <bb/device/MiracastStatus>
 *
 * @brief The status of the Miracast service.
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
class BB_DEVICE_EXPORT MiracastStatus
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
         * @brief The current state of the service could not be determined.
         *
         * @since BlackBerry 10.2.0
         */
    	Unknown = 0,

        /*!
         * @brief The service is running.
         *
         * @since BlackBerry 10.2.0
         */
        Running = 1,

        /*!
         * @brief The service is stopped.
         *
         * @since BlackBerry 10.2.0
         */
        Stopped = 2
    };

private:
    //!@cond PRIVATE
    MiracastStatus();
    ~MiracastStatus();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::MiracastStatus)
#endif // BB_DEVICE_MIRACASTSTATUS_HPP
