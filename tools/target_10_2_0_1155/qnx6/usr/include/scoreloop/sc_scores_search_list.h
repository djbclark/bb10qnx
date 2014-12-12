/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_scores_search_list.h
 * @brief       Definitions of search lists available on the server.
 *
 * @addtogroup  SC_ScoresSearchList
 * @{
 *
 * A search list in an abstraction for filtering and
 * sorting a set of entities that are stored on the
 * Scoreloop servers.
 *
 * Search lists are used by the following controllers to filter scores and rankings:
 * - \ref SC_ScoresController
 * - \ref SC_RankingController
 *
 * The following controllers use search lists to filter scores and rankings:
 * - Global search parameters
 * - The scores submitted during the previous 24 hours
 * - The country location of the user
 *
 * Basic use:
 * -# Set the search list of the relevant controller to perform
 *    the required filtering.
 * -# Use the controller to make the server request as normal.
 */

#ifndef __SC_SCORES_SEARCH_LIST_H__
#define __SC_SCORES_SEARCH_LIST_H__

#include <scoreloop/sc_types.h>
#include <scoreloop/sc_user.h>

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Time intervals that are used to limit the scores returned. 
 *
 * @since 10.0.0
 */
typedef enum SC_TimeInterval_tag {
    /** Return all the scores (no time restriction) */
    SC_TIME_INTERVAL_ALL = 0,
    /** Return the scores submitted during last 24 hours */
    SC_TIME_INTERVAL_24H,
    /** Return the scores submitted during last 7 days */
    SC_TIME_INTERVAL_7DAYS,
    /** Return the scores submitted during last 30 days */
    SC_TIME_INTERVAL_30DAYS
} SC_TimeInterval_t;

/** Country selectors that are used to limit the scores returned. 
 *
 * @since 10.0.0
 */
typedef enum SC_CountrySelector_tag {
    /** Return scores from all countries */
    SC_COUNTRY_SELECTOR_ALL,
    /** Return scores using nationality set in user's profile
     *
     * @deprecated 10.2.0
     */
    SC_COUNTRY_SELECTOR_USER_NATIONALITY,
    /** Return scores using country, the scores are submitted from (via geo-localization) */
    SC_COUNTRY_SELECTOR_LOCAL_COUNTRY,
    /** Return scores from country explicitly set in SC_ScoresSearchList
    *
    * @deprecated 10.2.0
    */
    SC_COUNTRY_SELECTOR_EXPLICIT
} SC_CountrySelector_t;

/** User selectors that are used to limit the scores returned. 
 *
 * @since 10.0.0
 */
typedef enum SC_UsersSelector_tag {
    /** Return scores from all users */
    SC_USERS_SELECTOR_ALL,
    /** Return scores from user's buddyhood - buddyhood is determined based on SC_ScoresSearchList.buddyhoodUser */
    SC_USERS_SELECTOR_BUDDYHOOD
} SC_UsersSelector_t;

/** Structure containing all available score search list load criterias. 
 *
 * @since 10.0.0
 */
typedef struct SC_ScoresSearchList_tag {
    /** Time interval filter */
    SC_TimeInterval_t timeInterval;
    /** Country filter */
    SC_CountrySelector_t countrySelector;
    /** Used only with combination with countrySelector == SC_COUNTRY_SELECTOR_EXPLICIT.
     * For other countrySelector types should be set to NULL.
     * The value should be a country code compliant to ISO3166. 
     *
     * @deprecated 10.2.0
     */
    const char *country;
    /** Users filter */
    SC_UsersSelector_t usersSelector;
    /** Used only with combination with usersSelector == SC_USERS_SELECTOR_BUDDYHOOD.
     * For other usersSelector types should be set to NULL. */
    SC_User_h buddyhoodUser;
} SC_ScoresSearchList_t;

/** Global search list 
 *
 * @since 10.0.0
 */
SC_PUBLISHED extern const struct SC_ScoresSearchList_tag SC_SCORES_SEARCH_LIST_ALL;
/** Search list of scores submitted during last 24 hours 
 *
 * @since 10.0.0
 */
SC_PUBLISHED extern const struct SC_ScoresSearchList_tag SC_SCORES_SEARCH_LIST_24H;
/** Global search list filtered with user's country 
 *
 * @since 10.0.0
 */
SC_PUBLISHED extern const struct SC_ScoresSearchList_tag SC_SCORES_SEARCH_LIST_USER_COUNTRY;

#ifdef __cplusplus
}
#endif

#endif /* __SC_SCORES_SEARCH_LIST_H__ */

/*! @} */
