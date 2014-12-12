/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @file        sc_message_controller.h
 * @brief       Controller class for sending messages through the
 *              server to various recipients, such as social networks or users.
 *
 * @addtogroup  SC_MessageController
 * @{
 *
 * The \ref SC_MessageController is used to post messages to a set of social networks or other receivers.
 *
 * Posted messages usually refer to some Scoreloop-related event such as:
 * - Achieving a score
 * - Creating a challenge
 * - Winning a challenge
 * - Achieving an award
 * - Inviting someone to join Scoreloop.
 *
 * NOTE:
 * -# Posting to social network is not supported on Blackberry
 * -# Where applicable, the user has to be logged in to the social network to be able to post messages.
 *
 * Basic use:
 * To post a message to a social network:
 * -# First check that the user is already connected to a social network.  To do this, use the SC_SocialController_IsConnectedToSocialNetwork() API.
 * -# If the user is not connected, connect by calling SC_SocialController_ConnectToSocialNetwork().
 * -# Once connected, create an instance of \ref SC_MessageController by calling SC_Client_CreateMessageController().
 * -# Use SC_MessageController to create a \ref SC_Message instance of the desired type by calling one of the following create message methods:
 *    - SC_MessageController_CreateGameInvitationMessage()
 *    - SC_MessageController_CreateGameRecomendationMessage()
 *    - SC_MessageController_CreateMessageForAchievement()
 *    - SC_MessageController_CreateMessageForChallenge()
 *    - SC_MessageController_CreateMessageForGame()
 *    - SC_MessageController_CreateMessageForScore()
 * -# Add receivers to the message by calling one of the following add receiver APIs:
 *    - SC_Message_AddEmailReceiver()
 *    - SC_Message_AddSocialNetworkReceiver()
 *    - SC_Message_AddUserReceiver()
 * -# Call SC_MessageController_SubmitMessage() to post the message.
 *
 * @sa SC_SocialNetwork
 * @sa SC_Message
 */

#ifndef __SC_MESSAGE_CONTROLLER_H__
#define __SC_MESSAGE_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_message.h>
#include <scoreloop/sc_achievement.h>
#include <scoreloop/sc_challenge.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_MessageController object handle 
 */
typedef struct SC_MessageController_tag* SC_MessageController_h;

/** Type descriptors for SC_MessageController. 
 */
SC_TYPEINFO(SC_MessageController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Creates a message for the game.
 *
 * Creates a message specific to the game.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self        An opaque handle for SC_MessageController instance.
 * @param   game        Instance of the game that the message is related to.
 * @param   pMessage    Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateMessageForGame(
        SC_MessageController_h self, SC_Game_h game, SC_Message_h* pMessage);

/**
 * @brief Creates a message for the score.
 *
 * Creates a message specific to the score.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self        An opaque handle for SC_MessageController instance.
 * @param   score       Instance of the score that the message is related to.
 * @param   pMessage    Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateMessageForScore(
        SC_MessageController_h self, SC_Score_h score, SC_Message_h* pMessage);

/**
 * @brief Creates a message for the challenge.
 *
 * Creates a message specific to the challenge.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self        An opaque handle for SC_MessageController instance.
 * @param   challenge   Instance of the challenge that the message is related to.
 * @param   pMessage    Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateMessageForChallenge(
        SC_MessageController_h self, SC_Challenge_h challenge, SC_Message_h* pMessage);

/**
 * @brief Creates a message for the achievement.
 *
 * Creates a message specific to the achievement.
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self          An opaque handle for SC_MessageController instance.
 * @param   achievement   Instance of the achievement that the message is related to.
 * @param   pMessage      Message instance to post.
 * @return SC_Error_t     A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateMessageForAchievement(
        SC_MessageController_h self, SC_Achievement_h achievement,
        SC_Message_h* pMessage);

/**
 * @brief Creates a game invitation message.
 *
 * Creates a game invitation message. Only email recipients can be added to this type of message.
 *
 * @param   self     An opaque handle for SC_MessageController instance.
 * @param   pMessage    Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateGameInvitationMessage(
        SC_MessageController_h self, SC_Message_h* pMessage);

/**
 * @brief Creates a game recommendation message.
 *
 * Creates a message for a game recommendation. Only user recipients can be added to this type of message.
 *
 * @param   self        An opaque handle for SC_MessageController instance.
 * @param   game        Instance of the game that the message is related to.
 * @param   pMessage    Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateGameRecomendationMessage(
        SC_MessageController_h self, SC_Game_h game, SC_Message_h* pMessage);

/**
 * @brief Creates a user abuse message.
 *
 * Creates a message for a user abuse report. No receiver should be added to this type of message.
 *
 * @param   self        An opaque handle for SC_MessageController instance.
 * @param   user        Instance of User that the message is related to.
 * @param   pMessage    Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_CreateUserAbuseReport(
        SC_MessageController_h self, SC_User_h user, SC_Message_h* pMessage);

/**
 * @brief Posts the message to the server. Returns SC_OK if the message can be successfully composed.
 *
 * Posts the message to the server. This method will first verify that the message properties are in order and that it can be posted
 * before the Scoreloop servers post the message to the specified receivers.
 * Note that this is an asynchronous call and a callback will be triggered upon success or failure.
 *
 * @param   self        An opaque handle for SC_MessageController instance.
 * @param   message     Message instance to post.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_SubmitMessage(SC_MessageController_h self,
        SC_Message_h message);

/**
 * @brief Method for Request Cancellation.
 *
 * Method to cancel any ongoing request or operation that is initiated
 * by this particular controller instance.
 *
 * @param self An opaque handle of the message controller instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 */
SC_PUBLISHED SC_Error_t SC_MessageController_Cancel(SC_MessageController_h self);

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count of the
 * current controller instance.
 *
 * @param self An opaque handle for the current controller.
 */
SC_PUBLISHED void SC_MessageController_Retain(SC_MessageController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the
 * current controller instance. The current instance will
 * be deleted when the reference count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current controller instance.
 */
SC_PUBLISHED void SC_MessageController_Release(SC_MessageController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_MESSAGE_CONTROLLER_H__ */

/*! @} */
