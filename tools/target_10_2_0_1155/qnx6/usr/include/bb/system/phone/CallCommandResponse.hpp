/*!
 * @file CallCommandResponse.hpp
 * @copyright Copyright (C) Research In Motion Limited 2013. All rights reserved.
 */


#ifndef BB_SYSTEM_PHONE_CALLCOMMANDRESPONSE_HPP
#define BB_SYSTEM_PHONE_CALLCOMMANDRESPONSE_HPP

#include <bb/system/Global>

#include <QSharedDataPointer>

namespace bb
{
namespace system
{
namespace phone
{

class CallCommandResponsePrivate;

/*!
 * @headerfile CallCommandResponse.hpp <bb/system/phone/Call>
 *
 * @brief Provides information on a call command response: call command, response ID, call ID, command error, and error description.
 *
 * An instance of the @c CallCommandResponse class will be provided through the @c Phone::callCommandResponseReceived() signal
 * to deliver information to the client about the network response to a call command.
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * <qml>
 *     <class register="no"/>
 * </qml>
 * @endxmlonly
 *
 * @permissions You must also specify the @c control_phone permission in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.2
 */

class BB_SYSTEM_EXPORT CallCommandResponse
{
public:

    /*!
     * @brief Constructs an invalid @c CallCommandResponse object.
     *
     * @since BlackBerry 10.2
     */
    CallCommandResponse();

    /*!
     * @brief Creates a copy of @c other.
     *
     * @param other The source @c CallCommandResponse object.
     *
     * @since BlackBerry 10.2
     */
    CallCommandResponse(const CallCommandResponse &other);

    /*!
     * @brief Copies another @c CallCommandResponse to this object.
     *
     * @param other The source @c CallCommandResponse object.
     * @return The @c CallCommandResponse instance.
     *
     * @since BlackBerry 10.2
     */
    CallCommandResponse& operator=(const CallCommandResponse &other);

    /*!
     * @brief Compares another @c CallCommandResponse to this object.
     *
     * @param other A @c CallCommandResponse object for comparison.
     * @return @c true if call id matches, @c false otherwise.
     *
     * @since BlackBerry 10.2
     */
    bool operator==(const CallCommandResponse &other);

    /*!
     * @brief Destroys this @c CallCommandResponse object.
     *
     * @since BlackBerry 10.2
     */
    ~CallCommandResponse();

    /*!
      * @brief Returns the command for which the response is for.
      *
      * @return The call command.
      *
      * @since BlackBerry 10.2
      */
    QString callCommand() const;
    /*!
      * @brief  Command response ID, it will match the ID used to send the call command.
      *
      * @return The command ID.
      *
      * @since BlackBerry 10.2
      */
    int responseId() const;
    /*!
     * @brief Returns the unique ID of the call which the response is for.
     *
     * @return A non-negative ID of the call if the @c CallCommandResponse object is valid, or @c -1 if the object is invalid.
     *
     * @since BlackBerry 10.2
     */
    int callId() const;
    /*!
     * @brief Returns the error code related to a command executed on a call
     *
     * @return Error returned when executing the call command.
     *         Empty if command was executed successfully.
     *
     * @since BlackBerry 10.2
     */
    QString error() const;

private:
    //!@cond PRIVATE
    friend class CallCommandResponsePrivate;

    QSharedDataPointer<CallCommandResponsePrivate> d_ptr;  /*!< private implementation */
    //!@endcond

};

} // phone
} // system
} // bb

Q_DECLARE_METATYPE(bb::system::phone::CallCommandResponse)

#endif /* BB_SYSTEM_PHONE_CALLCOMMANDRESPONSE_HPP */

