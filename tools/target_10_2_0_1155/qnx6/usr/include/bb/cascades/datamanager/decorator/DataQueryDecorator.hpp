/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAQUERYDECORATOR_HPP_
#define BB_CASCADES_DATAMANAGER_DATAQUERYDECORATOR_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/HeaderDataQuery>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataQueryDecoratorPrivate;

/*!
 * @headerfile DataQueryDecorator.hpp <bb/cascades/datamanager/DataQueryDecorator>
 *
 * @brief A @c DataQuery wrapper that can be used to extend the behaviour of existing queries.
 *
 * To use just override the @c processResults() or @c processHeaderResults() method(s) and
 * modify the data prior to it being returned by the underlying query.
 *
 * Here is a QML example showing the usage of a DataQueryDecorator:
 *
 * @snippet libbbcascadesdatamanager/examples/DataQueryDecorator/assets/DataQueryDecoratorExamples.qml dataquerydecorator1
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
class BB_CASCADES_DATAMANAGER_EXPORT DataQueryDecorator : public HeaderDataQuery
{
    Q_OBJECT

    /*!
     * @brief The query to be decorated. This decorator takes ownership of the query.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::datamanager::DataQuery *query READ query WRITE setQuery NOTIFY queryChanged)

public:
    /*!
     * @brief Constructor.
     *
     * @param query The query to be decorated. This decorator takes ownership of the query.
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataQueryDecorator(DataQuery* query, QObject *parent = 0);

    /*!
     * @brief Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataQueryDecorator(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataQueryDecorator();

    /*!
     * @brief Fetch the overall revision, total count and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * This method will emit error() signal if the data could not be successfully retrieved due to
     * a query error, source not found or other unexpected condition.
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
            int *totalCount, QList<DataItem> *results);

    /*!
     * @brief Fetch the data items from the data source if the data source is at the request revision.
     *
     * This is a synchronous call, but it must be safe to call this method from any thread.
     * The error() signal will be emitted on any database and query related errors only.
     * It will not be emitted if the data source does not match the requested revision; instead
     * this method will just return false.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param requestedRevision The requested revision id for the data source.
     * If the data source does not match this revision, this method will fail and return false.
     * @param[out] results The list of data items which is the return data. Pointer must not be null.
     * @return Returns true if the data could be successfully retrieved at the requested revision,
     * else returns false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getDataForRevision(int offset, int limit,
            const DataRevision &requestedRevision, QList<DataItem> *results);

    /*!
     * @brief Fetch the overall revision, total count, all header items and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * This method will emit error() signal if the data could not be successfully retrieved.
     *
     * @param offset The index offset within the view.
     * @param limit The number of items to retrieve.
     * @param[out] revision the current revision of the data source. Pointer must not be null.
     * @param[out] totalCount The total number of items in the view. Pointer must not be null.
     * @param[out] results The requested  items. Pointer must not be null.
     * @param[out] headerResults The header  items of the query. Pointer must not be null.
     *
     * @return true if it can fetch  from the revision, otherwise false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getHeaderData(int offset, int limit, DataRevision *revision,
            int *totalCount, QList<DataItem> *results, QList<HeaderDataItem> *headerResults);

    /*!
     * @brief Set the query to be decorated.
     *
     * Note that this decorator takes ownership of the query.
     *
     * @param query The query. Pointer must not be null.
     *
     * @since BlackBerry 10.2.0
     */
    void setQuery(bb::cascades::datamanager::DataQuery *query);

    /*!
     * @brief Get the delegate query.
     *
     * Note that the query is owned by the decorator and will be destroyed when the decorator is destroyed.
     *
     * @return The query.
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::datamanager::DataQuery *query() const;

    /*!
     * @brief Get a string representation of the query, for debugging purposes.
     *
     * @return The string.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

protected:
    /*!
     * @brief Override this function to modify the detail data before its returned to the model.
     *
     * @param[in,out] results The data items fetched by the query.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void processResults(QList<DataItem> *results);

    /*!
     * @brief Override this function to modify the header data before its returned to the model.
     *
     * @param[in,out] headerResults The header items fetched by the query.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void processHeaderResults(QList<HeaderDataItem> *headerResults);

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
     * @brief The query being decorated has changed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void queryChanged();

protected:
    /*! @cond PRIVATE */
    DataQueryDecorator(DataQueryDecoratorPrivate &dd, QObject *parent = 0);

    Q_DECLARE_PRIVATE(DataQueryDecorator)
    Q_DISABLE_COPY(DataQueryDecorator)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAQUERYDECORATOR_HPP_ */
