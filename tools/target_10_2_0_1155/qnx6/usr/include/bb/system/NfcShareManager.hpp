/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHAREMANAGER_HPP
#define BB_SYSTEM_NFCSHAREMANAGER_HPP

#include <bb/system/Global>

#include <bb/system/NfcShareSetContentError>
#include <bb/system/NfcShareSuccess>
#include <bb/system/NfcShareError>
#include <bb/system/NfcShareMode>
#include <bb/system/NfcShareStartTransferMode>
#include <bb/system/NfcShareHandoverTransport>
#include <bb/system/NfcShareFilesContent>
#include <bb/system/NfcShareDataContent>

#include <QObject>

namespace bb
{
namespace system
{

class NfcShareManagerPrivate;

/*!
 * @headerfile NfcShareManager.hpp <bb/system/NfcShareManager>
 *
 * @brief The @c NfcShareManager class manages all interactions related to sharing files and data over NFC.
 *
 * @details A client process can share content (data or files) using NFC technology by tapping
 *          an NFC-enabled device or an NFC tag. The @c NfcShareManager class is the entry point to access this
 *          functionality.
 *
 *          To share content via NFC, the client process must do the following:
 *           -# Specify the type of content to be shared and "Start Transfer" mode by calling @c setShareMode() with the
 *              desired content type.
 *           -# Specify the content to be shared by making a successful call to one of
 *              - @c setShareContent(const bb::system::NfcShareFilesContent&) to share a file, or
 *              - @c setShareContent(const bb::system::NfcShareDataContent&) to share data.
 *              .
 *              Note that the type of the content must match the type set in the preceding call to @c setShareMode().
 *           -# Tap the device with another NFC-enabled device or an NFC tag.
 *
 *          The client process can call @c setShareContent() as many times as needed provided that the content being set
 *          matches the current content type set in a preceding call to @c setShareMode().
 *
 *          When sharing files, the client process can call @c setShareContent() even after tapping another NFC enabled
 *          devices. To enable this functionality, the client process should call @c setShareMode(bb::system::NfcShareMode::File,
 *          bb::system::NfcShareStartTransferMode::OnDemand) method before.
 *
 *          The client process can change the content type and "Start Transfer" mode at any time by calling @c setShareMode()
 *          with a new content type and new "Start Transfer" mode. If the new content type differs from the previous content type,
 *          any content that was previously set by a call to @c setShareContent() will be cleared. If "Start Transfer" mode was
 *          set to @c bb::system::NfcShareStartTransferMode::OnTap, new content must be set before any sharing can take place.
 *
 *          The client application can reset both the content type and the content to be shared using the @c reset() method.
 *
 *          The status of any sharing operations is obtained using the signals @c finished() and @c error(). The @c finished()
 *          signal is emitted when the operation was successful. The @c error() signal is emitted when the operation failed.
 *          Both signals include a parameter providing more detailed information.
 *
 *          @note You should create only one instance of @c %NfcShareManger per application. Each additional instance that
 *          you create receives events that are identical to the original, making their creation redundant. In addition, there
 *          are cases where an @c %NfcShareManger might try to access an event that has already been managed exclusively
 *          by another instance of the @c %NfcShareManger, which can cause the application to crash.
 *
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */

class BB_SYSTEM_EXPORT NfcShareManager: public QObject
{
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c NfcShareManager object.
     *
     * You should create only one instance of @c %NfcShareManger per application. Each additional instance that
     * you create receives events that are identical to the original, making their creation redundant. In addition, there
     * are cases where an @c %NfcShareManger might try to access an event that has already been managed exclusively
     * by another instance of the @c %NfcShareManger, which can cause the application to crash.
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit NfcShareManager(QObject *parent = 0);

    /*!
     * @brief Destroys this @c NfcShareManager object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~NfcShareManager();

    /*!
     * @brief Specifies file content to be shared over NFC.
     *
     * @details The current share mode must be set to @c bb::system::NfcShareMode::File for this
     * method to complete successfully.
     *
     * The supplied request must contain at least one file in its list of URLs.
     *
     * @param request A description of the file content to share.
     * @return Returns the result of the operation. See @c bb::system::NfcShareSetContentError for the list
     * of values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::NfcShareSetContentError::Type setShareContent(const NfcShareFilesContent &request);

    /*!
     * @brief Specifies data content to be shared over NFC.
     *
     * @details The current share mode must be set to @c bb::system::NfcShareMode::Data for this
     * method to complete successfully.
     *
     * @param request A description of the data content to share.
     * @return Returns the result of the operation. See @c bb::system::NfcShareSetContentError for the list
     * of values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::NfcShareSetContentError::Type setShareContent(const NfcShareDataContent &request);

    /*!
     * @brief Returns the current share mode for this NFC manager.
     *
     * @return Returns the current NFC share mode. See @c bb::system::NfcShareMode for the list of share modes.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::NfcShareMode::Type shareMode() const;

Q_SIGNALS:
    /*!
     * @brief Emitted when the share mode for this NFC manager changes.
     *
     *  @param mode The new share mode. See @c bb::system::NfcShareMode for the list of share modes.
     *
     * @since BlackBerry 10.0.0
     */
    void shareModeChanged(bb::system::NfcShareMode::Type mode);

