/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_string_list.h
 * @brief       SC_StringList class
 *
 * @addtogroup  SC_StringList
 * @{
 * This file is used to store a list of strings.
 */

#ifndef __SC_STRING_LIST_H__
#define __SC_STRING_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_StringList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_StringList_tag* SC_StringList_h;

/** Type descriptors for SC_StringList.
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_StringList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments object's reference count.
 *
 * This method increments the reference count for the current \ref SC_StringList instance.
 *
 * @param self An opaque handle for the current SC_StringList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_StringList_Retain(SC_StringList_h self);

/**
 * @brief Decrements object's reference count, deletes the object if counter reaches 0
 *
 * This method decrements the reference count for the current \ref SC_StringList instance.
 * The current instance will be automatically deleted when the reference count reaches 0.
 *
 * @param self An opaque handle for the current SC_StringList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_StringList_Release(SC_StringList_h self);

/**
 * @brief Retrieves a specific string from the list.
 *
 * This method returns the string at the given index in the list.
 *
 * @param self An opaque handle for the current SC_StringList instance.
 * @param index The index of the score to be retrieved.
 * @return SC_String_h The string at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_StringList_GetAt(SC_StringList_h self, unsigned int index);

/**
 * @brief Returns the number of strings on the list.
 *
 * This method returns the total number of strings on the list.
 *
 * @param self An opaque handle for the current SC_StringList instance.
 * @return unsigned int The number of strings in the list.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_StringList_GetCount(SC_StringList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_STRING_LIST_H__ */

/*! @} */
