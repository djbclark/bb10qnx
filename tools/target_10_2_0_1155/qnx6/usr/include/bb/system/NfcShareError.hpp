/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREERROR_HPP
#define BB_SYSTEM_NFCSHAREERROR_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareError.hpp <bb/system/NfcShareError>
 *
 * @brief The list of notifications provided to the @c NfcShareManager::error()
 * signal after an unsuccessful attempt to share content via NFC.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT NfcShareError
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of notifications provided to the @c NfcShareManager::error()
     * signal after an unsuccessful attempt to share content via NFC.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief An unknown error occurred.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown                         = 0,

        /*!
         * @brief No content could be transferred because the sending device failed to set any content to share.
         *
         * @details There is no content to transfer because the sending device did not made a successful call to
         * either @c bb::system::NfcShareManager::setShareContent(const bb::system::NfcShareFilesContent&) or
         * @c bb::system::NfcShareManager::setShareContent(const bb::system::NfcShareDataContent&).
         *
         * @since BlackBerry 10.0.0
         */
        NoContentToShare                = 1,

        /*!
         * @brief The application was unable to register as a handler for NFC handover events.
         *
         * @details For file transfers, the application must register as a handler for NFC handover events.
         * This error occurs when this registration process fails.
         *
         * @since BlackBerry 10.0.0
         */
        RegisterFileSharing             = 2,

        /*!
         * @brief The application was unable to register as a handler for NFC tag events.
         *
         * @details For data transfers, the application must register as a handler for NFC tag events.
         * This error occurs when this registration process fails.
         *
         * @since BlackBerry 10.0.0
         */
        RegisterDataSharing             = 3,

        /*!
         * @brief The recipient NFC tag does not have enough memory for the request.
         *
         * @details The user should be advised to use an NFC tag with more memory.
         *
         * @since BlackBerry 10.0.0
         */
        MessageSize                     = 4,

        /*!
         * @brief The user attempted to write content to a locked NFC tag.
         *
         * @since BlackBerry 10.0.0
         */
        TagLocked                       = 5,

        /*!
         * @brief The user attempted to write content to an NFC tag of an unsupported type.
         *
         * @since BlackBerry 10.0.0
         */
        UnsupportedTagType              = 6,

        /*!
         * @brief An attempt to transfer data to another NFC-enabled device or write data to an NFC tag failed.
         *
         * @since BlackBerry 10.0.0
         */
        DataTransferFailed              = 7,

        /*!
         * @brief The NFC handover negotiation for file transfer failed.
         *
         * @since BlackBerry 10.0.0
         */
        HandoverFailed                  = 8,

        /*!
         * @brief File transfer over Bluetooth failed.
         *
         * @since BlackBerry 10.0.0
         */
        BluetoothFileTransferFailed     = 9,

        /*!
         * @brief File transfer over Bluetooth was cancelled.
         *
         * @details The user can ask to be prompted before sending files via NFC.  This notification
         * is sent if the user cancels the transfer in this prompt.
         *
         * @since BlackBerry 10.0.0
         */
        BluetoothFileTransferCancelled  = 10,

        /*!
         * @brief Share mode cannot be changed and no content could be transferred because the transfer to the
         * acquired target is already in progress
         *
         * @details Developer cannot change share mode using @c bb::system::NfcShareManager::setShareMode() method
         * once transfer is in progress. Developer should not be calling @c bb::system::NfcShareManager::startTransfer()
         * method more than once for each @c bb::system::NfcShareSuccess::TargetAcquired signal received
         * when "Start Transfer" mode is set to set to @c bb::system::NfcShareStartTransferMode::OnDemand
         *
         * @since BlackBerry 10.2.0
         */
        TransferInProgress              = 11,

        /*!
         * @brief The user attempted to set share mode that is currently not supported
         *
         * @since BlackBerry 10.2.0
         */
        UnsupportedShareMode            = 12,

        /*!
         * @brief File transfer over WiFi Direct failed.
         *
         * @since BlackBerry 10.2.0
         */
        WiFiDirectFileTransferFailed          = 13,

        /*!
         * @brief File transfer over WiFi Direct was cancelled.
         *
         * @details The user can ask to be prompted before sending files via NFC.  This notification
         * is sent if the user cancels the transfer in this prompt.
         *
         * @since BlackBerry 10.2.0
         */
        WiFiDirectFileTransferCancelled       = 14,

       /*!
         * @brief The user attempted to start the transfer, when no target was acquired
         *
         * @since BlackBerry 10.2.0
         */
        NoTransferTarget                = 15

    };
private:
//!@cond PRIVATE
    NfcShareError();
    ~NfcShareError();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREERROR_HPP */
