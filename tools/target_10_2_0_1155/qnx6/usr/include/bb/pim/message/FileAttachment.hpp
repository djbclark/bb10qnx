/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_FILE_ATTACHMENT_HPP
#define BB_PIM_MESSAGE_FILE_ATTACHMENT_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/Keys>

#include <QDateTime>
#include <QMetaType>
#include <QSharedPointer>
#include <QString>

namespace bb {
namespace pim {
namespace message {

class FileAttachmentPrivate;

/**
 * @brief The @c FileAttachment class represents a file attachment.
 *
 * @details This class includes information about a file attachment, such
 * as file path to the ( perhaps not yet ) downloaded attachment on the file
 * system, MIME type, and sender.
 *
 * You can retrieve the list of attachments by calling @c MessageService::attachments().
 *
 * You can download the attachment of a @c %Message by calling @c MessageService::downloadAttachment().
 *
 * Each @c %FileAttachment object has a key, which is represented by a @c FileAttachmentKey,
 * and this key uniquely identifies the file attachment.
 *
 * @see MessageService
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.2
 */
class BB_PIM_EXPORT FileAttachment
{
public:
    /*!
     * @brief Constructs an empty, invalid @c FileAttachment.
     *
     * @details This constructor may be used when returning a @c %FileAttachment by value to indicate
     * an error. When you use this constructor to create a @c %FileAttachment, the @c isValid() will
     * return @c false for the attachment.
     *
     * @since BlackBerry 10.0.2
     */
    FileAttachment();

    /*!
     * @brief Constructs a @c FileAttachment with the provided name, MIME type and download file path.
     *
     * @details This constructor creates a file attachment object with the provided name, MIME type and download file path.
     *
     * @param id             This attachment's id
     * @param accountId      The account id of this attachment
     * @param messageId      The message id of this attachment
     * @param conversationId The conversation id of this attachment
     * @param name           The name of this attachment
     * @param mimeType       The MIME type of this attachment
     * @param downloadPath   The path where this attachment is or would be downloaded to.
     *                       This is not the path that should be used to open or read the attachment, however.
     *                       You should instead open and read the attachment from the following path:
     *                       "/fs/pim/attachments/<accountId>/<messageId>/<id>/name".
     *                       The attachment will be downloaded if necessary before returning bytes.
     *
     * @since BlackBerry 10.0.2
     */
    FileAttachment(const bb::pim::message::AttachmentKey id,
                   const bb::pim::account::AccountKey accountId,
                   const bb::pim::message::MessageKey messageId,
                   const bb::pim::message::ConversationKey conversationId,
                   const QString &name,
                   const QString &mimeType,
                   const QString &downloadPath);

    /*!
     * @brief Constructs a @c FileAttachment from the provided private data.
     *
     * @param fileAttachmentPrivate The private data to construct the file attachment from.
     *
     * @since BlackBerry 10.0.2
     */
    FileAttachment(FileAttachmentPrivate *fileAttachmentPrivate);

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs an @c FileAttachment containing exactly the same values as the provided
     * @c %FileAttachment.
     *
     * @param other The @c %FileAttachment to be copied.
     *
     * @since BlackBerry 10.0.2
     */
    FileAttachment(const FileAttachment &other);

    /*!
     * @brief Destroys this @c FileAttachment.
     *
     * @details This function cleans up and frees the file attachment's data and resources.
     *
     * @since BlackBerry 10.0.2
     */
    ~FileAttachment();

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c FileAttachment into this @c %FileAttachment.
     *
     * @param other The @c %FileAttachment from which to copy all values.
     *
     * @return A @c %FileAttachment with all copied data.
     *
     * @since BlackBerry 10.0.2
     */
    FileAttachment &operator=(const FileAttachment &other);

    /*!
     * @brief Equality operator.
     *
     * @details This function indicates whether this @c FileAttachment has exactly the same values as the
     * provided @c %FileAttachment.
     *
     * @param other The @c %FileAttachment to compare values with.
     *
     * @return @c true if the file attachments are considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.2
     */
    bool operator==(const FileAttachment &other) const;

