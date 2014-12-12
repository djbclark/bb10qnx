/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_game_item.h
 * @brief       The SC_GameItem class models the virtual items attached to the game.
 *
 * @addtogroup  SC_GameItem
 * @{
 *
 * The \ref SC_GameItem class models all aspects of a Scoreloop game item.
 */

#ifndef __SC_GAME_ITEM_H__
#define __SC_GAME_ITEM_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_price_tier.h>
#include <scoreloop/sc_money.h>
#include <scoreloop/sc_string_dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_GameItem object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_GameItem_tag* SC_GameItem_h;

/** Type descriptors for SC_GameItem.
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_GameItem);

/** Types of virtual game items - coin packs or attached game data 
 *
 * @since 10.0.0
 */
typedef enum SC_GameItemKind_tag {
    SC_GAMEITEMKIND_NONCONSUMABLE           = 0,    /**< Item is non-consumable. Once purchased, will remain free for the user to redownload. */
    SC_GAMEITEMKIND_CONSUMABLE_COINPACK             /**< Item is a coin-pack, that increases the balance. */
} SC_GameItemKind_t;

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the object's reference count.
 *
 * @param self An opaque handle for the current game item instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItem_Retain(SC_GameItem_h self);

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
 * @param self An opaque handle for the current game item instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_GameItem_Release(SC_GameItem_h self);

/**
 * @brief Accessor that returns the identifier of the game.
 *
 * This method returns a unique identifier that is assigned to the specified game item.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The game item unique identifier.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetIdentifier(SC_GameItem_h self);

/**
 * @brief Accessor that returns the name of the game item.
 *
 * This method returns the same name that is defined and present
 * on the Game Items section at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The name of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetName(SC_GameItem_h self);

/**
 * @brief Accessor that returns the identifier of the product associated with game item.
 *
 * This method returns the same identifier of the product that is defined and present
 * on the Game Items section at https://developer.scoreloop.com
 *
 * In general it helps to connect the Scoreloop game item with items coming from other markets.
 * It is useful in cases where purchases are implemented
 * directly by the game developers, using the platform native API.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The product identifier of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetProductIdentifier(SC_GameItem_h self);

/**
 * @brief Accessor that returns the download URL for the game item.
 *
 * This method returns the URL to the game item content that is placed
 * on Scoreloop CDN servers. By default this value is @c NULL.
 * To get a valid URL, SC_GameItemController
 * must be used and the SC_GameItemController_LoadDownloadURL() action issued.
 * This will perform a server-side check whether the current session user is allowed
 * to download the item, and a temporary URL will be provided.
 *
 * The URL will expire after short time (default: 5 minutes), if the download
 * process is not started.
 *
 * Content can be defined as a single file
 * on the Game Items section at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The URL of the game item's content.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetDownloadUrl(SC_GameItem_h self);

/**
 * @brief Accessor that returns the description of the game item.
 *
 * This method returns the description assigned to the game item.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The description of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetDescription(SC_GameItem_h self);

/**
 * @brief Accessor that returns the metadata of the game item.
 *
 * This method returns the metadata assigned to the game item.
 * Metadata is developer specific information that can be
 * assigned on the Game Items section at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The metadata of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetMetadata(SC_GameItem_h self);

/**
 * @brief Accessor that returns the kind of the game item.
 *
 * This method returns the kind of game item (for example, a regular DLC
 * or a coin-pack increasing the balance).
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_GameItemKind_t The kind of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_GameItemKind_t SC_GameItem_GetKind(SC_GameItem_h self);

/**
 * @brief Accessor that returns the size of the game item's content.
 *
 * This method returns the size of the content assigned to the game item.
 * This is the size of the single file uploaded on Scoreloop CDN
 * servers.
 *
 * The content can be then loaded using the DownloadURL property
 * of the current game item.
 *
 * @param self An opaque handle for the game item instance.
 * @return unsigned int The size of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_GameItem_GetContentSize(SC_GameItem_h self);

/**
 * @brief Accessor that returns the MIME type of the game item's content.
 *
 * This method returns the MIME type of the content assigned to the game item.
 * Depending on the kind of file uploaded on Scoreloop CDN servers,
 * the MIME might vary. (For example, text/plain, image/png, or application/zip)
 *
 * The content can be then loaded using the DownloadURL property
 * of the current game item.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The MIME type of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetContentType(SC_GameItem_h self);

/**
 * @brief Accessor that returns the purchase date of the game item or @c NULL.
 *
 * This method returns either the purchase date of the game item, or @c NULL if it was not bought yet.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_String_h The purchase date of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_GameItem_GetPurchaseDate(SC_GameItem_h self);

/**
 * @brief Accessor that returns the coins increasing user's balance
 *        when purchased, or @c NULL if not a coin-pack item.
 *
 * This method returns the amount of coins that a user can add into their
 * balance when this coin pack is purchased. If the item is not a coin-pack,
 * @c NULL will be returned.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_Money_h The amount of coins of the coin pack.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Money_h SC_GameItem_GetCoinPackValue(SC_GameItem_h self);

/**
 * @brief Accessor that returns a list of URLs and identifiers 
 *        for images attached to the game item.
 *
 * This method returns a list of attached image URLs, together with related identifiers.
 *
 * The images in any resolution can be attached to the game item
 * on the Game Items section at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_StringDictionary_h The list of images of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_StringDictionary_h SC_GameItem_GetImages(SC_GameItem_h self);

/**
 * @brief Checks whether the game item is marked with a specified tag.
 *
 * This method evaluates if the game item is tagged with specified text.
 * If it is, it will return @c SC_TRUE.
 *
 * The tags can be defined for the game item
 * on the Game Items section at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the game item instance.
 * @param tag Tag expected for current game item.
 * @return SC_Bool_t The indication, if the game item is marked with given tag.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_GameItem_ContainsTag(SC_GameItem_h self, const char *tag);

/**
 * @brief Accessor that returns the price tier of the game item.
 *
 * This method returns the price tier of game item.
 * It is then possible to evaluate the prices for which the game item could be purchased.
 *
 * @param self An opaque handle for the game item instance.
 * @return SC_PriceTier_h The price tier of the game item.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_PriceTier_h SC_GameItem_GetPriceTier(SC_GameItem_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_GAME_ITEM_H__ */

/*! @} */
