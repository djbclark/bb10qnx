/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_context.h
 * @brief       Class used to represent arbitrary user/score/challenge data (context).
 *
 * @addtogroup  SC_Context
 * @{
 *
 * Class used to represent arbitrary user/score/challenge data (context).
 */

#ifndef __SC_CONTEXT_H__
#define __SC_CONTEXT_H__

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
/** Opaque SC_Context object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_Context_tag *SC_Context_h;

/** Type descriptors for SC_Context. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Context);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Creates a new SC_Context object.
 *
 * This method creates a new SC_Context object.
 *
 * @param pSelf An opaque handle for the SC_Context instance.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 *
 */
SC_PUBLISHED SC_Error_t SC_Context_New(SC_Context_h* pSelf);

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the SC_Context
 * instance.
 *
 * @param self An opaque handle for the SC_Context instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Context_Retain(SC_Context_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count of the SC_Context instance.
 * The instance will be automatically deleted when the reference count
 * reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the SC_Context instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Context_Release(SC_Context_h self);

/**
 * @brief Assigns a value for a given key.
 *
 * If any value was already assigned to a given key, it is replaced. If the method completes
 * successfully, a value object is retained.
 *
 * @param self  An opaque handle for the SC_Context instance.
 * @param key   Key string for which to assign the value.
 * @param value A value string to assign to a given key.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Context_Put(SC_Context_h self, const char* key,
        SC_String_h value);

/**
 * @brief Returns a value for a given key.
 *
 * This method returns a value for a given key.
 *
 * @param self   An opaque handle for the SC_Context instance.
 * @param key    Key string for which to retrieve the value.
 * @param pValue Where to store the value string reference.
 * @return SC_Error_t A return code (SC_NOT_FOUND if key is not present in the dictionary, SC_OK otherwise).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Context_Get(SC_Context_h self, const char* key,
        SC_String_h* pValue);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CONTEXT_H__ */

/*! @} */
