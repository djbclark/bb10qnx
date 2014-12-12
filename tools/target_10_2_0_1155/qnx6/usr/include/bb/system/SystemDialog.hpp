/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_SYSTEM_SYSTEMDIALOG_HPP
#define BB_SYSTEM_SYSTEMDIALOG_HPP

#include <bb/system/Global>
#include <bb/system/SystemUiButton>
#include <bb/system/SystemUiModality>
#include <bb/system/SystemUiReturnKeyAction>
#include <bb/system/SystemUiError>
#include <bb/system/SystemUiResult>

#include <QObject>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace system
{

class SystemDialogPrivate;

/*!
 * @headerfile SystemDialog.hpp <bb/system/SystemDialog>
 *
 * @brief A dialog box that presents the user with text and buttons in its content area.
 *
 * @details The dialog box displayed will be an application-modal window, though it is possible to use a system-modal window by setting
 * the @c SystemDialog::modality property.
 *
 * In addition, the @c buttonAreaLimit property controls the number of buttons that will be contained in the button area of the window.
 * By default, the button area will be large enough to contain @c confirmButton, @c customButton, and @c cancelButton, if they are valid.
 * The buttons will be considered invalid if they do not have a label set.
 *
 * Presentation properties are marked as such, and affect future requests.
 * Any pending requests will use the values of the presentation properties at the time of the request.
 *
 * <B>Note:</B> Once the dialog is displayed after a call to @c show() or @c exec() there are two ways of updating the dialog after changing its presentation properties.
 *
 * The default way is to update all the necessary presentation properties and call the @c update() method.
 * This guarantees that all the presentation properties will be updated at the same time.
 *
 * The second method is to have the dialog update automatically after every presentation property change. To enable these automatic updates,
 * the @c autoUpdateEnabled property must be set to @c true.
 *
 * Be aware that the second method does not guarantee atomic updates for all the presentation properties changes.
 * This method can lead to noticeable delays between updates of individual properties. If more than one property needs to be updated, use the first method.
 * If only one presentation property is being updated frequently
 * (for example the text on the dialog @c body must be updated to notify the user of the application's current status)
 * the second approach can be used.
 *
 * @xmlonly
 * <apigrouping group="User Interface/System UI"/>
 * <library name="bbsystem"/>
 * <qml>
 *    <class register="yes" />
 * </qml>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_SYSTEM_EXPORT SystemDialog : public QObject
{
    Q_OBJECT

    /*!
     * @brief @c title represents the title of the window.
     * @details This is a presentation property whose default value is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString title READ title WRITE setTitle RESET resetTitle NOTIFY titleChanged FINAL)

    /*!
     * @brief @c body represents the main text of the window.
     * @details This is a presentation property whose default value is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString body READ body WRITE setBody RESET resetBody NOTIFY bodyChanged FINAL)

    /*!
     * @brief Retrieves whether the text can be displayed with emoticons.
     * @details This is a presentation property whose default value is @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool emoticonsEnabled READ emoticonsEnabled WRITE setEmoticonsEnabled RESET resetEmoticonsEnabled NOTIFY emoticonsEnabledChanged FINAL)

    /*!
     * @brief @c includeRememberMe indicates whether a toggle switch for remembering user selection should be included in the dialog box.
     * @details If a toggle switch is requested, then the user will have the ability to enable and disable it.
     * The user selection will be available using @c rememberMeSelection() when the request is finished.
     * To customize how the toggle switch is presented, use @c rememberMeChecked and @c rememberMeText.
     *
     * This is a presentation property whose default value is @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool includeRememberMe READ includeRememberMe WRITE setIncludeRememberMe RESET resetIncludeRememberMe NOTIFY includeRememberMeChanged FINAL)

    /*!
     * @brief Indicates whether the dialog will be udpated every time a presentation property is changed.
     * @details If @c autoUpdateEnabled is @c true, every time any of the presentation properties on the dialog are changed,
     * the dialog will also update immediately to reflect the changes on the UI. If @c autoUpdateEnabled is @c false, the dialog
     * will not update automatically, instead the @c show() method must be called. This is the default behavior.
     *
     * @note The main difference in behavior with the @c autoUpdateEnabled flag is most apparent when multiple presentation properties are changed.
     * With @c autoUpdateEnabled set to @c true, the onscreen dialog may be updated after each individual presentation property is changed.
     * This may not be an ideal user experience, particularly as the number of changed presentation properties increases.
     * With @c autoUpdateEnabled set to @c false, it is possible to batch multiple presentation property updates and apply them
     * to the onscreen dialog as one unit by calling @c show().
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool autoUpdateEnabled READ isAutoUpdateEnabled WRITE setAutoUpdateEnabled RESET resetAutoUpdateEnabled NOTIFY autoUpdateEnabledChanged REVISION 1)

    /*!
     * @brief Represents the checked state of the toggle switch for remembering user selection.
     * @details The state is only applied if @c includeRememberMe is @c true.
     * To obtain the user selection for this property once the request is finished, use @c rememberMeSelection().
     *
     * This is a presentation property whose default value is @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool rememberMeChecked READ rememberMeChecked WRITE setRememberMeChecked RESET resetRememberMeChecked NOTIFY rememberMeCheckedChanged FINAL)

    /*!
     * @brief Represents the text to associate with the toggle switch associated with @c rememberMeChecked.
     * @details This property is only applied if @c includeRememberMe is @c true.
     *
     * This is a presentation property whose default value is @c "Remember Me".
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(QString rememberMeText READ rememberMeText WRITE setRememberMeText RESET resetRememberMeText NOTIFY rememberMeTextChanged FINAL)

    /*!
     * @brief The maximum number of buttons that can be shown without causing an overflow.
     * @details When overflow occurs all buttons will be stacked vertically.
     *
     * This is a presentation property whose default value is -1.
     * @note -1 implies that default system behavior will be applied. The supported range is 1-3, with any values outside the range resetting the property to its default value.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(int buttonAreaLimit READ buttonAreaLimit WRITE setButtonAreaLimit RESET resetButtonAreaLimit NOTIFY buttonAreaLimitChanged FINAL)

    /*!
     * @brief Indicates whether to dismiss the dialog box when a button is selected.
     * @details If @c false, the dialog box must be dismissed using @c cancel(). Otherwise, the dialog box is dismissed with a button selection.
     *
     * This is a presentation property whose default value is @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bool dismissAutomatically READ dismissAutomatically WRITE setDismissAutomatically RESET resetDismissAutomatically NOTIFY dismissAutomaticallyChanged FINAL)

    /*!
     * @brief Indicates whether to display an activity indicator in the title bar of the dialog.
     *
     * This is a presentation property whose default value is @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_PROPERTY(bool activityIndicatorVisible READ activityIndicatorVisible WRITE setActivityIndicatorVisible RESET resetActivityIndicatorVisible NOTIFY activityIndicatorVisibleChanged REVISION 1)

    /*!
     * @brief Represents the action associated with the return key for this dialog box.
     * @details This a presentation property whose default value is @c bb::system::SystemUiReturnKeyAction::Default.
     * @see @c bb::system::SystemUiReturnKeyAction for the list of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiReturnKeyAction::Type returnKeyAction READ returnKeyAction WRITE setReturnKeyAction RESET resetReturnKeyAction NOTIFY returnKeyActionChanged FINAL)

    /*!
     * @brief Represents the modality of the dialog box.
     * @details This is a presentation property whose value is @c bb::system::SystemUiModality::Application.
     * @see @c bb::system::SystemUiModality for the list of valid values.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiModality::Type modality READ modality WRITE setModality RESET resetModality NOTIFY modalityChanged FINAL)

    /*!
     * @brief Represents the button associated with the default confirming action of the window.
     *
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is @c "OK".
     *
     * @note This button is omitted if its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     *
     * @xmlonly
     * <qml>
     * <property groupedProperty="yes"/>
     * </qml>
     * @endxmlonly
     */
    Q_PROPERTY(bb::system::SystemUiButton* confirmButton READ confirmButton RESET resetConfirmButton FINAL)

    /*!
     * @brief Represents the button associated with the tertiary action of the window.
     *
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @note This button is omitted if its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     *
     * @xmlonly
     * <qml>
     * <property groupedProperty="yes"/>
     * </qml>
     * @endxmlonly
     */
    Q_PROPERTY(bb::system::SystemUiButton* customButton READ customButton RESET resetCustomButton FINAL)

    /*!
     * @brief Represents the button associated with the default cancellation action of the window.
     *
     * @details This is a presentation property whose default @c bb::system::SystemUiButton::label property is @c "Cancel".
     *
     * @note This button is omitted if its @c bb::system::SystemUiButton::label property is a default-constructed @c QString.
     *
     * @since BlackBerry 10.0.0
     *
     * @xmlonly
     * <qml>
     * <property groupedProperty="yes"/>
     * </qml>
     * @endxmlonly
     */
    Q_PROPERTY(bb::system::SystemUiButton* cancelButton READ cancelButton RESET resetCancelButton FINAL)

    /*!
     * @brief Represents the button associated with the return key action of the window.
     * @details When the user triggers the return key action, this button will be automatically selected.
     * If the @c defaultButton is @c NULL, then triggering the return key action will not select any button.
     *
     * If @c defaultButton is set to a button that this instance does not manage, then this property is undefined.
     *
     * This is a presentation property whose default value determined dynamically based on which managed buttons are available.
     * The precedence of the buttons
     * - @c confirmButton
     * - @c cancelButton
     * - @c customButton
     * - last element of @c buttons
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiButton* defaultButton READ defaultButton WRITE setDefaultButton RESET resetDefaultButton FINAL)

    /*!
     * @brief Represents any additional buttons to include in the window.
     *
     * @details This is a presentation property which is initialized as an empty list.
     *
     * @since BlackBerry 10.0.0
     *
     * @xmlonly
     * <qml>
     * <property defaultProperty="yes"/>
     * </qml>
     * @endxmlonly
     */
    Q_PROPERTY(QDeclarativeListProperty<bb::system::SystemUiButton> buttons READ qmlButtons FINAL)

    /*!
     * @brief Represents the result of the last completed request.
     * @details To obtain result values once the request is finished, use the following functions:
     * - @c result() - the result of the request
     * - @c error() - the error that occurred during the request (if applicable)
     * - @c buttonSelection() - the button selected (if applicable)
     * - @c rememberMeSelection() - the user preference as to whether the result should be remembered (if applicable)
     *
     * @see @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiResult::Type result READ result NOTIFY finished FINAL)

    /*!
     * @brief Represents the last error encountered.
     * @details This property is only valid when the @c SystemDialog::result property is @c bb::system::SystemUiResult::Error.
     * @see @c bb::system::SystemUiError for the list of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    Q_PROPERTY(bb::system::SystemUiError::Type error READ error FINAL)

    /*!
     * @brief The default property is @c buttons.
     */
    Q_CLASSINFO("DefaultProperty", "buttons")

public:
    /*!
     * @brief Constructs a new instance of a dialog box with default confirmation and cancellation buttons.
     * @details The confirmation and cancellation buttons will have their default label values.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemDialog(QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a dialog box with only a confirmation button.
     * @details To show the cancellation and custom button set the labels of @c SystemDialog::cancelButton
     * and @c SystemDialog::customButton respectively.
     * @param confirmLabel The label to use for the confirmation button.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit SystemDialog(const QString& confirmLabel, QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a dialog box with defined confirmation and cancellation buttons.
     * @details To show the custom button set the label of @c SystemDialog::customButton.
     * @param confirmLabel The label to use for the confirmation button.
     * @param cancelLabel The label to use for the cancellation button.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    SystemDialog(const QString& confirmLabel, const QString& cancelLabel, QObject* parent = 0);

    /*!
     * @brief Constructs a new instance of a dialog box with defined confirmation, custom and cancellation buttons.
     * @param confirmLabel The label to use for the confirmation button.
     * @param customLabel The label to use for the custom button.
     * @param cancelLabel The label to use for the cancellation button.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    SystemDialog(const QString& confirmLabel, const QString& customLabel, const QString& cancelLabel, QObject* parent = 0);

    /*!
     * @brief Destroys the dialog box, canceling any pending requests.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~SystemDialog();

    /*!
     * @brief Retrieves the title for the dialog box.
     * @return The title of the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    QString title() const;

    /*!
     * @brief Retrieves the main text of the dialog box.
     * @return The text of the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    QString body() const;

    /*!
     * @brief Retrieves whether the text can be displayed as emoticons.
     * @return Whether the dialog box supports emoticons.
     *
     * @since BlackBerry 10.0.0
     */
    bool emoticonsEnabled() const;

    /*!
     * @brief Retrieves the flag indicating if a toggle switch to remember user selection should be included in the dialog box.
     * @return @c true if a toggle for remembering the user selection should be included in the dialog box, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool includeRememberMe() const;

    /*!
     * @brief Retrieves the flag indicating if the dialog will be updated every time the value of a presentation property is changed.
     * @return @c true if the dialog automatically updates, @c false if the dialog doesn't update (in which case the @c show() method
     * must be called after updating the dialog presentation properties).
     *
     * @since BlackBerry 10.2.0
     */
    bool isAutoUpdateEnabled() const;

    /*!
     * @brief Retrieves whether the toggle switch for @c includeRememberMe will be selected by default.
     * @details To obtain the user selection, use @c rememberMeSelection() instead.
     * @return @c true if the toggle should be selected by default, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool rememberMeChecked() const;

    /*!
     * @brief Retrieves the text associated with the toggle switch for @c includeRememberMe.
     * @return The text for the toggle for @c includeRememberMe.
     *
     * @since BlackBerry 10.0.0
     */
    QString rememberMeText() const;

    /*!
     * @brief Retrieves the button attached to the dialog box's confirm button.
     * @details This instance retains ownership of the returned value.
     * @return The dialog box's confirmation button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* confirmButton();

    /*!
     * @brief Retrieves the dialog box's custom action button.
     * @details This instance retains ownership of the returned value.
     * @return The dialog box's custom action button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* customButton();

    /*!
     * @brief Retrieves the dialog box's cancellation button.
     * @details This instance retains ownership of the returned value.
     * @return The dialog box's cancellation button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* cancelButton();

    /*!
     * @brief Retrieves the dialog box's default button.
     * @details This instance retains ownership of the returned value.
     *
     * The default button is automatically selected when the user triggers the return key action.
     * If the default button is @c NULL, no button will be automatically selected.
     *
     * The returned value will be one of the buttons managed by this instance, or @c NULL.
     * @return The dialog box's default button.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiButton* defaultButton();

    /*!
     * @brief Indicates if the dialog box is dismissed when a button is selected.
     * @return @c true if selecting a button dismisses the dialog box, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool dismissAutomatically() const;

    /*!
     * @brief Indicates if an activity indicator is displayed on the title bar of the dialog.
     * @return @c true if the activity indicator is displayed, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    bool activityIndicatorVisible() const;

    /*!
     * @brief Retrieves the dialog box's return key action.
     * @return The dialog box's return key action.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiReturnKeyAction::Type returnKeyAction() const;

    /*!
     * @brief Retrieves the dialog box's modality.
     * @return The dialog box's modality.  See @c bb::system::SystemUiModality for the list of possible values.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiModality::Type modality() const;

    /*!
     * @brief The maximum number of buttons that can be shown without causing an overflow.
     * @details If @c buttonAreaLimit is larger than the number of buttons that will be displayed, all buttons will be stacked vertically.
     * @return The limit for the number of buttons that can be accommodated in the button area, or -1 if system defaults should be used.
     *
     * @since BlackBerry 10.0.0
     */
    int buttonAreaLimit() const;

    /*!
     * @brief Sets the title for the dialog box.
     * @param title The new title of the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    void setTitle(const QString& title);

    /*!
     * @brief Sets the main text of the dialog box.
     * @param body The new text of the dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    void setBody(const QString& body);

    /*!
     * @brief Sets whether the text can be displayed as emoticons.
     * @param newEmoticonsEnabled Whether the dialog box supports emoticons.
     *
     * @since BlackBerry 10.0.0
     */
    void setEmoticonsEnabled(bool newEmoticonsEnabled);

    /*!
     * @brief Sets the flag indicating if a toggle switch for remembering user selection should be included in the dialog box.
     * @param value @c true if a toggle for remembering user selection should be included, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void setIncludeRememberMe(bool value);

    /*!
     * @brief Sets the @c autoUpdateEnabled flag of the dialog.
     * @param update @c true if the dialog will update automatically,
     * @c false if the dialog will not update automatically (in which case the @c show() method
     * must be called after updating the dialog presentation properties).
     *
     * @since BlackBerry 10.2.0
     */
    void setAutoUpdateEnabled(bool update);

    /*!
     * @brief Sets whether the toggle switch for @c includeRememberMe will be selected by default.
     * @param newRememberMeSelected @c true if the toggle should be selected by default, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void setRememberMeChecked(bool newRememberMeSelected);

    /*!
     * @brief Sets the text associated with the toggle switch for @c includeRememberMe.
     * @param newRememberMeText The new text for the toggle for @c includeRememberMe.
     *
     * @since BlackBerry 10.0.0
     */
    void setRememberMeText(const QString& newRememberMeText);

    /*!
     * @brief Sets the dialog box's default button.
     * @details @c newDefaultButton must be one of the buttons managed by this instance, or @c NULL.
     * If @c NULL is specified, then no button will be associated with the return key action.
     *
     * If a non-managed button is specified, then this property is undefined.
     * @param newDefaultButton The button to associate with the return key action.
     *
     * @since BlackBerry 10.0.0
     */
    void setDefaultButton(bb::system::SystemUiButton* newDefaultButton);

    /*!
     * @brief Sets whether the dialog box is dismissed when a button is selected.
     * @param automaticDismissal @c true if the dialog box should be automatically dismissed on a button press,
     * @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    void setDismissAutomatically(bool automaticDismissal);

    /*!
     * @brief Sets whether an activity indicator is displayed on the title bar of the dialog.
     * @param visible @c true if the dialog will display an activity indicator, @c false otherwise.
     *
     * @since BlackBerry 10.2.0
     */
    void setActivityIndicatorVisible(bool visible);

    /*!
     * @brief Sets the return key action for the dialog box.
     * @param newReturnKeyAction The new return key action.
     *
     * @since BlackBerry 10.0.0
     */
    void setReturnKeyAction(bb::system::SystemUiReturnKeyAction::Type newReturnKeyAction);

    /*!
     * @brief Sets the modality for the dialog box.
     * @param newModality The new modality preference.  See @c bb::system::SystemUiModality for the list of
     * possible values.
     *
     * @since BlackBerry 10.0.0
     */
    void setModality(bb::system::SystemUiModality::Type newModality);

    /*!
     * @brief Sets the maximum number of buttons to accommodate in the dialog box button area without overflow.
     * @details Values outside the range [1,3] will reset the property to its default value, -1.
     * If @c newButtonAreaLimit is smaller than the number of buttons that will be displayed, all buttons will be stacked vertically.
     * @param newButtonAreaLimit The maximum number of buttons in the button area.
     *
     * @since BlackBerry 10.0.0
     */
    void setButtonAreaLimit(int newButtonAreaLimit);

    /*!
     * @brief Resets the title of the dialog box to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetTitle();

    /*!
     * @brief Resets the main text of the dialog box to @c QString::null.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetBody();

    /*!
     * @brief Resets whether the text can display emoticons to @c false.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetEmoticonsEnabled();

    /*!
     * @brief Resets the flag to show the toggle for remembering user selection to @c false.
     * @details To reset the selection state for the toggle, use @c resetRememberMeChecked().
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetIncludeRememberMe();

    /*!
     * @brief Resets the @c autoUpdateEnabled flag to @c false.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE void resetAutoUpdateEnabled();

    /*!
     * @brief Resets the selection state for the toggle switch for @c includeRememberMe to true.
     * @details To reset whether to include the toggle switch use @c resetIncludeRememberMe().
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetRememberMeChecked();

    /*!
     * @brief Resets the text for the toggle switch for @c includeRememberMe to @c "Remember Me".
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetRememberMeText();

    /*!
     * @brief Resets the confirmation button for this dialog box.
     * @details When the confirmation button is reset, its label will be set to the default value of @c "OK".
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetConfirmButton();

    /*!
     * @brief Resets the custom action button for this dialog box.
     * @details When the custom action button resets, its label will be an empty @c QString so this button will be
     * omitted during @c show() and @c exec() events.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetCustomButton();

    /*!
     * @brief Resets the cancellation button for this dialog box.
     * @details When the cancellation button is reset, its label will be set to the default value of @c "Cancel".
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetCancelButton();

    /*!
     * @brief Resets the default button for this dialog box based on the property's precedence rules.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetDefaultButton();

    /*!
     * @brief Resets whether the dialog box is dismissed when a button is selected to @c true.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetDismissAutomatically();

    /*!
     * @brief Resets the dialog's @c activityIndicatorVisible property to its default value.
     *
     * @since BlackBerry 10.2.0
     */
    Q_INVOKABLE Q_REVISION(1) void resetActivityIndicatorVisible();

    /*!
     * @brief Resets the return key action of the dialog box to @c bb::system::SystemUiReturnKeyAction::Default.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetReturnKeyAction();

    /*!
     * @brief Resets the modality of the dialog box to @c bb::system::SystemUiModality::Application.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetModality();

    /*!
     * @brief Resets the maximum number of buttons to accommodate in the dialog box button area without overflow to -1.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void resetButtonAreaLimit();

    /*!
     * @brief Appends a button to the list of other buttons for this dialog box.
     * @details The dialog box will become the parent of the button and be responsible for destroying it.
     * @param button The button to add to this dialog box.
     *
     * @since BlackBerry 10.0.0
     */
    void appendButton(bb::system::SystemUiButton* button);

    /*!
     * @brief Retrieves the number of other buttons added to the dialog box.
     * @details This method returns the count of buttons added using the @c appendButton() method.
     * The count does not include the confirmation, custom, or cancellation buttons.
     * @return The number of other buttons.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE int buttonCount() const;

    /*!
     * @brief Retrieves the button at the supplied index.
     * @details This instance retains ownership of the returned value.
     * @param index An index into the list of buttons added  using the @c appendButton() method.
     * @return The button at the supplied index or 0 if an invalid index is provided.
     *
     * @since BlackBerry 10.0.0
     */
    SystemUiButton* buttonAt(int index) const;

    /*!
     * @brief Clears the list of other buttons for this dialog box.
     * @details This only affects buttons added to the dialog box using the @c appendButton() method.
     * This method does not affect the confirmation, custom, or cancellation buttons.
     * The button instances will be deleted.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE void clearButtons();

    /*!
     * @brief Retrieves the result of the last completed request.
     *
     * @details If no request has been made, or if a request is pending, @c bb::system::SystemUiResult::None is returned.
     * @return The result of the last completed request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiResult::Type result() const;

    /*!
     * @brief Retrieves the error that occurred during the request.
     *
     * @details The return value will be reset when a new request is made.
     * @return The error that occurred.  See @c bb::system::SystemUiError for the list of possible errors.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiError::Type error() const;

    /*!
     * @brief Returns the button that was selected when a button selection is made.
     * @details If no button was selected, 0 will be returned.
     *
     * This function will return the result of the button selection of @c show() and @c exec().
     *
     * The return value will be reset when a new request is made.
     *
     * This instance retains ownership of the returned value.
     * @return The button selected by the user.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bb::system::SystemUiButton* buttonSelection() const;

    /*!
     * @brief Returns the state of the toggle for remembering user selection when the user dismisses the dialog box.
     *
     * @return @c true if the toggle for remembering the user selection was checked, @c false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE bool rememberMeSelection() const;

public Q_SLOTS:
    /*!
     * @brief Displays a dialog box based on current property values.
     * @details The result of the request can be retrieved with the @c SystemDialog::result property, or using the @c finished() signal.
     * The button selection can be retrieved with the @c SystemDialog::buttonSelection property.
     *
     * Control is returned to the caller immediately. For a blocking request, use @c exec().
     *
     * @since BlackBerry 10.0.0
     */
    void show();

    /*!
     * @brief Displays the dialog box based on current property values.
     * @details The result of the request can be retrieved with the @c SystemDialog::result property, or using the @c finished() signal.
     * The button selection can be retrieved with the @c SystemDialog::buttonSelection property.
     *
     * Unlike @c show(), this function will block until a button selection is made. If the dialog is already on the screen,
     * this method will return immediately with @c bb::system::SystemUiResult::DialogCannotBlock.
     *
     * @note Blocking occurs by starting a nested @c QEventLoop. To use this method safely, the following conditions must be met:
     * - Any connections to this slot must use a @c Qt::QueuedConnection, or the slot must be triggered using @c QTimer::singleShot(), and
     * - @c QObject::deleteLater() must be used in place of @c delete when deleting the dialog box object.
     * If these conditions are not met, unexpected behavior may result.
     *
     * @return The result of the request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    bb::system::SystemUiResult::Type exec();

    /*!
     * @brief Updates an on-screen dialog based on the current property values.
     * @details If the dialog is not on screen, this method returns immediately and no changes
     * are made to the dialog.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void update();

    /*!
     * @brief Cancels the dialog box if it is still displayed.
     *
     * @since BlackBerry 10.0.0
     */
    void cancel();

Q_SIGNALS:

    /*!
     * @brief Emitted when a request is completed.
     *
     * @details The button selection can be retrieved with @c buttonSelection().
     * The state of the toggle for remembering the content of this dialog box can be retrieved using @c rememberMeSelection().
     * @param value The result of the request.  See @c bb::system::SystemUiResult for the list of possible results.
     *
     * @since BlackBerry 10.0.0
     */
    void finished(bb::system::SystemUiResult::Type value);

    /*!
     * @brief Emitted when the @c title property is changed programmatically.
     * @param value The new value of the @c title property.
     *
     * @since BlackBerry 10.0.0
     */
    void titleChanged(const QString& value);

    /*!
     * @brief Emitted when the @c body property is changed programmatically.
     * @param value The new value of the @c body property.
     *
     * @since BlackBerry 10.0.0
     */
    void bodyChanged(const QString& value);

    /*!
     * @brief Emitted when the @c emoticonsEnabled property is changed programmatically.
     * @param newEmoticonsEnabled The new value of the @c emoticonsEnabled property.
     *
     * @since BlackBerry 10.0.0
     */
    void emoticonsEnabledChanged(bool newEmoticonsEnabled);

    /*!
     * @brief Emitted when the @c includeRememberMe property is changed programmatically.
     * @param value The new value of the @c includeRememberMe property.
     *
     * @since BlackBerry 10.0.0
     */
    void includeRememberMeChanged(bool value);

    /*!
     * @brief Emitted when the @c autoUpdateEnabled property is changed programmatically.
     * @param value The new value of the @c autoUpdateEnabled property.
     *
     * @since BlackBerry 10.2.0
     */
    void autoUpdateEnabledChanged(bool value);

    /*!
     * @brief Emitted when the @c rememberMeChecked property is changed programmatically.
     * @details When the user dismisses the dialog box, the user selection is available using @c rememberMeSelection().
     * @param newRememberMeSelected The new value of the @c rememberMeChecked property.
     *
     * @since BlackBerry 10.0.0
     */
    void rememberMeCheckedChanged(bool newRememberMeSelected);

    /*!
     * @brief Emitted when the @c rememberMeText property is changed programmatically.
     * @param newRememberMeText The new value of the @c rememberMeText property.
     *
     * @since BlackBerry 10.0.0
     */
    void rememberMeTextChanged(const QString& newRememberMeText);

    /*!
     * @brief Emitted when the @c defaultButton property is changed programmatically.
     * @param newDefaultButton The new value of the @c defaultButton property, or @c NULL if none is set.
     *
     * @since BlackBerry 10.0.0
     */
    void defaultButtonChanged(bb::system::SystemUiButton* newDefaultButton);

    /*!
     * @brief Emitted when the @c dismissAutomatically property is changed programmatically.
     * @param automaticDismissal The new value of the @c dismissAutomatically property.
     *
     * @since BlackBerry 10.0.0
     */
    void dismissAutomaticallyChanged(bool automaticDismissal);

    /*!
     * @brief Emitted when the @c activityIndicatorVisible property is changed programmatically.
     * @param value The new value of the @c activityIndicatorVisible property.
     *
     * @since BlackBerry 10.2.0
     */
    Q_REVISION(1) void activityIndicatorVisibleChanged(bool value);

    /*!
     * @brief Emitted when the @c returnKeyAction property is changed programmatically.
     * @param newReturnKeyAction The new value of the @c returnKeyAction property.
     *
     * @since BlackBerry 10.0.0
     */
    void returnKeyActionChanged(bb::system::SystemUiReturnKeyAction::Type newReturnKeyAction);

    /*!
     * @brief Emitted when the @c modality property is changed programmatically.
     * @param newModality The new value of the @c modality property.
     *
     * @since BlackBerry 10.0.0
     */
    void modalityChanged(bb::system::SystemUiModality::Type newModality);

    /*!
     * @brief Emitted when the @c buttonAreaLimit property is changed programmatically.
     * @param newButtonAreaLimit The new value of the @c buttonAreaLimit property.
     *
     * @since BlackBerry 10.0.0
     */
    void buttonAreaLimitChanged(int newButtonAreaLimit);

//!@cond PRIVATE
    /*!
     * @xmlonly
     * <qml>
     * <param name="value" type="bb::system::SystemUiResult::Type"/>
     * </qml>
     * @endxmlonly
     */
    void finished( int value );
    /*!
     * @xmlonly
     * <qml>
     * <param name="newReturnKeyAction" type="bb::system::SystemUiReturnKeyAction::Type"/>
     * </qml>
     * @endxmlonly
     */
    void returnKeyActionChanged(int newReturnKeyAction);
    /*!
     * @xmlonly
     * <qml>
     * <param name="newModality" type="bb::system::SystemUiModality::Type"/>
     * </qml>
     * @endxmlonly
     */
    void modalityChanged(int newModality);
//!@endcond

private:
//!@cond PRIVATE
    QDeclarativeListProperty<SystemUiButton> qmlButtons();

    Q_DECLARE_PRIVATE(SystemDialog)
    Q_DISABLE_COPY(SystemDialog)
    QScopedPointer<SystemDialogPrivate> d_ptr;
//!@endcond
};

} // namespace system
} // namespace bb

QML_DECLARE_TYPE(bb::system::SystemDialog)
#endif // BB_SYSTEM_SYSTEMDIALOG_HPP
