/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @file        sc_local_achievements_controller.h
 * @brief       A data controller which manages the achievements of a user.
 *
 * @addtogroup  SC_LocalAchievementsController
 * @{
 *
 * The \ref SC_LocalAchievementsController manages achievements of the current game for the
 * session user only. This information is stored locally and has to be synchronized by
 * the developer with the server.
 *
 * The APIs of \ref SC_LocalAchievementsController allow the following actions:
 * - set an award as being achieved
 * - update achievement progress
 * - query for local achievements progress
 * - synchronize local achievements with the server
 *
 * Note that you must configure awards for your game on https://developer.scoreloop.com.
 * Part of the configuration process includes choosing a unique reverse DNS identifier
 * for every award. Once awards have been configured, Scoreloop generates an awards bundle,
 * which you must add to you game projects. This provides local access to information about
 * the configured awards, including their identifiers and achieving values, among other things.
 * @sa SC_Award.
 *
 * <b>Basic use:</b>
 *
 * a) To set an award as being achieved for a user:
 *    When the game is played, as the user completes one of the incremental
 *    stages necessary to achieve the award, set the value of the award accordingly.
 * -# Get an instance of \ref SC_LocalAchievementsController or reuse an existing one.
 * -# To do this, use one of the following:
 *    - SC_LocalAchievementsController_SetValueForAwardIdentifier() or
 *    - SC_LocalAchievementsController_IncrementValueForAwardIdentifier() or
 *    - SC_LocalAchievementsController_SetAchievedValueForAwardIdentifier()
 *
 * b) To synchronize locally stored information with the server:
 * -# Get an instance of \ref SC_LocalAchievementsController or reuse an existing one.
 * -# Call the SC_LocalAchievementsController_ShouldSynchronize() method.
 * This will check to see if there is locally
 * stored information on the device that should be synchronized with the server.
 * -# If synchronization should occur, call SC_LocalAchievementsController_Synchronize()
 * to update the server with the local data.
 *
 * c) To retrieve lists of Achievement objects
 *
 * -# Get an instance of \ref SC_LocalAchievementsController or re-use an existing one.
 * -# Call SC_LocalAchievementsController_GetAchievements() to obtain achievements for the session user
 *
 */

#ifndef __SC_LOCAL_ACHIEVEMENTS_CONTROLLER_H__
#define __SC_LOCAL_ACHIEVEMENTS_CONTROLLER_H__

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

