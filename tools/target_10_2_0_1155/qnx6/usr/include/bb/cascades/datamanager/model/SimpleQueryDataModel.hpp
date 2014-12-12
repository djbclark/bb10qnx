/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_SIMPLEQUERYDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_SIMPLEQUERYDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/QueryDataModel>
#include <bb/cascades/DataModel>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class SimpleQueryDataModelPrivate;

/*!
 * A simple data model that loads data from a DataQuery.
 *
 * This data model provides a flat list and does not support hierarchical
 * data.
 *
 * This data model supports automatic update notifications, but in a
 * very simplistic way: all updates force a full reload of the data, and
 * notify listeners of a full init each time.
 *
 * Here is a QML example showing the usage of an SimpleQueryDataModel:
 *
 * @snippet libbbcascadesdatamanager/examples/SimpleQueryDataModel/assets/SimpleQueryDataModelExamples.qml simplequerydatamodel1
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
class BB_CASCADES_DATAMANAGER_EXPORT SimpleQueryDataModel: public QueryDataModel
{
Q_OBJECT

public:
    /*!
     * Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit SimpleQueryDataModel(QObject *parent = 0);

    /*!
     * Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~SimpleQueryDataModel();

    /*!
     * @brief Call the method childCount of the DataModel being decorated.
     *
     * @param indexPath The path to the data item to get child count for.
     *
     * @return The number of children. The return value for invalid index paths is undefined.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual int childCount(const QVariantList &indexPath);

    /*!
     * @brief Call the method hasChildren of the DataModel being decorated.
     *
     * @param indexPath The path to the data item to query for children.
     *
     * @return @c true if the data item has one or more children, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual bool hasChildren(const QVariantList &indexPath);

    /*!
     * @brief Call the method itemType of the DataModel being decorated.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return a string identifying the type for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QString itemType(const QVariantList &indexPath);

    /*!
     * @brief Call the method data of the DataModel being decorated.
     *
     * @param indexPath The path to the item in the model.
     *
     * @return The data for this item.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual QVariant data(const QVariantList &indexPath);

    /*!
     * @brief Set the data query that this model will use to load data.
     *
     * Ownership of the query object will be taken over by this model.
     *
     * @param query The data query to use with this data model.
     *
     * @since BlackBerry 10.2.0
     */
    virtual void setQuery(bb::cascades::datamanager::DataQuery *query);

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
    virtual bb::cascades::datamanager::DataQuery* query();

    /*!
     * @brief Return the total count of the data items in the model.
     *
     * @return total count of items.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE int totalSize();

    /*!
     * @brief Loads data.
     *
     * After setting the data query and other properties, call this method
     * to load the data.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE virtual void load();

private:
    /*! @cond PRIVATE */
    Q_DECLARE_PRIVATE(SimpleQueryDataModel);
    Q_DISABLE_COPY(SimpleQueryDataModel);
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_SIMPLEQUERYDATAMODEL_HPP_ */
