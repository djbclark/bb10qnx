/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_user_handle.h
 * @brief       An abstract handle for the user.
 *
 * @addtogroup  SC_UserHandle
 * @{
 *
 * An abstract handle for the user.
 */

#ifndef __USER_HANDLE_H__
#define __USER_HANDLE_H__

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

/** Opaque SC_UserHandle object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_UserHandle_tag* SC_UserHandle_h;

/** Type descriptors for SC_UserHandle. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_UserHandle);

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
SC_PUBLISHED void SC_UserHandle_Retain(SC_UserHandle_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count by one. The \ref SC_GameHandle instance
 * will be automatically deleted when the counter reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current game instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UserHandle_Release(SC_UserHandle_h self);

/**
 * @brief Compares two handles.
 *
 * This method compares two handles that is passed to the method.
 *
 * @param self An opaque handle.
 * @param other An opaque handle to the other object to compare.
 * @return SC_Bool_t SC_TRUE if handles represent the same entity. SC_FALSE otherwise.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_UserHandle_Equals(SC_UserHandle_h self, SC_UserHandle_h other);

#ifdef __cplusplus
}
#endif

#endif /* __USER_HANDLE_H__ */

/*! @} */

