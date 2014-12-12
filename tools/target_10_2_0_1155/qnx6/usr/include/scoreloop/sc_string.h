/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_string.h
 * @brief       String with reference counting.
 *
 * @addtogroup  SC_String
 * @{
 *
 * \ref SC_String is a convenience API that returns
 * a string-like instance using the UTF-8 character
 * data supplied.
 */

#ifndef __SC_STRING_H__
#define __SC_STRING_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_object.h>
#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque string handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_String_tag* SC_String_h;

/** Type descriptors for SC_String. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_String);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Creates a string instance.
 *
 * This method creates an instance of SC_String.
 * The string instance is created with a reference count equal to 1.
 *
 * @param   pSelf Opaque handle of the string instance created.
 * @param   text  A pointer to the UTF-8 encoded char data.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_String_New(SC_String_h* pSelf, const char* text);

/**
 * @brief Creates a string instance, which is a subset of the given array of chars.
 *
 * This method creates an instance of SC_String, copying the length from a given buffer.
 * The string instance is created with a reference count equal to 1.
 *
 * @param   pSelf  Opaque handle of the string instance created.
 * @param   text   A pointer to the UTF-8 encoded char data.
 * @param   length Number of chars to copy.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_String_NewWithLength(SC_String_h* pSelf, const char* text, unsigned int length);

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count of the string instance by 1.
 *
 * @param self An opaque handle for the current string.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_String_Retain(SC_String_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count of the current string instance. The current instance will be deleted automatically when the reference count reaches 0.
 *
 * Note that this method is NULL pointer safe. That is, NULL as an argument will not cause an exception.
 *
 * @param self An opaque handle for the current string instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_String_Release(SC_String_h self);

/**
 * @brief Gets the data owned by SC_String.
 *
 * This method provides access to the data owned by the SC_String.
 *
 * @param self An opaque handle for the current string instance.
 * @return const char* A pointer to the UTF-8 char data owned by the SC_String.
 *
 * @since 10.0.0
 */
SC_PUBLISHED const char* SC_String_GetData(SC_String_h self);

/**
 * @brief Compares two strings (case sensitive).
 *
 * This method performs a byte wise comparison of the UTF-8 data of the two strings. Note that strings on the Scoreloop servers might be normalized and change the byte sequence.
 * For a string comparison of composed Unicode vs. decomposed Unicode, please resort to a higher-level library like ICU or Qt.
 *
 * @param self  An opaque handle for the current string instance.
 * @param other The handle for the other string instance.
 * @return SC_Bool_t returns SC_TRUE if they are equal and SC_FALSE if not equal.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_String_Equals(SC_String_h self, SC_String_h other);

/**
 * @brief Compares two strings (case sensitive).
 *
 * This method compares whether two strings are equal.
 *
 * @param self An opaque handle for the current string instance.
 * @param other The other string instance.
 * @return int Returns relation between two strings, based on bytewise comparison
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_String_Compare(SC_String_h self, const char *other);

/*-------------------------------------------------------------------------------------*
 * Macros
 *-------------------------------------------------------------------------------------*/

/**
 * Macro assigns char * ptr (also NULL) to SC_String_h lvalue field
 * and modifies retCode depending on the success of the operation.
 *
 * @since 10.0.0
 */

#define SC_STR_SETPCHAR(retCode, lvalue, ptr)\
    do {\
       char *_ptr = (char *)(ptr);\
       SC_String_h pString = NULL;\
       if(_ptr == NULL) {\
            SC_String_Release(lvalue);\
            lvalue = NULL;\
            retCode = SC_OK;\
       } else {\
            retCode = SC_String_New(&pString, (_ptr));\
            if(retCode == SC_OK) {\
                SC_String_Release(lvalue);\
                lvalue = pString;\
            }\
        }\
    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* __SC_STRING_H__ */

/*! @} */
