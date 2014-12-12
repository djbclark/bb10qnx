/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_HEADERDATAITEM_HPP_
#define BB_CASCADES_DATAMANAGER_HEADERDATAITEM_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataItem>
#include <QSharedPointer>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class HeaderDataItemPrivate;

/*!
 * @headerfile HeaderDataItem.hpp <bb/cascades/datamanager/HeaderDataItem>
 *
 * @brief Class representing a single header data item.
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
class BB_CASCADES_DATAMANAGER_EXPORT HeaderDataItem: public DataItem
{
public:
    /*!
     * @brief Constructor.
     *
     * @param keyId The Id for this item.
     * @param revision The revision for this item.
     * @param childCount The child count for this item.
     * @param payload The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem(const QString &keyId, const DataRevision& revision, int childCount, const QVariant& payload);

    /*!
     * @brief Constructor.
     *
     * @param data The data item to obtain key, revision, payload data from.
     * @param childCount The child count for this item.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem(const DataItem &data, int childCount);

    /*!
     * @brief Constructor.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem();

    /*!
     * @brief Copy constructor.
     *
     * @param other The @c HeaderDataItem object to copy. This follows the rules of implicit sharing.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem(const HeaderDataItem& other);

    /*!
     * @brief Assignment operator.
     *
     * @param other The @c HeaderDataItem object to assign from. This follows the rules of implicit sharing.
     * @return The revised @c HeaderDataItem instance.
     *
     * @since BlackBerry 10.2.0
     */
    HeaderDataItem& operator=(const HeaderDataItem& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~HeaderDataItem();

    /*!
     * @brief Set the child count for this header item.
     *
     * @param childCount The child count.
     *
     * @since BlackBerry 10.2.0
     */
    void setChildCount(int childCount);

    /*!
     * @brief Get the child count for this header item.
     *
     * @return The child count.
     *
     * @since BlackBerry 10.2.0
     */
    int childCount() const;

    /*!
     * @brief String representation of this header item.
     *
     * @return the string representation.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<HeaderDataItemPrivate> d;
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

Q_DECLARE_METATYPE(bb::cascades::datamanager::HeaderDataItem)

#endif /* BB_CASCADES_DATAMANAGER_HEADERDATAITEM_HPP_ */
