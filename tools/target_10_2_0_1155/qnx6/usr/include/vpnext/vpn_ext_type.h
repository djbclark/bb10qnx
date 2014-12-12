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

#ifndef _VPN_EXT_TYPE_H_
#define _VPN_EXT_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <errno.h>

/**
 * @file vpn_ext_type.h
 * @brief VPN Extension macros, structs and enum definitions.
 * @details
 * @copyright Copyright (C) BlackBerry 2013. All rights reserved.
 *
 */


/** @name VPN Ext domain names
 *  Domain names used to open connections to a provider.
 * @{*/
#define VPN_EXT_DOMAIN_AUTH      "auth"                    //!< Domain name for Authorization APIs.
#define VPN_EXT_DOMAIN_CRYPTO    "crypto"                  //!< Domain name for Cryptography APIs.
#define VPN_EXT_DOMAIN_SERVICE   "service"                 //!< Domain name for Service Extension API.
#define VPN_EXT_DOMAIN_SUPPORT   "support"                 //!< Domain name for used to query the provider's functionality.
#define VPN_EXT_DOMAIN_KEYAGREE  "keyagree"                //!< Domain name for Key Agreement APIs.
/**@}*/

/** @name Key Agreement API names.
 * @{*/
#define VPN_EXT_KEYAGREE_CUSTOM_DH  "custom_dh"            //!< Name for Custom Diffe-Hellman Key Agreement API.
/**@}*/

/** @name JSON Attribute names returned by VPN_ExP_GetCapabilities.
 * @{*/
#define VPN_EXT_ATTR_PROVIDER          "provider"
#define VPN_EXT_ATTR_API_LIST          "api_list"
#define VPN_EXT_ATTR_API               "api"
#define VPN_EXT_ATTR_VERSION           "version"
#define VPN_EXT_ATTR_DOMAIN            "instance"
#define VPN_EXT_ATTR_ENTERPRISE        "enterprise"
/**@}*/

/** @name Maximum length of string names used in structures.
  */
#define VPN_EXT_NAME_LEN 31

/**
 * @brief An opaque pointer for VPN Extension Provider context
 */
typedef struct _vpn_ext_context *vpn_ext_context;


/**
 * @brief Callback function prototype
 *
 * @param[in] in_buffer       Input message to callback.
 * @param[in] in_buffer_len   Input message length.
 * @param[in] pOut_buffer     Output message from callback.
 *                            If set to NULL, then there is no message to return.
 *                            If set to in_buffer, then the input buffer is reused for output.
 *                            If none of the above, then the buffer should be allocated by the callback function.
 *                            Once the buffer is used then it will be freed by the caller after the message is sent to the VPN Manager.
 * @param[in] pOut_buffer_len Output message length.
 *
 * @return Values taken from errno.h
 *
 * @ingroup vpnextapi
 */
typedef errno_t (*vpn_ext_callback_t)( vpn_ext_context context,
                                       char *in_buffer,    unsigned int in_buffer_len,
                                       char **pOut_buffer, unsigned int *pOut_buffer_len );


/**
 * @brief Request Message Structure for Support callbacks.
 */
typedef struct support_request {
    char                domain[VPN_EXT_NAME_LEN + 1];      //!< The domain we are checking on. One of VPN_EXT_DOMAIN_*
    char                api[VPN_EXT_NAME_LEN + 1];         //!< The API we are checking on.  VPN_EXT_DOMAIN_SUPPORT_* or any api name
} support_request_t;


/**
 * @brief Response Message Structure for Support callbacks.
 */
typedef struct support_response {
    unsigned short      version_major;                     //!< Version major.
    unsigned short      version_minor;                     //!< Version minor.
    char                info[0];                           //!< JSON string listing information on the domain/api requested.
} support_response_t;


/**
 * @brief Custom Diffe-Hellman (DH) transaction types.
 * @details Custom Diffe-Hellman transaction types belong to only these types.
 *          Associated with each transaction type are a matching request and response structures.
 */
typedef enum key_agree_request {
    /**
     * @brief A DH information transaction
     */
    KEY_AGREE_REQUEST_DH_INFO          = 0,
    /**
     * @brief A DH initialization transaction
     */
    KEY_AGREE_REQUEST_DH_INIT          = 1,
    /**
     * @brief A DH transaction to obtain the extension's public key
     */
    KEY_AGREE_REQUEST_DH_PUBLIC_KEY    = 2,
    /**
     * @brief A DH transaction to return the gateway's public key and obtain the
     * extension's shared secret
     */
    KEY_AGREE_REQUEST_DH_SHARED_SECRET = 3,
    /**
     * @brief A DH termination transaction
     */
    KEY_AGREE_REQUEST_DH_TERM          = 4,
} key_agree_request_e;

#define DH_CUSTOM_MAX_LEN 16                               //!< Maximum length of custom DH name.
/**
 * @brief DH Information request - sent by VPN_ExP_DhInfo.
 */
typedef struct dh_info_request {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_INFO
    char                     dh_custom[DH_CUSTOM_MAX_LEN]; //!< DH Custom name.
} dh_info_request_t;
/**
 * @brief DH Initialization request - sent by VPN_ExP_DhInit.
 */
