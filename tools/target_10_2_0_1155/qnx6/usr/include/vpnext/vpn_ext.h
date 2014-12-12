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

/** @mainpage VPN Extensions Library
 *
 * @version 1.1
 *
 * @section intro_sec Introduction
 *
 * As part of session establishment the VPN service can use one or more configured adapters.
 * Each adapter may also be associated with an extension provider. This is the documentation
 * for the libraries that the extension providers and the VPN Manager (vpn_pps) use to communicate.
 *
 * Extension providers can be written in C or C++.
 *
 *
 */

/**
 * @file vpn_ext.h
 *
 * @brief VPN Extension Provider main header.
 *
 * @details VPN Extensions only have to include this header to build with the VPN Extensions Library.
 *
 * @copyright Copyright (C) BlackBerry 2013. All rights reserved.
 *
 */

#ifndef _VPN_EXT_H_
#define _VPN_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <vpnext/vpn_ext_type.h>
#include <vpnext/vpn_ext_api.h>

#ifdef __cplusplus
}
#endif

#endif // _VPN_EXT_H_
