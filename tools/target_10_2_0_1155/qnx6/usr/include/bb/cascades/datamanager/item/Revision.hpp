/*!
 * @copyright
 * Copyright Research In Motion Limited, 2013-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CASCADES_DATAMANAGER_REVISION_HPP_
#define BB_CASCADES_DATAMANAGER_REVISION_HPP_

#include <bb/cascades/datamanager/Global>
#include <QScopedPointer>

namespace bb
{
namespace cascades
{
namespace datamanager
{

class RevisionPrivate;

/*!
 * @headerfile Revision.hpp <bb/cascades/datamanager/Revision>
 *
 * @brief Interface for objects that can be compared, in order to determine
 * whether the associated data has changed.
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
class BB_CASCADES_DATAMANAGER_EXPORT Revision
{
public:
    /*!
     * @brief Constructor.
     *
     * @since BlackBerry 10.2.0
     */
    Revision();

    /*!
     * @brief Destructor.
     *
     * @since BlackBerry 10.2.0
     */
    virtual ~Revision();

    /*!
     * @brief Check for equality.
     *
     * @param other the revision to compare against.
     * @return true if the revisions are equal, else false.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool equals(const Revision &other) const = 0;

    /*!
     * @brief Check whether this revision is greater (newer) than the other.
     *
     * @param other the revision to compare against.
     * @return true if this object is greater (newer) than the given object.
     *
     * @since BlackBerry 10.2.0
     */
    virtual bool greaterThan(const Revision &other) const = 0;

    /*!
     * @brief Return a new revision based on this revision and another revision.
     *
     * The revision that is returned should be greater than or equal to both
     * this revision object, and @c other.
     *
     * @param other Another revision provider.
     *
     * @return A pointer to the newly created Revision object.
     *
     * @since BlackBerry 10.2.0
     */
    virtual Revision* newRevision(const Revision &other) const = 0;

    /*!
     * @brief String representation of this revision for debugging.
     *
     * @return the string representation.
     *
     * @since BlackBerry 10.2.0
     */
    virtual QString toString() const = 0;

protected:
    /*! @cond PRIVATE */
    Revision(RevisionPrivate &dd);
    // for future use
    QScopedPointer<RevisionPrivate> d_ptr;
    /*! @endcond */
};

} // datamanager
} // cascades
} // bb

#endif /* BB_CASCADES_DATAMANAGER_REVISION_HPP_ */
