/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief       Social network identifiers.
 * @file        sc_social_network.h
 * @addtogroup  SC_SocialNetwork
 * @{
 *
 * The \ref SC_SocialNetwork enumeration identifies a social network.
 * 
 * Social Networks could be used to search for user's friends and thereby invite
 * them to play the games.
 * 
 * The following Social Networks are currently supported:
 * - Facebook
 * - Twitter
 *
 * NOTE: Currently not supported on BlackBerry.
 * 
 */

#ifndef __SC_SOCIAL_NETWORK_H__
#define __SC_SOCIAL_NETWORK_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Social network identifier */
typedef enum SC_SocialNetwork_tag {
    SC_SOCIAL_FACEBOOK,
    SC_SOCIAL_TWITTER,
} SC_SocialNetwork_t;

#ifdef __cplusplus
}
#endif

#endif /* __SC_SOCIAL_NETWORK_H__ */

/*! @} */
