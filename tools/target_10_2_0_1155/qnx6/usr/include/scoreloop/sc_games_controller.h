/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup CoreSocial
 * @brief    The GamesController retrieves lists of games from the server.
 * @file    sc_games_controller.h
 * @addtogroup  SC_GamesController
 * @{
 * The \ref SC_GamesController retrieves lists of games from the server.
 *
 */

#ifndef __SC_GAMES_CONTROLLER_H__
#define __SC_GAMES_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_game_list.h>
#include <scoreloop/sc_range.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_games_search_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GamesController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_GamesController_tag* SC_GamesController_h;

/** Type descriptors for SC_GamesController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GamesController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
* @brief Returns the requested range to load for this controller.
*
* The range set by any of the load method set for this controller.
*
* @param   self        SC_GamesController instance handle
 * @return  SC_Range_t  The range of games requested to load for the controller.
 *
 * @since 10.0.0
*/
SC_PUBLISHED SC_Range_t SC_GamesController_GetRange(SC_GamesController_h self);

/**
 * @brief Returns the game list that was loaded from the server.
 *
 * This method returns the games list that was loaded from the server.
 *
 * @param   self        SC_GamesController instance handle.
 * @return  SC_GameList_h The list of games from the query.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameList_h SC_GamesController_GetGames(SC_GamesController_h self);

/**
 * @brief Requests all the games from the server.
 *
 * This method requests all the games from the server.
 * Note that this is an asynchronous call and a callback will be triggered, after which you can call SC_GamesController_GetGames() to access the list that was loaded.
 *
 * @param   self            SC_GamesController instance handle.
 * @param   gamesSearchList The type of filtering used in the query.
 * @param   range           The range of games to load.
 * @return  SC_Error_t      A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GamesController_LoadGames(SC_GamesController_h self,
        SC_GamesSearchList_t gamesSearchList, SC_Range_t range);

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the objects reference count.
 *
 * @param   self        SC_GamesController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GamesController_Retain(SC_GamesController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the objects reference count.
 * The object will be deleted automatically if the reference
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param   self        SC_GamesController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GamesController_Release(SC_GamesController_h self);

/**
 * @brief Method for Request Cancellation.
 *
 * This method cancels any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the score controller instance.
 * @return SC_Error_t   A return code. (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GamesController_Cancel(SC_GamesController_h self);

/**
 * @brief Requests the previous page of the last game list loaded from the server.
 *
 * This method requests the previous page of the last game list loaded from the server.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param   self        SC_GamesController instance handle.
 * @return  SC_Error_t  A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GamesController_LoadPreviousRange(SC_GamesController_h self);

/**
 * @brief Requests the next page of the last game list loaded from the server.
 *
 * This method requests the next page of the last game list loaded from the server.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param   self        SC_GamesController instance handle..
 * @return  SC_Error_t  A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GamesController_LoadNextRange(SC_GamesController_h self);

/**
 * @brief Indicates whether or not a previous range is available.
 *
 * This method returns SC_TRUE if a previous range is available, otherwise it returns SC_FALSE.
 *
 * @param   self        SC_GamesController instance handle.
 * @return SC_Bool_t A Boolean value that indicates whether backward pagination is possible.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_GamesController_HasPreviousRange(SC_GamesController_h self);

/**
 * @brief Indicates whether a next range is available or not.
 *
 * This method returns SC_TRUE if a next range is available, otherwise returns SC_FALSE.
 *
 * @param   self        SC_GamesController instance handle.
 * @return SC_Bool_t A Boolean value which indicates whether forward pagination is possible.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_GamesController_HasNextRange(SC_GamesController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAMES_CONTROLLER_H__ */

/*! @} */
