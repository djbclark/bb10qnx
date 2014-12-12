/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @file        sc_challenge_controller.h
 * @brief       The challenge controller manages single instance of the challenge class.
 * @addtogroup  SC_ChallengeController
 * @{
 * The \ref SC_ChallengeController manages single instance of the SC_Challenge class.
 *
 * The \ref SC_ChallengeController is used to
 * - Accept a challenge
 * - Reject a challenge
 * - Submit a challenge's score or context to the server
 *
 * \ref SC_Challenge life-cycle:
 * -# The contender decides on a stake and creates a challenge.
 *    The contender also decides if the challenge should be open to any user or directed to a designated user.
 * -# The contender plays the game and submits the challenge and the score he obtained to the Scoreloop server.
 * -# A second Scoreloop user, the contestant, accepts the challenge and pays the challenge stake. If the challenge is open it may
 *    be accepted by any Scoreloop user. If it is a direct challenge, only the user, to whom the challenge was assigned by the contender
 *    may accept it.
 * -# The contestant plays the game and submits the score to Scoreloop.
 * -# Scoreloop compares the scores of the contender and the contestant in accordance with the game scoring schema as
 *    defined by the game developer, and declares a winner.
 * -# The winner takes the challenge prize (the combined contender and contestant stakes decreased by a challenge sink).
 *
 * Basic use:
 *
 * To create a challenge:
 * -# Call the SC_Client_CreateChallenge() method to
 *    create the challenge with the given stake and contestant.
 * -# The challenge contender is automatically set as equal to the
 *    current session user. The contestant is equal to the
 *    user argument passed in step 1. Pass a NULL value as the
 *    user argument instead, in order to create an open challenge.
 *    The controller automatically sets the challenge in the
 *    current session (for further easier access).
 *
 * To accept, reject, or submit a challenge:
 * -# Get an instance of \ref SC_ChallengeController or re-use an
 *    existing instance.
 * -# Call the SC_ChallengeController_SetChallenge() on the controller.
 *    This is the challenge that the controller will deal with.
 *    If this is not explicitly set, the controller
 *    will take the challenge from the current session instead.
 * -# Call the appropriate method to accept, reject, or submit
 *    the challenge.
 *		- SC_ChallengeController_AcceptChallenge()
 *		- SC_ChallengeController_RejectChallenge()
 *		- SC_ChallengeController_SubmitChallenge()
 * -# Await notification of success using delegate callbacks.
 *
 * Important note:
 *
 * Do not modify a challenge object, or any of its sub-objects
 * like score or the userContext of a score, while one
 * of the following asynchronous methods is in progress, as
 * this might result in undefined results:
 *	- SC_ChallengeController_AcceptChallenge()
 *	- SC_ChallengeController_RejectChallenge()
 *	- SC_ChallengeController_SubmitChallenge()
 *	- SC_ChallengeController_SubmitChallengeScore()
 *
 * @sa SC_Challenge, @link coresocial-challenges Challenges @endlink
 *
 */

#ifndef __SC_CHALLENGE_CONTROLLER_H__
#define __SC_CHALLENGE_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_session.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_challenge.h>
#include <scoreloop/sc_score.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_money.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ChallengeController object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_ChallengeController_tag* SC_ChallengeController_h;

/** Type descriptors for SC_ChallengeController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_ChallengeController);

/*-------------------------------------------------------------------------------------*
 * Methods 
 *-------------------------------------------------------------------------------------*/
/**
 * @brief Increments the object's reference count
 *
 * This method increments the object's reference count.
 *
 * @param self An opaque handle for the current controller.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ChallengeController_Retain(SC_ChallengeController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the object's reference count by one. 
 * The object will be deleted automatically if the reference 
 * count reaches 0.
 *
 * Note that this method is NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current controller instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ChallengeController_Release(SC_ChallengeController_h self);

/**
 * @brief Returns the challenge object that the controller is dealing with.
 *
 * This method returns the challenge object that the controller is dealing with.
 * If no challenge has been explicitly set, the challenge from the current session will be returned by default.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @return SC_Challenge_h The challenge object that the controller is dealing with.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Challenge_h SC_ChallengeController_GetChallenge(
        SC_ChallengeController_h self);

/**
 * @brief Sets the challenge object that the controller will deal with.
 *
 * This method sets the challenge object that the controller is dealing with.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @param challenge The challenge object that the controller is dealing with.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengeController_SetChallenge(
        SC_ChallengeController_h self, SC_Challenge_h challenge);

/**
 *  @brief Submits the challenge score to the
 *  server.
 *
 * Convenience API that submits the challenge score to the
 *  server. The score object must be associated with
 *  the current session user.
 *
 *  The mode of the score to be submitted must be the same
 *  as the mode of the challenge object that the controller
 *  is dealing with.
 *
 * Note that this is an asynchronous call and a callback
 * will be triggered, which indicates whether the submission was successful or not.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @param score The score object to be submitted to the server.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengeController_SubmitChallengeScore(
        SC_ChallengeController_h self, SC_Score_h score);

/**
 *  @brief Submits the challenge to the server.
 *
 *  If the challenge is unknown to the server,
 *  it will be registered and assigned a unique identifier.
 *  If the challenge is already known to the server,
 *  calling this method will update the challenge details.
 *  If there are consistency errors a SC_REQUEST_FAILED (=104) error will be
 *  returned to the delegate.
 *
 * Note that this is an asynchronous call and a callback
 * will be triggered, which would indicate if the submission was successful or not.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengeController_SubmitChallenge(
        SC_ChallengeController_h self);

/**
 *  @brief Accepts the challenge on behalf of the session user.
 *
 *  This method accepts the challenge on behalf of the session user.
 *  Only open challenges or those that have been directly
 *  assigned to the session user can be accepted.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_Challenge, SC_ChallengeController_RejectChallenge()
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengeController_AcceptChallenge(
        SC_ChallengeController_h self);

/**
 * @brief Rejects the challenge on behalf of the session user.
 *
 * This method rejects the challenge. Only challenges that have been directly assigned to the
 * session user can be rejected.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_Challenge, SC_ChallengeController_AcceptChallenge()
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengeController_RejectChallenge(
        SC_ChallengeController_h self);

/**
 * @brief Cancels the request.
 *
 * Method to cancel any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the challenge controller instance.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ChallengeController_Cancel(SC_ChallengeController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CHALLENGE_CONTROLLER_H__ */

/*! @} */
