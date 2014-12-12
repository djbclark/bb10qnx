/*!
 * @copyright
 * Copyright BlackBerry Limited, 2013-2013
 * BlackBerry Limited. All rights reserved.
 */

#ifndef BB_DEVICE_WIFIDIRECTROLE_HPP
#define BB_DEVICE_WIFIDIRECTROLE_HPP

#include <bb/device/Global>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile WiFiDirectRole.hpp <bb/device/WiFiDirectRole>
 *
 * @brief The connection role within the network group.
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
class BB_DEVICE_EXPORT WiFiDirectRole
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The connection role within the network group.
     *
     * @since BlackBerry 10.2.0
     */
    enum Type {
    	/*!
    	 * @brief Your role within the network group could not be determined.
    	 *
    	 * @since BlackBerry 10.2.0
    	 */
        Unknown = 0,

        /*!
         * @brief You are the Group Owner of the network group.
         *
         * @since BlackBerry 10.2.0
         */
        GroupOwner = 1,

        /*!
         * @brief You are a client within the network group.
         *
         * @since BlackBerry 10.2.0
         */
        Client = 2
    };

private:
//!@cond PRIVATE
    WiFiDirectRole();
    ~WiFiDirectRole();
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::WiFiDirectRole)
#endif // BB_DEVICE_WIFIDIRECTROLE_HPP
