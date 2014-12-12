/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTMANAGER_HPP
#define BB_DEVICE_MIRACASTMANAGER_HPP

#include <bb/device/Global>

#include <bb/device/MiracastDeviceCategory>
#include <bb/device/MiracastDeviceSubCategory>
#include <bb/device/MiracastResult>
#include <bb/device/MiracastConnectionState>
#include <bb/device/MiracastDisplayState>
#include <bb/device/MiracastStopReason>
#include <bb/device/MiracastStatus>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

class MiracastManagerPrivate;

/*!
 * @headerfile MiracastManager.hpp <bb/device/MiracastManager>
 *
 * @brief The @c MiracastManager class provides the entry point to accessing information
 *        about Miracast devices, or establishing connections with those devices.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Control"/>
 * <library name="bbdevice"/>
 * <qml>
 *    <class register="yes" />
 * </qml>
 * @endxmlonly 
 *
 * @permissions The application must have the @c access_miracast_service permission to use this class.
 *
 * @since BlackBerry 10.2.0
 */
class BB_DEVICE_EXPORT MiracastManager : public QObject
{
    Q_OBJECT

    /*!
     * @brief The hardware address of the currently connected device, if any.
     *
     * @details Returns the hardware address of the currently connected device, or an empty string
     * if not currently connected.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString hardwareAddress READ hardwareAddress NOTIFY hardwareAddressChanged FINAL )

    /*!
     * @brief The current connection state of the Miracast service.
     *
     * @details See @c bb::device::MiracastConnectionState for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::MiracastConnectionState::Type connectionState READ connectionState NOTIFY connectionStateChanged FINAL )

    /*!
     * @brief A human readable name for the currently connected device, if any.
     *
     * @details Returns the reported name of the currently connected device, or an empty string
     * if not currently connected.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString deviceName READ deviceName NOTIFY deviceNameChanged FINAL )

    /*!
     * @brief Represents the screen resolution of the connected device.
     *
     * @details Returns the width and height of the connected device's screen in pixels
     * in a @c QSize object. If no device is connected the @c QSize object will have zero for
     * both height and width.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QSize devicePixelSize READ devicePixelSize NOTIFY devicePixelSizeChanged FINAL)

    /*!
     * @brief Indicates the current streaming state to the target device.
     *
     * @details See @c bb::device::MiracastDisplayState for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::MiracastDisplayState::Type displayState READ displayState NOTIFY displayStateChanged FINAL )

    /*!
     * @brief Indicates the Miracast category of the target connected device.
     *
     * @details Indicates the Miracast category of the target device. This value is reported by the target device.
     * See @c bb::device::MiracastDeviceCategory for more information.  If no device is connected, the value
     * @c bb::device::MiracastDeviceCategory::Unknown is returned.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::MiracastDeviceCategory::Type deviceCategory READ deviceCategory NOTIFY deviceTypeChanged FINAL )

    /*!
     * @brief Indicates the Miracast secondary category of the target connected device.
     *
     * @details Indicates the Miracast secondary category of the target device. This value is reported by the target device.
     * See @c bb::device::MiracastDeviceSubCategory for more information.  If no device is connected, the value
     * @c bb::device::MiracastDeviceSubCategory::Unknown is returned.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::MiracastDeviceSubCategory::Type deviceSubCategory READ deviceSubCategory NOTIFY deviceTypeChanged FINAL )

    /*!
     * @brief The unique identifier for the current connection to the target device, if any.
     *
     * @details Provides the identifier for the connection to the target Mircast device.  If no device is connected
     * the value will be blank.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( QString sessionId READ sessionId NOTIFY sessionIdChanged FINAL )

    /*!
     * @brief The reason the Miracast service was stopped.
     *
     * @details See @c bb::device::MiracastStopReason for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::MiracastStopReason::Type stopReason READ stopReason NOTIFY stopReasonChanged FINAL )

    /*!
     * @brief The status of the Miracast service on the device.
     *
     * @details See @c bb::device::MiracastStatus for more details.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bb::device::MiracastStatus::Type status READ status NOTIFY statusChanged FINAL )

    /*!
     * @brief Determines if the device has Miracast capability.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY( bool isSupported READ isSupported CONSTANT FINAL )

public:
    /*!
     * @brief Construct a @c MiracastManager instance.
     *
     * @param parent If not 0, the supplied parent is responsible for deleting 
     *               this instance.
     *
     * @since BlackBerry 10.2.0
     */
    explicit MiracastManager(QObject *parent = 0);

