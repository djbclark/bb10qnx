/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_CALL_HPP
#define BB_SYSTEM_PHONE_CALL_HPP

#include <bb/system/phone/CallState>
#include <bb/system/phone/CallType>
#include <bb/system/Global>

#include <QSharedDataPointer>

namespace bb
{
namespace system
{
namespace phone
{

class CallPrivate;


/*!
 * @headerfile Call.hpp <bb/system/phone/Call>
 *
 * @brief Provides a call's ID, state, and type information.
 *
 * When an outgoing call is initiated through a @c Phone object, an instance of this class will be returned to
 * represent the initiated call. If the @c isValid() function of the object returns @c true, the client of this object
 * can start to access other properties of the object.
 *
 * An instance of the @c Call class will also be provided through the @c Phone::callUpdated() signal
 * to provide information about an incoming call or update the state of an existing call.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * <qml>
 *     <class register="no"/>
 * </qml>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone permission in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT Call
{
public:
    /*!
     * @brief Constructs an invalid @c Call object.
     *
     * @since BlackBerry 10.0.0
     */
    Call();

    /*!
     * @brief Creates a copy of @c other.
     *
     * @param other The source @c Call object.
     *
     * @since BlackBerry 10.0.0
     */
    Call(const Call &other);

    /*!
     * @brief Copies another @c Call to this object.
     *
     * @param other The source @c Call object.
     * @return The @c Call instance.
     *
     * @since BlackBerry 10.0.0
     */
    Call& operator=(const Call &other);

    /*!
     * @brief Compares another @c Call to this object.
     *
     * @param other A @c Call object for comparison.
     * @return @c true if call id matches, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool operator==(const Call &other);

    /*!
     * @brief Destroys this @c Call object.
     *
     * @since BlackBerry 10.0.0
     */
    ~Call();

    /*!
     * @brief Returns the unique ID of the call.
     *
     * @return A non-negative ID of the call if the @c Call object is valid, or @c -1 if the object is invalid.
     *
     * @since BlackBerry 10.0.0
     */
    int callId() const;

    /*!
     * @brief Returns the state of the call, as defined by @c CallState::Type.
     *
     * @return The state of the call. If the @c Call object is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    CallState::Type callState() const;

    /*!
     * @brief Returns the type of the call, as defined by @c CallType::Type.
     *
     * @return The type of the call. If the @c Call object is invalid, the return value is undefined.
     *
     * @since BlackBerry 10.0.0
     */
    CallType::Type callType() const;

    /*!
     * @brief Indicates whether this object is valid or not. In general, the properties of this object should be
     * accessed only when the object is valid.
     *
     * @return @c true if this @c Call object contains valid information about a call, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    //!@cond PRIVATE
    friend class CallPrivate;

    QSharedDataPointer<CallPrivate> d_ptr;  /*!< private implementation */
    //!@endcond

//    Q_DECLARE_PRIVATE(Call)
//    Q_DISABLE_COPY(Call)
};

} // bb
} // system
} // phone

Q_DECLARE_METATYPE(bb::system::phone::Call)

#endif /* BB_SYSTEM_PHONE_CALL_HPP */
