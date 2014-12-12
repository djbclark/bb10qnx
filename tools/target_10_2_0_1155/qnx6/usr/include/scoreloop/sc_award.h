/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * \brief   Models an award that is available in a game application.
 *
 * @file        sc_award.h
 * @addtogroup  SC_Award
 * @{
 * The \ref SC_Award class models an award that is available in a game application.
 * You must configure awards on the Scoreloop developer website at https://developer.scoreloop.com, where you can specify or edit
 * each of the individual properties for the following class.
 *
 * @note Instances of Awards are not created directly, but are specified declaratively in the Scoreloop-generated awards bundle.
 *
 * Once an award is configured on the website, Scoreloop generates an awards bundle, which must be added to the game project after unzipping it.
 * The awards bundle provides local access to the individual properties like:
 * - The identifier
 * - The initial value of the award (which is any number)
 * - The achieving value of the award (which is any number, greater or equal to initial value)
 * - The reward
 * - The title and description
 * - The image names for both states (unachieved and achieved)
 *
 * Awards are static. You can only query the information defined in an award bundle. 
 * You can build a screen to list the awards. Achievements bring life to this screen.
 * Achievement describes if and when user gained an award.
 *
 * Users unlock an award by meeting a certain value that is set inside the bundle.
 * This is defined as the achieving value for the award. You can configure awards
 * so that this value can be reached in incremental stages, if desired.
 * The number of incremental stages is defined by subtraction:
 * SC_Award_GetAchievingValue() - SC_Award_GetInitialValue().
 *
 * For example, configure an award with the following properties:
 * - Initial value: 0, i.e., the starting value.
 * - Achieving value: 10,
 * - Then the expected progress tracked by an achievement must fall into range: (0,10),
 * that gives 10 incremental stages.
 *
 * When the game is played, this might mean that the user must collect 10 secret jewels in order to unlock the award.
 * Before the user finds the first jewel the following is true:
 * - Initial value = 0.
 *
 * With each jewel found, the value is incremented by 1. When the number of jewels found equals the achieving value then the current user achieves the award.
 *
 * The award identifiers with the reverse DNS style names are used to localize, invoke and increment the object on SC_AchievementsController.
 *
 * @sa SC_Achievement, SC_AchievementsController, @link coresocial-achievements Awards and Achievements @endlink */

#ifndef __SC_AWARD_H__
#define __SC_AWARD_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_money.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Award object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_Award_tag* SC_Award_h;

/** Type descriptors for SC_Award. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Award);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the instance by 1.
 *
 * @param self An opaque handle for the current SC_Award instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Award_Retain(SC_Award_h self);

/**
 * @brief Decrements the object's reference count; deletes the object if counter reaches 0.
 *
 * This method decrements the instance's reference count by 1.
 * The instance will automatically be deleted when the
 * reference count reaches 0.
 *
 * Note that this method is NULL pointer safe; that is, NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current award instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Award_Release(SC_Award_h self);

/**
 * @brief Returns the identifier that uniquely identifies the award.
 *
 * When you configure an award at https://developer.scoreloop.com , you
 * choose a unique reverse DNS style name to identify it (for example,
 * "com.mycompany.myfirstaward"). After the awards are configured on the
 * developer website, Scoreloop generates an award bundle which you must
 * unzip and add to your game application. This provides local access to all award
 * information, including award identifiers.
 *
 * @param self An opaque handle for the current award instance.
 * @return SC_String_h The identifier that identifies the award.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Award_GetIdentifier(SC_Award_h self);

/**
 * @brief Returns the initial value for the award.
 *
 * This method returns the initial value for the award.
 *
 * @param self An opaque handle for the current award instance.
 * @return int The intial value for the award instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_Award_GetInitialValue(SC_Award_h self);

/**
 * @brief Returns the achieving value for the award instance.
 *
 * This method returns the achieving value for the award instance. The achieving value
 * is the value that a user must reach before achieving the award.
 *
 * @param self An opaque handle for the current award instance.
 * @return int The achieving value of the award.
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_Award_GetAchievingValue(SC_Award_h self);

/**
 * @brief Returns the localized description for the award.
 *
 * A short description of the award that you write. The localized description
 * should be used to display additional information about the SC_Award to users.
 * This property is configured at https://developer.scoreloop.com , and is accessed locally
 * using the awards bundle.
 *
 * @param self An opaque handle for the current award instance.
 * @return SC_String_h The localized description for the award.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Award_GetLocalizedDescription(SC_Award_h self);

/**
 * @brief Returns the localized title for the SC_Award.
 *
 * In addition to the reverse DNS identifier, the award objects can also store a localized title.
 * The localized title provides a more meaningful or natural name for the SC_Award object,
 * which you use for display purposes.
 * This property is configured at https://developer.scoreloop.com and is accessed locally
 * using the award bundle.
 *
 * @param self An opaque handle for the current award instance.
 * @return SC_String_h The localized title of the award.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Award_GetLocalizedTitle(SC_Award_h self);

/**
 * @brief Returns an SC_Money object corresponding to the reward that the user will
 * receive if they achieve the award.
 *
 * The amount of money that is credited to the user's account once the award has been achieved.
 * This property is configured at https://developer.scoreloop.com and is accessed locally
 * using the SC_Awards bundle.

 * @param self An opaque handle for the current award instance.
 * @return SC_Money_h The reward.
 * @sa SC_Money
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Money_h SC_Award_GetRewardedMoney(SC_Award_h self);

/**
 * @brief Helper method, that checks whether the award could be achieved for the value supplied.
 *
 * This method checks whether the award could be achieved for the supplied value.
 * The supplied value must be greater than or equal to the achieving value.
 *
 * @param self An opaque handle for the current award instance.
 * @param value The value to be checked.
 * @return SC_Bool_t SC_TRUE if a value achieves the award, otherwise SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Award_IsAchievedByValue(SC_Award_h self, int value);

/**
 * @brief Helper method, that checks whether a value falls into the award's expected range.
 *
 * This method checks whether a given value falls into the range specified for the award.
 * The range is defined by initial and achieving values, which can be also obtained by calling:
 * SC_Award_GetInitialValue() and SC_Award_GetAchievingValue().
 *
 * @param self An opaque handle for the current award instance.
 * @param value The value to be checked.
 * @return SC_Bool_t SC_TRUE if the value falls into the range, otherwise SC_FALSE.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_Award_IsValidCounterValue(SC_Award_h self, int value);

/**
 * @brief Gets the name of the image name that should be displayed if the award is achieved by a user.
 *
 * This method returns the name of the image that should be displayed if a user achieves the award.
 * It could be also @c NULL, if an image was not assigned.
 *
 * @param self An opaque handle for the current award instance.
 * @return SC_String_h The image name.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Award_GetAchievedImageName(SC_Award_h self);

/**
 * @brief Gets the name of the image name that should be displayed if the award is not achieved by a user.
 *
 * This method returns the name of the image that should be displayed if a user does not achieve the award.
 *
 * @param self An opaque handle for the current award instance.
 * @return SC_String_h The image name.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_Award_GetUnachievedImageName(SC_Award_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_AWARD_H__ */

/*! @} */
