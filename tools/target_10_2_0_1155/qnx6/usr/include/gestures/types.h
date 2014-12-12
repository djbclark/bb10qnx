/*
 * $QNXLicenseC:
 * Copyright 2010, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

 /**
 @mainpage Gestures Library Overview
 
 Gesture recognizers (from here on simply referred to as "gestures") are
 independent state machines that progress through states in reaction to
 touch events received.
 
 Gesture sets contain one or more gestures, all of which are fed touch
 events simultaneously (with the exception of gestures with failure dependencies).

 Applications are responsible for selecting the gestures they're interested
 in and adding them to one or more sets to achieve the desired recognition
 behavior.

 When a gesture state transition occurs, the gesture set invokes the
 application specified callback function for the set.

 Applications can add their own gestures if they need specialized or custom
 behavior.
 
 @section touch_events_whatare What are touch events?
 
 Touch events are events generated by the touch controller. Touch events are 
 represented by the data structure @c mtouch_event_t, which contains various
 types of information about the touch event, such as the type of touch event
 (touch, move, or release), the timestamp of the event, the coordinates of the
 touch, and so on. See the file @c input/event_types.h for more information.
   
 @section gestures_whatare What are gestures?
 
 Gestures are self contained state machines that need not be aware of any other
 gesture. Inter-gesture relationships and dependencies are to be managed by the
 gesture set. This makes individual gestures relatively simple to implement and
 allows the application to customize the desired gesture relationships for its
 own needs. It also means applications only interested in a small subset of
 gestures can pick and choose its gestures of interest.

 There are two classes of gestures:

 <ul>
   <li>Composite</li>
   <li>Discrete</li>
 </ul>

 Once a composite (also called transform or continuous) gesture is recognized, 
 it may send further updates to the application as the user keeps touching or
 moving his/her fingers on the screen. Examples of composite gestures include
 pinch, rotate and two finger pan.

 Conversely, discrete gestures only send a single notification to the
 application. Examples of discrete gestures include tap, double tap and long
 press.

 @section gesture_sets_whatare What are gesture sets?
 
 You can think of a gesture set as the interface between gestures and the
 application. The application sends touch events to a gesture set, not
 to individual gestures. Individual gestures must belong to a gesture set
 to be able to receive touch events and invoke callback functions when 
 gesture state transitions happen.

 Gestures provide a list of callbacks to the gesture set. One of these is
 the @c process_event() callback; this is how a gesture receives touch
 events. This callback returns the new (or unchanged) state for the gesture,
 and the gesture set takes care of any handling required as part of the state
 transition, for example:

 <ul>
   <li>Invoking the set callback (gesture recognized or updated)</li>
   <li>Resetting all gestures in the set when they've all completed or
       failed</li>
   <li>Managing failure dependencies between gestures</li>
   <li>Timer handling for gestures needing time events (as opposed to touch
       events)</li>
   <li>Failure notification when all gestures in a set have failed</li>
 </ul>
 
 @section whats_in_gestures_lib What's in the gestures library?
 
 The gestures library contains the following public header files:
 
  <ul>
   <li>bucket.h</li>
   <li>defaults.h</li>
   <li>double_tap.h</li>
   <li>event_list.h</li>
   <li>long_press.h</li>
   <li>pinch.h</li>
   <li>press_and_tap.h</li>
   <li>rotate.h</li>
   <li>set.h</li>
   <li>swipe.h</li>
   <li>tap.h</li>
   <li>timer.h</li>
   <li>triple_tap.h</li>
   <li>two_finger_pan.h</li>
   <li>two_finger_tap.h</li>
   <li>types.h</li>
 </ul>
*/
 
/**
 * @file types.h
 *
 * @brief Common data types and helper functions
 *
 * The types.h header file provides data type definitions and helper functions for
 * recognizing gestures from the touch screen.
 *
 * 
 */
 
#include <sys/queue.h>
#include "input/event_types.h"
#include "gestures/bucket.h"

#ifndef GESTURES_TYPES_H_
#define GESTURES_TYPES_H_

#define GESTURE_DIRECTION_UP (1 << 0)
#define GESTURE_DIRECTION_DOWN (1 << 1)
#define GESTURE_DIRECTION_LEFT (1 << 2)
#define GESTURE_DIRECTION_RIGHT (1 << 3)

