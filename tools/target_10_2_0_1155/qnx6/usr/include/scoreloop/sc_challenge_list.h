/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_challenge_list.h
 * @brief       Class that models the collection of the SC_Challenges available in the game.
 *
 * @addtogroup  SC_ChallengeList
 * @{
 *
 * The collection of the \ref SC_Challenge available in the game.
 */

#ifndef __SC_CHALLENGE_LIST_H__
#define __SC_CHALLENGE_LIST_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_challenge.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_ChallengeList object handle.
 *
 * @since 10.0.0
 */
typedef struct SC_ChallengeList_tag* SC_ChallengeList_h;

/** Type descriptors for SC_ChallengeList.
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_ChallengeList);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments object's reference count.
 *
 * This method increments the reference count for the current SC_ChallengeList instance.
 * @param self An opaque handle for the current SC_ChallengeList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ChallengeList_Retain(SC_ChallengeList_h self);

/**
 * @brief Decrements object's reference count, deletes the object if counter reaches 0
 *
 * This method decrements the reference count for the current SC_ChallengeList instance.
 * The current instance will be automatically deleted when the reference count reaches 0.
 *
 * Please note that this method is NULL pointer safe, i.e. NULL as an argument will 
 * not cause an exception.
 *
 * @param self An opaque handle for the current SC_ChallengeList instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_ChallengeList_Release(SC_ChallengeList_h self);

/**
 * @brief Retrieves a specific challenge from the list.
 *
 * This method returns the challenge at the given index in the list.
 *
 * @param self An opaque handle for the current SC_ChallengeList instance.
 * @param index The index of the score to be retrieved.
 * @return SC_Challenge_h The challenge at the given index.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Challenge_h SC_ChallengeList_GetAt(SC_ChallengeList_h self,
        unsigned int index);

/**
 * @brief Returns the number of challenges on the list.
 *
 * This method returns the number of challenges retrieved from the server.
 *
 * @param self An opaque handle for the current SC_ChallengeList instance.
 * @return unsigned int The count of challenges
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_ChallengeList_GetCount(SC_ChallengeList_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CHALLENGE_LIST_H__ */

/*! @} */
