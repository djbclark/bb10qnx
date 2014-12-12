/*-----------------------------------------------------------------------------
 * BlackBerry VPN Extensions Library
 *
 * Copyright 2013, BlackBerry, All Rights Reserved.
 *
 * This source code may contain confidential information of BlackBerry
 * and its licensors. Any use, reproduction, modification,
 * disclosure, distribution or transfer of this software, or any software
 * that includes or is based upon any of this code, is prohibited unless
 * expressly authorized by BlackBerry by written agreement. For more information
 * (including whether this source code file has been published) please
 * email licensing@blackberry.com.
 */

/**
 * @file vpn_ext_api.h
 * @brief Functions that represent the VPN Extensions Provider API
 * 
 * @details You can use these functions to perform fundamental VPN Extension
 *          operations, such as creating a VPN Extension context
 *          (@c vpn_ext_create_context()), adding a Key Agreement callback
 *          (@c vpn_ext_register_key_agreement()), and running the VPN service
 *          (@c vpn_ext_run_service()).
 */
 
/** 
 * @defgroup vpnprovider VPN Extension Provider APIs
 */
 
#ifndef _VPN_EXT_API_H_
#define _VPN_EXT_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <vpnext/vpn_ext_type.h>

/**
 * @file vpn_ext_api.h
 * @brief VPN Extensions Provider API.
 * @details
 * @copyright Copyright (C) BlackBerry 2013. All rights reserved.
 */

/** @defgroup vpnprovider VPN Extension Provider APIs
 */

/** @brief Macro to tag APIs exported from the VPN Extension's shared library.
 */
#define VPN_EXT_PUBLIC __attribute__ ((visibility ("default")))


/**  Determines if the process is running in enterprise.
 *
 * @return bool                    True if process is running in enterprise perimeter.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
bool vpn_ext_running_in_enterprise( void );


/** @brief Creates the VPN Extension context.
 * Creates a context that is passed into all subsequent provider calls. Before the provider is finished
 * it should call VPN_ExP_DestroyContext to clean up memory allocated by the library.
 *
 * More information to come here.
 *
 * @param[in]  extensionName  Extension name that is used by the client to open connections.
 * @param[in]  maxMsgLen      Maximum message length. If zero a default is chosen.
 * @param[in]  maxGets        Maximum number of reply messages enqueued. If zero a default is chosen.
 *
 * @return context            The VPN Extensions context structure. If NULL then errno is set.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
vpn_ext_context vpn_ext_create_context( const char *extensionName, unsigned int maxMsgLen, unsigned int maxGets );


/** @brief Provides the list of callbacks for Service functions supported by the VPN_ExP.
 * These callbacks are used to start/stop a registered VPN service.
 * Typically these callbacks will be used to start/stop a 3rd party VPN daemon.
 * The service will be started/stopped under control of the VPN Manager.
 *
 * @param[in] context       The VPN Extensions context
 * @param[in] service_type  Service adapter type.
 * @param[in] callbacks     Callback structure
 *
 * @return EOK              Success.
 * @return EINVAL           Invalid parameter(s).
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_register_service( vpn_ext_context context, vpn_service_type_e service_type, const vpn_service_callbacks_t * callbacks );


/** @brief Adds a Key Agreement callback.
 *
 * @param[in] context        The VPN Extensions context.
 * @param[in] api            API Name. Values are VPN_EXT_KEYAGREE_*.
 * @param[in] version        API version in format xxxxyyyy where xxxx=major, yyyy=minor.
 * @param[in] mapping        JSON string containing the mapping the callback provides.
 * @param[in] callback       Callback function.
 *
 * @return EOK               Success.
 * @return EINVAL            Invalid parameter(s).
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_register_key_agreement( vpn_ext_context context,
                                        const char *api,
                                        unsigned int version,
                                        const char *mapping,
                                        vpn_ext_callback_t callback );


/** @brief Removes a Key Agreement callback added by VPN_ExP_RegisterKeyAgreement.
 *
 * @param[in] context        The VPN Extensions context.
 * @param[in] api            API Name. Values are VPN_EXT_KEYAGREE_*.
 *
 * @return EOK               Success.
 * @return EINVAL            Invalid parameter(s).
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_deregister_key_agreement( vpn_ext_context context, const char *api );


/** @brief Runs the service.
 *
 * @param[in] context        The VPN Extensions context.
 * @param[in] run_timeout    The time in seconds after which if there are no client connections, this will return.
 *                           If zero the a default is chosen.
 *
 * @return EOK               Success.
 * @return EINVAL            Invalid parameter(s).
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_run_service( vpn_ext_context context, unsigned int run_timeout );


/** @brief Closes the VPN Extension Provider library and IPC with the core VPN service.
 *
 * @param[in] context        The VPN Extensions context.
 *
 * @return EOK               Success.
 * @return ENOENT            Library was already closed.
 *
 * @ingroup vpnprovider
 */
VPN_EXT_PUBLIC
errno_t vpn_ext_destroy_context( vpn_ext_context context );

#ifdef __cplusplus
}
#endif

#endif // _VPN_EXT_API_H_
