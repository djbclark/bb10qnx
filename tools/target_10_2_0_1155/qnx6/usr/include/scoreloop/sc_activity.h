/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Models an activity related to your game application.
 *
 * @file        sc_activity.h
 * @addtogroup  SC_Activity
 * @{
 *
 * The Activity class is used to model a Scoreloop-related activity for a user.
 *
 * Activities relate to one of the following Scoreloop events:
 * - A User (joining Scoreloop, friendships)
 * - A Score
 * - A Challenge
 * - An Achievement
 *
 * Activity objects contain a message about the Scoreloop event that the Activity relates to.
 * An example message that relates to a score-based Scoreloop event might read: "Player001
 * has scored 50 points in the game SLDemoCore".
 *
 */

#ifndef __SC_ACTIVITY_H__
#define __SC_ACTIVITY_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_user_handle.h>
#include <scoreloop/sc_game_handle.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Activity object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_Activity_tag* SC_Activity_h;

/** Type descriptors for SC_Activity. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Activity);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the Activity instance by 1.
 *
 * @param self An opaque handle for the current SC_Activity instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Activity_Retain(SC_Activity_h self);

/**
 * @brief Decrements the object's reference count; deletes the object if counter reaches 0.
 *
 * This method decrements the reference count of the current controller instance.
 *
 * Note that this method is @c NULL pointer safe, that is, @c NULL as an argument will not cause an exception.
 *
 * @param self An opaque handle for the current SC_Activity instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Activity_Release(SC_Activity_h self);

/**
 * @brief Accessor to the message field
 *
 * This method is an accessor to the message field.
 *
 * @param self An opaque handle for the current SC_Activity instance.
 * @return SC_String_h The activity message.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Activity_GetMessage(SC_Activity_h self);

/**
 * @brief Accessor to get the handle to the game object associated with this activity.
 *
 * This method is an accessor to get the handle to the game object associated with this activity.
 *
 * @param self An opaque handle for the current SC_Activity instance.
 * @return SC_GameHandle_h The game handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameHandle_h SC_Activity_GetGameHandle(SC_Activity_h self);

/**
 * @brief Accessor to get the handle to the user associated with this activity.
 *
 * This method is an accessor to get the handle to the user associated with this activity.
 *
 * @param self An opaque handle for the current SC_Activity instance.
 * @return SC_UserHandle_h The user handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_UserHandle_h SC_Activity_GetUserHandle(SC_Activity_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ACTIVITY_H__ */

/*! @} */
