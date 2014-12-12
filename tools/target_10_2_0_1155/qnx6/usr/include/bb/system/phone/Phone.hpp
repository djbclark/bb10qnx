/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_PHONE_PHONE_HPP
#define BB_SYSTEM_PHONE_PHONE_HPP

#include <bb/system/phone/Line>
#include <bb/system/phone/Call>
#include <bb/system/phone/LineType>
#include <bb/system/phone/CallCommandResponse>
#include <bb/system/Global>
#include <QObject>
#include <QMap>
#include <QtDeclarative/QtDeclarative>


namespace bb
{
namespace system
{
namespace phone
{

class PhonePrivate;

/*!
 * @headerfile Phone.hpp <bb/system/phone/Phone>
 *
 * @brief Provides phone-related functionality.
 *
 * The @c Phone class is the entry point for phone-related functionality, such as showing the dial pad,
 * starting an outgoing call, checking the available lines supported on the phone, listening to call related
 * notifications, and so on.
 *
 * The following example shows how to start a cellular call to the phone number "519-555-0100":
 *
 * @code
 * bb::system::phone::Phone phone;
 * phone.initiateCellularCall("519-555-0100");
 * @endcode
 *
 * @xmlonly
 * <apigrouping group="Device and Communication/Phone"/>
 * <library name="bbsystem"/>
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * @endxmlonly
 *
 * @permissions You must also specify the @c access_phone and @c control_phone permissions in your bar-descriptor.xml file.
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT Phone: public QObject {
    Q_OBJECT
public:

    /*!
     * @brief Creates a new @c Phone object.
     *
     * @param parent If not @c 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit Phone(QObject *parent = 0);

    /*!
     * @brief Destroys this @c Phone object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~Phone();

    /*!
     * @brief Returns a map of lines supported on the device.
     *
     * @return A map of lines keyed on the line identifier supported on the device.
     *
     * @since BlackBerry 10.0.0
     */
    QMap<QString, Line> lines() const;

    /*!
     * @brief Returns the currently active line.
     *
     * @return The currently active line. If there is no active line, an invalid @c Line object is returned.
     *
     * @since BlackBerry 10.0.0
     */
    Line activeLine() const;

    /*!
     * @brief Checks whether a given line is available.
     *
     * @param type The type of the line to check.  See @c LineType for the list of line types.
     * @return @c true if the given line type is available, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isLineAvailable(LineType::Type type) const;

    /*!
     * @brief Returns a list of phone lines that are currently available to call a phone number.
     * The lines are sorted based on priority.
     *
     * For a given phone number, more than one line can be used to call. For instance a cellular
     * number can be called using MVS or cellular line. This method will return the list of lines
     * that can be used to call the given number and the lines are sorted according to their priority.
     * For e.g. an MVS line has more priority over cellular line when both lines are available
     * so MVS will be first item in the list followed by cellular and so on.
     *
     *
     * @param address The Phone number(e.g 3125559678) or PIN(e.g A564BBD1) or BBID (e.g test@blackberry.com) that can be used to call a contact.
     * @return A list of currently available lines which can be used to call the number. The lines are sorted
     * based on their priority.
     *
     * @since BlackBerry 10.2.0
     */
    QList<Line> availableLines(const QString &address) const;
public Q_SLOTS:

    /*!
     * @brief Brings the phone dial pad to the foreground with the number field pre-populated with the given address.
     *
     * The @c callUpdated() signal will not be emitted for calls resulting from the @c requestDialpad() method.
     *
     * @param address The address with which to populate the number field.
     * @param type The phone line to use when making the call. The default is @c LineType::Cellular.
     *        See @c LineType for the complete list of line types.
     *
     * @since BlackBerry 10.0.0
     */
    void requestDialpad(const QString &address, bb::system::phone::LineType::Type type =
        bb::system::phone::LineType::Cellular);

