/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_NFCSHARESTARTTRANSFERMODE_HPP
#define BB_SYSTEM_NFCSHARESTARTTRANSFERMODE_HPP

#include <bb/system/Global>

#include <QObject>

namespace bb
{
namespace system
{

/*!
 * @headerfile NfcShareStartTransferMode.hpp <bb/system/NfcShareStartTransferMode>
 *
 * @brief The list of supported modes for starting NFC Transfer
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/NFC"/>
 * <library name="bbsystem"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.2.0
 */
class BB_SYSTEM_EXPORT NfcShareStartTransferMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @brief The list of supported modes for starting NFC Transfer.
     */
    enum Type {
        /*!
         * @brief The transfer of specified NFC Share Content is performed automatically, when user taps
         * another NFC enabled device or NFC tag.
         */
        OnTap       = 0,

        /*!
         * @brief The transfer of specified NFC Share Content is performed when developer calls
         * @c bb::system::NfcShareManager::startTransfer().
         *
         * @note This mode allows developer to set a content to share after user taps another NFC enabled device,
         *       not before as in "onTap" mode. This mode might be useful when developer doesn't want to allocate
         *       resources to share in advance, when it is not clear if user would ever use NFC Share functionality
         *       at all.
         */
        OnDemand    = 1
    };

private:
//!@cond PRIVATE
    NfcShareStartTransferMode();
    ~NfcShareStartTransferMode();
//!@endcond
};
} // namespace system
} // namespace bb

#endif /* BB_SYSTEM_NFCSHARESTARTTRANSFERMODE_HPP */
