/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_money_list.h
 * @brief       Class that models the collection of SC_Money available in the game.
 *
 * @addtogroup  SC_MoneyList
 * @{
 *
 * The collection of the \ref SC_Money objects available in the game.
 *
 */

#ifndef __SC_MONEY_LIST_H__
#define __SC_MONEY_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_money.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_MoneyList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_MoneyList_tag* SC_MoneyList_h;

/** Type descriptors for SC_MoneyList.
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_MoneyList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count
 *
 * This method increments the reference count for the current SC_MoneyList instance.
 *
 * @param self An opaque handle for the current SC_MoneyList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_MoneyList_Retain(SC_MoneyList_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0
 *
 * This method decrements the reference count for the current SC_MoneyList instance.
 * The current instance will be automatically deleted when the reference count reaches 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_MoneyList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_MoneyList_Release(SC_MoneyList_h self);

/**
 * @brief Retrieves a specific SC_Money object from the list.
 *
 * This method returns the SC_Money object at the given index in the list.
 *
 * @param self An opaque handle for the current SC_MoneyList instance.
 * @param index The index of the score to be retrieved.
 * @return SC_Money_h The SC_Money object at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Money_h SC_MoneyList_GetAt(SC_MoneyList_h self, unsigned int index);

/**
 * @brief Returns the number of SC_Money objects in the list.
 *
 * This method returns the number of SC_Money objects in the list.
 *
 * @param self An opaque handle for the current SC_MoneyList instance.
 * @return unsigned int The number of SC_Money objects in the list.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_MoneyList_GetCount(SC_MoneyList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_MONEY_LIST_H__ */

/*! @} */
