/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_SQLHEADERDATAQUERY_HPP
#define BB_CASCADES_DATAMANAGER_SQLHEADERDATAQUERY_HPP

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/SqlDataQuery>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class SqlHeaderDataQueryPrivate;

/*!
 * @headerfile SqlDataQuery.hpp <bb/cascades/datamanager/SqlDataQuery>
 *
 * @brief The default HeaderDataQuery implementation that uses SQL selects to retrieve header and detail data.
 *
 * Headers and items are associated as follows:
 * - The query for headers must include a column named "count".  This represents
 * the count of items that belong to each header.  The sum of all "count"
 * properties should be equal to the total number of data items.
 * - The query for data must provide the data in an order that aligns with the headers.
 * - The headers and data are associated by grouping the data items into headers
 * based on the "count" properties of the headers.
 *
 * For example if the first header item has a count of 3, then the first three
 * data items will be grouped under this header.
 *
 * In implementing this class, the developer must make decisions
 * about how to handle error conditions. If there are SQL or other
 * expected or unexpected runtime errors, the developer must determine
 * which of these errors are catastrophic and which are recoverable.
 * See @c DataQuery class description for error handling guidelines.
 *
 * Here is a QML example showing the usage of an SqlHeaderDataQuery:
 * @snippet libbbcascadesdatamanager/examples/SqlHeaderDataQuery/assets/SqlHeaderDataQueryExamples.qml sqlheaderdataquery1
 *
 * Here is a C++ example showing the usage of an SqlHeaderDataQuery:
 * @snippet libbbcascadesdatamanager/examples/SqlHeaderDataQuery/src/SqlHeaderDataQueryExamples.cpp sqlheaderdataquery1
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
class BB_CASCADES_DATAMANAGER_EXPORT SqlHeaderDataQuery : public HeaderDataQuery
{
    Q_OBJECT

    /*!
     * @brief The source URL for the path to the local database. Mandatory.
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QUrl source READ source WRITE setSource)

    /*!
     * @brief The main SQL query statement. Mandatory.
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString query READ query WRITE setQuery)

    /*!
     * @brief Optional query used for improved performance when scrolling down.
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString scrollDownQuery READ scrollDownQuery WRITE setScrollDownQuery)

    /*!
     * @brief Optional query used for improved performance when scrolling up.
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString scrollUpQuery READ scrollUpQuery WRITE setScrollUpQuery)

    /*!
     * @brief The header data query for retrieving header items from the database. Mandatory.
     *
     * The query must include a numeric column named "count" or "count(*)" which identifies
     * the count of children for each header. The sum of these counts for all items
     * returned by the query must equal the total count for the data.
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString headerQuery READ headerQuery WRITE setHeaderQuery)

    /*!
     * @brief The name of the key column in the main query which is returned for each item.
     *
     * This key, if returned for each DataItem by the main query, will uniquely identify
     * the data item. It is used by the data model to signal listeners (usually an associated
     * list) that items have changed location or been deleted.
     *
     * Use of this property is optional. However, without keys, adding and deleting items in
     * the database may result in poor user interface visual updating.
     *
     * Once the property is set it cannot be changed.
     *
     * An example:
     *   The query:     "SELECT key_id, revision_id, lastname, firstname FROM contacts"
     *   The keyColumn: "key_id"
     *
     * @see DataItem
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString keyColumn READ keyColumn WRITE setKeyColumn)

    /*!
     * @brief The name of the revision column in the main query which is returned for each item.
     *
     * This revision, if returned for each DataItem by the main query, will identify the
     * current state of that item. It's used in conjunction with the overall revision.
     * When a database item is updated its revision should also be updated as well as the
     * overall database revision.
     *
     * It is used to determine when items must be updated in any cached data in memory.
     * Use of this property is optional. However, without item revisions, database changes
     * may not be reflected in the user interface in a timely manner.
     *
     * Once the property is set it cannot be changed.
     *
     * An example:
     *   The query:          "SELECT key_id, revision_id, lastname, firstname FROM contacts"
     *   The revisionColumn: "revision_id"
     *
     * @see DataItem
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString revisionColumn READ revisionColumn WRITE setRevisionColumn)

    /*!
     * @brief An SQL query statement which will return the total count of items.
     *
     * The property is mandatory when the query is being used in async models. It is
     * needed to obtain the total count of database items even when the model retains
     * only a partial cache in memory.
     *
     * An example:  "SELECT count(*) FROM contacts"
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString countQuery READ countQuery WRITE setCountQuery)

    /*!
     * @brief An SQL query statement to return the current overall revision for the source.
     *
     * This revision represents the current state of the database. It is used to ensure
     * that data for different database states is not mixed in memory. If the data model
     * determines that the overall revision of the data has changed then any cached data
     * is refreshed by querying the data source again.
     *
     * Use of this property is optional. However, without an overall revision, database
     * queries will always be a full refresh of the cache so that the data can be guaranteed
     * to be consistent.
     *
     * An example:  "SELECT revision_id FROM revision"
     *
     * Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QString revisionQuery READ revisionQuery WRITE setRevisionQuery)

    /*!
     * @brief A map of name-to-value bindings.
     *
     * This allows values to be inserted for named place holders in each
     * query statement. Once the property is set it cannot be changed.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(QVariantMap bindValues READ valuesToBind WRITE setValuesToBind)

public:
    /*!
     * @brief Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit SqlHeaderDataQuery(QObject *parent = 0);

    /*!
     * @brief Constructor.
     *
     * @param query The SQL data item query statement to use for this data query.
     * @param headerQuery The SQL header query statement to use for this data query.
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    SqlHeaderDataQuery(const QString &query, const QString &headerQuery, QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~SqlHeaderDataQuery();

    /*!
     * @brief Set the source url. Mandatory.
     *
     * @param source The source url.
     *
     * @since BlackBerry 10.2.0
     */
    void setSource(const QUrl& source);

    /*!
     * @brief Get the source.
     *
     * @return The source url.
     *
     * @since BlackBerry 10.2.0
     */
    QUrl source() const;

    /*!
     * @brief Set the query string. Mandatory.
     *
     * @param query The query string.
     *
     * @since BlackBerry 10.2.0
     */
    void setQuery(const QString& query);

    /*!
     * @brief Set the optional scrollDownQuery string used for improved performance when scrolling down.
     *
     * @param scrollDownQuery The query string to use when scrolling down.
     *
     * @since BlackBerry 10.2.0
     */
    void setScrollDownQuery(const QString& scrollDownQuery);

    /*!
     * @brief Set the optional scrollUpQuery string used for improved performance when scrolling up.
     *
     * @param scrollUpQuery The query string to use when scrolling up.
     *
     * @since BlackBerry 10.2.0
     */
    void setScrollUpQuery(const QString& scrollUpQuery);

    /*!
     * @brief Get the query.
     *
     * @return The query string.
     *
     * @since BlackBerry 10.2.0
     */
    QString query() const;

    /*!
     * @brief Get the optional scrollDownQuery string used when scrolling down.
     *
     * @return The scrollDownQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString scrollDownQuery() const;

    /*!
     * @brief Get the optional scrollUpQuery string used when scrolling up.
     *
     * @return The scrollUpQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString scrollUpQuery() const;

    /*!
     * @brief Set the SQL header query statement. Mandatory.
     *
     * @param query The SQL header query statement to use for this data query.
     *
     * @since BlackBerry 10.2.0
     */
    void setHeaderQuery(const QString &query);

    /*!
     * @brief Get the SQL header query statement.
     *
     * @return The SQL header query.
     *
     * @since BlackBerry 10.2.0
     */
    QString headerQuery() const;

    /*!
     * @brief Set the name of the key column in the main query.
     *
     * @param keyColumn The key column name.
     *
     * @since BlackBerry 10.2.0
     */
    void setKeyColumn(const QString& keyColumn);

    /*!
     * @brief Get the name of the key column in the main query.
     *
     * @return The keyColumn name.
     *
     * @since BlackBerry 10.2.0
     */
    QString keyColumn() const;

    /*!
     * @brief Set the name of the revision column in the main query.
     *
     * @param revisionColumn The revision column name.
     *
     * @since BlackBerry 10.2.0
     */
    void setRevisionColumn(const QString& revisionColumn);

    /*!
     * @brief Get the name of the revision column in the main query.
     *
     * @return The revisionColumn name.
     *
     * @since BlackBerry 10.2.0
     */
    QString revisionColumn() const;

    /*!
     * @brief Set the count query string.
     *
     * @param countQuery The count query string.
     *
     * @since BlackBerry 10.2.0
     */
    void setCountQuery(const QString& countQuery);

    /*!
     * @brief Get the count query.
     *
     * @return The countQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString countQuery() const;

    /*!
     * @brief Set the overall revision query string.
     *
     * @param revisionQuery The revision query string.
     *
     * @since BlackBerry 10.2.0
     */
    void setRevisionQuery(const QString& revisionQuery);

    /*!
     * @brief Get the revision query.
     *
     * @return The revisionQuery string.
     *
     * @since BlackBerry 10.2.0
     */
    QString revisionQuery() const;

    /*!
     * @brief Bind values to the queries by place holder name.
     *
     * This set of value bindings are used for all queries.
     *
     * @param nameValueMap a map of place holder name to value.
     *
     * @since BlackBerry 10.2.0
     */
    void setValuesToBind(const QVariantMap& nameValueMap);

    /*!
     * Retrieve the map of place holder name to value bindings.
     * This set of value bindings are used for all queries.
     *
     * @return map of place holder name to value.
     *
     * @since BlackBerry 10.2.0
     */
    QVariantMap valuesToBind() const;

    /*!
     * @brief Fetch the overall revision, total count and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     * This method will emit error() signal if the data could not be successfully retrieved due to
     * a query error, source not found or other unexpected condition.
     *
	 * See the discussion about error handling in the @c DataQuery class description.  A return of
	 * false by this method should be both:
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
            int *totalCount, QList<DataItem> *results);

    /*!
     * @brief Fetch the data items from the data source if the data source is at the request revision.
     *
     * This is a synchronous call, but it must be safe to call this method from any thread.
     * The error() signal will be emitted on any database and query related errors only.
     * It will not be emitted if the data source does not match the requested revision; instead
     * this method will just return false.
	 *
	 * See the discussion about error handling in the @c DataQuery class description.  A return of
	 * false by this method should be both:
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
     * If the data source does not match this revision, this method will fail and return false.
     * @param[out] results The list of data items which is the return data. Pointer must not be null.
     * @return Returns true if the data could be successfully retrieved at the requested revision,
     * else returns false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool getDataForRevision(int offset, int limit,
            const DataRevision& requestedRevision, QList<DataItem> *results);

    /*!
     * @brief Fetch the overall revision, total count, all header items and a range of data items from the data source.
     *
     * This is a synchronous call, but it must be possible to safely call this method from any thread.
     *
     * This method will emit error() signal and return false if the data could not be successfully
	 * retrieved due to a query error, source not found or other unexpected condition.
	 *
	 * See the discussion about error handling in the @c DataQuery class description.  A return of
	 * false by this method should be both:
     * - @c  preceeded by the query emitting an error signal
     * - @c  application-level handling of the error signal leading to some appropriate action
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
            int *totalCount, QList<DataItem> *results,
            QList<HeaderDataItem> *headerResults);

    /*!
     * @brief Get a string representation of the query, for debugging purposes.
     * @return The string.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

protected:
    /*! @cond PRIVATE */
    SqlHeaderDataQuery(SqlHeaderDataQueryPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(SqlHeaderDataQuery)
    Q_DISABLE_COPY(SqlHeaderDataQuery)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_SQLHEADERDATAQUERY_HPP */
