/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_awards_bundle.h
 * @brief A model that refers to the collection of the award objects that are available in the game.
 *
 * @addtogroup  SC_AwardsBundle
 * @{
 *
 * The collection of award objects that is available in the game.
 */

#ifndef __SC_AWARDS_BUNDLE_H__
#define __SC_AWARDS_BUNDLE_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_string.h>
#include <scoreloop/sc_errors.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_AwardsBundle object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_AwardsBundle_tag *SC_AwardsBundle_h;

/** Type descriptors for SC_AwardsBundle. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_AwardsBundle);

/*-------------------------------------------------------------------------------------*
 * Dependent includes
 *
 * These files depend on SC_AwardsBundle_h typedef.
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_award.h>
#include <scoreloop/sc_achievement.h>

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current SC_AwardsBundle instance.
 *
 * @param self An opaque handle for the current SC_AwardBundle instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_AwardsBundle_Retain(SC_AwardsBundle_h self);

/**
 * @brief Decrements the object's reference count, deletes the object if counter reaches 0
 *
 * This method decrements the reference count for the current SC_AwardsBundle instance.
 * The current instance will be deleted automatically when the reference count reaches 0.
 *
 * Please note that this method is NULL pointer safe; that is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_AwardsBundle instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_AwardsBundle_Release(SC_AwardsBundle_h self);

/**
 * @brief Compares two SC_AwardsBundle_h objects.
 *
 * This method checks if two AwardsBundle are equal or not. 
 *
 * @param self An opaque handle for the current SC_AwardsBundle instance.
 * @param other An opaque handle for the other SC_AwardsBundle instance.
 * @return SC_Bool_t Returns SC_TRUE if both objects are equal. SC_FALSE otherwise.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_AwardsBundle_Equals(SC_AwardsBundle_h self, SC_AwardsBundle_h other);

/**
 * @brief Retrieves specific award from the list.
 *
 * This method returns the award at the given index.
 *
 * @param self An opaque handle for the current SC_AwardsBundle instance.
 * @param index The index of the score to be retrieved.
 * @return SC_Award_h The SC_Award object at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Award_h SC_AwardsBundle_GetAt(SC_AwardsBundle_h self, unsigned int index);

/**
 * @brief Returns the number of awards of the bundle.
 *
 * This method returns the number of awards contained.
 *
 * @param self An opaque handle for the current SC_AwardsBundle instance.
 * @return unsigned int The count of awards
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_AwardsBundle_GetCount(SC_AwardsBundle_h self);

/**
 * @brief Use this method to retrieve an SC_Award object with the specified unique identifier.
 *
 * This method retrieves an SC_Award object with the unique identifier as specified
 * on the developer website.
 *
 * @param self An opaque handle for the current SC_AwardBundle instance.
 * @param awardIdentifier the unique Award identifier that you specified on the developer website.
 * @return SC_Award_h The SC_Award object corresponding to the award identifier.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Award_h SC_AwardsBundle_GetByIdentifier(SC_AwardsBundle_h self,
        const char *awardIdentifier);

#ifdef __cplusplus
}
#endif

#endif /* __SC_AWARDS_BUNDLE_H__ */

/*! @} */
