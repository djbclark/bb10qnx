/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAQUERY_HPP_
#define BB_CASCADES_DATAMANAGER_DATAQUERY_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataItem>
#include <QDebug>
#include <QObject>
#include <QVariant>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataQueryPrivate;

/*!
 * @headerfile DataQuery.hpp <bb/cascades/datamanager/DataQuery>
 *
 * @brief Retrieve data for a particular view of a data source.
 *
 * This supports concepts like keys, overall revisions, item revisions
 * and partial caching (using offset and limit) so that data models
 * can use this to maintain a window of data in memory (the cache)
 * consistent with a potentially much larger overall set of data
 * in persistent storage.
 *
 * In implementing this class, the developer must make decisions
 * about how to handle error conditions. If there are SQL or other
 * expected or unexpected runtime errors, the developer must determine
 * which of these errors are catastrophic and which are recoverable.
 *
 * Catastrophic errors can be dealt with by these steps:
 * - @c  Connect the application to the data query error signal
 * - @c  Query issues an error signal and returns false
 * - @c  Application detects that the error is unrecoverable
 * - @c  Application informs the users of the issue and remedies (if any)
 * - @c  User is instructed to terminate the application
 *
 * Recoverable errors may be dealt with in a few ways. It may depend
 * on whether the data is required or optional for the application to
 * function. It may depend on whether retries might be effective, either
 * immediately, after a certain elapsed timed or when the user wishes
 * to trigger a retry.
 *
 * For Query-handled recoverable errors, the steps may look like this:
 * - @c  Query detects an error and performs a finite number (N) of retries
 * - @c  If retry is successful then query returns true
 * - @c  If N retries fail then query emits an error and returns false
 * - @c  Application informs the users of the issue and remedies (if any)
 * - @c  User is instructed to ignore the error (if optional data) or to
 *    terminate the application
 *
 * For Application-handled recoverable errors, the steps may look like this:
 * - @c  Connect the application to the data query error signal
 * - @c  Query issues an error signal and returns false
 * - @c  Application detects that the error is recoverable
 * - @c  Application informs the users of the issue and remedies (if any)
 * - @c  User is instructed to initiate retries or ignore the error (if optional data)
 *    or to terminate the application
 *
 * To trigger a retry for a recoverable error use one of these methods:
 * - @c  Emit the DataQuery::dataChanged(Revision) signal.
 * - @c  Call the model load() method.
 *
 * @xmlonly
 * <qml>
 *    <class register="yes" />
 * </qml>
 * <apigrouping group="Data Management"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT DataQuery : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataQuery(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataQuery();

    /*!
     * @brief Fetch the overall revision, total count and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
	 *
	 * See the discussion about error handling in the class description.  A return of false by this
     * method should be both:
     * - @c  preceeded by the query emitting an error signal
     * - @c  application-level handling of the error signal leading to some appropriate action
	 *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision the current revision of the data source. The revision value must match
     * the state of the data items that are returned. Pointer must not be null.
	 * @param[out] totalCount The total number of items in the view. Pointer must not be null.
     * @param[out] results The list of data items which is the return data. Pointer must not be null.
     * @return Returns true if the data could be successfully retrieved, else returns false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results) = 0;

    /*!
     * @brief Fetch the data items from the data source if the data source is at the request revision.
     *
     * This is a synchronous call, but it must be safe to call this method from any thread.
     *
	 * See the discussion about error handling in the class description.  A return of false by this
     * method should be both:
     * - @c  preceeded by the query emitting an error signal
     * - @c  application-level handling of the error signal leading to some appropriate action
	 *
	 * IMPORTANT NOTE:
	 * The return of false by this method is always expected and never a catastrophic error since
	 * false is returned when the data source does not match the requested revision. The error() signal
	 * should be emitted on database and query related errors only.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param requestedRevision The requested revision id for the data source.
     * If the data source does not match this revision, this method will return false.
     * @param[out] results The list of data items which is the return data. Pointer must not be null.
     * @return Returns true if the data could be successfully retrieved at the requested revision,
     * else returns false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getDataForRevision(int offset, int limit,
            const DataRevision &requestedRevision, QList<DataItem> *results) = 0;

    /*!
     * @brief Get a string representation of the query, for debugging purposes.
     *
     * @return The string.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const = 0;

Q_SIGNALS:
    /*!
     * @brief Signal for data changes.
     *
     * @param revision the revision of the latest source data.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void dataChanged(DataRevision revision);

    /*!
     * @brief Signal for error when executing the query.
     *
     * @param code the error code
     * @param message the error message
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void error(int code, const QString& message);

protected:
    /*! @cond PRIVATE */
    DataQuery(DataQueryPrivate &dd, QObject *parent = 0);
    DataQueryPrivate * const d_ptr;

    Q_DECLARE_PRIVATE(DataQuery)
    Q_DISABLE_COPY(DataQuery)
    /*! @endcond */
};

QDebug operator<<(QDebug dbg, const DataQuery *p);

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAQUERY_HPP_ */
