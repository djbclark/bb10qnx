/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_errors.h
 * @brief       Errors related to ScoreloopCore.
 *
 * @addtogroup  SC_Errors
 * @{
 * This file contains the definition of ScoreloopCore error codes.
 *
 */

#ifndef __SC_ERRORS_H__
#define __SC_ERRORS_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Macros
 *-------------------------------------------------------------------------------------*/

/** Helper macro to save some typing when chaining operations. 
 *
 * @since 10.0.0
 */
#define DO_IF_OK(retCode,op)   if ((retCode) == SC_OK) { (retCode) = (op); }

/** Helper macro to save some typing when chaining operations. 
 *
 * @since 10.0.0
 */
#define DO_IF_OK_NORET(retCode, op) if ((retCode) == SC_OK) { op; }

/** Helper macro to save some typing when chaining operations. 
 *
 * @since 10.0.0
 */
#define RET_IF_NOT_OK(retCode, op) do { DO_IF_OK(retCode, op); \
    if (retCode != SC_OK) { return retCode; } } while (0)

/** Helper macro to save some typing when chaining operations. 
 *
 * @since 10.2.0
 */
#define RET_IF_NOT_OK_TRACED(retCode, op) do { DO_IF_OK(retCode, op); \
    if (retCode != SC_OK) { TRACE_EXIT_RC(retCode); return retCode; } } while (0)

/** Helper macro to mark unused params to get rid of compiler warnings. 
 *
 * @since 10.0.0
 */
#define SC_UNUSED_PARAM(param) (void)(param)

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** ScoreloopCore error codes. 
 *
 * @since 10.0.0
 */
typedef unsigned int SC_Error_t;

/** ScoreloopCore error codes. 
 *
 * @since 10.0.0
 */
enum SC_Error_tag {
    SC_OK                 = 0,     /**< No error occurred. */
    SC_OUT_OF_MEMORY,              /**< Failed to allocate memory. */
    SC_NOT_IMPLEMENTED_YET,        /**< Particular interface was not yet implemented. */
    SC_NOT_SUPPORTED,              /**< Particular functionality is not supported on this platform. */
    SC_PAL_INITIALIZATION_FAILED,  /**< Pal context cannot be created with init data. */
    SC_INVALID_STATE,              /**< Invalid state of object. */
    SC_UNKNOWN_AWARD,              /**< Given award's identifier was unknown. */
    SC_NOT_FOUND,                  /**< Requested object has not been found. */
    SC_AWARDS_BUNDLE_NOT_FOUND,    /**< SLAwards.bundle directory has not been found. */
    SC_INVALID_ARGUMENT,           /**< Invalid argument has been passed to method. */
    SC_SESSION_NOT_AUTHENTICATED,  /**< Session is not authenticated. */
    SC_INVALID_AWARDS_BUNDLE,      /**< Awards bundle is invalid. */
    SC_SYNCHRONIZATION_IN_PROGRESS,/**< Achievements synchronization already in progress. */
    SC_SCORE_FORMATTER_CFG_NOT_FOUND,   /**< Score formatter configuration file is missing. */
    SC_SCORE_FORMATTER_CFG_INVALID,     /**< Score formatter configuration file is invalid. */
    SC_STRING_INVALID_UTF8,         /**< The UTF8 sequence for an string is invalid */
    SC_DEV_PERMISSION_DENIED,       /**< Code failed to retrieve device ID due to permission restrictions. */
    SC_DISABLED_DUE_TO_CORPORATE_LIABLE_MODE, /**< The device is in corporate liable mode which forbids the usage of Scoreloop */

    /* Request-processing related codes */
    SC_HTTP_SERVER_ERROR = 100,     /**< Server returned non-200 response code. */
    SC_INVALID_RANGE,               /**< User tried to load next/previous range when there is none available. */
    SC_INVALID_SERVER_RESPONSE,     /**< Invalid response received from server. */
    SC_HANDSHAKE_FAILED,            /**< Handshake request wasn't successful. */
    SC_REQUEST_FAILED,              /**< Request failed for other reason (server-side). */
    SC_REQUEST_CANCELLED,           /**< Request has been cancelled by the submitter. */
    SC_TOO_MANY_REQUETS_QUEUED,     /**< There are too many requests in the queue now. */
    SC_INVALID_GAME_ID,             /**< Invalid game id was used in handshake */
    SC_USER_NOT_FOUND,              /**< Specified user doesn't exist */
    SC_INACCESSIBLE_USER,           /**< Request in context of invalid user, e.g. asking for activities of a user that is not a friend of the session user */
    SC_NO_NETWORK,                  /**< Request failed due to no network connectivity */
    SC_INVALID_GAME_SECRET,         /**< Invalid game secret used in handshake
                                     *
                                     * @since 10.2.0 */

