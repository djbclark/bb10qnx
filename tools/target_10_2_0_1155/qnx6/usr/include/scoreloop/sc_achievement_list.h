/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_achievement_list.h
 * @brief       Class that models the collection of the SC_Achievements available in the game.
 *
 * @addtogroup  SC_AchievementList
 * @{
 *
 * The collection of the \ref SC_Achievement that is available in the game.
 * Call SC_AchievementList_GetAchievedCount(), to retrieves the awards achieved by the user.
 * SC_AchievementList_GetCount() returns the number of achievements in the list.
 */

#ifndef __SC_ACHIEVEMENT_LIST_H__
#define __SC_ACHIEVEMENT_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_achievement.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_AchievementList object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_AchievementList_tag* SC_AchievementList_h;

/** Type descriptors for SC_AchievementList. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_AchievementList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current SC_AchievementList instance.
 *
 * @param self An opaque handle for the current SC_AchievementList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_AchievementList_Retain(SC_AchievementList_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0
 *
 * This method decrements the reference count for the current SC_AchievementList instance.
 * The current instance is automatically deleted when the reference count reaches 0.
 *
 * Please note that this method is NULL pointer safe; that is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_AchievementList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_AchievementList_Release(SC_AchievementList_h self);

/**
 * @brief Retrieves a specific SC_Achievement from the list of achievements.
 *
 * This method returns the SC_Achievement object at the given index in the SC_AchievementList.
 *
 * @param self An opaque handle for the current SC_AchievementList instance.
 * @param index The index of the SC_Achievement to be retrieved.
 * @return SC_Achievement_h The SC_Achievement object retrieved from the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Achievement_h SC_AchievementList_GetAt(
        SC_AchievementList_h self, unsigned int index);

/**
 * @brief Returns the number of SC_Achievement objects in the SC_AchievementList.
 *
 * This method returns the number of SC_Achievement objects in the SC_AchievementList.
 *
 * @param self An opaque handle for the current SC_AchievementList instance.
 * @return unsigned int The number of SC_Achievement objects in the list.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_AchievementList_GetCount(SC_AchievementList_h self);

/**
 * @brief This method counts how many awards have been achieved in the SC_AchievementList.
 *
 * This method returns the number of awards achieved by the user.
 *
 * @param self An opaque handle for the current SC_AchievementList instance.
 * @return unsigned int The number of SC_Achievement objects achieved by the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_AchievementList_GetAchievedCount(SC_AchievementList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ACHIEVEMENT_LIST_H__ */

/*! @} */
