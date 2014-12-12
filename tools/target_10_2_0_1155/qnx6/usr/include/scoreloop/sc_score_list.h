/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_score_list.h
 * @brief       Models the collection of SC_Scores.
 *
 * @addtogroup  SC_ScoreList
 * @{
 *
 * Instances of \ref SC_ScoreList store the list of scores that
 * are retrieved from the server after making a successful request by
 * using an instance of \ref SC_ScoresController.
 *
 * Basic use:
 * -# Get an instance of \ref SC_ScoresController.
 * -# Use the controller to request scores from the server.
 * -# Wait for a successful server request via delegate callbacks.
 * -# After a successful request, use SC_ScoresController_GetScores() to access the score list that is returned.
 * -# Access individual scores in the list using SC_ScoreList_GetAt().
 *
 * @sa SC_ScoresController, @link coresocial-leaderboards About Scores and Leaderboards @endlink.
 */

#ifndef __SC_SCORE_LIST_H__
#define __SC_SCORE_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_score.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ScoreList object handle. */
typedef struct SC_ScoreList_tag* SC_ScoreList_h;

/** Type descriptors for SC_ScoreList. */
SC_TYPEINFO(SC_ScoreList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current SC_ScoreList instance.
 *
 * @param self An opaque handle for the current SC_ScoreList instance.
 */
SC_PUBLISHED void SC_ScoreList_Retain(SC_ScoreList_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0
 *
 * This method decrements the reference count for the current SC_ScoreList instance.
 * The current instance will be automatically deleted when the reference count reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_ScoreList instance.
 */
SC_PUBLISHED void SC_ScoreList_Release(SC_ScoreList_h self);

/**
 * @brief Retrieves a specific score from the list.
 *
 * This method returns the score at the given index in the list.
 *
 * @param self An opaque handle for the current SC_ScoreList instance.
 * @param index The index of the score to be retrieved.
 * @return SC_Score_h The score at the given index.
 */
SC_PUBLISHED SC_Score_h SC_ScoreList_GetAt(SC_ScoreList_h self, unsigned int index);

/**
 * @brief Returns the number of scores on the list that is returned from the server.
 *
 * This method returns the number of scores that have been requested from the server by
 * using one of the following load methods:
 * - SC_ScoresController_LoadScores()
 * - SC_ScoresController_LoadScoresAroundScore()
 * - SC_ScoresController_LoadScoresAroundUser()
 *
 * The rangeLength parameter passed to these load methods determines how many scores are to
 * be retrieved.
 *
 * @param self An opaque handle for the current SC_ScoreList instance.
 * @return unsigned int The number of scores in the list that is returned.
 */
SC_PUBLISHED unsigned int SC_ScoreList_GetCount(SC_ScoreList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORE_LIST_H__ */

/*! @} */
