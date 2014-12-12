/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_ASYNCHIERARCHICALDATAMODEL_HPP_
#define BB_CASCADES_DATAMANAGER_ASYNCHIERARCHICALDATAMODEL_HPP_

#include <bb/cascades/datamanager/Global>
#include  <bb/cascades/datamanager/AsyncDataModel>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class AsyncHierarchicalDataModelPrivate;

/*!
 * @headerfile AsyncHierarchicalDataModel.hpp <bb/cascades/datamanager/AsyncHierarchicalDataModel>
 *
 * @brief A data model that supports index paths with length greater than one.
 *
 * See the definition of index paths and how they are used in @c DataModel.
 *
 * The user needs to provide a HeaderDataQuery in order to populate the DataModel.
 * A HeaderDescriptor is needed to specify the structure of the header data
 * returned by HeaderDataQuery. This is done by extending this class and implementing
 * the pure virtual headerDescriptor() method of this class.
 *
 * Note that the header data from the HeaderDataQuery is cached in its full size
 * and used to refer to child data level (leaf) items. Only the data level items
 * are partially cached.
 *
 * @xmlonly
 * <qml>
 *    <class register="no" />
 * </qml>
 * <apigrouping group="Data Management"/>
 * <library name="bbcascadesdatamanager"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.2.0
 */
class BB_CASCADES_DATAMANAGER_EXPORT AsyncHierarchicalDataModel : public AsyncDataModel
{
Q_OBJECT
public:
    /*!
     * @brief HeaderDescriptor is used to describe the header data
     * returned by the HeaderDataQuery.
     *
     * @since BlackBerry 10.2.0
     */
    class BB_CASCADES_DATAMANAGER_EXPORT HeaderDescriptor {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~HeaderDescriptor();

        /*!
         * @brief The header child count of the index path.
         *
         * @param indexPath The index path.
         * @param headerData The header data used to get the child count of the
         * index path. Header data is return from the HeaderDataQuery.
         * @return The child count of the index path.
         *
         * @since BlackBerry 10.2.0
         */
        virtual int headerChildCount(const QVariantList &indexPath,
                                const QList<HeaderDataItem> &headerData) = 0;

        /*!
         * @brief The header data of the index path.
         *
         * @param indexPath The index path.
         * @param headerData The header data returned from the HeaderDataQuery.
         * @return The header data of the index path.
         *
         * @since BlackBerry 10.2.0
         */
        virtual HeaderDataItem headerData(const QVariantList &indexPath,
                                const QList<HeaderDataItem> &headerData) = 0;
    };

    /*!
     * @brief Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit AsyncHierarchicalDataModel(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~AsyncHierarchicalDataModel();

    /*!
     * @brief Get the header descriptor of the header DataModel.
     *
     * @return The header descriptor.
     *
     * @see HeaderContiguousCacheModel::HeaderDescriptor
     *
     * @since BlackBerry 10.2.0
     */
    virtual QSharedPointer<AsyncHierarchicalDataModel::HeaderDescriptor> headerDescriptor() const = 0;

protected:
    /*! @cond PRIVATE */
    AsyncHierarchicalDataModel(AsyncHierarchicalDataModelPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(AsyncHierarchicalDataModel);
    Q_DISABLE_COPY(AsyncHierarchicalDataModel)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_ASYNCHIERARCHICALDATAMODEL_HPP_ */
