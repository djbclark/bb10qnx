/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_DEVICE_MIRACASTDEVICESUBCATEGORY_HPP
#define BB_DEVICE_MIRACASTDEVICESUBCATEGORY_HPP

#include <bb/device/Global>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace device
{

/*!
 * @headerfile MiracastDeviceSubCategory.hpp <bb/device/MiracastDeviceSubCategory>
 *
 * @brief Indicates the secondary category of the Miracast device.
 *
 * @details The categories here are taken from the Wi-Fi Peer-to-Peer (P2P) Technical
 * Specification, version 1.2, section B2, table B1.
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
class BB_DEVICE_EXPORT MiracastDeviceSubCategory
{
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief Indicates the secondary category of the Miracast device.
	 *
	 * @since BlackBerry 10.2.0
     */
    enum Type
    {
        /*!
         * @brief The type of device could not be determined.
		 *
		 * @since BlackBerry 10.2.0
         */
        Unknown = 0,

        /*!
         * @brief The device is identified as a keyboard.
		 *
		 * @since BlackBerry 10.2.0
         */
        Keyboard = 1,

        /*!
         * @brief The device is identified as a mouse.
		 *
		 * @since BlackBerry 10.2.0
         */
        Mouse = 2,

        /*!
         * @brief The device is identified as a joystick.
		 *
		 * @since BlackBerry 10.2.0
         */
        Joystick = 3,

        /*!
         * @brief The device is identified as a trackball.
		 *
		 * @since BlackBerry 10.2.0
         */
        Trackball = 4,

        /*!
         * @brief The device is identified as a gaming controller.
		 *
		 * @since BlackBerry 10.2.0
         */
        GamingController = 5,

        /*!
         * @brief The device is identified as a remote control.
		 *
		 * @since BlackBerry 10.2.0
         */
        Remote = 6,

        /*!
         * @brief The device is identified as a touchscreen.
		 *
		 * @since BlackBerry 10.2.0
         */
        Touchscreen = 7,

        /*!
         * @brief The device is identified as a biometric reader.
		 *
		 * @since BlackBerry 10.2.0
         */
        BiometricReader = 8,

        /*!
         * @brief The device is identified as a barcode reader.
		 *
		 * @since BlackBerry 10.2.0
         */
        BarcodeReader = 9,

        /*!
         * @brief The device is identified as a printer or print server.
		 *
		 * @since BlackBerry 10.2.0
         */
        PrinterOrPrintServer = 10,

        /*!
         * @brief The device is identified as a scanner.
		 *
		 * @since BlackBerry 10.2.0
         */
        Scanner = 11,

        /*!
         * @brief The device is identified as a fax machine.
		 *
		 * @since BlackBerry 10.2.0
         */
        Fax = 12,

        /*!
         * @brief The device is identified as a copier.
		 *
		 * @since BlackBerry 10.2.0
         */
        Copier = 13,

        /*!
         * @brief The device is identified as a multi-function or all-in-one device.
		 *
		 * @since BlackBerry 10.2.0
         */
        AllInOne = 14,

        /*!
         * @brief The device is identified as a digital still camera.
		 *
		 * @since BlackBerry 10.2.0
         */
        DigitalStillCamera = 15,

        /*!
         * @brief The device is identified as a video camera.
		 *
		 * @since BlackBerry 10.2.0
         */
        VideoCamera = 16,

        /*!
         * @brief The device is identified as a web camera.
		 *
		 * @since BlackBerry 10.2.0
         */
        WebCamera = 17,

        /*!
         * @brief The device is identified as a security camera.
		 *
		 * @since BlackBerry 10.2.0
         */
        SecurityCamera = 18,

        /*!
         * @brief The device is identified as a network attached storage.
		 *
		 * @since BlackBerry 10.2.0
         */
        NAS = 19,

        /*!
         * @brief The device is identified as an access point.
		 *
		 * @since BlackBerry 10.2.0
         */
        AP = 20,

        /*!
         * @brief The device is identified as a router.
		 *
		 * @since BlackBerry 10.2.0
         */
        Router = 21,

        /*!
         * @brief The device is identified as a switch.
		 *
		 * @since BlackBerry 10.2.0
         */
        Switch = 22,

        /*!
         * @brief The device is identified as a gateway.
		 *
		 * @since BlackBerry 10.2.0
         */
        Gateway = 23,

        /*!
         * @brief The device is identified as a television.
		 *
		 * @since BlackBerry 10.2.0
         */
        Television = 24,

        /*!
         * @brief The device is identified as an electronic picture frame.
		 *
		 * @since BlackBerry 10.2.0
         */
        ElectronicPictureFrame = 25,

        /*!
         * @brief The device is identified as a projector.
		 *
		 * @since BlackBerry 10.2.0
         */
        Projector = 26,

        /*!
         * @brief The device is identified as a monitor.
		 *
		 * @since BlackBerry 10.2.0
         */
        Monitor = 27,

        /*!
         * @brief The device is identified as a DAR.
		 *
		 * @since BlackBerry 10.2.0
         */
        DAR = 28,

        /*!
         * @brief The device is identified as a PVR.
		 *
		 * @since BlackBerry 10.2.0
         */
        PVR = 29,

        /*!
         * @brief The device is identified as an MCX.
		 *
		 * @since BlackBerry 10.2.0
         */
        MCX = 30,

        /*!
         * @brief The device is identified as a set top box.
		 *
		 * @since BlackBerry 10.2.0
         */
        SetTopBox = 31,

        /*!
         * @brief The device is identified as a media server, media adapter or media extender.
		 *
		 * @since BlackBerry 10.2.0
         */
        MediaServerAdapterOrExtender = 32,

        /*!
         * @brief The device is identified as a portable video player.
		 *
		 * @since BlackBerry 10.2.0
         */
        PortableVideoPlayer = 33,

        /*!
         * @brief The device is identified as an XBox.
		 *
		 * @since BlackBerry 10.2.0
         */
        XBox = 34,

        /*!
         * @brief The device is identified as an XBox360.
		 *
		 * @since BlackBerry 10.2.0
         */
        XBox360 = 35,

        /*!
         * @brief The device is identified as an PlayStation.
		 *
		 * @since BlackBerry 10.2.0
         */
        PlayStation = 36,

        /*!
         * @brief The device is identified as a game console or game console adapter.
		 *
		 * @since BlackBerry 10.2.0
         */
        GameConsoleOrConsoleAdapter = 37,

        /*!
         * @brief The device is identified as a portable gaming device.
		 *
		 * @since BlackBerry 10.2.0
         */
        PortableGamingDevice = 38,

        /*!
         * @brief The device is identified as Windows Mobile device.
		 *
		 * @since BlackBerry 10.2.0
         */
        WindowsMobile = 39,

        /*!
         * @brief The device is identified as a phone - single mode.
		 *
		 * @since BlackBerry 10.2.0
         */
        PhoneSingleMode = 40,

        /*!
         * @brief The device is identified as a phone - dual mode.
		 *
		 * @since BlackBerry 10.2.0
         */
        PhoneDualMode = 41,

        /*!
         * @brief The device is identified as a smartphone - single mode.
		 *
		 * @since BlackBerry 10.2.0
         */
        SmartphoneSingleMode = 42,

        /*!
         * @brief The device is identified as a smartphone - dual mode.
		 *
		 * @since BlackBerry 10.2.0
         */
        SmartphoneDualMode = 43,

        /*!
         * @brief The device is identified as an audio tuner/receiver.
		 *
		 * @since BlackBerry 10.2.0
         */
        AudioTunerReceiver = 44,

        /*!
         * @brief The device is identified as speakers.
		 *
		 * @since BlackBerry 10.2.0
         */
        Speakers = 45,

        /*!
         * @brief The device is identified as a portable music player.
		 *
		 * @since BlackBerry 10.2.0
         */
        PortableMusicPlayer = 46,

        /*!
         * @brief The device is identified a headset.
		 *
		 * @since BlackBerry 10.2.0
         */
        Headset = 47,

        /*!
         * @brief The device is identified as headphones.
		 *
		 * @since BlackBerry 10.2.0
         */
        Headphones = 48,

        /*!
         * @brief The device is identified as a microphone.
		 *
		 * @since BlackBerry 10.2.0
         */
        Microphone = 49,

        /*!
         * @brief The device is identified as a personal computer.
		 *
		 * @since BlackBerry 10.2.0
         */
        PC = 50,

        /*!
         * @brief The device is identified as a server.
		 *
		 * @since BlackBerry 10.2.0
         */
        Server = 51,

        /*!
         * @brief The device is identified as a media center.
		 *
		 * @since BlackBerry 10.2.0
         */
        MediaCenter = 52,

        /*!
         * @brief The device is identified as an ultra-mobile personal computer.
		 *
		 * @since BlackBerry 10.2.0
         */
        UltraMobilePC = 53,

        /*!
         * @brief The device is identified as a notebook computer.
		 *
		 * @since BlackBerry 10.2.0
         */
        Notebook = 54,

        /*!
         * @brief The device is identified as a desktop computer.
		 *
		 * @since BlackBerry 10.2.0
         */
        Desktop = 55,

        /*!
         * @brief The device is identified as a mobile internet device.
		 *
		 * @since BlackBerry 10.2.0
         */
        MobileInternetDevice = 56,

        /*!
         * @brief The device is identified as a netbook computer.
		 *
		 * @since BlackBerry 10.2.0
         */
        Netbook = 57,

        /*!
         * @brief The device is identified as a tablet computer.
		 *
		 * @since BlackBerry 10.2.0
         */
        Tablet = 58
    };

private:
    //!@cond PRIVATE
    MiracastDeviceSubCategory();
    ~MiracastDeviceSubCategory();
    //!@endcond
};

} // namespace device
} // namespace bb

QML_DECLARE_TYPE(bb::device::MiracastDeviceSubCategory)
#endif // BB_DEVICE_MIRACASTDEVICESUBCATEGORY_HPP