typedef struct dh_init_request {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_INIT
    char                     dh_custom[DH_CUSTOM_MAX_LEN]; //!< DH Custom name.
} dh_init_request_t;
/**
 * @brief DH Public Key request - sent by VPN_ExP_DhPublicKey.
 */
typedef struct dh_public_key_request {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_PUBLIC_KEY
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
} dh_public_key_request_t;
/**
 * @brief DH Shared Secret request  - sent by VPN_ExP_DhSharedSecret.
 */
typedef struct dh_shared_secret_request {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_SHARED_SECRET
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
    unsigned int             public_key_size;              //!< Size in bytes of the gateway's public key.
    unsigned char            public_key[];                 //!< Public key from the gateway.
} dh_shared_secret_request_t;
/**
 * @brief DH Termination request - sent by VPN_ExP_DhTerm.
 */
typedef struct dh_term_request {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_TERM
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
} dh_term_request_t;
/**
 * @brief Key Agreement request message including all request types.
 */
typedef struct key_agree_request_t {
    union {
        key_agree_request_e            request_type;       //!< Request type from key_agree_request_e.
        dh_info_request_t              dh_info;            //!< DH_INFO request.
        dh_init_request_t              dh_init;            //!< DH_INIT request.
        dh_public_key_request_t        dh_public_key;      //!< DH_PUBLIC_KEY request.
        dh_shared_secret_request_t     dh_shared_secret;   //!< DH_SHARED_SECRET request.
        dh_term_request_t              dh_term;            //!< DH_TERM request
    };
} key_agree_request_t;


/**
 * @brief DH Info response - returned to VPN_ExP_DhInfo.
 */
typedef struct dh_info_response {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_INFO
    unsigned int             public_key_size;              //!< Size in bytes of the provider's public key.
    unsigned int             shared_secret_size;           //!< Size in bytes of the shared secret key
} dh_info_response_t;
/**
 * @brief DH Info response - returned to VPN_ExP_DhInit.
 */
typedef struct dh_init_response {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_INIT.
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
} dh_init_response_t;
/**
 * @brief DH Info response - returned to VPN_ExP_DhPublicKey.
 */
typedef struct dh_public_key_response {
    key_agree_request_e      request_type;                 //!< Set to fKEY_AGREE_REQUEST_DH_PUB:IC_KEY.
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
    unsigned int             public_key_size;              //!< Size in bytes of the provider's public key.
    unsigned char            public_key[];                 //!< Public key.
} dh_public_key_response_t;
/**
 * @brief DH Info response - returned to VPN_ExP_DhSharedSecret.
 */
typedef struct dh_shared_secret_response {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_SHARED_SECRET.
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
    unsigned int             shared_secret_size;           //!< Size in bytes of the shared secret key.
    unsigned char            shared_secret[];              //!< Shared secret key
} dh_shared_secret_response_t;
/**
 * @brief DH Info response - returned to VPN_ExP_DhTerm.
 */typedef struct dh_term_response {
    key_agree_request_e      request_type;                 //!< Set to KEY_AGREE_REQUEST_DH_TERM.
    unsigned int             session_id;                   //!< Session identifier to be used for key and termination requests.
} dh_term_response_t;
/**
 * @brief DH Response including all request types.
 */
typedef struct key_agree_response {
    union {
        key_agree_request_e            request_type;       //!< Request type from key_agree_request_e.
        dh_info_response_t             dh_info;            //!< DH_INFO response.
        dh_init_response_t             dh_init;            //!< DH_INIT response.
        dh_public_key_response_t       dh_public_key;      //!< DH_PUBLIC_KEY response.
        dh_shared_secret_response_t    dh_shared_secret;   //!< DH_SHARED_SECRET response.
        dh_term_response_t             dh_term;            //!< DH_TERM response.
    };
} key_agree_response_t;


/**
 * @brief VPN Service Types.
 * @details The service type maps to a specific shared library name specific to that service.

 */
typedef enum vpn_service_type {
    /**
     * @brief The AnyConnect service
     */
    VPN_SERVICE_ANYCONNECT    = 0,
    /**
     * @brief The OpenVPN service
     */
    VPN_SERVICE_OPENVPN      = 1,
    /**
     * @brief The Max service
     */
    VPN_SERVICE_MAX
} vpn_service_type_e;

/**
 * @brief Structure for VPN_ExP Service callbacks.
 * @details These callbacks are used to start/stop a registered VPN service.
 * Typically these callbacks will be used to start/stop a 3rd party VPN daemon.
 * The service will be started/stopped under control of the VPN Manager.
 */
typedef struct _vpn_service_callbacks
{
    /**
    @brief Function to start the VPN service.

    @param[out] service_ctx     returns service data.

    @return EOK     success.

    */
    errno_t (*service_start) ( void ** service_ctx );

    /**
    @brief Function to stop the VPN service.

    @param[in,out] service_ctx     pointer to the service data.

    @return EOK     success.

    */
    errno_t (*service_stop) ( void ** service_ctx );

} vpn_service_callbacks_t;

#ifdef __cplusplus
}
#endif

#endif // _VPN_EXT_TYPE_H_
