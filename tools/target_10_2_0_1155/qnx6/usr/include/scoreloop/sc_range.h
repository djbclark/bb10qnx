/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_range.h
 * @brief       Structure to define range for data.
 */

#ifndef __SC_RANGE_H__
#define __SC_RANGE_H__

#ifdef __cplusplus
extern "C" {
#endif


/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Common structure to handle range data. It contains offset and length fields.
 *
 * This structure describes a data range and is commonly used in all queries,
 * where more than a single result is returned.
 *
 * @since 10.0.0
 */
typedef struct SC_Range_tag
{
    /** Offset of the data. */
    unsigned int offset;
    /** Number of records */
    unsigned int length;
} SC_Range_t;


#ifdef __cplusplus
}
#endif

#endif /* __SC_RANGE_H__ */

/*! @} */
