/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
 * 
 * You must obtain a written license from and pay applicable license fees to QNX 
 * Software Systems before you may reproduce, modify or distribute this software, 
 * or any work that includes all or part of this software.   Free development 
 * licenses are available for evaluation and non-commercial purposes.  For more 
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *  
 * This file may contain contributions from others.  Please review this entire 
 * file for other proprietary rights or license notices, as well as the QNX 
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/ 
 * for other information.
 * $
 */

#if !defined(SYS_STRM_H_INCLUDED)
#define SYS_STRM_H_INCLUDED

#if !defined(__TYPES_H_INCLUDED)
#include <sys/types.h>
#endif

/*
  Dictionary object API

  A dictionary object is a collection of key+value pairs,
  where both the key and the value are strings.
  The API allows the creation of multiple "handles" to a dictionary object
  that can be independently used and destroyed
  by independent components of a program.
  (Note that multiple handles may be represented
  by identical pointer values; you should not compare handles.)
  Since a dictionary, once created, is immutable until destroyed,
  components can access it through their handles
  without worrying about synchronization.
 */

__BEGIN_DECLS

/**
    Dictionary handle used to keep track of dictionary objects.

    As a convention, function parameters and return values
    declared as pointers to non-const strm_dict_t
    indicate that the ownership of the handle
    (i.e. the responsibility for destroying it)
    is transferred to or from the function,
    whereas pointers to const strm_string_t
    indicate that no transfer of ownership occurs.
    When a function returns a pointer to a const strm_dict_t,
    the guaranteed lifetime of the returned handle
    needs to be documented explicitly.
 */
typedef struct strm_dict strm_dict_t;

/**
 *  Create a new handle for an empty dictionary.
 */
strm_dict_t *strm_dict_new( void );

/**
 *  Duplicate a dictionary handle.
 *  Creates a new handle to the dictionary object
 *  referenced by an existing handle.
 */
strm_dict_t *strm_dict_clone( const strm_dict_t *dict );

/**
 *  Destroy a dictionary handle.
 */
int strm_dict_destroy( strm_dict_t *dict );

/**
 *  Add or modify a dictionary entry.
 *  Creates a new dictionary object that is an exact replica of the old object,
 *  except the specified entry is added or modified.
 *  Returns a new handle for the new dictionary object, or NULL on failure.
 *  On success, the original dictionary handle is destroyed.
 */
strm_dict_t *strm_dict_set( strm_dict_t *dict, const char *key, const char *value );

/**
 *  Remove an entry from a dictionary.
 *  Creates a new dictionary object that is an exact replica of the old object,
 *  except the named key is deleted if present.
 *  Returns a new handle for the new dictionary object, or NULL on failure.
 *  On success, the original dictionary handle is destroyed.
 */
strm_dict_t *strm_dict_key_delete( strm_dict_t *dict, char const *key );

/**
 *  Remove an entry from a dictionary by index.
 *  Creates a new dictionary object that is an exact replica of the old object,
 *  except the specified entry is deleted.
 *  Returns a new handle for the new dictionary object,
 *  or NULL on failure (including when the index is out of range).
 *  On success, the original dictionary handle is destroyed.
 */
strm_dict_t *strm_dict_index_delete( strm_dict_t *dict, size_t index );

/**
 *  Return the value of the named entry (or a null pointer if not found).
 *  The returned string is owned by the dictionary object,
 *  and remains valid until the dictionary handle is destroyed.
 */
const char *strm_dict_find_value( const strm_dict_t *dict, const char *key );

/**
 *  Return the index of the named entry if present (or -1 if not).
 */
ssize_t strm_dict_find_index( const strm_dict_t *dict, const char *key );

/**
 *  Return the number of entries in a dictionary.
 */
size_t strm_dict_size( const strm_dict_t *dict );

/**
 *  Return the name of the n-th key in dictionary, as a null-terminated string.
 *  The returned string is owned by the dictionary object,
 *  and remains valid until the dictionary handle is destroyed.
 */
const char *strm_dict_key_get( const strm_dict_t *dict, size_t n );

/**
 *  Return the value of the n-th entry of a dictionary, as a null-terminated string.
 *  The returned string is owned by the dictionary object,
 *  and remains valid until the dictionary handle is destroyed.
 */
const char *strm_dict_value_get( const strm_dict_t *dict, size_t n );




