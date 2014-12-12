/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_message.h
 * @brief       Class that creates a message that you can send to
 *              various recipients, like social networks or Scoreloop users.
 *
 * @addtogroup  SC_Message
 * @{
 *
 * The \ref SC_Message instance includes the message text, subject, and receivers who will
 * receive the message.
 *
 * Instances of this class are created by calling one of the many create message methods in SC_MessageController.
 *
 * Once the message instance is created, add message receivers by using
 * SC_Message_AddEmailReceiver(), SC_Message_AddUserReceiver(), and
 * SC_Message_AddSocialNetworkReceiver() calls.
 * @sa SC_MessageController
 */

#ifndef __SC_MESSAGE_H__
#define __SC_MESSAGE_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_session.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_social_network.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque Message object handle */
typedef struct SC_Message_tag* SC_Message_h;

/** Type descriptors for SC_Message.*/
SC_TYPEINFO(SC_Message);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Adds an email message receiver
 *
 * This method adds an email message receiver.
 *
 * @param self          Instance handle
 * @param email         Email address to add
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value
 *                    indicates an error).
*/
SC_PUBLISHED SC_Error_t SC_Message_AddEmailReceiver(SC_Message_h self,
        const char* email);

/**
 * @brief Adds a Scoreloop user receiver
 *
 * This method adds a Scoreloop user receiver.
 *
 * @param self          Instance handle
 * @param user          User receiver to add
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value
 *                    indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Message_AddUserReceiver(SC_Message_h self,
        SC_User_h user);

/**
 * @brief Adds a social network receiver
 *
 * This method adds a social network receiver.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param self          Instance handle
 * @param network       Target social network
 * @param user          Target user
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value
 *                    indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Message_AddSocialNetworkReceiver(SC_Message_h self,
        SC_SocialNetwork_t network, SC_User_h user);

/**
 * @brief Clears the list of receivers
 *
 * This method clears the list of receivers.
 *
 * @param self          Instance handle
 * @return SC_Error_t   Error code (a value of SC_OK indicates success, any other value
 *                      indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Message_FlushReceivers(SC_Message_h self);

/**
 * @brief Sets the message text
 *
 * This method sets the message text.
 *
 * @param self      Instance handle
 * @param text      Message text
 * @return SC_Error_t   Error code (a value of SC_OK indicates success, any other value
 *                      indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Message_SetText(SC_Message_h self, const char *text);

/**
 * @brief Checks whether it is possible to submit a message.
 *
 * This call checks whether it is possible to post a message. For example, whether the user account
 * is connected to all the social networks that were referenced with SC_Message_AddSocialNetworkReceiver().
 *
 * @param self      Instance handle
 * @param pAllowed  Pointer to SC_Bool_t variable where the result is stored
 * @return SC_Error_t   Error code (a value of SC_OK indicates success, any other value
 *                      indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_Message_IsSubmitAllowed(SC_Message_h self, SC_Bool_t* pAllowed);

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count of the Message instance by 1.
 *
 * @param self An opaque handle for the current Message.
 */
SC_PUBLISHED void SC_Message_Retain(SC_Message_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count of the
 * current controller instance.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current Message.
 */
SC_PUBLISHED void SC_Message_Release(SC_Message_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_MESSAGE_H__ */

/*! @} */
