/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_game_handle.h
 * @brief       An abstract handle for the game.
 *
 * @addtogroup  SC_GameHandle
 * @{
 *
 * An abstract handle for the game.
 */

#ifndef __GAME_HANDLE_H__
#define __GAME_HANDLE_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/
#include <scoreloop/sc_object.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GameHandle object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_GameHandle_tag* SC_GameHandle_h;

/** Type descriptors for SC_GameHandle. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GameHandle);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count by one.
 *
 * @param self An opaque handle for the current game instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameHandle_Retain(SC_GameHandle_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count by one. The SC_GameHandle instance
 * will be automatically deleted when the counter reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current game instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameHandle_Release(SC_GameHandle_h self);

/**
 * @brief Compares two handles.
 *
 * This method compares two handles.
 *
 * @param self An opaque handle.
 * @param other An opaque handle to the other object to compare.
 * @return SC_Bool_t SC_TRUE if handles represent the same entity. SC_FALSE otherwise.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_GameHandle_Equals(SC_GameHandle_h self, SC_GameHandle_h other);

#ifdef __cplusplus
}
#endif

#endif /* __GAME_HANDLE_H__ */

/*! @} */

