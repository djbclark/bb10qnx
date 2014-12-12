/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_games_search_list.h
 * @brief       Definitions of games search lists available on server.
 *
 * @addtogroup  SC_GamesSearchList
 * @{
 *
 * \ref SC_GamesSearchList in an abstraction for filtering games that are stored on the Scoreloop servers.
 *
 * Games search lists are used by the \ref SC_GamesController to filter games respectively.
 *
 * Games search lists can be set up to filter games according to:
 * - all games (filtering is turned off),
 * - games of current user buddies,
 * - featured games,
 * - popular games,
 * - new games.
 */

#ifndef __SC_GAMES_SEARCH_LIST_H__
#define __SC_GAMES_SEARCH_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Possible list of games, that can be loaded from server. 
 *
 * @since 10.0.0
 */
typedef enum SC_GamesSearchList_tag {
    SC_GAMES_SEARCH_LIST_ALL,           /**< All games for all platforms. */
    SC_GAMES_SEARCH_LIST_BUDDIES,       /**< Games played by friends of the session user. */
    SC_GAMES_SEARCH_LIST_FEATURED,      /**< Currently featured games. */
    SC_GAMES_SEARCH_LIST_POPULAR,       /**< Currently popular games. */
    SC_GAMES_SEARCH_LIST_NEW            /**< Recently released games. */
} SC_GamesSearchList_t;

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAMES_SEARCH_LIST_H__ */

/*! @} */