    /* Challenge related codes */
    SC_CHALLENGE_NOT_ENOUGH_MONEY = 200,/**< There is not enough money to play the challenge. */
    SC_CANNOT_ACCEPT_CHALLENGE,    /**< Challenge is not playable for user. */
    SC_CANNOT_REJECT_CHALLENGE,    /**< User cannot reject challenge. */
    SC_CHALLENGE_NOT_SET,          /**< Challenge is not set. */
    SC_SCORE_MODE_DOES_NOT_MATCH,  /**< Score's mode does not match with challenge's mode. */
    SC_CHALLENGE_WRONG_CURRENCY,   /**< Challenge submitted with currency different than the game defined on server. */

    /* User related error codes */
    SC_INVALID_USER_DATA = 300,    /**< User data validation failed when updating */
    SC_CONTEXT_VERSION_MISMATCH,   /**< Could not update old user context. */
    SC_INVALID_USER_IMAGE_FORMAT,  /**< Provided image isn't proper JPEG nor PNG file */

    SC_FILE_ERROR = 400,           /**< Filesystem operation failed. */

    SC_BUDDYHOOD_FAILED = 450,     /**< Generic adding buddy failure */
    SC_BUDDYHOOD_SELF_FAILED,      /**< Trying to add yourself as a buddy? */
    SC_BUDDYHOOD_INVITATION_INVALID,/**< Buddyhood invitation invalid or expired */
    SC_BUDDYHOOD_ALREADY_BUDDY,    /**< User is already a buddy */
    SC_BUDDYHOOD_NOT_BUDDY,        /**< User is not a buddy */

    /* Social related error codes */
    SC_AUTHORIZATION_FAILED = 500, /**< Authorization failed. */
    SC_AUTHORIZATION_DENIED,       /**< Authorization denied by user. */
    SC_AUTHORIZATION_CANCELED,     /**< Authorization canceled by user. */

    /* Game-items related codes */
    SC_GAMEITEM_NOT_PURCHASED = 550, /**< Ownership validation check failed. */

    /* UI related codes */
    SC_UI_ALREADY_DISPLAYED = 2000, /**< UI already displayed a view and can't show another one until dismissed. */
    SC_UI_SHOW_FAILED,              /**< UI view displaying failed */
    SC_UI_CLOSE_FAILED,             /**< UI view closing failed */
    SC_UI_MISSING_FIELD,            /**< UI missed a field set, when invoking a view */
    SC_UI_MISSING_VALUE,            /**< UI missed a value set for a field, when invoking a view */
};

/** Possible user profile validation errors (see SC_UserController_GetValidationErrors). 
 *
 * @since 10.0.0
 */
typedef enum SC_UserValidationError_tag {
    SC_EMAIL_ALREADY_TAKEN = (1 << 0),       /**< The E-mail is already registered */
    SC_EMAIL_FORMAT_INVALID = (1 << 1),      /**< The format of the E-mail address id invalid  */
    SC_USERNAME_ALREADY_TAKEN = (1 << 2),    /**< The username is already registered */
    SC_USERNAME_FORMAT_INVALID = (1 << 3),   /**< The format of the username is invalid */
    SC_USERNAME_TOO_SHORT = (1 << 4),        /**< The given username is too short */
    SC_IMAGE_TOO_LARGE = (1 << 5),           /**< The image is too large */
    SC_IMAGE_UNSUPPORTED_MIME_TYPE = (1 << 6),/**< The image is of an unsupported type */
    SC_USERNAME_TOO_LONG = (1 << 7),         /**< The given username is too long */
    SC_USERNAME_INAPPROPRIATE = (1 << 8)     /**< The given username is inappropriate */
} SC_UserValidationError_t;

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Maps an error code to its name.
 *
 * This method maps an error code to its name.
 *
 * @param error The type of error occurred
 * @return const char The error description
 *
 * Maps an error code to its name.
 *
 * @since 10.0.0
 */
SC_PUBLISHED const char * SC_MapErrorToStr(SC_Error_t error);

#ifdef __cplusplus
}
#endif

#endif /* __SC_ERRORS_H__ */

/*! @} */
