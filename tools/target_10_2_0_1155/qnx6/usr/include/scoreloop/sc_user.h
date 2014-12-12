/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_user.h
 * @brief       Models the game user.
 *
 * @addtogroup  SC_User
 * @{
 *
 * Instances of \ref SC_User model the game user.
 * Scoreloop considers users to be unique players tied to unique devices.
 * Instances of \ref SC_Session maintain an instance of the local user, referred to as the session user.
 *
 * Instances of \ref SC_User that are not the session user may not have all properties available.
 *
 * However, the following properties are always available:
 * - Login
 *
 * Instances of \ref SC_User are available from:
 * -# The Scoreloop session - SC_Session_GetUser()
 * -# An instance of \ref SC_Score - SC_Score_GetUser()
 * -# An instance of \ref SC_UserController - SC_UserController_GetUser() 
 * -# An instance of \ref SC_UsersController - SC_UsersController_GetUsers()
 * -# An instance of \ref SC_Challenge :
 *  - SC_Challenge_GetContender()
 *  - SC_Challenge_GetContestant()
 *  - SC_Challenge_GetLoser()
 *  - SC_Challenge_GetWinner()
 *
 * \ref SC_User objects are managed by two controllers:
 * -# The \ref SC_UserController is used to retrieve information for an arbitrary user from the server. It is also used to update the attributes of the session user.
 * -# The \ref SC_UsersController, retrieves lists of \ref SC_User objects from the server.
 *
 * @note To display strings received from the Scoreloop APIs (e.g. when using SC_User_GetLogin), watch out for string encodings issues. The Scoreloop APIs always return UTF-8 encoded strings. If the UI Toolkit has it's own datatype for strings (e.g. QString in the case of the Cascades framework), ensure that the encoding is respected when copying the Scoreloop string into the frameworks datatype.
 *
 * Sample code to copy string into QStrings:
 * 
 * <table><tr><td>
 * @code
 *
 * SC_String_h *mySCString = SC_User_GetLogin(myUser);
 *
 * QString myQString;
 * if (mySCString && SC_String_GetData(mySCString)) // handle NULL cases
 * {
 *   myQString = QString::fromUtf8(SC_String_GetData(mySCString)); // tell QString that the data we copy is UTF8
 * }
 *
 * </td></tr></table>
 * @endcode
 *
 */

#ifndef __SC_USER_H__
#define __SC_USER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_object.h>
#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_string.h>
#include <scoreloop/sc_context.h>
#include <scoreloop/sc_money.h>
#include <scoreloop/sc_activity.h>

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** The user's profile image source 
 *
 * @since 10.0.0
 */
typedef enum SC_UserImageSource_tag {
    SC_USER_IMAGE_SOURCE_SCORELOOP,
    SC_USER_IMAGE_SOURCE_FACEBOOK,
    SC_USER_IMAGE_SOURCE_TWITTER,
    SC_USER_IMAGE_SOURCE_NOT_SET
} SC_UserImageSource_t;

/** The state of the user. 
 *
 * @since 10.0.0
 */
typedef enum SC_UserState_tag {
  SC_USER_STATE_ANONYMOUS = 0, /**< No user information was supplied, the user name was generated by Scoreloop. */
  SC_USER_STATE_ACTIVE, /**< The account validation process for the user has been completed.*/
  SC_USER_STATE_DELETED,/**< The user account has been deleted. */
  SC_USER_STATE_PASSIVE,/**< A passive state describes an anonymous user who has chosen a user name and who is identified by their device.*/
  SC_USER_STATE_PENDING,/**< A user is pending when the Scoreloop confirmation email has been sent out but the user has not yet responded to it.*/
  SC_USER_STATE_SUSPENDED /**< The user account has been suspended.*/
} SC_UserState_t;

/** Opaque SC_User object handle. 
 *
 * @since 10.0.0
 */
typedef struct SC_User_tag* SC_User_h;

/** Type descriptors for SC_User. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_User);

/*-------------------------------------------------------------------------------------*
 * Dependent includes
 *
 * SC_User class needs SC_UserList typedef for GetBuddies, but SC_UserList needs
 * SC_User_h typedef, so header cannot be included earlier.
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_user_list.h>
#include <scoreloop/sc_game.h>

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count for the current instance.
 *
 * @param self An opaque handle for the current SC_User instance.
 *
 * @since 10.0.0
 *
 */
SC_PUBLISHED void SC_User_Retain(SC_User_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the current SC_User instance. The current instance of SC_User will be deleted when the counter reaches 0.
 *
 * Note that this method is NULL pointer safe. That is, NULL as an argument will not cause an exception.
 *
 * @param self An opaque handle for the current SC_User instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_User_Release(SC_User_h self);

/**
 * @brief Returns a handle to the user object.
 *
 * This method returns a unique handle of the user.
 * It plays a role of a wrapper around globally unique identifier on Scoreloop network.
 * The value hidden behind this handle will never change.
 *
 * @param self An opaque handle for the SC_User instance.
 * @return SC_UserHandle_h The handle of the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_UserHandle_h SC_User_GetHandle(SC_User_h self);

/**
 * @brief Sets the user's login.
 *
 * This method is used to set the login of the user. The login is the preferred "display name" for the user. This method is available only to the session user. 
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param login The preferred login name, UTF-8 encoded.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_User_SetLogin(SC_User_h self, const char *login);

/**
 * @brief Returns the user's login.
 *
 * This method returns the login for the user. The login for the user can be changed.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_String_h The login of the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_User_GetLogin(SC_User_h self);

/**
 * @brief Sets the user's email address.
 *
 * This method is used to set the email address of the user.
 * This method is available only to the session user.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param email The email address to be set, UTF-8 encoded.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_User_SetEmail(SC_User_h self, const char *email);

/**
 * @brief Returns the user's email address.
 *
 * This method returns the session user's email address.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_String_h The email address of the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_User_GetEmail(SC_User_h self);

/**
 * @brief Returns the number of Scoreloop-enabled games that the user has played.
 *
 * This method returns the number of Scoreloop-enabled games that the user has played.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return int The number of games that the user has played.
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_User_GetGamesCount(SC_User_h self);

/**
 * @brief Returns the number of achievements of the user across all games that they have played until now.
 *
 * This method returns the number of achievements of the user across all games that they have played until now.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return int The number of achievements
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_User_GetGlobalAchievementsCount(SC_User_h self);

/**
 * @brief Returns the number of buddies the user has.
 *
 * This method returns the number of buddies the user has.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return int The number of buddies for the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_User_GetBuddiesCount(SC_User_h self);

/**
 * @brief Returns the URL of the user's image.
 *
 * This method returns the URL of the user's image.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_String String representing the URL with user's image or NULL if it's unavailable.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_String_h SC_User_GetImageUrl(SC_User_h self);

/**
 * @brief Returns the source of the image URL.
 *
 * This method returns the source of the image URL.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_UserImageSource_t enum value representing source of the image.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_UserImageSource_t SC_User_GetImageSource(SC_User_h self);

/**
 * @brief Sets the user's image from an external source.
 *
 * After calling this method, the previous image becomes outdated, and
 * GetImageUrl returns NULL.
 * The request is sent to the server after a UserController calls UpdateUser.
 * The image is updated on the server side asynchronously.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param source Correct external source value
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_User_SetImageFromExternalService(SC_User_h self,
        SC_UserImageSource_t source);

/**
 * @brief Sets the user's image.
 *
 * This method is used to set the image of the user.
 *
 * After calling this method, the previous image becomes outdated, and
 * GetImageUrl returns NULL.
 * The image is sent to the server after a UserController calls UpdateUser, and
 * then the image URL containing the new image will become available.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param imageData    Binary data containing new user's image in JPG or PNG format.
 * @param imageDataLen The length of binary data
 * @param imageMime    Mime type of the image. Currently "image/png" and "image/jpeg" are supported.
 * @return SC_Error_t  A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_User_SetImageFromData(SC_User_h self,
        const unsigned char *imageData, unsigned int imageDataLen,
        const char *imageMime);

/**
 * @brief Removes the user's image.
 *
 * This method is used to remove the image of the user.
 *
 * After calling this method, the previous image becomes outdated, and
 * GetImageUrl returns NULL.
 * The image is removed from the server after a UserController calls UpdateUser.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_User_ResetImage(SC_User_h self);

/**
 * @brief Sets the user's nationality.
 *
 * This method sets the nationality of the user.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param nationality The nationality of the user.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 *
 * @deprecated 10.2.0
 */
SC_PUBLISHED SC_Error_t SC_User_SetNationality(SC_User_h self, const char *nationality);

/**
 * @brief Returns the user's nationality.
 *
 * This method returns the nationality of the user.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_String_h The nationality of the user.
 *
 * @since 10.0.0
 *
 * @deprecated 10.2.0
 */
SC_PUBLISHED SC_String_h SC_User_GetNationality(SC_User_h self);

/**
 * @brief An accessor method that returns the game-specific context associated with user.
 *
 * This property becomes valid after a successful user context request. See
 * SC_UserController_LoadUserContext().
 * If the server doesn't return the context, the method returns NULL.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_Context_h Context of the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Context_h SC_User_GetContext(SC_User_h self);

/**
 * @brief Sets the context for the user.
 *
 * This method is used to set the context of a user. The context is updated on the server with a call to
 * SC_UserController_UpdateUserContext.
 *
 * @param self     An opaque handle for the current SC_User instance.
 * @param context  New user's context
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_User_SetContext(SC_User_h self, SC_Context_h context);

/**
 * @brief Examines the state of the user to see if they can be challenged or not.
 *
 * This method examines the state of the user to see if they can be challenged or not.
 *
 * @param self     An opaque handle for the SC_User instance.
 * @return SC_Bool_t SC_TRUE if the user can be challenged, otherwise SC_FALSE
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_User_IsChallengable(SC_User_h self);

/**
 * @brief Returns the context sent to the server.
 *
 * This property is valid when the callback of SC_UserController_UpdateUserContext() is called with
 * SC_CONTEXT_VERSION_MISMATCH. In this case, SC_User_GetOutdatedContext() contains the old context
 * that was sent to the server and which caused an error, SC_User_GetContext() returns a new context that was
 * returned by the server.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_Context_h Old context
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Context_h SC_User_GetOutdatedContext(SC_User_h self);

/**
 * @brief Compares two user objects.
 *
 * This method returns true if both objects are equal, otherwise it returns false.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param other An opaque handle for the another SC_User instance.
 * @return SC_Bool_t The result of the comparison, true/false.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_User_Equals(SC_User_h self, SC_User_h other);

/**
 * @brief Examines the state of the user.
 *
 * This method returns the current state of the user. The following states
 * are possible:
 * - SC_USER_STATE_ANONYMOUS
 * - SC_USER_STATE_ACTIVE
 * - SC_USER_STATE_DELETED
 * - SC_USER_STATE_PASSIVE
 * - SC_USER_STATE_PENDING
 * - SC_USER_STATE_SUSPENDED
 *
 * @param self An opaque handle for the current SC_User instance.
 * @return SC_UserState_t The state of the user.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_UserState_t SC_User_GetState(SC_User_h self);

/**
 * @brief Examines the state of the user and checks if specified game belongs to favorite ones.
 *
 * This method returns true if given game appears on the list of favorite games, otherwise it returns false.
 *
 * @param self An opaque handle for the current SC_User instance.
 * @param game An opaque handle for game instance to find on the list of favorites.
 * @return SC_Bool_t The result of the check, true/false.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_User_IsFavoriteGame(SC_User_h self, SC_Game_h game);

#ifdef __cplusplus
}
#endif

#endif /* __SC_USER_H__ */

/*! @} */
