/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_price_tier.h
 * @brief       The SC_PriceTier class models the virtual price for game item.
 *
 * @addtogroup  SC_PriceTier
 * @{
 *
 * The \ref SC_PriceTier class models the virtual price for game item.
 */

#ifndef __SC_PRICE_TIER_H__
#define __SC_PRICE_TIER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_money_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_PriceTier object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_PriceTier_tag* SC_PriceTier_h;

/** Type descriptors for SC_PriceTier. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_PriceTier);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count by one.
 *
 * @param self An opaque handle for the current price tier instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_PriceTier_Retain(SC_PriceTier_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count by one. The SC_PriceTier instance
 * will be automatically deleted when the counter reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the price tier instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_PriceTier_Release(SC_PriceTier_h self);

/**
 * @brief Accessor that returns the identifier of the price tier.
 *
 * This method returns a unique identifier that is assigned to the specified price tier.
 *
 * @param self An opaque handle for the price tier instance.
 * @return SC_String_h The price tier unique identifier.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_PriceTier_GetIdentifier(SC_PriceTier_h self);

/**
 * @brief Accessor that returns the name of the price tier.
 *
 * This method returns the same name that is defined and present
 * on Custom Price Tiers section at https://developer.scoreloop.com
 *
 * @param self An opaque handle for the price tier instance.
 * @return SC_String_h The name of the price tier.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_PriceTier_GetName(SC_PriceTier_h self);

/**
 * @brief Accessor that returns the description of the price tier.
 *
 * This method returns the description assigned to price tier.
 *
 * @param self An opaque handle for the price tier instance.
 * @return SC_String_h The description of the price tier.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_PriceTier_GetDescription(SC_PriceTier_h self);

/**
 * @brief Returns an indication, if given price tier is free.
 *
 * This method returns @c SC_TRUE, when there is no price attached.
 * Free price tiers don't need any balance checks and payments processed.
 * Items marked with such a price tier will be immediately available for download.
 *
 * @param self An opaque handle for the price tier instance.
 * @return SC_Bool_t Indication if the price tier is free.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_PriceTier_IsFree(SC_PriceTier_h self);

/**
 * @brief Accessor that returns a list of prices.
 *
 * Each non-free price tier will have at least single price assigned.
 * The number of prices returned might however be more. It depends on:
 *  - payment methods
 *  - available currencies.
 *
 * NOTE: Currently purchases are not yet supported using this SDK.
 *
 * @param self An opaque handle for the price tier instance.
 * @return SC_MoneyList_h List of available prices.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_MoneyList_h SC_PriceTier_GetMinimumPrices(SC_PriceTier_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_PRICE_TIER_H__ */

/*! @} */