    /*!
     * @brief Initiates an outgoing cellular call.
     * @details Subsequent updates for the initiated call are indicated by the @c callUpdated() signal.
     *
     * @param phoneNumber The phone number to call.
     * @param applySmartDialing Whether to apply smart dialing or not. The default is @c false.
     *
     * @since BlackBerry 10.0.0
     */
    void initiateCellularCall(const QString &phoneNumber,
            bool applySmartDialing = false);

    /*!
     * @brief Initiate an outgoing call.
     *
     * @param address The address (for example, phone number for cellular call, BBID for video chat, and so on) to call.
     * @param lineType The phone line to use when making the call. The default is @c LineType::Cellular.
     * See @c LineType for the list of line types.
     *
     * @since BlackBerry 10.0.0
     */
    void initiateCall(const QString &address,
        bb::system::phone::LineType::Type lineType = bb::system::phone::LineType::Cellular);

    /*!
     * @brief Sends DTMF tones to the active call.
     *
     * The DTMF tones are sent in the order in which they appear in the @c QByteArray.
     *
     * @param tones The DTMF tones to send. Each element in @c tones should correspond to a DTMF tone.
     * @param lineType The phone line to which the DTMF tones should be sent.  The default is @c LineType::Cellular.
     *        See @c LineType::Type for the complete list of line types.
     * @return @c true if the tones were successfully sent to the active call, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool sendDTMFTones(const QByteArray &tones,
        bb::system::phone::LineType::Type lineType = bb::system::phone::LineType::Cellular);

    /*!
     * @brief Ends an ongoing call
     *
     * endCall will return a boolean to inform the client if the end call command was sent successfully. If the
     * client wants to know about the response of the execution of the call command, it needs to listen to
     * callCommandResponseReceived signal.
     *
     * @param callId Unique call session identifier
     * @return true if the end call command was sent successfully
     *         false otherwise
     *
     * @since BlackBerry 10.2
     */
    bool endCall(int callId);

Q_SIGNALS:

    /*!
     * @brief Emitted when an incoming call is received or updated, or an outgoing call initiated through this @c Phone object instance is updated.
     *
     * @param call A @c Call object with updated information.
     *
     * @xmlonly
     * <qml>
     * <param name="call" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    void callUpdated(const bb::system::phone::Call &call);

    /*!
     * @brief Emitted when the response of a call command (e.g. endCall) initiated through this @c Phone object instance is returned.
     *
     * @param commandResponse A @c CallCommandResponse object with updated information.
     *
     * @xmlonly
     * <qml>
     * <param name="commandResponse" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.2
     */
    void callCommandResponseReceived(const bb::system::phone::CallCommandResponse &commandResponse);

    /*!
     * @brief Emitted when a line is updated.
     *
     * @param line A @c Line object with updated information.
     *
     * @xmlonly
     * <qml>
     * <param name="line" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    void lineUpdated(const bb::system::phone::Line &line);

    /*!
     * @brief Emitted when a line is removed.
     *
     * @param line A @c Line object that was removed
     *
     * @xmlonly
     * <qml>
     * <param name="line" type="QVariant"/>
     * </qml>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    void lineRemoved(const bb::system::phone::Line &line);


    //!@cond PRIVATE
    /*!
     *  Emitted when a call is updated
     */
    void callUpdated(const QVariant &call);

    /*!
     * Emitted when the response to a call command is updated.
     */
    void callCommandResponseReceived(const QVariant &commandResponse);

    /*!
     * Emitted when a line is updated.
     */
    void lineUpdated(const QVariant &line);

    /*!
     * Emitted when a line is removed.
     */
    void lineRemoved(const QVariant &line);
    //!@endcond

private:
    //!@cond PRIVATE
    Q_DECLARE_PRIVATE(Phone);

    PhonePrivate* const d_ptr;   /**< private implementation */
    Q_DISABLE_COPY(Phone);
    //!@endcond
};

} // phone
} // system
} // bb

QML_DECLARE_TYPE(bb::system::phone::Phone)
#endif /* BB_SYSTEM_PHONE_PHONE_HPP */
