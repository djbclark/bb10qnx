/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_DEVICE_DEVICEINFO_HPP
#define BB_DEVICE_DEVICEINFO_HPP

#include <bb/device/Global>
#include <bb/device/DeviceOrientation>
#include <bb/device/UserActivityState>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class DeviceInfoPrivate;

/*!
 * @headerfile DeviceInfo.hpp <bb/device/DeviceInfo>
 *
 * @brief Provides access to information about the current state of the device.
 *
 * @details The @c DeviceInfo class provides access to information about the current state
 * of the device, such as the orientation in which the device is currently being held and the
 * activity state of the device.
 *
 * @section sec_ActivityState Device Activity State
 * 
 * Instances of this class can be used to monitor the activity state of the
 * device, which can be used to determine if the end user can interact with the device.
 * 
 * If the device is active, then the user is able to interact with it.  This implies
 * that the display is enabled, but does not imply anything about the lock state of the
 * device. A user is still able to interact with a locked device, to unlock it.
 * That is, an active device may be unlocked, screen-locked, or password-locked.
 * 
 * If the device is inactive, then the user is not able to interact with it.  This
 * implies that the display is disabled. Further, the device may be screen-locked
 * or password-locked, and may even be in standby mode.
 * 
 * Also note that this is the device activity state. The state of the requesting
 * process (fullscreen, thumbnailed, or invisible) has no effect on the result.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Info"/>
 * <library name="bbdevice"/>
 * <qml>
 *    <class register="yes" />
 * </qml>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_DEVICE_EXPORT DeviceInfo: public QObject
{
    Q_OBJECT

    /*!
     * @brief The current orientation of the device.
     *
     * @details To interpret the value, see @c bb::device::DeviceOrientation.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::device::DeviceOrientation::Type orientation READ orientation NOTIFY orientationChanged FINAL)

    /*!
     * @brief The activity state of the device.
     * 
     * @details See @c bb::device::UserActivityState for a list of possible states.
     * 
     * @since BlackBerry 10.2.0
     */
     Q_PROPERTY(bb::device::UserActivityState::Type activityState READ activityState NOTIFY activityStateChanged FINAL REVISION 1)

public:
   /*!
    * @brief Constructs a @c DeviceInfo object.
    *
    * @details Constructs a @c DeviceInfo object from which may be retrieved information about the device.
    *
    * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
    *
    * @since BlackBerry 10.0.0
    */
   explicit DeviceInfo(QObject * parent = 0);

   /*!
    * @brief Destroys this @c DeviceInfo object.
    *
    * @since BlackBerry 10.0.0
    */
   virtual ~DeviceInfo();

    /*!
     * @brief Retrieves the current orientation of the device.
     *
     * @details This function lets you retrieve the current orientation of the device. To interpret the
     * result, see @c bb::device::DeviceOrientation.
     *
     * @return Returns the current orientation of the device as specified in @c bb::device::DeviceOrientation.
     *
     * @since BlackBerry 10.0.0
     */
    bb::device::DeviceOrientation::Type orientation() const;

    /*!
     * @brief Returns the current user activity state.
     * 
     * @return The current user activity state.  See @c bb::device::UserActivityState
     * for a list of possible states.
     * 
     * @since BlackBerry 10.2.0
     */
    bb::device::UserActivityState::Type activityState() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the orientation of the device has changed.
     *
     * @details This notification is independent of the orientation of the display
     * changing. Specifically, this signal will still be emitted as the device is 
     * tilted, even if an application has locked the screen rotation.
     *
     * @param orientation The new orientation the device has assumed.
     *
     * @note Do not use this signal to control any aspect of your UI layout. Use
     * the appropriate orientation signals supplied by the Cascades UI framework.
     *
     * @since BlackBerry 10.0.0
     */
    void orientationChanged( bb::device::DeviceOrientation::Type orientation );

    /*!
     * @brief Emitted when the user activity state has changed.
     * 
     * @param activityState The new activity state of the device.
     * 
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void activityStateChanged(bb::device::UserActivityState::Type activityState);

protected:
//!@cond PRIVATE
    /*!
     * @xmlonly
     * <qml>
     *    <param name="orientation" type="bb::device::DeviceOrientation::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void orientationChanged( int orientation );

    /*!
     * @xmlonly
     * <qml>
     *   <param name="state" type="bb::device::UserActivityState::Type"/>
     * </qml>
     * @endxmlonly
     */
    Q_REVISION(1) Q_SIGNAL void activityStateChanged(int activityState);
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(DeviceInfo);
    Q_DISABLE_COPY(DeviceInfo);
    QScopedPointer<DeviceInfoPrivate> d_ptr;
//!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::DeviceInfo)
#endif // BB_DEVICE_DEVICEINFO_HPP
