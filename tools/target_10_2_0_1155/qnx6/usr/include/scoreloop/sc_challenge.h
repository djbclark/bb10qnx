/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief   The Challenge class models all aspects of a Scoreloop challenge.
 *
 * @file  sc_challenge.h
 * @addtogroup  SC_Challenge
 * @{
 * The \ref SC_Challenge class models all aspects of a Scoreloop challenge.
 *
 * See @link coresocial-challenges Challenges @endlink for a detailed explanation of a Scoreloop challenge and information on how to integrate it into your game.
 * 
 * @sa SC_Session, SC_ChallengeController, SC_ChallengesController, @link coresocial-challenges Challenges @endlink,
 *
 */

#ifndef __SC_CHALLENGE_H__
#define __SC_CHALLENGE_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_money.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_score.h>
#include <scoreloop/sc_context.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Challenge object handle 
 *
 * @since 10.0.0*/
typedef struct SC_Challenge_tag* SC_Challenge_h;

/** Type descriptors for SC_Challenge. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Challenge);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This methods increments the object's reference count.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Challenge_Retain(SC_Challenge_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the object's reference count by one. 
 * The object will be deleted automatically if the reference 
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Challenge_Release(SC_Challenge_h self);

/**
 * @brief Returns the challenge stake, which is the in-game currency that both the
 * contender and contestant must pay in order to participate.
 *
 * This method returns the amount of in-game currency that both the contender
 * and contestant must pay in order to participate in the challenge.
 * The size of the stake is set by the contender when
 * creating the challenge. If a challenge expires without
 * being accepted, the stake returns to the contender.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Money_h The challenge stake.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Money_h SC_Challenge_GetStake(SC_Challenge_h self);

/**
 * @brief Accessor that returns the challenge contender.
 *
 * This method returns the challenge contender. The contender is the Scoreloop user who begins the challenge.
 * The user properties available for the contender are: handle, login.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return  SC_User_h The challenge contender.
 * @sa SC_User
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_Challenge_GetContender(SC_Challenge_h self);

/**
 * @brief Accessor that returns the score achieved by the challenge contender.
 *
 * This method returns the score of the contender for the completed challenge.
 * It returns @c NULL if the challenge is not yet complete.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return  SC_Score_h The score achieved by the contender.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Score_h SC_Challenge_GetContenderScore(SC_Challenge_h self);

/**
 * @brief Accessor that returns the challenge contestant.
 *
 * This method returns the challenge contestant.
 * The user properties that are available for the contestant are: handle, login.
 * It returns @c NULL if the challenge has not yet been accepted.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_User_h The challenge contestant or @c NULL.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_Challenge_GetContestant(SC_Challenge_h self);

/**
 * @brief Accessor that returns the score achieved by the challenge contestant.
 *
 * This method returns the score of the contestant for the completed challenge.
 * It returns @c NULL if the contestant has not submitted the score.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return  SC_Score_h The score achieved by the contestant.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Score_h SC_Challenge_GetContestantScore(SC_Challenge_h self);

/**
 * @brief Accessor that returns the date on which the challenge was created.
 *
 * This method returns the date on which the challenge was created.
 * Challenges have a limited lifespan, during which they can be accepted,
 * and expire after this time has passed.
 *
 * The lifespan of challenges for a game can be configured
 * at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_String_h The date on which the challenge was created.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Challenge_GetCreatedAt(SC_Challenge_h self);

/**
 * @brief Accessor that returns the initial level that a challenge was created with.
 *
 * This method returns the initial level that a challenge was created with.
 * Note that a challenge can have a different end level from the one that
 * it was created with. Levels are optional properties that
 * refer to different game stages.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return int The initial level of the challenge.
 * @sa SC_Score_h
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_Challenge_GetLevel(SC_Challenge_h self);

/**
 * @brief Accessor that returns the date, on which the challenge was completed.
 *
 * This method returns the date on which the challenge was completed. A challenge is deemed to be
 * completed only after the contestant has played the challenge and has submitted
 * their score to Scoreloop.
 *
 * @param self An opaque handle for the SC_Challenge instance
 * @return SC_String_h The challenge completion date.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Challenge_GetCompletedAt(SC_Challenge_h self);

/**
 * @brief Accessor that returns the date, on which the challenge will expire.
 *
 * This method returns the date on which the challenge will expire. If the challenge
 * is not completed before that date, the challenge will be cancelled by the server.
 *
 * @param self An opaque handle for the SC_Challenge instance
 * @return SC_String_h The challenge expiry date.
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_String_h SC_Challenge_GetExpiryDate(SC_Challenge_h self);

/**
 * @brief Accessor that returns the Scoreloop user who lost the challenge.
 *
 * This method returns the loser of a completed challenge.
 * It returns @c NULL if the challenge is not yet complete.
 *
 * The user properties available for the loser are: handle, login.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_User_h The loser of the challenge.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_Challenge_GetLoser(SC_Challenge_h self);

/**
 * @brief Accessor that returns the mode of the challenge.
 *
 * This method returns the mode of the challenge.
 * Modes are optional properties that relate to different aspects of
 * gameplay, such as speed or difficulty.
 *
 * Mode has a default value of 0, unless otherwise specified.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return unsigned int The mode of the challenge.
 * @sa SC_Score_h
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_Challenge_GetMode(SC_Challenge_h self);

/**
 * @brief Accessor that returns the amount of in-game currency that is awarded to the winner of the challenge.
 *
 * This method returns the amount, in coins, that is awarded to the winner of the challenge.
 * The prize is determined by adding together the stakes submitted by
 * both the contender and contestant and decreasing it by given Challenge Sink.
 *
 * By default the sink is equal to 25% of the total, then, prize = 2 * stake * (1 - 0.25).
 * This value can be changed in the Challenges Management section on https://developer.scoreloop.com
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Money_h The challenge prize.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Money_h SC_Challenge_GetPrize(SC_Challenge_h self);

/**
 * @brief Accessor that returns the Scoreloop user who won the challenge.
 *
 * This method returns the winner of the completed challenge.
 * It returns @c NULL if the challenge is not yet completed.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_User_h The winner of the challenge or @c NULL.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_Challenge_GetWinner(SC_Challenge_h self);

/**
 * @brief Checks whether a given user is the winner of the challenge.
 *
 * This method checks whether a given user is the winner of the challenge.
 *
 * @param self An opaque handle for the SC_Challenge instance
 * @param user The user to be checked
 * @return SC_Bool_t @c SC_TRUE if given user is the challenge winner, otherwise @c SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsWinner(SC_Challenge_h self, SC_User_h user);

/**
 * @brief Checks whether the challenge has been accepted.
 *
 * This method returns @c SC_TRUE, if the contestant has accepted the challenge and is currently playing it.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t @c SC_TRUE if the contestant has accepted the challenge, otherwise @c SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsAccepted(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge has been assigned to any contender.
 *
 * This method checks the state of the challenge to determine whether or not the challenge
 * is open or direct. Open challenge can be accepted by anybody in the public, while
 * direct is a challenge against a designated user.
 *
 * As it returns @c SC_TRUE when a specific user is challenged,
 * a value of @c SC_TRUE always indicates that this is a direct challenge.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t @c SC_TRUE if the challenge was assigned, otherwise @c SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsAssigned(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge has been cancelled by the server.
 *
 * This method checks the current state of the challenge to determine
 * whether the challenge has been cancelled by the server. Challenges are automatically
 * cancelled when their lifespan has elapsed and nobody has accepted them.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t @c SC_TRUE if the challenge has been cancelled.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsCancelled(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge has been completed.
 *
 * This method returns @c SC_TRUE, when both the contender and the contestant have played the challenge,
 * submitted their scores and a winner has been declared.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t Returns @c SC_TRUE if the challenge has been completed.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsComplete(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge is in an initial state. If it is, the challenge object has been instantiated,
 * but neither contender nor contestant have submitted any scores.
 *
 * The initial state of the challenge.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t @c SC_TRUE if the challenge has been created.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsCreated(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge is no longer acceptable.
 *
 * This method determines if the challenge can still be accepted.
 * Returns @c SC_TRUE if it is impossible to accept the challenge, otherwise returns @c SC_FALSE.
 *
 * Represents the aggregate of several states.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t Returns @c SC_TRUE if it is not possible to accept the challenge.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsDone(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge is invalid.
 *
 * For example, a challenge is deemed invalid if the contestant and contender is the same Scoreloop user.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t Returns @c SC_TRUE if the challenge is invalid.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsInvalid(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge's contender invited a non-Scoreloop user to play when the challenge was created.
 *
 * This method returns @c SC_TRUE, when the contender has played the challenge
 * and invited a friend, who is a non-Scoreloop user, to join Scoreloop and accept the challenge.
 * The non-Scoreloop user will be notified by email or through a social network provider.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t Returns @c SC_TRUE if the challenge is invited.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsInvited(SC_Challenge_h self);

/**
 * @brief Checks whether the contender has played the challenge and left it open for any Scoreloop user to accept.
 *
 * This method returns @c SC_TRUE, when the contender has played the challenge.
 * Any Scoreloop user can accept open challenges.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t Returns @c SC_TRUE if the challenge is open.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsOpen(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge has been rejected by a contestant.
 *
 * This method returns @c SC_TRUE if a contestant has rejected the challenge.
 * Only challenges that have been directly assigned to a contestant can be rejected.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Bool_t Returns @c SC_TRUE if the challenge has been rejected.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsRejected(SC_Challenge_h self);

/**
 * @brief Checks whether the challenge can be accepted by a designated user.
 *
 * This method returns @c SC_TRUE if, for example, the challenge
 * is an open challenge and the user in question did not create it.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @param user The User object to be checked.
 * @return SC_Bool_t @c SC_TRUE if user may play the challenge, otherwise @c SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Challenge_IsPlayableForUser(SC_Challenge_h self, SC_User_h user);

/**
 * @brief Accessor that returns the context associated with the challenge.
 *
 * This method returns @c NULL if there is no context associated with the challenge.
 *
 * @param self An opaque handle for the SC_Challenge instance.
 * @return SC_Context Context of the challenge.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Context_h SC_Challenge_GetContext(SC_Challenge_h self);

/**
 * @brief Sets the context for the challenge.
 *
 * This method sets the persistent (server-side stored) context for this challenge.
 * You can use this context to store game-specific information (i.e.: additional data about the level,
 * mode or achievements made by contender) when creating the challenge.
 * Later it can be accessed by the contestant-side, when accepting the challenge.
 *
 * Context is not taken into an account when evaluating the winner.
 *
 * @param self     An opaque handle for the SC_Challenge instance.
 * @param context  New challenge's context
 * @return SC_Error_t A return code (a value of @c SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t
        SC_Challenge_SetContext(SC_Challenge_h self, SC_Context_h context);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CHALLENGE_H__ */

/*! @} */