/** Opaque SC_LocalAchievementsController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_LocalAchievementsController_tag* SC_LocalAchievementsController_h;

/** Type descriptors for SC_LocalAchievementsController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_LocalAchievementsController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the
 * current controller instance. 
 * 
 * @param   self        SC_LocalAchievementsController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_LocalAchievementsController_Retain(SC_LocalAchievementsController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count of the
 * current controller instance. 
 *
 * Please note that this method is @c NULL pointer safe; that is, @c NULL as an argument will 
 * not cause an exception.
 *  
 * @param   self        SC_LocalAchievementsController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_LocalAchievementsController_Release(SC_LocalAchievementsController_h self);

/**
 * @brief Accessor method to get the loaded awards bundle.
 * 
 * This method returns the SC_AwardsBundle to provide access to information about the awards of current game.
 *
 * @param   self        SC_LocalAchievementsController instance handle
 * @return SC_AwardsBundle The returned AwardsBundle
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_AwardsBundle_h SC_LocalAchievementsController_GetAwardsBundle(SC_LocalAchievementsController_h self);

/**
 * @brief Accessor method to get the local achievements.
 *
 * Method to get the local achievements. There will be one achievement per each award with the status refleting
 * if it was already achieved or the current progress.
 *
 * @param   self        SC_LocalAchievementsController instance handle
 * @return SC_AchievementList_h The list of retrieved achievements.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_AchievementList_h SC_LocalAchievementsController_GetAchievements(SC_LocalAchievementsController_h self);

/**
 * @brief Synchronizes the local achievements database with the Scoreloop server.
 *
 * This method synchronizes information about achievements that is stored locally on the device with the Scoreloop server.
 * This method should be called if:
 *  - the local database has never been synchronized with the Scoreloop server (i.e. on first application launch), or
 *  - an award has been unlocked since the last synchronization call.
 *
 * Use SC_LocalAchievementsController_ShouldSynchronize() to check when this method should be called.
 * 
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param   self        SC_LocalAchievementsController instance handle
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-synchronise here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_LocalAchievementsController_Synchronize(SC_LocalAchievementsController_h self);

/**
 * @brief Method to check whether SC_LocalAchievementsController_Synchronize() should be called or not.
 *
 * This method checks whether synchronization with Scoreloop server should be performed or not.
 * Synchronization should occur if the local database has never been synchronized with the server, or if
 * an award has been achieved since the last synchronization.
 *
 * @param   self        SC_LocalAchievementsController instance handle
 * @return SC_Bool_t SC_TRUE if synchronize should be called, otherwise SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_LocalAchievementsController_ShouldSynchronize(SC_LocalAchievementsController_h self);

/**
 * @brief Method returns the date on which the award associated with the given identifier was achieved.
 *
 * This method returns the date on which the award associated with the given identifier was achieved.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique reverse DNS string chosen by the developer and used by Scoreloop
 *                              to identify the award.
 * @return  SC_String_h         Returns the date on which the award was achieved. The parameter will be NULL
 *                              if the award has not yet been achieved.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_LocalAchievementsController_GetAchievementDateForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier);

/**
 * @brief Method to return the achievement related to the award-identifier from the achievements list.
 *
 * This method returns the achievement related to the award-identifier from the achievements list.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique reverse DNS string chosen by the developer and used by Scoreloop
 *                              to identify the award.
 * @return SC_Achievement_h     returns an achievement of award with specified identifier or NULL if award with such identifier doesn't exist.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Achievement_h SC_LocalAchievementsController_GetAchievementForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier);

/**
 * @brief  This method returns the value of the award specified by the given identifier.
 *
 * This method returns the value of the award specified by the given identifier.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique reverse DNS string chosen by the developer and used by Scoreloop
 *                              to identify the award.
 * @return  int                 Returns the value property of award.
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_LocalAchievementsController_GetValueForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier);

/**
 * @brief Sets the value of a local achievement.
 *
 * This method is used to set the progress value of a specific award.
 *
 * In order to reset the value for an unachieved award, SC_LocalAchievementsController_ResetValueForAwardIdentifier()
 * should be used instead.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique reverse DNS string chosen by the developer and used by Scoreloop to identify
 *                              the award.
 * @param   value               The value to which the award will be set. It can range between the initial value and the achieving value for the award.
 *                              For anything above the range, value is set to the achieving value.
 * @param   pGetAchieved        Returns SC_TRUE if calling the method results in the award being achieved by the user
 *                              for first time. Otherwise SC_FALSE.
 * @return SC_Error_t           A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-SetValueForAwardIdentifier here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_LocalAchievementsController_SetValueForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier, int value,
        SC_Bool_t *pGetAchieved);

/**
 * @brief This method resets the value of the award to its initial starting value.
 *
 * Method to reset the value of the award to the initial value.  Note that in cases where the award has already been
 * achieved, it cannot be reset.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique reverse DNS string chosen by the developer and used by Scoreloop to identify
 *                              the award.
 * @param   pGetAchieved        Returns SC_TRUE if the value has been reset, otherwise SC_FALSE.
 * @return SC_Error_t           A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_LocalAchievementsController_ResetValueForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier,
        SC_Bool_t *pGetAchieved);

/**
 * @brief This method checks the status of the award with the given identifier to see if it has been achieved.
 * 
 * Method which checks the status of the award with the given identifier to see if it has been achieved.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique identifier for the award, (chosen by the developer).
 * @return  SC_Bool_t           returns SC_TRUE if award with specified id is achieved, or SC_FALSE if it's not achieved or doesn't exist.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_LocalAchievementsController_IsAchievedForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier);

/**
 * @brief This method sets the status of the given award as being "achieved"
 *
 * This method:
 *  - sets the value of the award equal to its achievingValue
 *  - sets the achieved property of the award equal to SC_TRUE
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique identifier for the award, (chosen by the developer).
 * @param   pGetAchieved        Returns SC_TRUE if the status of the award has been successfully set to achieved,
 *                              otherwise SC_FALSE.
 * @return SC_Error_t           A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_LocalAchievementsController_SetAchievedValueForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier,
        SC_Bool_t *pGetAchieved);

/**
 * @brief This method increments the value of the specified award by one.
 *
 * This method increments the value of the specified award by one. If the incremented value reaches the achieving value
 * for the award, the user will achieve the award.
 *
 * @param   self                SC_LocalAchievementsController instance handle
 * @param   awardIdentifier     The unique reverse DNS string chosen by the developer and used by Scoreloop to identify
 *                              the award.
 * @param   pGetAchieved        Returns SC_TRUE if, after incrementing the value, the award is achieved, otherwise SC_FALSE.
 * @return SC_Error_t           A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_LocalAchievementsController_IncrementValueForAwardIdentifier(
        SC_LocalAchievementsController_h self, const char *awardIdentifier,
        SC_Bool_t *pGetAchieved);

/**
 * @brief Cancels the request.
 *
 * Method to cancel any ongoing request or operation initiated by this particular controller instance.
 *
 * @param   self        SC_LocalAchievementsController instance handle
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t
        SC_LocalAchievementsController_Cancel(SC_LocalAchievementsController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_LOCAL_ACHIEVEMENTS_CONTROLLER_H__ */

/*! @} */
