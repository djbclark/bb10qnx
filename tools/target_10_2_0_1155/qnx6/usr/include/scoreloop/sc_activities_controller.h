/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup CoreSocial
 * @brief    The ActivitiesController retrieves lists of activities from the server.
 * @file    sc_activities_controller.h
 * @addtogroup  SC_ActivitiesController
 * @{
 * The \ref SC_ActivitiesController retrieves lists of activities from the server.
 * The list that is retrieved relates to activities of a user across all games.
 *
 * An example activity might contain the message:
 * "Player001 has played SLDemoCore".
 *
 */

#ifndef __SC_ACTIVITIES_CONTROLLER_H__
#define __SC_ACTIVITIES_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_activity.h>
#include <scoreloop/sc_activity_list.h>
#include <scoreloop/sc_completion_callback.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ActivitiesController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_ActivitiesController_tag* SC_ActivitiesController_h;

/** Type descriptors for SC_ActivitiesController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_ActivitiesController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Returns the activities list from the server.
 *
 * This method requests the activities list from the server.
 *
 * @param   self        SC_ActivitiesController instance handle.
 * @return  SC_ActivityList_h Activities list from the server.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_ActivityList_h SC_ActivitiesController_GetActivities(
        SC_ActivitiesController_h self);

/**
 * @brief Requests all activities associated with the specified user.
 *
 * This method returns all the activities of the user across all of the games.
 * Note that this is an asynchronous call and a callback will be triggered, after which you
 * can access the activities that were retrieved by using SC_ActivitiesController_GetActivities().
 *
 * @param   self        SC_ActivitiesController instance handle.
 * @param   user        Specified user for which you seek activities.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ActivitiesController_LoadUserActivities(
        SC_ActivitiesController_h self, SC_User_h user);

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the object's reference count.
 *
 * @param   self        SC_ActivitiesController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ActivitiesController_Retain(SC_ActivitiesController_h self);

/**
 * @brief Decrements the object's reference count; deletes the object if counter reaches 0.
 *
 * The reference count of the current controller instance is decremented.
 *
 * Note that this method is @c NULL pointer safe, that is, @c NULL as an argument will not cause an exception.
 *
 * @param   self        SC_ActivitiesController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ActivitiesController_Release(SC_ActivitiesController_h self);

/**
 * @brief Cancels or aborts any ongoing request or operation.
 *
 * This method cancels or aborts any ongoing request or operation that was initiated by this particular controller instance.
 *
 * @param self An opaque handle of the score controller instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ActivitiesController_Cancel(SC_ActivitiesController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ACTIVITIES_CONTROLLER_H__ */

/*! @} */
