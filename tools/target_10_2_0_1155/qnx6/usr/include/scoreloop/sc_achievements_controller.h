/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @brief       A data controller that retrieves the achievements of a user for any Scoreloop-enabled game.
 * @file        sc_achievements_controller.h
 * @addtogroup  SC_AchievementsController
 * @{
 * The \ref SC_AchievementsController is used to retrieve lists of achievements from the server.
 * The \ref SC_AchievementsController provides access to the achievements information for any 
 * game and any user.
 *
 * Note that if you want to use the SC_AchievementsController_LoadAchievements()
 * method, you must configure awards for your game at https://developer.scoreloop.com .
 * Part of the configuration process includes choosing a unique reverse DNS identifier
 * for every award. Once awards are configured, Scoreloop generates an awards bundle,
 * which you must add to your game projects. This provides local access to information
 * about the configured awards, such as their identifiers and achieving values.
 *
 *
 * @sa SC_Award.
 *
 * <b>Basic use:</b>
 *
 * To retrieve lists of achievement objects from the server:
 *
 * -# Get a new instance of \ref SC_AchievementsController or reuse an existing one.
 * -# Call SC_AchievementsController_LoadAchievements() to make the request:
 * -# Await notification of success using delegate callbacks.
 * -# After a successful request, access the
 * \ref SC_Achievement objects that are retrieved by calling SC_AchievementsController_GetAchievements().
 *
 */
#ifndef __SC_ACHIEVEMENTS_CONTROLLER_H__
#define __SC_ACHIEVEMENTS_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_session.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_social_network.h>
#include <scoreloop/sc_awards_bundle.h>
#include <scoreloop/sc_achievement_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_AchievementsController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_AchievementsController_tag* SC_AchievementsController_h;

/** Type descriptors for SC_AchievementsController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_AchievementsController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the
 * current controller instance.
 *
 * @param   self        SC_AchievementsController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_AchievementsController_Retain(SC_AchievementsController_h self);

/**
 * @brief Decrements the object's reference count; deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count of the
 * current controller instance.
 *
 * Please note that this method is @c NULL pointer safe; that is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param   self        SC_AchievementsController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_AchievementsController_Release(SC_AchievementsController_h self);

/**
 * @brief Gets the user for whom the achievements were requested.
 *
 * This method returns the same user instance that was passed to the SC_AchievementsController_LoadAchievements
 * method.
 *
 * @param self SC_AchievementsController instance handle.
 * @return SC_User_h The user for whom the achievements are requested.
 * @sa SC_User, SC_Session, SC_Achievement, SC_Award
 *
 * @since 10.0.0
 *
 */
SC_PUBLISHED SC_User_h SC_AchievementsController_GetUser(SC_AchievementsController_h self);

/**
 * @brief Gets the award bundle for which the achievements were requested.
 *
 * This method returns the same awards bundle instance that was used in the LoadAchievements
 * methods.
 *
 * @param   self        SC_AchievementsController instance handle
 * @return SC_AwardsBundle_h   The returned AwardsBundle
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_AwardsBundle_h SC_AchievementsController_GetAwardsBundle(SC_AchievementsController_h self);

/**
 * @brief This method loads the achievements from the current game for the specified user.
 * 
 * This method loads the achievements for the specified user in the current game.
 * This method loads all achievements whether they have been achieved or not.
 * It uses the local awards bundle that must be defined and placed inside the current game.
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param   self        SC_AchievementsController instance handle.
 * @param   user        The user whose achievements are to be loaded.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_AchievementsController_LoadAchievements(
        SC_AchievementsController_h self, SC_User_h user);

/**
 * @brief Gets the achievements which are loaded by calling SC_AchievementsController_LoadAchievements
 * method.
 *
 * This method returns achievements list.
 *
 * @param  self        SC_AchievementsController instance handle.
 * @return SC_AchievementList_h The list of achievements that are retrieved.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_AchievementList_h SC_AchievementsController_GetAchievements(
        SC_AchievementsController_h self);

/**
 * @brief Request Cancellation.
 *
 * This method cancels or aborts any ongoing request or operation initiated by this particular controller instance.
 *
 * @param   self        SC_AchievementsController instance handle.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_AchievementsController_Cancel(SC_AchievementsController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ACHIEVEMENTS_CONTROLLER_H__ */

/*! @} */
