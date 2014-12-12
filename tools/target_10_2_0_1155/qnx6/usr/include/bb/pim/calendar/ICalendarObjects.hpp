
/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_CALENDAR_ICALENDAROBJECTS_HPP
#define BB_PIM_CALENDAR_ICALENDAROBJECTS_HPP

#include <bb/pim/Global>
#include <bb/pim/calendar/DataTypes>
#include <QSharedDataPointer>
#include <QList>

namespace bb {
namespace pim {
namespace calendar {

class CalendarEvent;
class ICalendarTodo;
class ICalendarObjectsPrivate;

/*!
 * @brief Container for iCalendar objects
 *
 * @details
 * This holds objects constructed by CalendarService::readICalendarFile from data
 * in an iCalendar file.
 *
 * @xmlonly
 * <apigrouping group="App Integration/Calendar"/>
 * <library name="bbpim"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PIM_EXPORT ICalendarObjects {
public:

    /*!
     * @brief Constructor
     *
     * @details
     * Creates an object
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects();

    /*!
     * @brief Destructor
     *
     * @details
     * Class destructor
     *
     * @since BlackBerry 10.0.0
     */
    ~ICalendarObjects();

    /*!
     * @brief Copy constructor
     *
     * @details
     * Creates an object with values copied from the one passed as parameter.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects(const ICalendarObjects& other);

    /*!
     * @brief Assignment operator
     *
     * @details
     * Updates the object's fields with values from the one passed as parameter.
     *
     * @return Reference to the object that received the assignment.
     *
     * @since BlackBerry 10.0.0
     */
    ICalendarObjects& operator=(const ICalendarObjects& other);

    /*!
     * @brief Events in the iCalendar file
     *
     * @details
     * Returns the calendar events (VEVENT) found in the iCalendar file.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QList<CalendarEvent> events() const;

    /*!
     * @brief To-dos in the iCalendar file
     *
     * @details
     * Returns the to-dos (VTODO) found in the iCalendar file.
     *
     * @return The attribute's value.
     *
     * @since BlackBerry 10.0.0
     */
    QList<ICalendarTodo> todos() const;


    /*!
     * @brief Adds an event
     *
     * @details
     * Puts a new event at the end of the list of events.
     *
     * @param event object to be added
     *
     * @since BlackBerry 10.0.0
     */
    void addEvent(const CalendarEvent& event);

    /*!
     * @brief Removes all events
     *
     * @details
     * Clears the list of events.
     *
     * @since BlackBerry 10.0.0
     */
    void resetEvents();

    /*!
     * @brief Setter for the events' list
     *
     * @details
     * Changes the list of events.
     *
     * @param events new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setEvents(const QList<CalendarEvent>& events);

    /*!
     * @brief Adds a to-do
     *
     * @details
     * Puts a new to-do at the end of the object's list of to-dos.
     *
     * @param todo object to be added
     *
     * @since BlackBerry 10.0.0
     */
    void addTodo(const ICalendarTodo& todo);

    /*!
     * @brief Removes all to-dos
     *
     * @details
     * Clears the list of to-dos.
     *
     * @since BlackBerry 10.0.0
     */
    void resetTodos();

    /*!
     * @brief Setter for the list of to-dos
     *
     * @details
     * Assigns a new list of to-dos to the object.
     *
     * @param todos new value for the attribute
     *
     * @since BlackBerry 10.0.0
     */
    void setTodos(const QList<ICalendarTodo>& todos);

    /*!
     * @brief Object correctness
     *
     * @details
     * Checks if the object's attributes have acceptable values.
     *
     * @return True if the object is valid, false otherwise.
     *
     * @since BlackBerry 10.0.0
     */
    bool isValid() const;

private:
    QSharedDataPointer<ICalendarObjectsPrivate> d_ptr;

};

} // namespace calendar
} // namespace pim
} // namespace bb

#endif // BB_PIM_CALENDAR_ICALENDAROBJECTS_HPP