    /*!
     * @brief Destroy the @c MiracastManager instance.
     */
    virtual ~MiracastManager();

    /*!
     * @brief Initiates a scan for discoverable Miracast devices.
     *
     * @details During the scan the @c deviceDiscovered signal will be emitted once
     * for each discovered device.  The @c scanCompleted signal will be emitted when
     * the scan has completed.
     *
     * Scanning for Miracast devices in C++
     * @snippet libbbdevice/MiracastManager_requestScan.cpp All
     *
     * Scanning for Miracast devices in QML
     * @snippet libbbdevice/MiracastManager_requestScan.qml All
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void requestScan();

    /*!
     * @brief Starts a connection attempt to the supplied hardware address using the
     * supplied PIN.  
     *
     * @details The result of the connection request will be available when the 
     * @c connectCompleted signal is emitted.
     *
     * @param hardwareAddress A unique identifier used to determine which device to connect
     * to.  You can obtain a hardware address by using @c requestScan and noting the hardware address
     * given when the @c deviceDiscovered signal is emitted.
     *
     * @param pin A code to authorize the connection attempt to the device.
     *
     * Connecting to a Miracast device in C++
     * @snippet libbbdevice/MiracastManager_requestConnect.cpp All
     *
     * Connecting to a Miracast device in QML
     * @snippet libbbdevice/MiracastManager_requestConnect.qml All
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void requestConnect(const QString &hardwareAddress, const QString &pin);

    /*!
     * @brief Shuts down the Miracast service on the device.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void requestShutdown();

    /*!
     * @brief Attempts to start the Miracast service on the device if it is not already started.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void warmup();

    /*!
     * @brief Attempts to disconnect from the currently connected device, if one exists.
     *
     * @details The result of the disconnection attempt will be available when the @c disconnectCompleted
     * signal is emitted.
     *
     * Disconnecting from a Miracast device in C++
     * @snippet libbbdevice/MiracastManager_requestDisconnect.cpp All
     *
     * Disconnecting from a Miracast device in QML
     * @snippet libbbdevice/MiracastManager_requestDisconnect.qml All
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void requestDisconnect();

    /*!
     * @brief Attempts to suspend streaming to the connected device, if one exists.
     *
     * @details If the device is connected and the request is successful, the streaming to the device
     * will be suspended.  This will have no effect if there is no currently connected device.
     *
     * Pausing the Miracast stream in C++
     * @snippet libbbdevice/MiracastManager_requestPause.cpp All
     *
     * Pausing the Miracast stream in QML
     * @snippet libbbdevice/MiracastManager_requestPause.qml All
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void requestPause();

    /*!
     * @brief Attempts to resume streaming to the connected device, if one exists.
     *
     * @details If the device is connected and the request is successful and the device is currently paused
     * the streaming to the device will be resumed.  This will have no effect if there is no currently connected device,
     * or if the current device is not paused.
     *
     * Resuming the Miracast stream in C++
     * @snippet libbbdevice/MiracastManager_requestResume.cpp All
     *
     * Resuming the Miracast stream in QML
     * @snippet libbbdevice/MiracastManager_requestResume.qml All
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT void requestResume();

    /*!
     * @brief The hardware address of the currently connected device.
     *
     * @returns Returns the hardware address of the currently connected device, or an empty string
     * if not currently connected.
     *
     * @since BlackBerry 10.2.0
     */
    QString hardwareAddress() const;

