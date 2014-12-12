/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @file sc_scores_controller.h
 * @brief  Retrieves lists of score objects from the server.
 *
 * @addtogroup  SC_ScoresController
 * @{
 *
 * Instances of \ref SC_ScoresController retrieve lists of scores from the server.
 *
 * Basic use:
 * -# Get an instance of \ref SC_Client.
 * -# Use the client instance to call SC_Client_CreateScoresController().
 * -# Search criteria can be set as follows:
 *    Specify the search list for the controller by calling SC_ScoresController_SetSearchList().
 *    You can specify the following search lists: 
 *      - SC_SCORES_SEARCH_LIST_ALL
 *      - SC_SCORES_SEARCH_LIST_24H
 *      - SC_SCORES_SEARCH_LIST_USER_COUNTRY.
 * -# Set the mode for the controller by calling SC_ScoresController_SetMode().
 * -# Request the scores by using one of the following loadScores methods:
 *    - SC_ScoresController_LoadScores()
 *    - SC_ScoresController_LoadScoresAroundScore()
 *    - SC_ScoresController_LoadScoresAroundUser()
 * -# Wait for a successful server response via delegate callbacks.
 * -# Once the request is complete, access the scores that were returned by calling SC_ScoresController_GetScores().
 *
 * To page through additional scores:
 * -# Call SC_ScoresController_HasNextRange() and SC_ScoresController_HasPreviousRange() to determine if it is possible to page.
 * -# Use SC_ScoresController_LoadNextRange() or SC_ScoresController_LoadPreviousRange() to request the next or previous list of scores from
 * the server.
 * -# After a successful server response, access the SC_Scores_list that was returned, by calling SC_ScoresController_GetScores().
 */

#ifndef __SC_SCORES_CONTROLLER_H__
#define __SC_SCORES_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_range.h>
#include <scoreloop/sc_session.h>
#include <scoreloop/sc_scores_search_list.h>
#include <scoreloop/sc_score_list.h>
#include <scoreloop/sc_completion_callback.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ScoresController object handle. */
typedef struct SC_ScoresController_tag* SC_ScoresController_h;

/** Type descriptors for SC_ScoresController. */
SC_TYPEINFO(SC_ScoresController);


/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Sets the search list used for subsequent requests.
 *
 * This method specifies the searchlist that will be used
 * during the server request made by the controller. The following pre-defined
 * search lists are currently available : SC_SCORES_SEARCH_LIST_ALL,
 *    SC_SCORES_SEARCH_LIST_24H or SC_SCORES_SEARCH_LIST_USER_COUNTRY.
 *
 * @param self An opaque handle for the current controller instance.
 * @param searchList The search list that is to be set for the controller.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-SetSearchList here@endlink).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_SetSearchList(SC_ScoresController_h self,
        const SC_ScoresSearchList_t searchList);

/**
 * @brief Returns the search list assigned to the current controller instance.
 *
 * This method returns the previously set search list instance.
 *
 * @param self An opaque handle for the current controller instance.
 * @return SC_ScoreSearchList_t The search list instance associated with the current controller instance.
 */
SC_PUBLISHED SC_ScoresSearchList_t SC_ScoresController_GetSearchList(SC_ScoresController_h self);

/**
 * @brief Set the game mode used for subsequent requests.
 *
 * This method sets the mode for the controller. The controller will
 * only retrieve scores whose modes match this value.
 * If no mode is explicitly set for the controller, it will
 * retrieve the scores for mode 0.
 *
 * @param self An opaque handle for the current controller instance.
 * @param mode The mode to be set for the controller.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-SetMode here@endlink).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_SetMode(SC_ScoresController_h self,
        unsigned int mode);

/**
 * @brief Returns the mode assigned to the current controller instance.
 *
 * This method returns the previously set mode value.
 *
 * @param self An opaque handle for the current controller instance.
 * @return unsigned int The mode value associated with the current controller instance.
 */
SC_PUBLISHED unsigned int SC_ScoresController_GetMode(SC_ScoresController_h self);

/**
 * @brief Returns the retrieved list of scores.
 *
 * This method returns the list of scores that were
 * returned by the server. Call this method only
 * after receiving notification of a successful server
 * request via delegate callbacks.
 *
 * @param self An opaque handle for the current controller instance.
 * @return SC_Scorelist_h The list of scores returned by the server.
 */
SC_PUBLISHED SC_ScoreList_h SC_ScoresController_GetScores(SC_ScoresController_h self);

