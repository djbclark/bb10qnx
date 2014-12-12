/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_MESSAGE_CONVERSATION_HPP
#define BB_PIM_MESSAGE_CONVERSATION_HPP

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/ConversationStatus>
#include <bb/pim/message/Folder>
#include <bb/pim/message/Message>
#include <bb/pim/message/MessageContact>

#include <QDateTime>
#include <QSharedPointer>

namespace bb {
namespace pim {
namespace message {

class ConversationPrivate;
class ConversationUpdate;

/*!
 * @headerfile Conversation.hpp <bb/pim/message/Conversation>
 *
 * @brief The @c Conversation class represents a conversation between message recipients.
 * 
 * @details A conversation is a set of related messages between recipients. By using the
 * @c %Conversation class, you can retrieve information such as conversation subject,
 * participants, and the most recent message in the conversation. You can use this
 * information to display a conversation in a custom interface that you create yourself
 * (for example, an interface that's similar to BBM).
 * 
 * You can also use the @c MessageService to retrieve conversation information. For
 * example, you can retrieve a list of conversations by calling
 * @c MessageService::conversations(), or retrieve a list of just conversation IDs by
 * calling @c MessageService::conversationKeys().
 * 
 * @see MessageService, Message
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT Conversation
{
public:
    /*!
     * @brief Constructs a new @c Conversation.
     *
     * @since BlackBerry 10.0.0
     */
    Conversation();

    /*!
     * @brief Destroys this @c Conversation.
     *
     * @since BlackBerry 10.0.0
     */
    ~Conversation();

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs a @c Conversation containing exactly the same values as
     * the provided @c %Conversation.
     * 
     * @param other The @c %Conversation to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    Conversation(const Conversation &other);

    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c Conversation into this
     * @c %Conversation.
     * 
     * @param other The @c %Conversation from which to copy all values.
     *
     * @return A @c %Conversation with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    Conversation &operator=(const Conversation &other);

    /*!
     * @brief Constructs a @c Conversation with the provided private conversation information.
     * 
     * @details This constructor creates a @c %Conversation by using a @c d_ptr to private
     * conversation information.
     * 
     * @param conversationPrivate The private conversation information to use.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Conversation(ConversationPrivate* conversationPrivate);

    /*!
     * @brief Indicates whether this @c Conversation is valid.
     * 
     * @return @c true if this @c %Conversation is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

    /*!
     * @brief Retrieves the ID of this @c Conversation.
     *
     * @details This ID is unique per account.
     *
     * @return The conversation's ID.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationKey id() const;

    /*!
     * @brief Retrieves the account ID of this @c Conversation.
     * 
     * @details You can use this ID to determine which account the conversation belongs to.
     *
     * @return The conversation's account ID.
     *
     * @since BlackBerry 10.0.0
     */
    bb::pim::account::AccountKey accountId() const;

    /*!
     * @brief Retrieves the list of folder IDs for this @c Conversation.
     * 
     * @details The folder IDs are based on the folder ID of each message in the conversation
     * (in no particular order).
     *
     * For example, consider a conversation that consists of messages from the following folders:
     * - inbox
     * - inbox
     * - sent
     * - inbox
     *
     * In this case, this function returns a @c QList with two folder IDs: inbox and sent.
     *
     * @return The conversation's folder IDs.
     *
     * @since BlackBerry 10.0.0
     */
    QList<FolderKey> folderIds() const;

    /*!
     * @brief Retrieves the ID of the most recent message in this @c Conversation.
     *
     * @return The ID of the most recent message in the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    MessageKey latestMessageId() const;

    /*!
     * @brief Retrieves the source ID of this @c Conversation.
     * 
     * @details This ID is the identifier that's supplied by the provider of the conversation.
     *
     * @return The conversation's source ID.
     *
     * @since BlackBerry 10.0.0
     */
    QString sourceId() const;


    /*!
     * @brief Retrieves the raw transmission status of this @c Conversation.
     * 
     * @details Note that this is the status of the latest message in the conversation,
     * coming from the data store.
     *
     * @return The conversation's raw transmission status.
     *
     * @since BlackBerry 10.0.0
     */
    long transmissionStatus() const;

    /*!
     * @brief Retrieves the subject of this @c Conversation.
     *
     * @return The conversation's subject.
     *
     * @since BlackBerry 10.0.0
     */
    QString subject() const;

    /*!
     * @brief Retrieves a list of the participants in this @c Conversation.
     *
     * @return A list of the conversation's participants.
     *
     * @since BlackBerry 10.0.0
     */
    QList<MessageContact> participants() const;

    /*!
     * @brief Retrieves the number of messages in this @c Conversation.
     *
     * @return The number of messages in the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    int messageCount() const;

    /*!
     * @brief Retrieves the number of unread messages in this @c Conversation.
     *
     * @return The number of unread messages in the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    int unreadMessageCount() const;

    /*!
     * @brief Retrieves a bitmask representing the status of this @c Conversation.
     * 
     * @details The @c ConversationStatus class includes the possible flags for the status
     * of a conversation.
     *
     * @return A bitmask representing the status of the conversation.
     *
     * @since BlackBerry 10.0.0
     */
    ConversationStatus::Types status() const;

    /*!
     * @brief Retrieves the name of this @c Conversation.
     *
     * @return The conversation's name.
     *
     * @since BlackBerry 10.0.0
     */
    QString name() const;

    /*!
     * @brief Retrieves the timestamp of this @c Conversation.
     *
     * @return The conversation's timestamp.
     *
     * @since BlackBerry 10.0.0
     */
    QDateTime timeStamp() const;

    /*!
     * @brief Retrieves the summary of this @c Conversation.
     *
     * @return The conversation's summary.
     *
     * @since BlackBerry 10.0.0
     */
    QString summary() const;

    /*!
    * @brief Retrieves the MIME type of this @c Conversation.
    *
    * @return The conversation's MIME type, as a @c QString.
     *
     * @since BlackBerry 10.0.0
    */
    QString mimeType() const;

    /*!
     * @brief Applies the provided conversation update to this @c Conversation.
     *
     * @details This update is triggered by user interaction such as reading or flagging
     * a message in the conversation. The @c ConversationUpdate class includes information
     * for a particular update of a conversation.
     * 
     * @param data The conversation update to apply.
     *
     * @since BlackBerry 10.0.0
     */
    void apply(const ConversationUpdate &data);

    /*!
	 * @brief Indicates whether this @c Conversation should be in the priority inbox.
	 *
	 * @details You can use this function to determine whether or not a conversation that's returned
	 * from the message service should be in the priority inbox.
	 *
	 * @return @c true if this @c Conversation should be in the priority inbox, @c false otherwise.
	 */
	bool isPriorityInbox() const;

private:
    QSharedPointer<ConversationPrivate> d_ptr;

    friend class ConversationPrivate;
};

} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif // BB_PIM_MESSAGE_CONVERSATION_HPP
