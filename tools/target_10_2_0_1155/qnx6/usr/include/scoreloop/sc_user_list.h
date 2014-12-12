/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_user_list.h
 * @brief       Class that models the collection of SC_Users in the game.
 *
 * @addtogroup  SC_UserList
 * @{
 *
 * Class that models the collection of \ref SC_User in the game.
 */

#ifndef __SC_USER_LIST_H__
#define __SC_USER_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_user.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_UserList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_UserList_tag* SC_UserList_h;

/** Type descriptors for SC_UserList. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_UserList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current \ref SC_UserList instance.
 *
 * @param self An opaque handle for the current SC_UserList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UserList_Retain(SC_UserList_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0
 *
 * This method decrements the reference count for the current \ref SC_UserList instance.
 * The current instance will be automatically deleted when the reference count reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_UserList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UserList_Release(SC_UserList_h self);

/**
 * @brief Retrieves a specific user from the list.
 *
 * This method returns the user at the given index in the list.
 *
 * @param self An opaque handle for the current SC_UserList instance.
 * @param index The index of the score to be retrieved.
 * @return SC_User_h The user at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_UserList_GetAt(SC_UserList_h self, unsigned int index);

/**
 * @brief Returns the number of users on the list.
 *
 * This method returns the total number of users on the list.
 *
 * @param self An opaque handle for the current SC_UserList instance.
 * @return unsigned int The number of users on the list.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_UserList_GetCount(SC_UserList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_USER_LIST_H__ */

/*! @} */
