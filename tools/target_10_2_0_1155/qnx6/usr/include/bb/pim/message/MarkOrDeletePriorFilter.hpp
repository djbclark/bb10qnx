/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef MarkOrDeletePrior_HPP_
#define MarkOrDeletePrior_HPP_

#include <bb/pim/Global>
#include <bb/pim/account/Account>
#include <bb/pim/message/MarkOrDeletePriorOp>

#include <QSharedDataPointer>
#include <QHash>

namespace bb {
namespace pim {
namespace message {

class MarkOrDeletePriorFilterPrivate;

/*!
 * @brief The @c MarkOrDeletePriorFilter class lets you specify options and parameters for prior options.
 *
 * @details lets you specify options and parameters for prior options. You need to instantiate MarkOrDeletePriorFilter object
 * date prior, folder id and or options such MarkOrDeletePriorFilter::OperateOnFiledMessages or
 *  MarkOrDeletePriorFilter::OperateOnSentMessages (Note: These options do not apply, when you are specifying a folder id for folder operation).
 *  And then you need to pass this object to MessageService::markOrDeletePrior() function.
 *
 *
 * @see Message, MessageService, MarkOrDeletePriorOp
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT MarkOrDeletePriorFilter
{

public:

    /* @brief An enumeration of supported prior to Date operations for messages.
    *
    * @since BlackBerry 10.0.0
    */
    enum Options {
       /*!
       * @brief Indicates that the prior to date operations should apply to unread messages.
       * NOTE: This Option is not meant to be used for prior operations on search results.
        *
        * @since BlackBerry 10.0.0
       */
       OperateOnFiledMessages= 1 << 0,
       /*!
       * @brief Indicates that the prior to date operations should apply to flagged messages.
        * NOTE: This Option is not meant to be used for prior operations on search results.
        * @since BlackBerry 10.0.0
       */
       OperateOnSentMessages = 1 << 1
    };


    /*!
     * @brief Constructs a new @c MarkOrDeletePriorFilter.
     *
     * @since BlackBerry 10.0.0
     */
    MarkOrDeletePriorFilter();

    /*!
     * @brief Copy constructor.
     *
     * @details This function constructs a @c MarkOrDeletePriorFilter containing exactly the same values as
     * the provided @c %MarkOrDeletePriorFilter.
     *
     * @param other The @c %MarkOrDeletePriorFilter to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    MarkOrDeletePriorFilter(const MarkOrDeletePriorFilter &other);

    /*!
     * @brief Assignment operator.
     *
     * @details This operator copies all values from the provided @c MarkOrDeletePriorFilter into this
     * @c %MarkOrDeletePriorFilter.
     *
     * @param other The @c %MarkOrDeletePriorFilter from which to copy all values.
     *
     * @return A @c %MarkOrDeletePriorFilter with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    MarkOrDeletePriorFilter& operator=(const MarkOrDeletePriorFilter &other);

    /*!
     * @brief Destroys this @c MarkOrDeletePriorFilter.
     *
     * @since BlackBerry 10.0.0
     */
    ~MarkOrDeletePriorFilter();


    /*!
     * @brief Sets the folder ID of the message folder where operation is to be performed @c MarkOrDeletePriorFilter
     * applies to.
     *
     * @param folderId The folder where MarkPrior Or DeletePrior operation will be performed.
     *
     * @since BlackBerry 10.0.0
     */
    void setFolderId(MessageFolderKey folderId);

    /*!
     * @brief Sets the Date Time prior to which operation will be performed @c MarkOrDeletePriorFilter.
     *
     * @details This function sets the dateTime prior to which an operation has to be performed
     * this @c %MarkOrDeletePriorFilter.
     *
     * @param dateTime The date and time representing upperbound time limit on the bulk delete action,
     * expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format (for example, 2012-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    void setPriorDateTime(QDateTime& dateTime);

    /*!
     * @brief Adds a option Flags to this @c MarkOrDeletePriorFilter.
     *
     * @details For example, if you want perform action excluding filed messages, you should call this
     * function with a parameter of @c (getOptions() | MarkOrDeletePriorFilter::OperateOnFiledMessages) with parameter value
     *
     * @param value corresponding what all MarkOrDeletePriorFilter::Options are set
     *
     * @since BlackBerry 10.0.0
     */
    void setOptions(int value);

    /*!
     * @brief Gets the folder ID of the message folder where operation is to be performed @c MarkOrDeletePriorFilter
     * applies to.
     *
     * @since BlackBerry 10.0.0
     */
    MessageFolderKey getFolderId() const;

    /*!
     * @brief Gets the Date Time prior to which operation will be performed @c MarkOrDeletePriorFilter.
     *
     * @details This function gets the dateTime prior to which an operation is to be performed
     * This return a QString object expressed in yyyy-MM-dd hh:mm:ss.zzzzzz format
     * (for example, 2012-07-25 23:59:59.999999).
     *
     * @since BlackBerry 10.0.0
     */
    QString getPriorDateTime() const;
    /*!
     * @brief Gets all the options set set in form of integer
     *
     * @details For example, if you want check what all options have been set(e.g. if OperateOnFiledMessages options has been), you should call this
     * function and perform check of @c ((getOptions() & MarkOrDeletePriorFilter::OperateOnFiledMessages) != 0)
     *
     * @since BlackBerry 10.0.0
     */
    int getOptions() const;

    /*!
     * @brief Sets the priority inbox flag for search
     * @c MessageSearchFilter.
     *
     * @param isPriorityInboxSearch Set to true if only priority inbox emails are to be operated on.
     *
     * @since BlackBerry 10.2.0
     */
     void setPriorityInboxSearch(bool);

     /*!
      * @brief Gets the priority inbox flag  status for search
      * @c MessageSearchFilter.
      *
      * @return Return true if Priority Inbox Search flag was set to true earlier.
      *
      * @since BlackBerry 10.2.0
      */
     bool isPriorityInboxSearch() const;

private:
    QSharedDataPointer<MarkOrDeletePriorFilterPrivate> d_ptr;
};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */

#endif /* MarkOrDeletePriorFilter_HPP_ */