    /*!
     * @brief The current connection state of the Miracast service.
     *
     * @returns Returns the current connection state of the Miracast service.
     * See @c bb::device::MiracastConnectionState for more details.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::MiracastConnectionState::Type connectionState() const;

    /*!
     * @brief A human readable name for the connected device.
     *
     * @returns Returns the reported name of the currently connected device, or an empty string
     * if not currently connected.
     *
     * @since BlackBerry 10.2.0
     */
    QString deviceName() const;

    /*!
     * @brief Device screen resolution of the connected device.
     *
     * @returns A @c QSize object containing the width and height of the connected device.
     * If not currently connected to a device the width and height will be zero.
     *
     * Accessing the device properties in C++
     * @snippet libbbdevice/MiracastManager_properties.cpp All
     *
     * Accessing the device properties in QML
     * @snippet libbbdevice/MiracastManager_properties.qml All
     *
     * @since BlackBerry 10.2.0
     */
    QSize devicePixelSize() const;

    /*!
     * @brief Indicates the current streaming state to the target device.
     *
     * @returns The current streaming state to the target device.
     * See @c bb::device::MiracastDisplayState for more details.
     *
     * Accessing the device properties in C++
     * @snippet libbbdevice/MiracastManager_properties.cpp All
     *
     * Accessing the device properties in QML
     * @snippet libbbdevice/MiracastManager_properties.qml All
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::MiracastDisplayState::Type displayState() const;

    /*!
     * @brief Indicates the Miracast category of the target connected device, if any.
     *
     * @returns Returns the category of the connected Miracast device.
     * See @c bb::device::MiracastDeviceCategory for more information.  If no device is connected, the value
     * @c bb::device::MiracastDeviceCategory::Unknown is returned.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::MiracastDeviceCategory::Type deviceCategory() const;

    /*!
     * @brief Indicates the Miracast secondary category of the target connected device, if any.
     *
     * @returns Returns the sub-category of the connected Miracast device.
     * See @c bb::device::MiracastDeviceSubCategory for more information.  If no device is connected, the value
     * @c bb::device::MiracastDeviceSubCategory::Unknown is returned.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::MiracastDeviceSubCategory::Type deviceSubCategory() const;

    /*!
     * @brief Provides the identifier for the connection to the target Mircast device.
     *
     * @details If no device is connected the value will be blank.
     *
     * @returns Returns a @c QString containing the identifier for the session with the target Miracast device.
     *
     * @since BlackBerry 10.2.0
     */
    QString sessionId() const;

    /*!
     * @brief Provides the reason the Miracast service was stopped.
     *
     * @returns See @c bb::device::MiracastStopReason for more details.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::MiracastStopReason::Type stopReason() const;

    /*!
     * @brief Provides the status of the Miracast service on the device.
     *
     * @returns See @c bb::device::MiracastStatus for more details.
     *
     * @since BlackBerry 10.2.0
     */
    bb::device::MiracastStatus::Type status() const;

    /*!
     * @brief Determines if the device has Miracast capability.
     *
     * @returns Returns @c true if the device has Miracast capability, otherwise returns @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE static bool isSupported();

Q_SIGNALS:
    /*!
     * @brief Emitted when a device is found during a scan.
     *
     * @details This signal will be emitted once for each device discovered during a scan.  The @c hardwareAddress will be
     * needed to establish a connection with that device.
     *
     * @param deviceName A human readable name for the device.
     *
     * @param hardwareAddress The unique address of the device.  This is needed for establishing a connection to the device.
     *
     * @param category Indicates the primary type of the discovered device.  See @c bb::device::MiracastDeviceCategory for more details.
     *
     * @param subCategory Indicates the secondary type of discovered device.  See @c bb::device::MiracastDeviceSubCategory for more details.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceDiscovered(const QString &deviceName, const QString &hardwareAddress, bb::device::MiracastDeviceCategory::Type category, bb::device::MiracastDeviceSubCategory::Type subCategory);

    /*!
     * @brief Emitted when a device is successfully paired.
     *
     * @details This signal will be emitted upon connection to a target device.
     *
     * @param deviceName A human readable name for the device.
     *
     * @param hardwareAddress The unique address of the device.  This is needed for establishing a connection to the device.
     *
     * @param category Indicates the primary type of the discovered device.  See @c bb::device::MiracastDeviceCategory for more details.
     *
     * @param subCategory Indicates the secondary type of discovered device.  See @c bb::device::MiracastDeviceSubCategory for more details.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceConnected(const QString &deviceName, const QString &hardwareAddress, bb::device::MiracastDeviceCategory::Type category, bb::device::MiracastDeviceSubCategory::Type subCategory );

    /*!
     * @brief Emitted when the connection to the target device is lost or terminated.
     *
     * @details This signal will be emitted upon disconnection from the target device.  This can happen in response to a request to disconnect
     * or if the connection was terminated by any other means.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceDisconnected();

    /*!
     * @brief Emitted when a request for a scan for devices is completed.
     *
     * @details The @c deviceDiscovered signal is emitted once for each discovered device before this signal is emitted.
     *
     * @param result Indicates the status of the scan.
     * See @c bb::device::MiracastResult for more details on the result codes.
     *
     * @since BlackBerry 10.2.0
     */
    void scanCompleted(bb::device::MiracastResult::Type result);

