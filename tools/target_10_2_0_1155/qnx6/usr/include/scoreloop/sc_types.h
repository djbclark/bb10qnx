/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_types.h
 * @brief       Scoreloop Core - basic types.
 *
 * @addtogroup  SC_Types
 * @{
 *
 * Scoreloop Core - basic types.
 */

#ifndef __SC_TYPES_H__
#define __SC_TYPES_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_platform.h>

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Maximum unsigned integer value. 
 *
 * @since 10.0.0
 */
#define MAX_UINT    ((unsigned int)(0-1))
/** Maximum integer value. 
 *
 * @since 10.0.0
 */
#define MAX_INT     (MAX_UINT/2)

/** Boolean type 
 *
 * @since 10.0.0
 */
typedef unsigned char SC_Bool_t;
/** Boolean 'false' value. 
 *
 * @since 10.0.0
 */
#define SC_FALSE 0
/** Boolean 'true' value. 
 *
 * @since 10.0.0
 */
#define SC_TRUE 1

/** Int64 type 
 *
 * @since 10.0.0
 */
typedef long long SC_Int64_t;
/** Unsigned Int64 type 
 *
 * @since 10.0.0
 */
typedef unsigned long long SC_UInt64_t;

/** Float type 
 *
 * @since 10.0.0
 */
typedef double SC_Float_t;

/** NULL constant 
 *
 * @since 10.0.0
 */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif /* __SC_TYPES_H__ */

/*! @} */

