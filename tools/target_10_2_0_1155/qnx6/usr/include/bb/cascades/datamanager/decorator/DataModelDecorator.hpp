/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_CASCADES_DATAMANAGER_DATAMODELDECORATOR_HPP_
#define BB_CASCADES_DATAMANAGER_DATAMODELDECORATOR_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/DataModel>
#include <QScopedPointer>


namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataModelDecoratorPrivate;

/*!
 * @headerfile DataModelDecorator.hpp <bb/cascades/datamanager/DataModelDecorator>
 *
 * @brief DataModelDecorator is used to decorate the DataModel before it is used by ListView.
 *
 * This base class merely delegates all DataModel method calls to the model being
 * decorated. It also connects the corresponding DataModel Q_SIGNALS to the model
 * being decorated.
 *
 * This class can be useful when we want to reinterpret the data before it is used by
 * ListView. For example, the @c itemType() method can return custom types depending on the
 * contents of the data. Or custom data columns can be added based on existing data when
 * the @c data() method is called.
 *
 * DataModelDecorator can be used to insert data too. The inserted data can be generated
 * from the existing data being decorated, or anything that does not have to be related
 * to the model being decorated.
 *
 * This class can serve the role of a View Model in the MVVM design pattern. See a
 * description of MVVM here - http://en.wikipedia.org/wiki/Model_View_ViewModel
 *
 * Here is a QML example showing the usage of a DataModelDecorator:
 *
 * @snippet libbbcascadesdatamanager/examples/DataModelDecorator/assets/DataModelDecoratorExamples.qml datamodeldecorator1
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
class BB_CASCADES_DATAMANAGER_EXPORT DataModelDecorator: public bb::cascades::DataModel
{
    Q_OBJECT

    /*!
     * @brief The model to be decorated.
     *
     * If the model has no parent, the DataModelDecorator takes ownership of it
     * and sets itself as parent to it. Any previously set DataModel is
     * unaffected by this call, its parent won't change and it won't be
     * deleted as a result of calling setModel().
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bb::cascades::DataModel *model READ model WRITE setModel NOTIFY modelChanged FINAL)

public:
    /*!
     * @brief Constructor.
     *
     * @param parent The parent owner or 0. Optional and will default to 0 if not specified.
     *
     * @since BlackBerry 10.2.0
     */
    explicit DataModelDecorator(QObject *parent = 0);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataModelDecorator();

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
     * @brief Get the DataModel being decorated.
     *
     * @return The DataModel being decorated
     *
     * @since BlackBerry 10.2.0
     */
    bb::cascades::DataModel* model();

    /*!
     * @brief Set the DataModel being decorated.
     *
     * If model has no parent, the DataModelDecorator takes ownership of it
     * and sets itself as parent to it. Any previously set DataModel is
     * unaffected by this call, its parent won't change and it won't be
     * deleted as a result of calling setModel().
     *
     * @param model The DataModel being decorated. Pointer must not be null.
     *
     * @since BlackBerry 10.2.0
     */
    void setModel(bb::cascades::DataModel *model);

    /*!
     * @brief Connect to the decorated model's itemAdded signal and forward the signal.
     *
     * @param indexPath The path to the item in the model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemAdded(QVariantList indexPath);

    /*!
     * @brief Connect to the decorated model's itemUpdated signal and forward the signal.
     *
     * @param indexPath The path to the item in the model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemUpdated(QVariantList indexPath);

    /*!
     * @brief Connect to the decorated model's itemRemoved signal and forward the signal.
     *
     * @param indexPath The path to the item in the model.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemRemoved(QVariantList indexPath);

    /*!
     * @brief Connect to the decorated model's itemsChanged signal and forward the signal.
     *
     * Emitted when the model has changed in a way that would be inefficient
     * to describe with single instances of the other signals.
     *
     * No other signals (@c DataModel::itemAdded, @c DataModel::itemUpdated,
     * or @c DataModel::itemRemoved) are emitted if this signal is emitted
     * when a change occurs in this @c DataModel.
     *
     * Typical examples of when this signal is emitted: data has been sorted (so
     * that many items have changed places), the @c %DataModel has been cleared
     * (all items have been removed), or a batch of items has been added.
     *
     * If @c eChangeType is @c DataModelChangeType::Init, or if @c eChangeType
     * is @c DataModelChangeType::AddRemove and @c indexMapper is @c 0, a
     * @c ListView reacts to this signal by releasing all of the items in its cache.
     *
     * If @c eChangeType is @c AddRemove and an @c IndexMapper is provided, the
     * @c %ListView instead calls @c IndexMapper::newIndexPath() for each item in its cache.
     *
     * If @c eChangeType is @c DataModelChangeType::Update, a @c %ListView reacts to
     * this signal by calling @c DataModel::data() again for every item in its
     * cache.
     *
     * @param eChangeType The type of change.
     * @param indexMapper An index mapper that contains update information.
     *
     * @since BlackBerry 10.2.0
     */
    Q_SLOT virtual void onItemsChanged(bb::cascades::DataModelChangeType::Type eChangeType = bb::cascades::DataModelChangeType::Init,
                QSharedPointer<bb::cascades::DataModel::IndexMapper> indexMapper =
                QSharedPointer<bb::cascades::DataModel::IndexMapper>(0));

Q_SIGNALS:
    /*!
     * @brief The DataModel being decorated has changed.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.2.0
     */
    void modelChanged();

private:
    /*! @cond PRIVATE */
    QScopedPointer<DataModelDecoratorPrivate> const d_ptr;

    Q_DECLARE_PRIVATE(DataModelDecorator)
    Q_DISABLE_COPY(DataModelDecorator)
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_DATAMODELDECORATOR_HPP_ */
