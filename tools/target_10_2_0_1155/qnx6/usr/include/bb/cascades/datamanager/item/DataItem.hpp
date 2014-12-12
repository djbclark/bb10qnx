/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_DATAITEM_HPP_
#define BB_CASCADES_DATAMANAGER_DATAITEM_HPP_

#include <bb/cascades/datamanager/Global>
#include <bb/cascades/datamanager/DataRevision>
#include <QDebug>
#include <QSharedDataPointer>
#include <QString>
#include <QVariant>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class DataItemPrivate;

/*!
 * @headerfile DataItem.hpp <bb/cascades/datamanager/DataItem>
 *
 * @brief Class representing a single item of data in the result set.
 *
 * This is a Qt value object which supports implicit data sharing.
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
class BB_CASCADES_DATAMANAGER_EXPORT DataItem
{
public:
    /*!
     * @brief Constructor.
     *
     * @param keyId The Id for this item.
     * @param revision The revision for this item.
     * @param payload The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem(const QString &keyId, const DataRevision& revision, const QVariant& payload);

    /*!
     * @brief Constructor.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem();

    /*!
     * @brief Copy constructor.
     *
     * @param other The @c DataItem object to copy. This follows the rules of implicit sharing.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem(const DataItem& other);

    /*!
     * @brief Assignment operator.
     *
     * @param other The @c DataItem object to assign from. This follows the rules of implicit sharing.
     * @return The revised @c DataItem instance.
     *
     * @since BlackBerry 10.2.0
     */
    DataItem& operator=(const DataItem& other);

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~DataItem();

    /*!
     * @brief Set the Id for this item.
     *
     * This value must uniquely identify this item in the data source across data updates.
     *
     * @param keyId The Id for this item.
     *
     * @since BlackBerry 10.2.0
     */
    void setKeyId(const QString &keyId);

    /*!
     * @brief Get the Id for this item.
     *
     * This value must uniquely identify this item in the data source across data updates.
     *
     * @return The Id.
     *
     * @since BlackBerry 10.2.0
     */
    QString keyId() const;

    /*!
     * @brief Set the revision value for this item.
     *
     * This value must uniquely identify a discreet state of this item in the data source,
     * including the states of all of the items properties.
     *
     * @param revision The revision for this item.
     *
     * @since BlackBerry 10.2.0
     */
    void setRevision(const DataRevision& revision);

    /*!
     * @brief Get the revision value for this item.
     *
     * This value must uniquely identify a discreet state of this item in the data source,
     * including the states of all of the items properties.
     *
     * @return The revision.
     *
     * @since BlackBerry 10.2.0
     */
    DataRevision revision() const;

    /*!
     * @brief Set the data payload for this item.
     *
     * @param payload The data payload for this item.
     *
     * @since BlackBerry 10.2.0
     */
    void setPayload(const QVariant &payload);

    /*!
     * @brief Get the data payload for this item.
     *
     * @return The data payload.
     *
     * @since BlackBerry 10.2.0
     */
    QVariant payload() const;

    /*!
     * @brief String representation of this data item.
     *
     * @return the string representation.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const;

private:
    /*! @cond PRIVATE */
    QSharedDataPointer<DataItemPrivate> d;
    /*! @endcond */
};

QDebug operator<<(QDebug dbg, const DataItem &item);

} // datamanager
} // cascades
} // bb

Q_DECLARE_METATYPE(bb::cascades::datamanager::DataItem)

#endif /* BB_CASCADES_DATAMANAGER_DATAITEM_HPP_ */
