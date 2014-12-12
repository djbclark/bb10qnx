/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @brief       The controller that is used to connect the user to one of the social networks.
 * @file        sc_social_controller.h
 * @addtogroup  SC_SocialController
 * @{
 *
 * The \ref SC_SocialController that is used to connect the user to one of the social networks.
 *
 * Basic use:
 * -# Use the client instance to get an instance of \ref SC_SocialController by calling SC_Client_CreateSocialController().
 *    Specify the social network that you want to connect to as an argument to SC_Client_CreateSocialController(). Currently, Facebook and Twitter are supported.
 *    The identifiers are the following: SC_SOCIAL_FACEBOOK, SC_SOCIAL_TWITTER).
 * -# Check whether the user is already connected to the social network by calling SC_SocialController_IsConnectedToSocialNetwork().
 * -# If the user is not connected, connect to the social network by calling SC_SocialController_ConnectToSocialNetwork().
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 */

#ifndef __SC_SOCIAL_CONTROLLER_H__
#define __SC_SOCIAL_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_object.h>
#include <scoreloop/sc_types.h>
#include <scoreloop/sc_social_network.h>
#include <scoreloop/sc_completion_callback.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_SocialController object handle */
typedef struct SC_SocialController_tag* SC_SocialController_h;

/** Type descriptors for SC_SocialController. */
SC_TYPEINFO(SC_SocialController);

/** Callback event types */
typedef enum SC_SocialControllerCallbackEvent_tag
{
    /** Authorization phase finished */
    SC_SOCIAL_AUTHORIZATION_FINISHED,
    /** Connecting process finished */
    SC_SOCIAL_CONNECTING_FINISHED
} SC_SocialControllerCallbackEvent_t;

/**
 * @brief Callback type for social controller's progress notifications
 */
typedef void (*SC_SocialControllerCompletionCallback_t)(void* userData,
        SC_SocialControllerCallbackEvent_t event, SC_Error_t completionStatus);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Check whether the user is  connected to a social network handled
 *        by this controller
 *
 * This method allows you to check whether the user is already connected to a given social
 * network. If the user is connected to a social network, it is possible to post
 * messages to a social network on behalf of the user.
 *
 * Otherwise, the user must first be connected to the social network by calling
 * SC_SocialController_ConnectToSocialNetwork.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param self      SC_SocialController instance handle
 * @return SC_Bool_t SC_TRUE if the user is already connected to this controller's social network.
 */
SC_PUBLISHED SC_Bool_t SC_SocialController_IsConnectedToSocialNetwork(
        SC_SocialController_h self);

/**
 * @brief Connects the user to a social network.
 *
 * This method connects the Scoreloop user to a given social network. 
 * The process is asynchronous and consists of two phases.
 *
 * In the first phase a web browser is opened, where the user logs in to the social
 * network and grants the necessary permissions to the Scoreloop application (if applicable).
 * When this phase is complete, the callback is issued with the SC_SOCIAL_AUTHORIZATION_FINISHED event.
 *
 * The second phase is triggered only if the first phase finished successfully, that is, the
 * callback method is called and returns SC_OK as the completionStatus. Otherwise, no further
 * processing is performed the and controller becomes idle.
 *
 * During the second phase, the web browser window is closed and the controller updates the user
 * status on the Scoreloop servers. When this stage is complete, the callback method is called and returns SC_SOCIAL_CONNECTING_FINISHED.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param self      SC_SocialController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success,
 *                      any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_SocialController_ConnectToSocialNetwork(
        SC_SocialController_h self);

/**
 * @brief Gets the social network handled by this controller.
 *
 * This method gets the social network handled by this controller.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param self      SC_SocialController instance handle
 * @return SC_SocialNetwork_t The Social network that this controller handles.
 */
SC_PUBLISHED SC_SocialNetwork_t SC_SocialController_GetSocialNetwork(
        SC_SocialController_h self);

/**
 * @brief Cancels the pending operation.
 *
 * This method cancels any ongoing operations initiated by this particular controller instance.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self    SC_SocialController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success,
 *                      any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_SocialController_Cancel(SC_SocialController_h self);

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the current instance by 1.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self    SC_SocialController instance handle
 */
SC_PUBLISHED void SC_SocialController_Retain(SC_SocialController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the current instance by 1. 
 * The current controller instance will be automatically deleted when the reference count equals 0.
 *
 * Note that this method is NULL pointer safe. That is, NULL as an argument will not cause an exception.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self    SC_SocialController instance handle
 */
SC_PUBLISHED void SC_SocialController_Release(SC_SocialController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_SOCIAL_CONTROLLER_H__ */

/*! @} */