    /*!
     * @brief Inequality operator.
     *
     * @details This function indicates whether this @c FileAttachment does not have exactly the same values
     * as the provided @c %FileAttachment.
     *
     * @param other The @c %FileAttachment to compare values with.
     *
     * @return @c true if the file attachments are not considered equal, @c false otherwise.
     *
     * @since BlackBerry 10.0.2
     */
    bool operator!=(const FileAttachment &other) const;

    /*!
     * @brief Indicates whether this @c FileAttachment is valid.
     *
     * @return @c true if this @c %FIleAttachment is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.2
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the file attachment ID of this @c FileAttachment.
     *
     * @details This function returns the ID that's associated with the file attachment.
     *
     * @return The file attachment's ID.
     *
     * @since BlackBerry 10.0.2
     */
    bb::pim::message::AttachmentKey id() const;

    /*!
     * @brief Retrieves the account ID of this @c FileAttachment.
     *
     * @details This function returns the account ID that's associated with the file attachment.
     *
     * @return The file attachment's account ID.
     *
     * @since BlackBerry 10.0.2
     */
    bb::pim::account::AccountKey accountId() const;

    /*!
     * @brief Retrieves the message ID of this @c FileAttachment.
     *
     * @details This function returns the message ID that's associated with the file attachment.
     *
     * @return The file attachment's message ID.
     *
     * @since BlackBerry 10.0.2
     */
    bb::pim::message::MessageKey messageId() const;

    /*!
     * @brief Retrieves the conversation ID of this @c FileAttachment.
     *
     * @details This function returns the conversation ID that's associated with the file attachment.
     *
     * @return The file attachment's conversation ID.
     *
     * @since BlackBerry 10.0.2
     */
    bb::pim::message::ConversationKey conversationId() const;

    /*!
     * @brief Retrieves the name of this @c FileAttachment.
     *
     * @return The file attachment's name.
     *
     * @since BlackBerry 10.0.2
     */
    QString name() const;

    /*!
     * @brief Retrieves the MIME type of this @c FileAttachment.
     *
     * @return The file attachment's MIME type.
     *
     * @since BlackBerry 10.0.2
     */
    QString mimeType() const;

    /*!
     * @brief Retrieves the file path of this @c FileAttachment on the file system.
     *
     * @details This function returns the path to the file attachment's data as a URL using the @c file://
     * schema.  Accessing this path will cause the attachment to first be downloaded if it hasn't been already.
     *
     * @return The file attachment's path as a @c file:// URL.
     *
     * @since BlackBerry 10.0.2
     */
    QString fullPath() const;

    /*!
     * @brief Retrieves the download path to the @c FileAttachment on the file system.
     *
     * @details This function returns the path to the file attachment's data as a URL using the @c file://
     * schema.  This path is empty if the attachment hasn't yet been downloaded.
     *
     * @return The file attachment's download path as a @c file:// URL.
     *
     * @since BlackBerry 10.0.2
     */
    QString downloadPath() const;

    /*!
     * @brief Retrieves the sender of this @c FileAttachment.
     *
     * @return The file attachment's sender.
     *
     * @since BlackBerry 10.0.2
     */
    QString sender() const;

    /*!
     * @brief Retrieves the date that this @c FileAttachment was sent.
     *
     * @return The file attachment's sent date.
     *
     * @since BlackBerry 10.0.2
     */
    QDateTime date() const;

    /*!
     * @brief Retrieves the total size (in bytes) of this @c FileAttachment.
     *
     * @return The file attachment's total size (in bytes).
     *
     * @since BlackBerry 10.0.2
     */
    int totalSize() const;

    /*!
     * @brief Retrieves the available size (in bytes) of this @c FileAttachment.
     *
     * @details This function returns the available size (in bytes) of the file attachment. The available
     * size is typically the same as the total size but may be different for some services. For example,
     * the messaging service uses the available size to determine how much of the file attachment has actually
     * been downloaded.
     *
     * @return The file attachment's available size (in bytes).
     *
     * @since BlackBerry 10.0.2
     */
    int availableSize() const;

private:
    QSharedPointer<FileAttachmentPrivate> d_ptr;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

Q_DECLARE_METATYPE(bb::pim::message::FileAttachment)

#endif // BB_PIM_MESSAGE_FILE_ATTACHMENT_HPP
