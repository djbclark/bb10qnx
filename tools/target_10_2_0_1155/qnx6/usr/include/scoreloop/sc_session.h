/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_session.h
 * @brief       The Scoreloop session - SC_Session class.
 *
 * @addtogroup  SC_Session
 * @{
 *
 * An instance of \ref SC_Session models the current Scoreloop
 * session between the game application and the Scoreloop servers.
 *
 * An instance of \ref SC_Session is created transparently when an \ref SC_Client
 * instance is created.
 *
 * The following properties are accessible through an \ref SC_Session instance:
 * - The session user
 * - The current game instance
 * - The state of the current session
 * - The device associated with the current session
 * - The user's balance of game-specific currency
 *
 * The session will read any existing data for the session user from
 * secure storage, if available.
 */

#ifndef __SC_SESSION_H__
#define __SC_SESSION_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_challenge.h>
#include <scoreloop/sc_money_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Possible SC_Session states.
 *
 * @since 10.0.0
 */
typedef enum SC_SessionState_tag
{
    /** The initial state of the session before authentication. */
    SC_SESSION_INITIAL,
    /** The session is switched into 'authenticating' state just before starting a first request */
    SC_SESSION_AUTHENTICATING,
    /** The session is authenticated. */
    SC_SESSION_AUTHENTICATED,
    /** The session authentication failed. */
    SC_SESSION_FAILED,
    /** The session has timed out and will be re-authenticated. */
    SC_SESSION_TIMEOUT
} SC_SessionState_t;

/** Opaque SC_Session object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_Session_tag* SC_Session_h;

/** Type descriptors for SC_Session.
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Session);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count for the current session instance.
 *
 * @param self An opaque handle for the current session instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Session_Retain(SC_Session_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the current session
 * instance. The session instance will be deleted when the reference
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current session instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Session_Release(SC_Session_h self);

/**
 * @brief Gets the game associated with this session instance.
 *
 * This method returns the current game instance associated with the session.
 *
 * @param self An opaque handle for the current session instance.
 * @return SC_Game_h The current game instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Game_h SC_Session_GetGame(SC_Session_h self);

/**
 * @brief Gets the session user.
 *
 * This method provides access to the current session user. Note that, to get the
 * latest updated user attributes, you must make a server request by calling SC_UserController_LoadUser().
 *
 * @param self An opaque handle for the current session instance.
 * @return SC_User_h The current session user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_Session_GetUser(SC_Session_h self);

/**
 * @brief Checks whether a user is the session user.
 *
 * This method compares a specified user to the user stored in the session.
 *
 * @param self An opaque handle for the current session instance.
 * @param user A user object to compare
 * @return SC_Bool_t SC_TRUE if the user is the same as the user from the session; SC_FALSE otherwise.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Session_IsOwnedByUser(SC_Session_h self, SC_User_h user);

/**
 * @brief Gets the current session state.
 *
 * This method returns the state of the current session.
 * Note that the session will be authenticated automatically
 * after the first server request is made.
 *
 * @param self An opaque handle for the current session instance.
 * @return SC_SessionState_t The state of the current session.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_SessionState_t SC_Session_GetState(SC_Session_h self);

/**
 * @brief Returns the challenge currently underway in the session (if any).
 *
 * Accessor that returns the challenge currently underway in the session (if any).
 * The challenge object will be set in and removed from the session automatically by a ChallengeController.
 *
 * @param self An opaque handle for the current session instance.
 * @return SC_Challenge_h The returned challenge object associated with the current session.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Challenge_h SC_Session_GetChallenge(SC_Session_h self);

/**
 * @brief Allows to set a challenge.
 *
 * Associates a challenge with a session object.
 *
 * @param self An opaque handle for the current session instance.
 * @param challenge Challenge object to set.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Session_SetChallenge(SC_Session_h self, SC_Challenge_h challenge);

/**
 * @brief Returns the session user's balance of game-specific currency.
 *
 * This method returns the session user's balance of game-specific currency.
 * The user should have a balance sufficient to play challenges. Note that, to get the
 * updated balance, you must make a server request by calling SC_UserController_LoadUser().
 *
 * @param self An opaque handle for the current session instance.
 * @return SC_Money_h The money object that specifies the user's balance of game-specific currency.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Money_h SC_Session_GetBalance(SC_Session_h self);

/**
 * @brief Returns the permitted stake amounts that are available for the user to use in challenges.
 *
 * The lowest stake amount permitted is dependent on the balance of the current session user,
 * and will generally increase as the user's balance increases.
 *
 * Users with low balances may use relatively small stakes when instigating challenges. 
 * Users with higher balances will have to use slightly higher stakes when starting challenges.
 *
 * @param self An opaque handle for the current session instance.
 * @return SC_MoneyList List with stake amounts
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_MoneyList_h SC_Session_GetChallengeStakes(SC_Session_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SESSION_H__ */

/*! @} */
