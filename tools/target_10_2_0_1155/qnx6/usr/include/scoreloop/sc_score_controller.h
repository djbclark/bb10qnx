/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @file        sc_score_controller.h
 * @brief       The Controller is used to submit a score to the servers.
 *
 * @addtogroup  SC_ScoreController
 * @{
 *
 * Instances of \ref SC_ScoreController are used to submit scores to Scoreloop.
 *
 * Basic use:
 * -# Get an instance of \ref SC_Client.
 * -# Use the client instance to call SC_Client_CreateScoreController().
 * -# Call the SC_ScoreController_SubmitScore() method to submit the score.
 * -# Wait for a successful server response via delegate callbacks.
 */

#ifndef __SC_SCORE_CONTROLLER_H__
#define __SC_SCORE_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_session.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_score.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ScoreController object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_ScoreController_tag* SC_ScoreController_h;

/** Type descriptors for SC_ScoreController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_ScoreController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Submits a given score to the server.
 *
 * This method is used to submit a score to the server.
 * Note that this is an asynchronous call, and a callback will be triggered upon success or failure.
 *
 * @param self An opaque handle for the current controller instance.
 * @param score The score that is to be submitted.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-SubmitScore here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ScoreController_SubmitScore(SC_ScoreController_h self,
        SC_Score_h score);

/**
 * @brief Cancels the request.
 *
 * This method cancels any ongoing request or operation that was initiated by this particular controller instance.
 *
 * @param self An opaque handle of the score controller instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_ScoreController_Cancel(SC_ScoreController_h self);

/**
 * @brief Provides access to the last score that was submitted.
 *
 * Returns the SC_Score_h object that was submitted using the SC_ScoreController_SubmitScore method.
 *
 * @param self An opaque handle of the score controller instance.
 * @return SC_Score_h The last submitted score object.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Score_h SC_ScoreController_GetScore(SC_ScoreController_h self);

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count of the
 * current controller instance.
 *
 * @param self An opaque handle for the current controller.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ScoreController_Retain(SC_ScoreController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the
 * current controller instance. The current instance will
 * be deleted when the reference count reaches 0.
 *
 * Please note that this method is NULL pointer safe, i.e. NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current controller instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ScoreController_Release(SC_ScoreController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORE_CONTROLLER_H__ */

/*! @} */
