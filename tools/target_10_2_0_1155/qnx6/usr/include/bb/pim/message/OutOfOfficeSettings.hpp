/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_PIM_MESSAGE_OUT_OF_OFFICE_SETTINGS_HPP
#define BB_PIM_MESSAGE_OUT_OF_OFFICE_SETTINGS_HPP

#include <bb/pim/Global>

#include <QSharedDataPointer>

namespace bb {
namespace pim {
namespace message {

class OutOfOfficeSettingsPrivate;

/*!
 * @brief The @c OutOfOfficeSettings class includes information about out-of-office replies
 * for messages.
 * 
 * @details You can use this class to set the Out of Office option, and you can specify
 * the text to use as the out-of-office reply message.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Message"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */

class BB_PIM_EXPORT OutOfOfficeSettings
{
public:
    /*!
     * @brief Constructs a new @c OutOfOfficeSettings.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings();

    /*!
     * @brief Destroys this @c OutOfOfficeSettings.
     *
     * @since BlackBerry 10.0.0
     */
    ~OutOfOfficeSettings();

    /*!
     * @brief Constructs a new @c OutOfOfficeSettings with the provided state and text.
     * 
     * @details The state is an integer that should be either 0 (to disable the
     * out-of-office option) or 1 (to enable the out-of-office option). The provided
     * text is used as the out-of-office reply.
     * 
     * @param state The state of the out-of-office option (either 0 or 1).
     * @param text The out-of-office reply text.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings(int state, const QString& text);

    /*!
     * @brief Constructs an @c OutOfOfficeSettings with the provided private out-of-office information.
     * 
     * @details This constructor creates an @c %OutOfOfficeSettings by using a @c d_ptr to private
     * out-of-office information.
     * 
     * @param outOfOfficeSettingsPrivate The private out-of-office information to use.
     *
     * @since BlackBerry 10.0.0
     */
    explicit OutOfOfficeSettings(OutOfOfficeSettingsPrivate* outOfOfficeSettingsPrivate);

    /*!
     * @brief Copy constructor.
     * 
     * @details This function constructs an @c OutOfOfficeSettings containing exactly the same values as
     * the provided @c %OutOfOfficeSettings.
     * 
     * @param other The @c %OutOfOfficeSettings to be copied.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings(const OutOfOfficeSettings &other);


    /*!
     * @brief Assignment operator.
     * 
     * @details This operator copies all values from the provided @c OutOfOfficeSettings into this
     * @c %OutOfOfficeSettings.
     * 
     * @param other The @c %OutOfOfficeSettings from which to copy all values.
     *
     * @return An @c %OutOfOfficeSettings with all copied data.
     *
     * @since BlackBerry 10.0.0
     */
    OutOfOfficeSettings& operator=(const OutOfOfficeSettings &other);

    /*!
     * @brief Retrieves the state of this @c OutOfOfficeSettings.
     * 
     * @details The state is either 0 (if the out-of-office option is disabled) or 1
     * (if the out-of-office option is enabled).
     * 
     * @return The state of the out-of-office option (either 0 or 1).
     *
     * @since BlackBerry 10.0.0
     */
    int isEnabled() const;

    /*!
     * @brief Sets the state of this @c OutOfOfficeSettings.
     * 
     * @details The provided state should be either 0 (to disable the out-of-office option)
     * or 1 (to enable the out-of-office option).
     *
     * @param state The new state of the out-of-office option (either 0 or 1).
     *
     * @since BlackBerry 10.0.0
     */
    void setState(int state);

    /*!
     * @brief Retrieves the out-of-office reply text of this @c OutOfOfficeSettings.
     *
     * @since BlackBerry 10.0.0
     */

    QString Text() const;

    /*!
     * @brief Sets the out-of-office reply text of this @c OutOfOfficeSettings.
     *
     * @param text The new out-of-office reply text.
     *
     * @since BlackBerry 10.0.0
     */
    void setText(const QString& text);

    /*!
     * @brief Indicates whether this @c OutOfOfficeSettings is valid.
     * 
     * @return @c true if this @c %OutOfOfficeSettings is valid, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<OutOfOfficeSettingsPrivate> d_ptr;

};


} /* namespace message */
} /* namespace pim */
} /* namespace bb */


#endif // BB_PIM_MESSAGE_OUT_OF_OFFICE_SETTINGS_HPP