    /*!
     * @brief Emitted when content is successfully shared via NFC.
     *
     * @param result More specific information on the successfully completed operation. See @c bb::system::NfcShareSuccess
     * for the list of values.
     *
     * @since BlackBerry 10.0.0
     */
    void finished(bb::system::NfcShareSuccess::Type result);

    /*!
     * @brief Emitted when an attempt to share content via NFC fails.
     *
     * @param error More specific information about the failure. See @c bb::system::NfcShareError for the list
     * of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    void error(bb::system::NfcShareError::Type error);

    /*!
     * @brief A connection handover was successfully established.
     *
     * @details This signal is only sent when "Start Transfer" mode from
     * @c bb::system::NfcShareManager::setShareMode() method is set to @c bb::system::NfcShareStartTransferMode::OnDemand.
     * This signal notifies the developer that they can now set the content to share and initiate file transfer by calling
     * @c bb::system::NfcShareManager::startTransfer() method.
     *
     * @note Currently this signal is only emitted when share mode is set to @c bb::system::NfcShareMode::File and
     * "Start Transfer" mode set to @c bb::system::NfcShareStartTransferMode::OnDemand in
     * @c bb::system::NfcShareManager::setShareMode() method.
     *
     * @since BlackBerry 10.2.0
     */
    void targetAcquired();

    /*!
     * @brief A target that was acquired during the last successful handover is discarded.
     *
     * @details This signal is only sent when "Start Transfer" mode from
     * @c bb::system::NfcShareManager::setShareMode() method is set to @c bb::system::NfcShareStartTransferMode::OnDemand.
     * This signal notifies the developer that there is no more targets to transfer data/files to and any attempt to initiate a file
     * transfer by calling @c bb::system::NfcShareManager::startTransfer() method will fail with @c bb::system::NfcShareError::NoTransferTarget
     * error.
     *
     * @since BlackBerry 10.2.0
     */
    void targetCancelled();


public Q_SLOTS:

    /*!
     * @brief Changes the share mode for this NFC manager.
     *
     * @details If the new mode is different than the previous mode, any content that was set by
     * a previous call to @c setShareContent() is cleared. If data/file sharing is in progress,
     * attempt to change Share Mode will fail and NFC Share Manager will deliver
     * @c bb::system::NfcShareError::TransferInProgress error.
     *
     * @note If this method is called, "Start Transfer" mode is set to @c bb::system::NfcShareStartTransferMode::OnTap
     * by default
     *
     * @param method The new share mode for this manager. See @c bb::system::NfcShareMode for
     * the list of share modes.
     *
     * @since BlackBerry 10.0.0
     */
    void setShareMode(bb::system::NfcShareMode::Type method);

    /*!
     * @brief Changes the share mode for this NFC manager.
     *
     * @details If the mode is being switched between different "File" and "Data" modes, any content
     * that was set by a previous call to @c setShareContent() is cleared. If data/file sharing is in progress,
     * attempt to change Share Mode and/or "Transfer On Tap" setting will have no effect and NFC Share Manager
     * will deliver @c bb::system::NfcShareError::TransferInProgress error
     *
     * @param method The new share mode for this manager. See @c bb::system::NfcShareMode for
     * the list of share modes.
     *
     * @param transferMode Specifies "Start Transfer" mode for this NFC manager for a given Share Mode.
     * When this option is set to @c bb::system::NfcShareStartTransferMode::OnTap, the share content being set by
     * @c bb::system::NfcShareManager::setShareContent() will be shared with the device being tapped
     * as soon as tap happens. When "Start Transfer" mode is set to @c bb::system::NfcShareStartTransferMode::OnDemand,
     * the share content WILL NOT be transferred to the device being tapped until @c bb::system::NfcShareManager::startTransfer()
     * method is called by developer. This option allows developer to prepare (and set) a content to share
     * AFTER the tap occurs. Currently, @c bb::system::NfcShareStartTransferMode::OnDemand option is supported for files only.
     *
     * @note When handover parameters are not specified, the most appropriate order of transports available will be used based
     * on the payload that shared content contains at the moment of tap
     *
     * @since BlackBerry 10.2.0
     */
    void setShareMode(bb::system::NfcShareMode::Type method,
                      bb::system::NfcShareStartTransferMode::Type transferMode);

