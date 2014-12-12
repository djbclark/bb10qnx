/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief       Models the collection of the SC_Activity that are available in the game.
 * @file        sc_activity_list.h
 *
 * @addtogroup  SC_ActivityList
 * @{
 *
 * The collection of the \ref SC_Activity that is available in the game.
 */

#ifndef __SC_ACTIVITY_LIST_H__
#define __SC_ACTIVITY_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_activity.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ActivityList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_ActivityList_tag* SC_ActivityList_h;

/** Type descriptors for SC_ActivityList. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_ActivityList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current SC_ActivityList instance.
 *
 * @param self An opaque handle for the current SC_ActivityList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ActivityList_Retain(SC_ActivityList_h self);

/**
 * @brief Decrements the object's reference count; deletes the object if counter reaches 0
 *
 * This method decrements the reference count for the current SC_ActivityList instance.
 * The current instance will be deleted automatically when the reference count reaches 0.
 *
 * Note that this method is NULL pointer safe, that is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_ActivityList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ActivityList_Release(SC_ActivityList_h self);

/**
 * @brief Retrieves a specific activity from the list.
 *
 * This method returns the activity at the given index in the list.
 *
 * @param self An opaque handle for the current SC_ActivityList instance.
 * @param index The index of the score to be retrieved.
 * @return SC_Activity_h The activity at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Activity_h SC_ActivityList_GetAt(SC_ActivityList_h self,
        unsigned int index);

/**
 * @brief Returns the number of activities on the list.
 *
 * This method returns the number of activities that are retrieved from the server.
 *
 * @param self An opaque handle for the current SC_ActivityList instance.
 * @return unsigned int The count of activities
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_ActivityList_GetCount(SC_ActivityList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ACTIVITY_LIST_H__ */

/*! @} */