#ifdef __QNXNTO__
__BEGIN_DECLS
#else
#ifdef __cplusplus
extern "C" {
#endif
#endif

struct gesture_base;
struct gestures_set;
struct contact_id_map;

/**
 * @brief Gesture type enumeration
 *
 * The enumeration @c gesture_e represents the set of possible gestures.
 *
 */
typedef enum {
	GESTURE_NONE = 0,
	GESTURE_TWO_FINGER_PAN,
	GESTURE_ROTATE,
	GESTURE_SWIPE,
	GESTURE_PINCH,
	GESTURE_TAP,
	GESTURE_DOUBLE_TAP,
	GESTURE_TRIPLE_TAP,
	GESTURE_PRESS_AND_TAP,
	GESTURE_TWO_FINGER_TAP,
	GESTURE_LONG_PRESS,
	GESTURE_USER
} gesture_e;

/**
 * @brief Gesture state enumeration
 *
 * The enumeration @c gesture_state_e represents state of a gesture as it is
 * being processed. The possible next state depends on the type of gesture.
 */
typedef enum {
	GESTURE_STATE_NONE = 0,
	GESTURE_STATE_UNRECOGNIZED,
	GESTURE_STATE_RECOGNIZED, /* Composite gestures only */
	GESTURE_STATE_UPDATING, /* Composite gestures only */
	GESTURE_STATE_COMPLETE,
	GESTURE_STATE_FAILED
} gesture_state_e;

/**
 * @brief Touch event handling functions
 *
 * The data type @c gesture_funcs_t consists of pointers to functions that
 * handle touch events by updating the gesture state, resetting the
 * gesture data structures or freeing memory associated with the gesture. The
 * following functions must be defined for each gesture: 
 * 
 * <ul>
 *   <li>@c process_event()</li>
 *   <li>@c reset()</li>
 *   <li>@c free()</li>
 * </ul>
 * 
 * The @c process_event() callback function is responsible for state handling and returning
 * the new (or unchanged) gesture state. The list of gesture states, with valid transitions
 * in brackets, consists of: 
 * 
 * <ul>
 *   <li> UNRECOGNIZED (recognized, updating, complete, failed)</li>
 *   <li> RECOGNIZED (updating, complete, failed)</li>
 *   <li> UPDATING (complete, failed)</li>
 *   <li> COMPLETE</li> 
 *   <li> FAILED</li>
 * </ul>
 *
 * Discrete gestures do not use the RECOGNIZED or UPDATING states; they transition directly
 * from UNRECOGNIZED to FAILED or COMPLETE.
 *
 * The @c reset() callback function resets the gesture-specific data structures to the
 * initial state. 
 *
 * The @c free() callback function frees all memory associated with the gesture that was allocated
 * by the gesture's @c alloc() function. 
 */
typedef struct {
	void (*free)(struct gesture_base* gesture);
	gesture_state_e (*process_event)(struct contact_id_map* map, struct gesture_base* gesture, mtouch_event_t* event, int* consumed);
	void (*reset)(struct gesture_base* gesture);
} gesture_funcs_t;


/**
 * @brief Gesture callback function prototype
 *
 * The callback function @c gesture_callback_f is invoked every time a gesture
 * changes state, with the exception of the transition from UNRECOGNIZED to
 * FAILED.
 *
 * Note that if the event passed to the callback is NULL, it means the callback
 * was invoked following a timer callback (as opposed to an event coming in).
 * The @c async parameter indicates which thread invoked the callback:
 *   <ul>
 *     <li>the thread that called @c gestures_set_process_event() (@c async == 0) </li>
 *     <li>the timer thread (@c async == 1)</li>
 *   </ul>
 *
 * @param gesture A pointer to the gesture.
 * @param event   A pointer to the last touch event.
 * @param param   A pointer to the parameter list.
 * @param async   Indicator of the originating thread (see description).
 *
 * @return Nothing. 
 */
typedef void(*gesture_callback_f)(struct gesture_base* gesture, mtouch_event_t* event, void* param, int async);

/**
 * @brief Common data structure for all gestures
 *
 * The structure @c gesture_base_t represents information that is common to all
 * gestures. Specific gestures include the gesture base in their representation,
 * and also include additional members to capture gesture-specific information.
 * 
 * It is up to the application to define the failure dependencies between 
 * gestures and to add gestures to a gesture set.
 */
typedef struct gesture_base {
	TAILQ_ENTRY(gesture_base) glink;    /**< A macro that resolves to pointers into the gestures
	                                         bucket. Use the @c gestures_bucket_*() functions to
	                                         manipulate the gestures bucket, rather than manipulating
	                                         it directly.*/
	struct gestures_set* set;           /**< A pointer to the gesture set. */
	gesture_e type;                     /**< The gesture type. */
	gesture_state_e state;              /**< The current state of the gesture. */
	gesture_funcs_t funcs;              /**< The state and memory handling functions. */
	gesture_callback_f callback;        /**< The gesture handling function, triggered when a 
	                                         gesture changes state. */
	gestures_bucket_t mustallfail;      /**< List of gestures that must fail for this gesture
	                                         to complete. */
	gestures_bucket_t faildependents;   /**< List of gestures that can only complete after this
	                                         gesture fails. */
} gesture_base_t;

/**
 * @brief Gesture coordinates
 *
 * The structure @c gesture_coords_t carries the x and y coordinates of a touch gesture,
 * as well as the time that it occured.
 *
 */
typedef struct {
	_Int32t x;
	_Int32t y;
	_Uint64t timestamp;
} gesture_coords_t;

/**
 * @brief Initialize the gesture base data structure
 *
 * The function @c gesture_base_init() initializes the gesture base data structure,
 * @c gesture_base_t.
 *
 * @param gesture The gesture to initialize.
 * 
 * @return None.
 */
void gesture_base_init(gesture_base_t* gesture);


/**
 * @brief Add a gesture to the 'must fail' list.
 *
 * The function @c gesture_add_mustfail() adds a gesture to the 'must fail' list of another gesture.
 * That is, the gesture added to the list must fail in order for the gesture that owns the list
 * to complete.
 *
 * @param target   The gesture dependent on the failure of the second gesture.
 * @param mustfail The gesture that must fail. This gesture is added to the 'must fail' list
 *                 of the target gesture.
 *
 * @return 0 on sucess; -1 on error.
 */
int gesture_add_mustfail(gesture_base_t* target, gesture_base_t* mustfail);

/* Helpers for gesture recognizers */
/**
 * @brief Save the touch event coordinates
 * 
 * The function @c save_coords() saves the coordinates of a touch event in the 
 * specified @c gesture_coords_t data structure. You'll probably need this
 * function only if you're defining your own gestures.
 *
 * @param event   A pointer to the event for which to save the coordinates.
 * @param coords  A pointer to the gesture coordinates structure to use for saving. 
 * 
 * @return Nothing.
 */
void save_coords(mtouch_event_t* event, gesture_coords_t* coords);

/**
 * @brief Return the elapsed time between two events
 * 
 * The function @c diff_time_ms() returns the elapsed time between the two specified 
 * gesture events. You'll probably need this function only if you're defining your
 * own gestures.
 *
 * @param coords1  A pointer to the first gesture event.
 * @param coords2  A pointer to the second gesture event. 
 * 
 * @return The elapsed time in milliseconds.
 */
int32_t diff_time_ms(gesture_coords_t* coords1, gesture_coords_t* coords2);

/**
 * @brief Calculate the maximum displacement between two gesture events
 * 
 * The function @c max_displacement_abs() returns the the maximum displacement, in pixels,
 * between two gesture events. For example, if the absolute value of the difference between
 * the x coordinates of the two gestures is greater than the absolute value of the difference
 * between the y coordinates, the former is returned by the function. You'll probably need
 * this function only if you're defining your own gestures.
 *
 * @param coords1  A pointer to the first gesture event.
 * @param coords2  A pointer to the second gesture event.
 * 
 * @return The maximum displacement, in pixels.
 */
uint32_t max_displacement_abs(gesture_coords_t* coords1, gesture_coords_t* coords2);

/**
 * @brief Remap the contact id from the touch evemt
 * 
 * The function @c map_contact_id() remaps contact identifiers from touch events to 
 * contact identifiers to be used by gestures. The touch event data structure contains
 * a contact_id element that is assigned a value from a 0-based index that corresponds
 * to the individual fingers that touch the screen. The ID assigned to a finger will not
 * change until that finger is released. The contact ID from the touch event should not
 * be used directly by the gesture recognizer. Instead, user gestures should call
 * @c map_contact_id() to get a 0-indexed contact ID remapped from the gesture set's 
 * perspective. This is necessary because, for example, the event contact ID 1 could
 * actually correspond to the gesture set's contact ID 0 if there are multiple gesture
 * sets in play, or if the user's finger is resting on the touch-sensitive bezel. 
 * You'll probably need this function only if you're defining your own gestures.
 *
 * @param map         A pointer to the gesture map. The gesture passes the map to the 
 *                    process_event() callback function.
 * @param contact_id  A touch event contact id. 
 * 
 * @return The remapped contact ID.
 */
int map_contact_id(struct contact_id_map* map, unsigned contact_id);

#ifdef __QNXNTO__
__END_DECLS
#else
#ifdef __cplusplus
};
#endif
#endif

#endif /* GESTURES_TYPES_H_ */

__SRCVERSION( "$URL: $ $Rev: $" );