    /*!
     * @brief Emitted when a request for a connection to a device is completed.
     *
     * @param result Indicates the result of the connection attempt.
     * See @c bb::device::MiracastResult for more details on the result codes.
     *
     * @since BlackBerry 10.2.0
     */
    void connectCompleted(bb::device::MiracastResult::Type result);

    /*!
     * @brief Emitted when a request to pause the stream is completed.
     *
     * @param result Indicates the result of the pause attempt.
     * See @c bb::device::MiracastResult for more details on the result codes.
     *
     * @since BlackBerry 10.2.0
     */
    void pauseCompleted(bb::device::MiracastResult::Type result);

    /*!
     * @brief Emitted when a request to resume the stream is completed.
     *
     * @param result Indicates the result of the resume attempt.
     * See @c bb::device::MiracastResult for more details on the result codes.
     *
     * @since BlackBerry 10.2.0
     */
    void resumeCompleted(bb::device::MiracastResult::Type result);

    /*!
     * @brief Emitted when a request for disconnection from a device is completed.
     *
     * @param result Indicates the result of the disconnection attempt, such as @c bb::device::MiracastResult::Success.
     * See @c bb::device::MiracastResult for more details on the result codes.
     *
     * @since BlackBerry 10.2.0
     */
    void disconnectCompleted(bb::device::MiracastResult::Type result);

    /*!
     * @brief Emitted when the service has completed shutting down.
     *
     * @param result Indicates the result of the shutdown attempt, such as @c bb::device::MiracastResult::Success.
     * See @c bb::device::MiracastResult for more details on the result codes.
     *
     * @since BlackBerry 10.2.0
     */
    void shutdownCompleted(bb::device::MiracastResult::Type result);

    /*!
     * @brief Emitted when the state of the connection to the target device changes.
     *
     * @param state Indicates the current state of the connection.
     * See @c bb::device::MiracastConnectionState for more details on the states.
     *
     * @since BlackBerry 10.2.0
     */
    void connectionStateChanged(bb::device::MiracastConnectionState::Type state);

    /*!
     * @brief Emitted when hardware address of the currently connected device has changed.
     *
     * @param hardwareAddress The hardware address of the currently connected device, or an empty string
     * if not currently connected.
     *
     * @since BlackBerry 10.2.0
     */
    void hardwareAddressChanged( const QString &hardwareAddress );

    /*!
     * @brief Emitted when the name of the currently connected device has changed.
     *
     * @details The human readable name for the device, or an empty string if no device is connected.
     *
     * @param deviceName The reported name of the currently connected device, or an empty string
     * if not currently connected.
     *
     * @since BlackBerry 10.2.0
     */
    void deviceNameChanged( const QString &deviceName );

    /*!
     * @brief Emitted when the screen resolution of the currently connected device has changed.
     *
     * @param devicePixelSize A @c QSize object containing the width and height of the connected device's screen. If no device
     * is connected, the width and height will be zero.
     *
     * @since 10.2.0
     */
    void devicePixelSizeChanged(const QSize &devicePixelSize);

