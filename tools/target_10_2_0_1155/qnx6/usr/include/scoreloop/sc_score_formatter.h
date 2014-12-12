/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_score_formatter.h
 * @brief       Utility class for formatting the game's score.
 *
 * @addtogroup  SC_ScoreFormatter
 * @{
 *
 * \ref SC_ScoreFormatter allows you to configure and display the score as required.
 *
 * -# Create an SLScoreFormatter.strings file. The Score Definition section on the <a href="https://developer.scoreloop.com" target="_blank">developer website</a> offers a score formatter,
 * to configure the score to meet your game's requirements. Edit, copy and save the score formatter to SLScoreFormatter.strings.
 * Additionally, the "Get Leaderboard Widget" link offers a preview of the formatted scores. It is important that the SLScoreFormatter.strings file contains your modified configuration.
 * The widget is useful to display your game's score on a website.
 * -# Use the following bar-descriptor.xml entry to add the SLScoreFormatter.strings file to the scoreloop directory of your game project. Make sure to first create the scoreloop subdirectory.
 * <table><tr><td>
 * @code
 *
 * <asset path="SLScoreFormatter.strings">scoreloop/SLScoreFormatter.strings</asset>
 *
 * @endcode
 * </td></tr></table>
 * -# Use the client instance to get the score formatter by calling SC_Client_GetScoreFormatter().
 * -# For each score in the score list that is returned, call SC_ScoreFormatter_FormatScore(). Release the \ref SC_String instance that is created.
 *
 * Steps 3 and 4 can be implemented in the load Leaderboard Completion callback or wherever you want to display scores (for example, during score submission).
 *
 * See @link coresocial-leaderboards Leaderboards @endlink for sample code to integrate the score formatter.
 */

#ifndef __SC_SCORE_FORMATTER_H__
#define __SC_SCORE_FORMATTER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_score.h>
#include <scoreloop/sc_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ScoreFormatter object handle. */
typedef struct SC_ScoreFormatter_tag* SC_ScoreFormatter_h;

/** Type descriptors for SC_ScoreFormatter. */
SC_TYPEINFO(SC_ScoreFormatter);

/** Supported score formats */
typedef enum SC_ScoreFormat_tag {
    SC_SCORE_FORMAT_DEFAULT = 0, 
    SC_SCORE_FORMAT_SCORES_ONLY,
    SC_SCORE_FORMAT_LEVEL_AND_MODE,
    SC_SCORE_FORMAT_LEVEL_ONLY,
    SC_SCORE_FORMAT_MODE_ONLY,
    SC_SCORE_FORMAT_NO_LEVEL,
    SC_SCORE_FORMAT_SCORES_AND_LEVEL,

    SC_SCORE_FORMATS_COUNT
} SC_ScoreFormat_t;

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Formats the given SC_Score object into a string using a given format.
 *
 * This method creates a new instance of SC_String, with a reference count
 * equal to 1. It must be released by the caller.
 *
 * @param self      An opaque handle of the SC_ScoreFormatter instance.
 * @param score    A score to format.
 * @param format   A format string to use to format the score, @see SC_ScoreFormat_t.
 * @param pString   Out: pointer to the handle of the SC_String instance created.
 * @return SC_Error_t   An error code (a value of SC_OK indicates success,
 *                      any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_ScoreFormatter_FormatScore(SC_ScoreFormatter_h self,
        SC_Score_h score, SC_ScoreFormat_t format, SC_String_h* pString);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORE_FORMATTER_H__ */

/*! @} */