/*
  Shareable string handle API.
  Used by the "advanced" verion of the dictionary API.

  This API allows the creation of multiple "handles" to a string
  that can be independently used and destroyed
  by independent components of a program.
  (Note that multiple handles may be represented
  by identical pointer values; you should not compare handles.)
  Since the string represented by a handle is immutable until destroyed,
  components can access it through their handles
  without worrying about synchronization.
 */

/**
 *  Handle for shareable strings.
 */
typedef struct strm_string strm_string_t;

/**
 *  Create a new string handle from a null-terminated string.
 *  The handle will reference a string identical to the one passed in.
 */
strm_string_t *strm_string_make( const char *cstring );

/**
 *  Allocate a new string object to be filled in by the caller.
 *  The caller must put a null-terminated string in the buffer
 *  before calling strm_string_clone(), strm_string_modify() or strm_string_destroy(),
 *  and not modify it after.
 *  @param len The length of the string to make room for, not including the terminating '\0'
 *  @param handle A pointer to a variable where to store the new string handle
 *  @return A pointer to the first byte of the string buffer, or NULL on error.
 */
char *strm_string_alloc( size_t len, strm_string_t **handle );

/**
 *  Return the pointer to the first character of the string.
 *  The string is null-terminated.
 */
const char *strm_string_get( const strm_string_t *sstr );

/**
 *  Create a new handle to the string represented by an existing handle.
 */
strm_string_t *strm_string_clone( const strm_string_t *sstr );

/**
 *  Destroy a string handle.
 */
int strm_string_destroy( strm_string_t *sstr );


/**
 * Destroy a string handle and create a new handle from a null-terminated string.
 * This is an equivalent of calling strm_string_destroy() and strm_string_make(),
 * but may take a shortcut by reusing the old object's memory.
 * Note: the handle is destroyed even on failure!
 */
strm_string_t *strm_string_modify( strm_string_t *sstr, const char *cstring );



/*
   The "advanced" version of the dictionary API.
   It uses shareable string handles instead of regular C strings.
 */

/**
 *  Add or modify an a dictionary entry.
 *  Equivalent to strm_dict_set(), except it may be more efficient
 *  if you use clones of the same "key" handle repeatedly.
 *  
 *  This call consumes the "key" and "value" handles, even on failure.
 */
strm_dict_t *strm_dict_set_rstr( strm_dict_t *dict, strm_string_t *key, strm_string_t *value );

/**
 *  Return the value of the named entry (or a null pointer).
 *  The returned string handle is owned by the dictionary,
 *  and remains valid until the dictionary handle is destroyed.
 */
const strm_string_t *strm_dict_find_rstr( const strm_dict_t *dict, const char *key );

/**
 *  Return the key of the n-th entry of a dictionary.
 *  The returned string handle is owned by the dictionary,
 *  and remains valid until the dictionary handle is destroyed.
 */
const strm_string_t *strm_dict_key_rstr( const strm_dict_t *dict, size_t n );

/**
 *  Return the value of the n-th entry of a dictionary.
 *  The returned string handle is owned by the dictionary,
 *  and remains valid until the dictionary handle is destroyed.
 */
const strm_string_t *strm_dict_value_rstr( const strm_dict_t *dict, size_t n );



/**
 *  Subtract two dictionaries.
 *  Creates a replica of "left" and removes all those entries
 *  that have matching keys in "right" regardless of their value.
 *  Note that the "left" handle is consumed by this function,
 *  even on a failure, but "right" is not (unless it's the same handle).
 */
strm_dict_t *strm_dict_subtract( strm_dict_t *left, strm_dict_t const *right );

/**
 *  Compare two dictionaries.
 *  Creates a replica of "newdict" and removes all those entries
 *  that also exist in "olddict" and have the same value.
 *  In other words, if "olddict" is an old version of some dictionary
 *  and "newdict" is a newer version, the resulting dictionary contains
 *  the entries that were changed or added, but not the ones
 *  that were left alone or deleted.
 *  Note that the "newdict" handle is consumed by this function,
 *  even on a failure, but "olddict" is not (unless it's the same handle).
 */
strm_dict_t *strm_dict_compare( strm_dict_t *newdict, strm_dict_t const *olddict );


__END_DECLS

#endif



__SRCVERSION( "$URL$ $Rev$" )
