/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_game_item_list.h
 * @brief       Class that models the collection of the SC_GameItem available in the game.
 *
 * @addtogroup  SC_GameItemList
 * @{
 *
 * Class that models the collection of the \ref SC_GameItem available in the game.
 */

#ifndef __SC_GAME_ITEM_LIST_H__
#define __SC_GAME_ITEM_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_game_item.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GameItemList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_GameItemList_tag* SC_GameItemList_h;

/** Type descriptors for SC_GameItemList. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GameItemList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the object's reference count.
 *
 * @param self An opaque handle for the current SC_GameItemsList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItemList_Retain(SC_GameItemList_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the object's reference count by one. 
 * The object will be deleted automatically if the reference 
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_GameItemList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItemList_Release(SC_GameItemList_h self);

/**
 * @brief Retrieves specific game item from the list.
 *
 * This method returns the game item at the given index in the list.
 *
 * @param self An opaque handle for the current SC_GameItemList instance.
 * @param index The index of the game item to be retrieved.
 * @return SC_GameItem_h The game item at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameItem_h SC_GameItemList_GetAt(SC_GameItemList_h self, unsigned int index);

/**
 * @brief Returns the number of game items on the list.
 *
 * This method returns the number of games kept on the list.
 *
 * @param self An opaque handle for the current SC_GameItemList instance.
 * @return unsigned int The count of game items
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_GameItemList_GetCount(SC_GameItemList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAME_ITEM_LIST_H__ */

/*! @} */
