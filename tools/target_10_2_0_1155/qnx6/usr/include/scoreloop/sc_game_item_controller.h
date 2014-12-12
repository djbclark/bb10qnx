/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @brief       The GameItemController operates on a single instance of game item on
 *              the server.
 * @file        sc_game_item_controller.h
 * @addtogroup  SC_GameItemController
 *
 * @{
 * The \ref SC_GameItemController retrieves lists of game items from the server.
 */

#ifndef __SC_GAME_ITEM_CONTROLLER_H__
#define __SC_GAME_ITEM_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game_item.h>
#include <scoreloop/sc_completion_callback.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GameItemController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_GameItemController_tag* SC_GameItemController_h;

/** Type descriptors for SC_GameItemController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GameItemController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the objects reference count.
 *
 * @param   self        SC_GameItemController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItemController_Retain(SC_GameItemController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the objects reference count.
 * The object will be deleted automatically if the reference
 * count reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param   self        SC_GameItemController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItemController_Release(SC_GameItemController_h self);

/**
 * @brief Method for Request Cancellation.
 *
 * This method cancels any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the score controller instance.
 * @return SC_Error_t   A return code. (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemController_Cancel(SC_GameItemController_h self);

/**
 * @brief Returns the game item that have been requested from the server.
 *
 * This method returns the game item object that the controller is dealing with.
 *
 * If this method is called before a request to the server has been made, a @c NULL value will be returned.
 *
 * @param  self         SC_GameItemController instance handle.
 * @return SC_GameItem_h The game item that has been retrieved from the server.
 * @sa SC_GameItemController_LoadItem(), SC_GameItemController_SubmitOwnership(), SC_GameItemController_LoadDownloadURL().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameItem_h SC_GameItemController_GetItem(SC_GameItemController_h self);

/**
 * @brief This method loads the latest info about the specified game item in context of
 * the current session user.
 *
 * This method loads the latest info about the specified game item in context of
 * the current session user.
 *
 * It will load the latest known state of provided SC_GameItem from the Scoreloop server.
 * Then, it puts the results into a new instance of the game item, accessible using the SC_GameItemController_GetItem().
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemController instance handle.
 * @param  item         An instance of SC_GameItem to reload data.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_GameItemController_GetItem
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemController_LoadItem(SC_GameItemController_h self,
        SC_GameItem_h item);

/**
 * @brief This method loads the latest info about the specified game item in context of
 * the current session user and user's local currency (for example, EUR or USD).
 *
 * This method loads the latest info about the specified game item in context of
 * the current session user and user's local currency (for example, EUR or USD).
 *
 * It will load the latest known state of the provided SC_GameItem from the Scoreloop server.
 * Then, it puts the results into a new instance of the game item, accessible using SC_GameItemController_GetItem().
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemController instance handle.
 * @param  item         An instance of SC_GameItem to reload data.
 * @param  currency     A user's local currency, the evaluation should be performed against or @c NULL.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_GameItemController_GetItem
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemController_LoadItemWithCurrency(
        SC_GameItemController_h self, SC_GameItem_h item, SC_String_h currency);

/**
 * @brief Assigns the game item directly to the user.
 *
 * This method will assign the game item directly for the session user.
 * However this method will succeed only if the item is available for free.
 * This indication is given as PriceTier property of the game item.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemController instance handle.
 * @param  item         An instance of SC_GameItem to submit ownership over.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemController_SubmitOwnership(
        SC_GameItemController_h self, SC_GameItem_h item);

/**
 * @brief Requests the download URL for specified game item.
 *
 * This method will let the game item to be downloaded on the user's device
 * by providing an URL to Scoreloop Content Delivery Network, where the actual
 * game item's content file is placed. The regular HTTP request can then be performed
 * to load that content and process respectively.
 *
 * The URL has an expiration date set to few minutes (by default 5) and will
 * automatically invalidate after that time. It should prevent unauthorized access to the content.
 *
 * Additionally, if user has no ownership for the item, an error will be returned.
 * That's why even free game items, must be claimed by SC_GameItemController_SubmitOwnership(), before
 * try to download them.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemController instance handle.
 * @param  item         An instance of SC_GameItem to request the download URL.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_GameItemController_SubmitOwnership
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemController_LoadDownloadURL(
        SC_GameItemController_h self, SC_GameItem_h item);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAME_ITEM_CONTROLLER_H__ */

/*! @} */
