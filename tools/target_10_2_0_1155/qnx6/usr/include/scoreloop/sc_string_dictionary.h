/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_string_dictionary.h
 * @brief       String-key, string-value dictionary.
 *
 * @addtogroup  SC_StringDictionary
 * @{
 *
 * String-key, string-value dictionary.
 */

#ifndef __SC_STRING_DICTIONARY_H__
#define __SC_STRING_DICTIONARY_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/
/** Opaque SC_StringDictionary object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_StringDictionary_tag *SC_StringDictionary_h;

/** Type descriptors for SC_StringDictionary. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_StringDictionary);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments object's reference count
 *
 * This method increments the reference count of the SC_StringDictionary instance.
 *
 * @param self An opaque handle for the SC_StringDictionary.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_StringDictionary_Retain(SC_StringDictionary_h self);

/**
 * @brief Decrements object's reference count, deletes the object if counter reaches 0.
 *
 * This method decrements the reference count of the SC_Dictionary instance.
 * The instance will be automatically deleted when the reference count reaches 0.
 *
 * @param self An opaque handle for the SC_StringDictionary instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_StringDictionary_Release(SC_StringDictionary_h self);

/**
 * @brief Returns a value for a given key.
 *
 * This method returns a value for a given key.
 *
 * @param self   An opaque handle for the SC_StringDictionary instance.
 * @param key    Key string for which to retrieve the value.
 * @return SC_String_h The value kept under given key or @c NULL, when not found.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_StringDictionary_Get(SC_StringDictionary_h self, const char* key);


/**
 * @brief (Re)starts dictionary iteration.
 *
 * Dictionary supports very simple iteration model. There can only be one iteration at a time. 
 * This call starts the iteration if it is not ongoing, or restarts current iteration from the first key/value pair.
 *
 * @param self An opaque handle for the SC_StringDictionary instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_StringDictionary_StartIteration(SC_StringDictionary_h self);

/**
 * @brief Returns next iterated key/value pair.
 *
 * This method returns next iterated key/value pair.
 *
 * @param self   An opaque handle for the SC_StringDictionary instance.
 * @param pKey   Where to store the key string pointer (can be NULL).
 * @param pValue Where to store the value object reference (can be NULL).
 * @return  SC_Bool_t (SC_TRUE if there was a next pair, in such case, or, SC_FALSE  if iteration ended, in such case pKey and pValue are not modified
 *
 * Note: it is up to the user to ensure that the dictionary is not modified during the iteration.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_StringDictionary_NextPair(SC_StringDictionary_h self,
        const char** pKey, SC_String_h* pValue);

/**
 * @brief Returns the number of items stored in the dictionary.
 *
 * This method returns the number of items stored in the dictionary.
 *
 * @param self   An opaque handle for the dictionary instance.
 * @return unsigned int The number of items.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_StringDictionary_GetCount(SC_StringDictionary_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_STRING_DICTIONARY_H__ */

/*! @} */
