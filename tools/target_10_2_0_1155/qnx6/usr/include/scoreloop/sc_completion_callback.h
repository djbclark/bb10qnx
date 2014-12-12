/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_completion_callback.h
 * @brief       Completion callback type declaration for request controllers.
 */

#ifndef __SC_COMPLETION_CALLBACK_H__
#define __SC_COMPLETION_CALLBACK_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Callback type for request completion.
 *
 * All requests to the request controllers are asynchronous requests. Each
 * request is concluded with a call to a user-provided callback method of this type.
 *
 * @since 10.0.0
 */
typedef void (*SC_RequestControllerCompletionCallback_t)(void* cookie, SC_Error_t completionStatus);

#ifdef __cplusplus
}
#endif

#endif /* __SC_COMPLETION_CALLBACK_H__ */

/*! @} */
