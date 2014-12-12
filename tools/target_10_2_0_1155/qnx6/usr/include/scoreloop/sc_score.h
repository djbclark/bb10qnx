/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_score.h
 * @brief       Models the score achieved by a particular user in a particular game session.
 *
 * @addtogroup  SC_Score
 * @{
 *
 * Instances of \ref SC_Score model the score achieved by a particular user in a particular game session.
 *
 * Instances of \ref SC_Score must contain, at minimum, a result, which
 * is typically the main numerical outcome achieved by a user of the game.
 * A Score is achieved by a player of your game at the end of gameplay.
 *
 * - Result is the primary score that is achievable in your game.
 * - A score can be a simple numerical score, one that is based on time or something more complex, 
 * having multiple criteria, such as the number of hits made, the average speed, or the maximum speed.
 * - You can model the score using the following:
 *  - Result: Primary score, mandatory
 *  - Minor result: secondary score, optional
 *  - Level: secondary score, optional
 * - A score is submitted to the server. Score sorting decides the winner of a challenge and the leaderboard rankings.
 * - Scores can be sorted in ascending or descending order.
 *  - Descending order: Highest score is on top.
 *  - Ascending order:  Lowest score is on top. E.g., the fastest user wins a game; sorting as time.
 * - If modes are defined, Scoreloop generates separate leaderboards for each mode in the game.
 * 
 * The result, minor result, and level are used to compare scores. You can configure the comparison schema 
 * on our <a href="https://developer.scoreloop.com" target="_blank">developer website</a>.
 * 
 * Two data controllers that manage the scores are:
 * - An \ref SC_ScoreController, which manages single instances of \ref SC_Score
 * - An \ref SC_ScoresController, which manages lists of \ref SC_Score
 *
 * Instances of \ref SC_Score can also contain information about score rank, which is the
 * position of the score on a Scoreloop leaderboard. However, the rank of a score
 * will generally only have a meaningful value when it is retrieved from the
 * server using an \ref SC_ScoresController.
 *
 * Basic use:
 * Score objects are returned in the following scenarios:
 * - After creating a score object by calling SC_Client_CreateScore()
 * - From a \ref SC_ScoresController after the controller has requested scores from the server,
 *   the list of score objects can be accessed by using the calling SC_ScoresController_GetScores().
 *
 * @sa SC_ScoreController, SC_ScoresController, @link coresocial-leaderboards Leaderboards @endlink
 */

#ifndef __SC_SCORE_H__
#define __SC_SCORE_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_context.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_user.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Score object handle. */
typedef struct SC_Score_tag* SC_Score_h;

/** Type descriptors for SC_Score. */
SC_TYPEINFO(SC_Score);

/*-------------------------------------------------------------------------------------*
 * Constants
 *-------------------------------------------------------------------------------------*/

/** Constant used to mark a score level as undefined */
#define SC_SCORE_LEVEL_UNDEFINED    (MAX_UINT)

/** Constant used to mark a score mode as undefined */
#define SC_SCORE_MODE_UNDEFINED     (MAX_UINT)

/** Constant used to mark a score rank as undefined */
#define SC_SCORE_RANK_UNDEFINED     (MAX_UINT)

/** Constant used to mark a score rank as not part of a leaderboard */
#define SC_SCORE_RANK_OUT_OF_RANGE  (0)

/** Maximum allowed value for score's mode  */
#define SC_SCORE_MODE_MAX           (MAX_INT)

/** Maximum allowed value for score's level  */
#define SC_SCORE_LEVEL_MAX          (MAX_INT)

/** Minimum allowed value for score's result and minor result  */
#define SC_SCORE_RESULT_MIN         (-2147483648.0)

/** Maximum allowed value for score's result and minor result  */
#define SC_SCORE_RESULT_MAX         (4294967295.0)

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count for the instance by 1.
 *
 * @param self An opaque handle for the current score instance.
 */
SC_PUBLISHED void SC_Score_Retain(SC_Score_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the instances's reference count by 1.
 * The instance will be deleted automatically when the reference count reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will not cause an exception.
 *
 * @param self An opaque handle for the current score instance.
 */
SC_PUBLISHED void SC_Score_Release(SC_Score_h self);

/**
 * @brief Set the result of the score.
 *
 * This method sets the result property for the score. The result is generally the main numerical result achieved by a user in the game.
 *
 * @param self An opaque handle for the current score instance.
 * @param result The score result that is being set.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Score_SetResult(SC_Score_h self, double result);

/**
 * @brief Gets the result of the score.
 *
 * This method returns the result property of the score instance.
 *
 * @param self An opaque handle for the current score instance.
 * @return double A double representing the score result.
 */
SC_PUBLISHED double SC_Score_GetResult(SC_Score_h self);

/**
 * @brief Sets the minor result of the score.
 *
 * This method sets the minor result property for the score. The minor result is a secondary result
 * that can be optionally used for score comparison purposes.
 *
 * @param self An opaque handle for the current score instance.
 * @param minorResult The minor result that is being set.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Score_SetMinorResult(SC_Score_h self, double minorResult);

/**
 * @brief Gets the minor result of the score
 *
 * This method returns the minor result for the current score instance. The minor
 * result is a secondary result that can be optionally used for score comparison purposes.
 *
 * @param self An opaque handle for the current score instance.
 * @returns A double representing the minor result of the current score instance.
 */
SC_PUBLISHED double SC_Score_GetMinorResult(SC_Score_h self);

/**
 * @brief Sets the level of the score.
 *
 * This method sets the level that the current score was achieved at. The level represents
 * the game stage that the score was achieved at and may optionally be used for score comparison purposes.
 *
 * @param self An opaque handle for the current score instance.
 * @param level A unsigned int corresponding to the game level.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Score_SetLevel(SC_Score_h self, unsigned int level);

/**
 * @brief Gets the level of the score
 *
 * This method returns the level at which the current score instance was achieved.
 *
 * @param self An opaque handle for the current score instance.
 * @return unsigned int Corresponding to the level the
 * score was achieved at.
 */
SC_PUBLISHED unsigned int SC_Score_GetLevel(SC_Score_h self);

/**
 * @brief Sets the mode of the score.
 *
 * This method sets the mode at which the score was achieved. The mode refers to the gameplay setting at which the score was achieved, 
 * for example, slow/medium/fast. Scoreloop generates separate leaderboards for each mode in a game.
 *
 * @param self An opaque handle for the current score instance.
 * @param mode The mode to be set.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Score_SetMode(SC_Score_h self, unsigned int mode);

/**
 * @brief Gets the mode of the score
 *
 * This method returns the mode at which the score was achieved.
 *
 * @param self An opaque handle for the current score instance.
 * @return unsigned int Corresponding to the mode the score was achieved at.
 */
SC_PUBLISHED unsigned int SC_Score_GetMode(SC_Score_h self);

/**
 * @brief Gets the rank of the score
 *
 * This method returns the rank for the score.
 * The rank refers to the score's position on a leaderboard and as such, this will only have a meaningful value if the score is returned using a \ref SC_ScoresController.
 *
 * @param self An opaque handle for the current score instance.
 * @return unsigned int Corresponding to the score rank.
 */
SC_PUBLISHED unsigned int SC_Score_GetRank(SC_Score_h self);

/**
 * @brief Gest the user who submitted the score.
 *
 * This method returns the user who obtained and submitted the score.
 *
 * @param self An opaque handle for the current score instance.
 * @return SC_User_h The user who obtained and submitted the score.
 */
SC_PUBLISHED SC_User_h SC_Score_GetUser(SC_Score_h self);

/**
 * @brief Accessor that returns the context associated with score.
 *
 * If there's no context associated with the score, this method returns @c NULL.
 *
 * @param self An opaque handle for the current score instance.
 * @return     SC_Context Context of the score.
 */
SC_PUBLISHED SC_Context_h SC_Score_GetContext(SC_Score_h self);

/**
 * @brief Sets the score context.
 *
 * Sets the score context. The amount of information that is stored as part of the context should be kept to a minimum.
 *
 * @param self        An opaque handle for the current score instance.
 * @param context     New user's context
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Score_SetContext(SC_Score_h self, SC_Context_h context);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORE_H__ */

/*! @} */
