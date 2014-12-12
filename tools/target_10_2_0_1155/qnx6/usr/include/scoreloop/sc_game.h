/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_game.h
 * @brief       The SC_Game class models the game application.
 *
 * @addtogroup  SC_Game
 * @{
 *
 * Instances of \ref SC_Game model the game application.
 *
 * Games must be registered at <a href="https://developer.scoreloop.com">
 * https://developer.scoreloop.com</a>, where they are assigned a unique
 * game-id and game secret, and where you can configure additional game properties.
 *
 *
 * \ref SC_Game provides access to the game identifier and game secret
 * that were assigned by Scoreloop when you registered the game.
 *
 *
 * Basic Usage:
 * -# Get an instance of \ref SC_Client.
 * -# Use the Client object to call SC_Client_GetGame(), which returns the game instance associated with the client.
 * -# Alternatively,
 *    - Use the Client object to call SC_Client_GetSession() and retrieve the current session object.
 *      An instance of \ref SC_Session is created transparently when the client is created.
 *    - Use the session instance to call SC_Session_GetGame(). This returns
 *      the current game instance.
 * -# Use this game instance to access individual game properties:
 *    - Call SC_Game_GetIdentifier() to access the game identifier
 *    - Call SC_Game_GetName() to access the game name
 *    - Call SC_Game_GetImageUrl() to access the image url
 *    - Call SC_Game_GetPublisherName() to access the publisher name
 *    - Call SC_Game_GetVersion() to access the version
 *    - Call SC_Game_GetDownloadUrl() to access the download url
 *    - Call SC_Game_GetDescription() to access the game description
 *    - Call SC_Game_GetModeCount() to access the game mode count
 */

#ifndef __SC_GAME_H__
#define __SC_GAME_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_object.h>
#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Game object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_Game_tag* SC_Game_h;

/** Type descriptors for SC_Game. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Game);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count by one.
 *
 * @param self An opaque handle for the current game instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Game_Retain(SC_Game_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count by one. The SC_Game instance
 * will be automatically deleted when the counter reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current game instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Game_Release(SC_Game_h self);

/**
 * @brief Accessor to the Name field.
 *
 * This method is an accessor to the Name field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return SC_String_h The name field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetName(SC_Game_h self);

/**
 * @brief Accessor to the imageUrl field.
 *
 * This method is an accessor to the imageUrl field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return SC_String_h The imageUrl field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetImageUrl(SC_Game_h self);

/**
 * @brief Returns the game identifier.
 *
 * This method returns the identifier for the current
 * game instance. Scoreloop assigns the identifier
 * when the game is registered at
 * <a href="https://developer.scoreloop.com">
 * https://developer.scoreloop.com</a>.
 *
 * @param self An opaque handle for the current game instance.
 * @return SC_String_h The game identifier field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetIdentifier(SC_Game_h self);

/**
 * @brief Accessor to the publisherName field.
 *
 * This method is an accessor to the publisherName field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return SC_String_h The publisherName field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetPublisherName(SC_Game_h self);

/**
 * @brief Accessor to the version field.
 *
 * This method is an accessor to the version field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return SC_String_h The version field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetVersion(SC_Game_h self);

/**
 * @brief Accessor to the downloadUrl field.
 *
 * This method is an accessor to the downloadUrl field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return SC_String_h The downloadUrl field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetDownloadUrl(SC_Game_h self);

/**
 * @brief Accessor to the description field.
 *
 * This method is an accessor to the description field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return SC_String_h The description field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Game_GetDescription(SC_Game_h self);

/**
 * @brief Accessor to the modeCount field.
 *
 * This method is an accessor to the modeCount field.
 *
 * @param self An opaque handle for the current SC_Game instance.
 * @return unsigned int The modeCount field value.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_Game_GetModeCount(SC_Game_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAME_H__ */

/*! @} */
