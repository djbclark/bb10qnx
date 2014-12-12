/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief       Platform-specific definitions for QNX
 *
 * @file        sc_platform.h
 * @addtogroup  SC_Client
 * @{
 */

#ifndef __SC_PLATFORM_H__
#define __SC_PLATFORM_H__


#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------
 * Constants
 *-----------------------------------------------------------------------------------
 */

/** Type of the platform 
 *
 * @since 10.0.0
 */
#ifndef SC_PLATFORM_QNX
#   define SC_PLATFORM_QNX          (1)
#endif

/** Social providers implementation not available 
 *
 * @since 10.0.0
 */
#define SC_HAS_SOCIAL_PROVIDERS     (0)

/** Enabled object tracing across the platform memory allocations 
 *
 * @since 10.0.0
 */
#ifndef SC_TRACK_ALLOCS
    #define SC_TRACK_ALLOCS         (1)
#endif

/**
 * Macro for marking the Scoreloop CoreSocial public API.
 * SC_PUBLISHED API has default visibility on this platform.
 *
 * @since 10.0.0
 */
#define SC_PUBLISHED               __attribute__((visibility("default")))

/**
 * @brief Macro for marking the Scoreloop CoreSocial weak public API.
 *
 * API marked as SC_PUBLISHED_WEAKLY has to be checked at runtime before use:
 * e.g.
 *
 * @code
 * SC_PUBLISHED_WEAKLY SC_Error_t SC_User_SomeNewGetter(SC_User_h self)
 *
 * // usage:
 * if (SC_User_SomeNewGetter) {
 *     SC_User_SomeNewGetter(myUser);
 * }
 * @endcode
 *
 * API might move from SC_PUBLISHED_WEAKLY to SC_PUBLISHED in a next version of the library which
 * implies a change of the shared-library version. e.g. libscoreloopcore.so.1 -&gt; libscoreloopcore.so.2
 *
 * @since 10.0.0
 */
#define SC_PUBLISHED_WEAKLY         SC_PUBLISHED __attribute__((weak))

/** The shared library version number libscoreloop.so.&lt;SC_SHARED_LIB_VERSION&gt; corresponding to this API 
 *
 * @since 10.0.0
 */
#define SC_SHARED_LIB_VERSION       (1)

#ifdef __cplusplus
}
#endif

#endif /* __SC_PLATFORM_H__ */

/*! @} */
