/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @brief       Models whether an SC_Award is achieved by a user or not.
 * @file        sc_achievement.h
 * @addtogroup  SC_Achievement
 * @{
 *
 * The Achievement class models whether or not a user has achieved an \ref SC_Award.
 * It maintains information about achievement progress when the award cannot be granted in a single step,
 * It keeps track of the date and the image, which reflects the current state.
 *
 * You query this state by checking the Boolean value returned by SC_Achievement_IsAchieved().
 * - If the Boolean value equals SC_TRUE, then the user has achieved the award.
 * - If the Boolean value equals SC_FALSE, then the user has not achieved the award.
 *
 * To achieve an award, a user must reach an arbitrary value that you set; this is 1 in most cases. You can configure the "achieving value" so it can be reached in stages.
 * You must configure both the "achieving value" of the award and the number of stages that it takes to reach it at https://developer.scoreloop.com.
 *
 * For example, you might configure an award so that the "achieving value" equals 10,
 * and that this can be reached in 10 separate incremental stages.
 * When the game is played, this might mean that the user could achieve the award
 * by collecting 10 secret jewels - finding a single jewel would represent completing
 * one of the configured incremental stages. After the tenth jewel has been found then
 * the user has reached the configured "achieving value" and achieves the award.
 *
 * The progress however is stored only locally on the device.
 * Just the information about achieved awards is synchronized with the server.
 *
 * Achievement objects are retrieved from the server by using an AchievementsController.
 *
 * @sa SC_Award, SC_AchievementsController, @link coresocial-achievements Awards and Achievements @endlink.
 *
 */

#ifndef __SC_ACHIEVEMENT_H__
#define __SC_ACHIEVEMENT_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_award.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Achievement object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_Achievement_tag* SC_Achievement_h;

/** Type descriptors for SC_Achievement. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Achievement);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the instance by 1.
 *
 * @param self An opaque handle for the current achievement instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Achievement_Retain(SC_Achievement_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the instance's reference count by 1.
 * The instance will be automatically deleted when the reference
 * count reaches 0.
 *
 * Note that this method is NULL pointer safe; that is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current achievement instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Achievement_Release(SC_Achievement_h self);

/**
 * @brief Returns the SC_Award object that this achievement refers to.
 *
 * This method returns the award object that this achievement refers to.
 *
 * @param self An opaque handle for the current achievement instance.
 * @return SC_Award_h The Award that this achievement refers to.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Award_h SC_Achievement_GetAward(SC_Achievement_h self);

/**
 * @brief Returns the identifier that uniquely identifies the achievement on the Scoreloop server.
 *
 * This method returns the identifier that uniquely identifies the achievement on
 * the Scoreloop server. The value is generated and assigned by Scoreloop.
 *
 * @param self An opaque handle for the current achievement instance.
 * @return SC_String_h The identifier that identifies the achievement.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Achievement_GetIdentifier(SC_Achievement_h self);

/**
 * @brief Returns the date on which the SC_Award was achieved.
 *
 * This method returns the date on which the award was achieved. It will have a value of @c NULL
 * if the award has not yet been achieved.
 *
 * @param self An opaque handle for the current achievement instance.
 * @return SC_String_h The date on which the award was achieved.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Achievement_GetDate(SC_Achievement_h self);

/**
 * @brief Returns whether or not the SC_Award has been achieved.
 *
 * This method returns a Boolean value that indicates if the SC_Award has been achieved
 * or not.
 *
 * @param self An opaque handle for the current achievement instance.
 * @return SC_Bool_t Boolean value that indicates whether or not the award was achieved.
 *
 * @since 10.0.0
 *
 */
SC_PUBLISHED SC_Bool_t SC_Achievement_IsAchieved(SC_Achievement_h self);

/**
 * @brief Returns the current value of the achieving progress obtained by the user.
 *
 * This method returns the value of the achieving progress that is obtained by the user.
 * The value will fall into the range defined by an award: SC_Award_GetInitialValue()
 * and SC_Award_GetAchievingValue().
 * If this property matches or exceeds the achieving value the achievement is granted.
 *
 * @param self An opaque handle for the current achievement instance.
 * @return int The achieving progress obtained by the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_Achievement_GetValue(SC_Achievement_h self);

/**
 * @brief Returns the name of the image associated with the achievement.
 *
 * This method returns the image name of an achievement. If achieved, this name
 * will refer to the achieved image of the award object, otherwise to the unachieved image.
 *
 * @param self An opaque handle for the current achievement instance.
 * @return SC_String_h The name of the image associated with the achievement.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Achievement_GetImageName(SC_Achievement_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ACHIEVEMENT_H__ */

/*! @} */
