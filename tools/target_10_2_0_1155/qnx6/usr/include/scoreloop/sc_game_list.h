/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_game_list.h
 * @brief       Class that models the collection of the SC_Game available in the game.
 *
 * @addtogroup  SC_GameList
 * @{
 *
 * Class that models the collection of the \ref SC_Game available in the game.
 */

#ifndef __SC_GAME_LIST_H__
#define __SC_GAME_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_game.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GameList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_GameList_tag* SC_GameList_h;

/** Type descriptors for SC_GameList. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GameList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current SC_GameList instance.
 *
 * @param self An opaque handle for the current SC_GameList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameList_Retain(SC_GameList_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0
 *
 * This method decrements the reference count for the current SC_GameList instance.
 * The current instance will be deleted automatically when the reference count reaches 0.
 *
 * Please note that this method is @c NULL pointer safe, i.e. @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_GameList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameList_Release(SC_GameList_h self);

/**
 * @brief Retrieves specific game from the list.
 *
 * This method returns the game at the given index in the list.
 *
 * @param self An opaque handle for the current SC_GameList instance.
 * @param index The index of the game to be retrieved.
 * @return SC_Games_h The games at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Game_h SC_GameList_GetAt(SC_GameList_h self, unsigned int index);

/**
 * @brief Returns the number of games on the list.
 *
 * This method returns the number of games  kept on the list.
 *
 * @param self An opaque handle for the current SC_GameList instance.
 * @return unsigned int The count of games
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_GameList_GetCount(SC_GameList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAMES_LIST_H__ */

/*! @} */