    /*!
     * @brief Emitted when the reason for the Miracast service being stopped has changed.
     *
     * @param status See @c bb::device::MiracastStopReason for more details.
     *
     * @since 10.2.0
     */
    void stopReasonChanged( bb::device::MiracastStopReason::Type stopReason );

    /*!
     * @brief Emitted when the status of the Miracast service has changed.
     *
     * @param status See @c bb::device::MiracastStatus for more details.
     *
     * @since 10.2.0
     */
    void statusChanged( bb::device::MiracastStatus::Type status );

    /*!
     * @brief Emitted when the current streaming state to the target device has changed.
     *
     * @param state See @c bb::device::MiracastDisplayState for more details.
     *
     * @since BlackBerry 10.2.0
     */
    void displayStateChanged(bb::device::MiracastDisplayState::Type state);

    /*!
     * @brief Emitted when the reported category and subCategory of the target device has changed.
     *
     * @details Indicates the Miracast category and subCategory of the target device. This value is reported by the target device.
     * See @c bb::device::MiracastDeviceSubCategory for more information.  If no device is connected, the value
     * @c bb::device::MiracastDeviceSubCategory::Unknown is returned.
     *
     * @param category See @c bb::device::MiracastDeviceCategory
     *
     * @param subCategory See @c bb::device::MiracastDeviceSubCategory
     *
     * @since BlackBerry 10.2.0
     */
    void deviceTypeChanged(bb::device::MiracastDeviceCategory::Type category, bb::device::MiracastDeviceSubCategory::Type subCategory);

    /*!
     * @brief Emitted when the per-connection identifier for the target Miracast device has changed.
     *
     * @details Provides the identifier for the connection to the target Mircast device.  If no device is connected
     * the value will be blank.
     *
     * @param sessionId A string containing the identifier for the session with the current target Miracast device.
     *
     * @since BlackBerry 10.2.0
     */
    void sessionIdChanged( const QString &sessionId );

protected:
//!@cond PRIVATE
    /*!
     * @xmlonly
     * <qml>
     *    <param name="deviceType" type="bb::device::MiracastDeviceCategory::Type" />
     *    <param name="deviceSubType" type="bb::device::MiracastDeviceSubCategory::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void deviceTypeChanged(int category, int subCategory);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="deviceType" type="bb::device::MiracastDeviceCategory::Type" />
     *    <param name="deviceSubType" type="bb::device::MiracastDeviceSubCategory::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void deviceDiscovered(const QString &deviceName, const QString &hardwareAddress, int category, int subCategory);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="deviceType" type="bb::device::MiracastDeviceCategory::Type" />
     *    <param name="deviceSubType" type="bb::device::MiracastDeviceSubCategory::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void deviceConnected(const QString &deviceName, const QString &hardwareAddress, int category, int subCategory);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastResult::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void scanCompleted(int result);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastResult::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void connectCompleted(int result);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastResult::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void pauseCompleted(int result);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastResult::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void resumeCompleted(int result);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastResult::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void disconnectCompleted(int result);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastConnectionState::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void connectionStateChanged(int state);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastDisplayState::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void displayStateChanged(int state);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastStopReason::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void stopReasonChanged(int stopReason);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastStatus::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void statusChanged(int status);

    /*!
     * @xmlonly
     * <qml>
     *    <param name="result" type="bb::device::MiracastResult::Type" />
     * </qml>
     * @endxmlonly
     */
    Q_SIGNAL void shutdownCompleted(int result);
//!@endcond

private:
//!@cond PRIVATE
    Q_DECLARE_PRIVATE(MiracastManager)
    Q_DISABLE_COPY(MiracastManager)
    QScopedPointer<MiracastManagerPrivate> d_ptr;
//!@endcond
};

} // device
} // bb

QML_DECLARE_TYPE(bb::device::MiracastManager)

#endif // BB_DEVICE_MIRACASTMANAGER_HPP
