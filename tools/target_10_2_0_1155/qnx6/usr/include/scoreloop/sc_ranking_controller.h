/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @file        sc_ranking_controller.h
 * @brief       SC_RankingController - controller class for high-score rank query
 *
 * @addtogroup  SC_RankingController
 * @{
 *
 * Instances of \ref SC_RankingController are used to retrieve
 * the rank for a given user or score. The rank represents
 * the position of a user or score on a particular leaderboard.
 *
 * Basic Usage:
 * -# Get an instance of \ref SC_Client.
 * -# Use the client instance to get an instance of \ref SC_RankingController by calling SC_Client_CreateRankingController().
 * -# Set the searchlist for the \ref SC_RankingController
 *    using the SC_RankingController_SetSearchList() method.
 * -# Request the ranking from the server using one of:
 *		- SC_RankingController_LoadRankingForUserInMode()
 *		- SC_RankingController_LoadRankingForScore()
 * -# Await a successful server response via delegate callbacks.
 * -# After a successful server response, access the requested
 *    rank by calling SC_RankingController_GetRanking().
 * -# If you wish to display the highest score associated with a user, you could call 
 *    SC_RankingController_GetScore(), which would return the score object associated with the user.
 */

#ifndef __SC_RANKING_CONTROLLER_H__
#define __SC_RANKING_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_session.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_scores_search_list.h>
#include <scoreloop/sc_scores_controller.h>
#include <scoreloop/sc_score.h>
#include <scoreloop/sc_user.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_RankingController object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_RankingController_tag* SC_RankingController_h;

/** Type descriptors for SC_RankingController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_RankingController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Set the search list used for subsequent requests.
 * 
 * This method sets the searchlist for the current controller instance.
 *
 * @param self An opaque handle for the current controller instance.
 * @param searchList The searchlist to be set for the controller.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_RankingController_SetSearchList(SC_RankingController_h self,
        const SC_ScoresSearchList_t searchList);

/**
 * @brief Returns the search list assigned to the current controller instance.
 *
 * This method returns previously set search list instance.
 *
 * @param self An opaque handle for the current controller instance.
 * @return SC_ScoreSearchList_t The search list instance associated with the current controller instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_ScoresSearchList_t SC_RankingController_GetSearchList(SC_RankingController_h self);

/**
 * @brief Requests the ranking of a given score. 
 *
 * This method is used to request the ranking for a given score.
 * Search list with countrySelector equal SC_COUNTRY_SELECTOR_USER_NATIONALITY is not supported in this case.
 *
 * Note that this is an asynchronous call and a callback will be triggered after which you could access the retrieved ranking by calling SC_RankingController_GetRanking().
 *
 * @param   self      An opaque handle for the current controller instance.
 * @param   score     The score whose rank is to be retrieved.
 * @return  SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_RankingController_LoadRankingForScore(
        SC_RankingController_h self, SC_Score_h score);

/**
 * @brief Requests the ranking of a given user for a given mode.
 *
 * This method is used to request the ranking of a given user.
 *
 * Note that this is an asynchronous call and a callback will be triggered after which you could access the retrieved ranking by calling SC_RankingController_GetRanking().
 *
 * @param   self An opaque handle for the current controller instance.
 * @param   user The user for whom the ranking is to be requested.
 * @param   mode The ranking mode
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_RankingController_LoadRankingForUserInMode(
        SC_RankingController_h self, SC_User_h user, unsigned int mode);

/**
 * @brief Returns the ranking that is retrieved after making a successful server request. 
 *
 * After a successful server request, use this method to return the 
 * rank that was requested. 
 * 
 * @param   self An opaque handle for the current controller instance. 
 * @return An unsigned int corresponding to the rank that was retrieved. If the requested rank is not part of the leaderboard, SC_SCORE_RANK_OUT_OF_RANGE is returned.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_RankingController_GetRanking(SC_RankingController_h self);

/**
 * @brief Accessor that returns the received total number of scores.
 *
 * This method is used to get the total number of scores used for ranking purposes.
 *
 * @param   self An opaque handle of the rankingController
 * @return unsigned int corresponding to the total number of scores returned. 
 * by the server.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_RankingController_GetTotal(SC_RankingController_h self);

/**
 * @brief Increments object's reference count.
 * 
 * This method increments the reference count of the
 * current controller instance.
 * 
 * @param   self  An opaque handle for the current controller instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_RankingController_Retain(SC_RankingController_h self);

/**
 * @brief Decrements object's reference count, deletes the object if counter reaches 0.
 * 
 * This method decrements the reference count for the current controller
 * instance. The current instance will be deleted when the reference
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe, i.e. NULL as an argument will 
 * not cause an exception.
 *
 * @param   self  An opaque handle for the current controller instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_RankingController_Release(SC_RankingController_h self);

/**
 * @brief Returns the score object which is retrieved from the server and associated with a rank or user.
 *
 * Method to return the score object associated with a rank/user. 
 * For example if you want to display the score in addition 
 * to the rank for a particular user, you could call this method.
 *
 * @param   self  An opaque handle for the current controller instance.  
 * @return SC_Score_h The score object associated with the rank that is retrieved.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Score_h SC_RankingController_GetScore(SC_RankingController_h self);

/**
 * @brief Method for Request Cancellation.
 *
 * Method to cancel or abort any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the ranking controller instance.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_RankingController_Cancel(SC_RankingController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_RANKING_CONTROLLER_H__ */

/*! @} */
