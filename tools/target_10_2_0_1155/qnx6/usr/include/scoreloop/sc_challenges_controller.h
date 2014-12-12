/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup CoreSocial
 * @brief   The ChallengesController retrieves lists of challenges on behalf of the current session user from the Scoreloop servers
 * @file    sc_challenges_controller.h
 * @addtogroup  SC_ChallengesController
 * @{
 * The \ref SC_ChallengesController retrieves lists of challenges
 * on behalf of the current session user from the Scoreloop servers.
 *
 * Two separate lists may be retrieved:
 * - List of challenges currently available to the user to play
 * - User's challenge history
 * (The list of all challenges associated with the user, e.g. completed, current, rejected, etc.)
 *
 * Basic Usage:
 * -# To request the appropriate challenge list, you can call one of the methods below: 
 *		- SC_ChallengesController_LoadOpenChallenges()
 *		- SC_ChallengesController_LoadChallengeHistory()
 * -# Await a successful server response via delegate callbacks.
 * -# After a successful request, the challenges will be loaded into \ref SC_ChallengeList which can be Access by calling SC_ChallengesController_GetChallenges().
 * @sa RequestController
 */

#ifndef __SC_CHALLENGES_CONTROLLER_H__
#define __SC_CHALLENGES_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_session.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_challenge.h>
#include <scoreloop/sc_challenge_list.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_completion_callback.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ChallengesController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_ChallengesController_tag* SC_ChallengesController_h;

/** Type descriptors for SC_ChallengesController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_ChallengesController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments object's reference count.
 *
 * This method increments the object's reference count.
 *
 * @param   self        SC_ChallengesController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ChallengesController_Retain(SC_ChallengesController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the object's reference count by one. 
 * The object will be deleted automatically if the reference 
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 * @param   self        SC_ChallengesController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ChallengesController_Release(SC_ChallengesController_h self);

/**
 * @brief Returns the list of all challenges that have been requested from the server. 
 *
 * The list will contain either the list of all open challenges available to the user to play, 
 * or the user's challenge history, depending on the type of request made by the controller.
 *
 * If this method is called before a request to the server has been made, an empty list will be returned.
 *
 * @param   self        SC_ChallengesController instance handle
 * @return  SC_ChallengeList_h The list of challenges that have been retrieved from the server.
 * @sa SC_ChallengesController_LoadOpenChallenges(), SC_ChallengesController_LoadChallengeHistory().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_ChallengeList_h SC_ChallengesController_GetChallenges(
        SC_ChallengesController_h self);

/**
 *  @brief This method requests all challenges which may be played by
 *  the current session user.
 *
 * The direct challenges will be requested first.
 * If no direct challenges exist, then all open challenges will be requested.
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you
 * may access the retrieved/loaded challenges using SC_ChallengesController_GetChallenges().
 *
 * @param   self        SC_ChallengesController instance handle
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengesController_LoadOpenChallenges(
        SC_ChallengesController_h self);

/**
 * @brief Requests the challenges associated with the current session user.
 *
 * Method that requests the challenges associated with the current session user. These include:
 * - All completed challenges,
 * - All direct challenges for the user,
 * - Any direct challenges created by the user excluding rejected challenges.
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you 
 * may access the retrieved/loaded challenges using SC_ChallengesController_GetChallenges(). 
 *
 * @param   self        SC_ChallengesController instance handle
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengesController_LoadChallengeHistory(
        SC_ChallengesController_h self);

/**
 * @brief Method for Request Cancellation.
 *
 * Method to cancel or abort any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the challenges controller instance. 
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengesController_Cancel(SC_ChallengesController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CHALLENGES_CONTROLLER_H__ */

/*! @} */