/**
 * @brief Starts loading the next range of scores.
 *
 * This method requests the next available range of scores from the server. 
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you can access the retrieved scores by calling SC_ScoresController_GetScores().
 *
 * @param self An opaque handle for the current controller instance.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_LoadNextRange(SC_ScoresController_h self);

/**
 * @brief Starts loading the previous range of scores.
 *
 * This method requests the previous range of scores from the server. 
 * This method is used for backward pagination. 
 *
 * Note that this is an asynchronous call and a callback will be
 * triggered, after which you can access the retrieved scores by calling SC_ScoresController_GetScores().
 *
 * @param  self An opaque handle for the current controller instance.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_LoadPreviousRange(SC_ScoresController_h self);

/**
 * @brief Checks whether there is a next range (page) of scores.
 *
 * This method checks whether there is a "next range" of scores available from the server. 
 * This method is used to check whether forward pagination through a list of scores is possible.
 *
 * @param self An opaque handle for the current controller instance.
 * @return SC_Bool_t A boolean value indicating whether forward pagination is possible.
 */
SC_PUBLISHED SC_Bool_t SC_ScoresController_HasNextRange(SC_ScoresController_h self);

/**
 * @brief Checks whether there is a previous range (page) of scores.
 *
 * This method checks if a "previous range" of scores is available from the server. 
 * This method is used to check whether backward pagination through a list of scores is possible.
 *
 * @param   self An opaque handle for the current controller instance.
 * @return SC_Bool_t A boolean value indicating if backward pagination is possible.
 */
SC_PUBLISHED SC_Bool_t SC_ScoresController_HasPreviousRange(SC_ScoresController_h self);

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the current instance by 1.
 *
 * @param self An opaque handle for the current controller instance.
 */
SC_PUBLISHED void SC_ScoresController_Retain(SC_ScoresController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the current instance by 1. 
 * The current controller instance will be automatically deleted when the reference count equals 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current controller instance.
 */
SC_PUBLISHED void SC_ScoresController_Release(SC_ScoresController_h self);

/**
 * @brief Returns the requested range to load.
 *
 * This method returns the position from where the scores are loaded
 * using any of the SC_ScoresController's load methods.
 *
 * @param self An opaque handle for the current controller instance.
 * @return SC_Range_t The range requested to load.
 */
SC_PUBLISHED SC_Range_t SC_ScoresController_GetRange(SC_ScoresController_h self);

/**
 * @brief  Cancels any ongoing request or operation initiated by this particular controller instance.
 *
 * This method cancels any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the scores controller instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_Cancel(SC_ScoresController_h self);

/**
 * @brief Starts loading the given range of scores
 *
 * This method requests the list of scores, defined by the supplied range, from the server.
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you can access the
 * retrieved scores by calling SC_ScoresController_GetScores().
 *
 * @param   self  An opaque handle for the current controller instance.
 * @param   range  The starting position and offset of the requested scores range (numbered from 0, the first score to load).
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_LoadScores(SC_ScoresController_h self,
        SC_Range_t range);

/**
 * @brief Starts loading the range of scores beginning at a given rank.
 *
 * Requests the list beginning at the given rank. The rank refers to a score's position on the global leaderboard. 
 * All lists start at 1, therefore the minimum rank possible is 1.
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you can access the
 * retrieved scores by calling SC_ScoresController_GetScores().
 *
 * @param   self  An opaque handle for the current controller instance.
 * @param   rank  The starting position of the range (numbered from 1, the first score to load).
 * @param   rangeLength  The length of the range requested.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-LoadScoresAtRank here@endlink).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_LoadScoresAtRank(SC_ScoresController_h self,
        unsigned int rank, unsigned int rangeLength);

/**
 * @brief Requests the list of scores that includes the given score in the middle.
 *
 * This method returns the list of scores that includes the given score in the middle.
 * The score is included even if it did not make it into the high score list. 
 *
 * Note that this is an asynchronous call and a callback will be
 * triggered, after which you can access the retrieved scores by calling SC_ScoresController_GetScores().
 *
 * @param   self  An opaque handle for the current controller instance.
 * @param   score The score object that appears in the middle of the retrieved list.
 * @param   rangeLength  The length of the range requested.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_LoadScoresAroundScore(SC_ScoresController_h self,
        SC_Score_h score, unsigned int rangeLength);

/**
 * @brief Requests the list of scores that includes the high score of the user in the middle.
 *
 * This method returns the list of scores that includes the high score of the user in the middle. 
 *
 * Note that this is an asynchronous call and a callback will be
 * triggered, after which you can access the retrieved scores by calling SC_ScoresController_GetScores().
 *
 * @param   self  An opaque handle for the current controller instance.
 * @param   user  The user whose top score appears in the middle of the retrieved list.
 * @param   rangeLength  The length of the range requested.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoresController_LoadScoresAroundUser(SC_ScoresController_h self,
        SC_User_h user, unsigned int rangeLength);


#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORES_CONTROLLER_H__ */

/*! @} */
