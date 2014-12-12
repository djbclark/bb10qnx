/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_QUERYDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_QUERYDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataQuery>
#include <bb/cascades/DataModel>
#include <QObject>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class QueryDataModelPrivate;

/*!
 * @headerfile QueryDataModel.hpp <bb/cascades/datamanager/QueryDataModel>
 *
 * @brief A data model that loads its data from a @c DataQuery.
 *
 * The @c QueryDataModel class is the base class for data models which
 * can use a @c DataQuery to allow them to query and load data.
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
class BB_CASCADES_DATAMANAGER_EXPORT QueryDataModel : public bb::cascades::DataModel
{
    Q_OBJECT

    /*!
     * @brief The data query to use for obtaining data.
     * Note: Ownership of the query object will be taken over by this model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::datamanager::DataQuery* query READ query WRITE setQuery NOTIFY queryChanged)

public:
    /*!
     * @brief Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit QueryDataModel(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~QueryDataModel();

    /*!
     * @brief Set the data query that this model will use to load data.
     *
     * Ownership of the query object will be taken over by this model.
     *
     * @param query The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void setQuery(bb::cascades::datamanager::DataQuery *query) = 0;

    /*!
     * @brief Get the data query for this model.
     *
     * The data model owns this pointer and will destroy it when the data
     * model is destroyed or the query is changed.
     *
     * @return The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bb::cascades::datamanager::DataQuery* query() = 0;

    /*!
     * @brief Loads data.
     *
     * After setting the data query and other properties, call this method
     * to load the data.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual void load() = 0;

Q_SIGNALS:
    /*!
     * @brief Emitted when the query has changed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void queryChanged();

    /*!
     * @brief Emitted when the DataModel is first loaded after calling the load method.
     *
     * The number of loaded signal may not equal to the number of load method call. But it is always
     * guaranteed that a load method call results in a loaded signal being emitted. For example, two
     * consecutive load method calls could results in only one loaded signal.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void loaded();

protected:
    /*! @cond PRIVATE */
    QueryDataModel(QueryDataModelPrivate &dd, QObject *parent = 0);
    QueryDataModelPrivate * const d_ptr;

    Q_DECLARE_PRIVATE(QueryDataModel)
    Q_DISABLE_COPY(QueryDataModel)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb


#endif /* BB_CASCADES_DATAMANAGER_QUERYDATAMODEL_HPP_ */
