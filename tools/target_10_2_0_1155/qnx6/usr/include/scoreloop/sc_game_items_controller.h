/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup     CoreSocial
 * @brief       The GameItemsController retrieves lists of game items from the server.
 * @file        sc_game_items_controller.h
 * @addtogroup  SC_GameItemsController
 *
 * @{
 * The \ref SC_GameItemsController retrieves lists of game items from the server.
 */

#ifndef __SC_GAME_ITEMS_CONTROLLER_H__
#define __SC_GAME_ITEMS_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_games_search_list.h>
#include <scoreloop/sc_game_item_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GameItemsController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_GameItemsController_tag* SC_GameItemsController_h;

/** Type descriptors for SC_GameItemsController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GameItemsController);

/**
 * A TagOperator allows a choice between one of two modes of applying tags:
 * - game item must be marked with all specified tags
 * - game item must be marked with at least one tag
 *
 * @since 10.0.0
 */
typedef enum SC_GamesItemsTagOperator_tag {
    SC_GAMEITEMS_TAG_OPERATOR_ALL,              /**< Game item must be marked with all specified tags. */
    SC_GAMEITEMS_TAG_OPERATOR_ONE_OR_MORE,      /**< Game item must be marked with at least one tag. */
} SC_GamesItemsTagOperator_t;

/**
 * A VersionOperator allows a choice of how the versioning should be applied. Available
 * options are:
 * - all available game items,
 * - items only for current version
 *
 * @since 10.0.0
 */
typedef enum SC_GameItemsVersionOperator_tag {
    SC_GAMEITEMS_VERSION_OPERATOR_ANY,          /**< Game version is ignored. */
    SC_GAMEITEMS_VERSION_OPERATOR_CURRENT       /**< Game items must be valid for current game version. */
} SC_GameItemsVersionOperator_t;

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the object's reference count.
 *
 * @param   self        SC_GameItemsController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItemsController_Retain(SC_GameItemsController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the object's reference count by one. 
 * The object will be deleted automatically if the reference 
 * count reaches 0.
 *
 * Please note that this method is NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param   self        SC_GameItemsController instance handle.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItemsController_Release(SC_GameItemsController_h self);

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
SC_PUBLISHED SC_Error_t SC_GameItemsController_Cancel(SC_GameItemsController_h self);

/**
 * @brief Returns the list of game items that have been requested from the server.
 *
 * This method returns the list of game items that the controller loaded with the most recent request.
 *
 * If this method is called before a request to the server has been made, a @c NULL value will be returned.
 *
 * @param  self         SC_GameItemsController instance handle.
 * @return SC_GameItemList_h The list of game items that have been retrieved from the server.
 * @sa SC_GameItemsController_LoadGameItems(), SC_GameItemsController_LoadCoinPacks(), SC_GameItemsController_LoadGameItemsWithOptions().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameItemList_h SC_GameItemsController_GetItems(SC_GameItemsController_h self);

/**
 * @brief Returns the currency that the most recent server request was performed with.
 *
 * This method returns the currency used in the most recent request made to the server.
 *
 * If this method is called before a request or after a request that had no currency
 * parameter, a @c NULL value will be returned.
 * 
 * @param  self         SC_GameItemsController instance handle.
 * @return SC_String_h The currency symbol used.
 * @sa SC_GameItemsController_LoadCoinPacksWithCurrency(), SC_GameItemsController_LoadGameItemsWithOptions().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItemsController_GetCurrency(SC_GameItemsController_h self);

/**
 * @brief Returns the operator used to find game items with matching tags when requesting from the server.
 *
 * This method returns the tag operator used by the controller while performing the most recent request.
 *
 * @param  self         SC_GameItemsController instance handle.
 * @return SC_GamesItemsTagOperator_t The tag operator used when loading game items the server.
 * @sa SC_GameItemsController_LoadGameItemsWithOptions().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GamesItemsTagOperator_t SC_GameItemsController_GetTagsOperator(SC_GameItemsController_h self);

/**
 * @brief Returns the version operator used to find matching game items when requesting from the server.
 *
 * This method returns the game version operator used by the controller while performing the most recent request.
 * Each game item can be assigned a minimum and maximum game version for which it is accessible.
 * Editing this value is possible on the Game Items section at https://developer.scoreloop.com
 *
 * Then during the loading process from the server, the list can be narrowed to only
 * those that match the current game version (as passed during SC_Client instantiation).
 *
 * @param  self         SC_GameItemsController instance handle.
 * @return SC_GameItemsVersionOperator_t The game version operator used when loading game items the server.
 * @sa SC_GameItemsController_LoadGameItemsWithOptions().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameItemsVersionOperator_t SC_GameItemsController_GetGameVersionOperator(SC_GameItemsController_h self);

/**
 * @brief This method loads the list of game items from the server for the current session user.
 *
 * It will load the full list of game items valid for the current game version, discarding all tags.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemsController instance handle.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_GameItemsController_LoadGameItemsWithOptions
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemsController_LoadGameItems(SC_GameItemsController_h self);

/**
 * @brief This method loads the list of coin packs from the server, available for purchase for the current session user.
 *
 * It will load the full list of available coin packs for any game version.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemsController instance handle.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_GameItemsController_LoadCoinPacksWithCurrency
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemsController_LoadCoinPacks(SC_GameItemsController_h self);

/**
 * @brief This method loads the list of coin packs from the server, available for purchase for the current session user.
 *
 * It will load the full list of available coin packs for any game version.
 * Additionally it allows specification of the local currency in order to limit the results and payment 
 * methods (for example, EUR or USD).
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemsController instance handle.
 * @param  currency     User local currency or @c NULL.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_GameItemsController_LoadCoinPacksWithCurrency
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemsController_LoadCoinPacksWithCurrency(SC_GameItemsController_h self, const char *currency);

/**
 * @brief This method loads the list of game items from the server for the current session user with all options.
 *
 * It will load the list of game items valid for the specified game version (current or any) and tags filtering capabilities.
 * Tags can be filtered in two ways. Requested items must be marked with all specified tags or at least one.
 * To ignore tags filtering, a @c NULL value can be passed.
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self         SC_GameItemsController instance handle.
 * @param  gameVersionOperator Operator to let load list of game items valid only for current or any game version.
 * @param  tagsArray    An array of tags, that should match searched items. Last item of the array should be NULL, to indicate end of the tags.
 * @param  tagsOperator Operator describing usage of tags array.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_GameItemsController_LoadGameItemsWithOptions(
        SC_GameItemsController_h self, SC_GameItemsVersionOperator_t gameVersionOperator,
        const char *tagsArray[], SC_GamesItemsTagOperator_t tagsOperator);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAME_ITEMS_CONTROLLER_H__ */

/*! @} */
