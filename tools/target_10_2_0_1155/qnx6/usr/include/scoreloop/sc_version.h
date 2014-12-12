/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_version.h
 * @brief       Common API for accessing information about current deployment.
 *
 * @addtogroup  SC_Version
 * @{
 * This file is used to store version information.
 */

#ifndef __SC_VERSION_H__
#define __SC_VERSION_H__

/*-------------------------------------------------------------------------------------*
* Includes
*-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_init.h>
#include <scoreloop/sc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Returns version information about the linked to Scoreloop library.
 *
 * This method returns version information of the Scoreloop library linked to the project. The content of the returned
 * string is not final and can change without any notice. This method is primarily intended to be used
 * when communicating with the Scoreloop support team. Do not use it to guess enabled library features.
 *
 * @param pInitData     Currently ignored.
 * @param buffer        A non-null character buffer which will be filled up to bufferSize.
 * @param bufferSize    The length of the buffer. Choose a big enough buffer to get all data.
 * @return SC_Bool_t    SC_TRUE if bufferSize was big enough, SC_FALSE if return was truncated because of too small buffer.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_GetVersionInfo(const SC_InitData_t *pInitData, char *buffer, unsigned int bufferSize);

#ifdef __cplusplus
}
#endif

#endif /* __SC_VERSION_H__ */

/*! @} */