    /*!
     * @brief Changes the share mode for this NFC manager.
     *
     * @details If the mode is being switched between different "File" and "Data" modes, any content
     * that was set by a previous call to @c setShareContent() is cleared. If data/file sharing is in progress,
     * attempt to change Share Mode and/or "Transfer On Tap" setting will have no effect and NFC Share Manager
     * will deliver @c bb::system::NfcShareError::TransferInProgress error
     *
     * @param method The new share mode for this manager. See @c bb::system::NfcShareMode for
     * the list of share modes.
     *
     * @param transferMode Specifies "Start Transfer" mode for this NFC manager for a given Share Mode.
     * When this option is set to @c bb::system::NfcShareStartTransferMode::OnTap, the share content being set by
     * @c bb::system::NfcShareManager::setShareContent() will be shared with the device being tapped
     * as soon as tap happens. When ""Start Transfer" mode is set to @c bb::system::NfcShareStartTransferMode::OnDemand,
     * the share content WILL NOT be transferred to the device being tapped until @c bb::system::NfcShareManager::startTransfer()
     * method is called by developer. This option allows developer to prepare (and set) a content to share
     * AFTER the tap occurs. Currently, @c bb::system::NfcShareStartTransferMode::OnDemand option is supported for files only.
     *
     * @param transports Specifies the list of the handover transports that should be used during handover negotiation. The order
     * is important as the transport specified first will be used as the most preferred transport during the handover negotiation process.
     *
     * @since BlackBerry 10.2.0
     */
    void setShareMode(bb::system::NfcShareMode::Type method,
                      bb::system::NfcShareStartTransferMode::Type transferMode,
                      const QList<bb::system::NfcShareHandoverTransport::Type>& transports);

    /*!
     * @brief Triggers the transfer of the shared content when "Start Transfer" mode was previously set to @c bb::system::NfcShareStartTransferMode::OnDemand
     *
     * @details Triggers the transfer of the shared content, "Start Transfer" mode was set to @c bb::system::NfcShareStartTransferMode::OnDemand.
     * As with @c bb::system::NfcShareManager::setShareMode(), the result of this call is obtained using the
     * signals @c finished() and @c error(). Developer should not be calling @c bb::system::NfcShareManager::startTransfer() method more than
     * once for every @c bb::system::NfcShareSuccess::TargetAcquired signal received when "Start Transfer" mode is set to
     * @c bb::system::NfcShareStartTransferMode::OnDemand. Currently, only the file transfer is supported. If data/file sharing is in progress,
     * attempt to call this method will result in @c bb::system::NfcShareError::TransferInProgress error
     * being delivered over @c bb::system::NfcShareError::error() signal
     *
     * @note If this method is called 20 sec after the tap occured, the transfer will fail as Bluetooth
     * pairing between two devices has timed out.
     *
     * @since BlackBerry 10.2.0
     */
    void startTransfer();

    /*!
     * @brief Cancels the target that was acquired as a result of the last successful handover.
     *
     * @details Discards the target that was acquired as a result of the last successful handover. This method should be used developer doesn't have
     * intention to start transfer to the recently acquired target. Cancellation of the target will result in clearing (resetting) the target acquired
     * as result of the latest tap.
     * Developer should not be calling @c bb::system::NfcShareManager::cancelTransfer() method more than
     * once for every @c bb::system::NfcShareSuccess::TargetAcquired signal received when "Start Transfer" mode is set to
     * @c bb::system::NfcShareStartTransferMode::OnDemand. This method will not cancel the target if the transfer is already in progress.
     * Successful execution of this command will emit targetCancelled() signal.
     *
     * @since BlackBerry 10.2.0
     */
    void cancelTarget();

    /*!
     * @brief Resets the state of this NFC manager.
     *
     * @details The share mode is reset to @c bb::system::NfcShareMode::Disabled. Any content set by a call
     * to @c setShareContent() is cleared.
     *
     * @since BlackBerry 10.0.0
     */
    void reset();

private:
//!@cond PRIVATE
    QScopedPointer<NfcShareManagerPrivate> const d_ptr;
    Q_DECLARE_PRIVATE(NfcShareManager)
    Q_DISABLE_COPY(NfcShareManager)
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHAREMANAGER_HPP */
