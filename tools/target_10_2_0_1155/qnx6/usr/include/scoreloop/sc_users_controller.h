/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_users_controller.h
 * @ingroup     CoreSocial
 * @brief       The Data controller to search for users based on certain criteria, for example, a login ID or email address.
 * @addtogroup  SC_UsersController
 * @{
 *
 * The \ref SC_UsersController requests lists of SC_User objects from the server based on a variety of different criteria:
 *  - User login 
 *  - User email address
 *  - The local address book
 *  - A social provider
 *  - buddyhood
 *
 * Basic use:
 *  -# Set the match limit for the controller by using SC_UsersController_SetSearchLimit().
 *     The search request stops returning user objects once this limit has been reached
 *     and will return only the number of matches instead. This number is limited to 999.
 *  -# Set the flag that indicates whether the search should extend beyond users of the current game
 *     by calling SC_UsersController_SetSearchesGlobal().
 *  -# Make the server request by calling one of the following methods:
      - SC_UsersController_SearchByLogin()
      - SC_UsersController_SearchByEmail()
      - SC_UsersController_SearchBySocialProvider()
 *  -# Wait for a successful server response via delegate callbacks.
 *  -# Call SC_UsersController_GetUsers() to access the list of users that is retrieved from the server.
 *
 * If the number of users matched on the server exceeds the limit set by SC_UsersController_SetSearchLimit(), the following happens:
 * - Matched users will not be accessible.
 * - Only the number of matched users will be accessible by using SC_UsersController_GetUsersCount().
 *
 * Other usage to load the buddy list of a user:
 * -# Create an instance of UsersController, or re-use an existing instance.
 * -# Call SC_UsersController_LoadBuddies() to make the server request.
 * -# All the other search criteria are then ignored.
 * -# Wait for notification via delegate callbacks.
 * -# After a successful request, access the retrieved buddy list by using SC_User's SC_UsersController_GetUsers().
 */

#ifndef __SC_USERS_CONTROLLER_H__
#define __SC_USERS_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_session.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_social_network.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_UsersController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_UsersController_tag* SC_UsersController_h;

/** Type descriptors for SC_UsersController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_UsersController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the current instance by 1.
 *
 * @param   self        SC_UsersController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UsersController_Retain(SC_UsersController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the current instance by 1. The current controller instance will
 * be automatically deleted when the reference count equals 0.
 *
 * Please note that this method is @c NULL pointer safe. That is, @c NULL as an argument will
 * not cause an exception.
 *
 * @param   self        SC_UsersController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UsersController_Release(SC_UsersController_h self);

/**
 * @brief Sets the maximum number of user objects to be matched per server request.
 *
 * Sets the upper limit for the total number of matched users to be returned. User searches where positive matches
 * exceed this limit will not return the array of users.
 * This means that calling SC_UsersController_GetUsers() in these cases will return an empty list. However, the count of
 * positive matches will still be accessible using SC_UsersController_GetUsersCount().
 *
 * Note that Scoreloop includes an automatic upper limit of 999 on search matches.
 *
 * @param   self        SC_UsersController instance handle
 * @param   limit       The maximum number of users to be matched per server request.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UsersController_SetSearchLimit(SC_UsersController_h self, unsigned int limit);

/**
 * @brief Returns the maximum number of user objects to be matched per server request.
 *
 * The search request will stop once this limit has been reached. If the number of positive matches
 * on the server exceeds this limit then the matched user objects will not be accessible.
 * This means that calling SC_UsersController_GetUsers() in these cases will return an empty list. However, the count of
 * positive matches will still be accessible using SC_UsersController_GetUsersCount().
 *
 * Note that Scoreloop includes an automatic upper limit of 999 on search matches.
 *
 * @param   self        SC_UsersController instance handle
 * @return unsigned int Integer corresponding to this limit
 * \sa SC_UsersController_GetUsersCount(), SC_UsersController_IsOverLimit()
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_UsersController_GetSearchLimit(SC_UsersController_h self);

/**
 * @brief Returns the list of user objects that have been successfully retrieved from the server after calling one of the search methods.
 *
 * After a successful server request, the user objects that are retrieved will normally be accessible using this accessor.
 *
 * In cases where the number of positive matches found on the server exceeds the value set by calling SC_UsersController_SetSearchLimit(), then
 * this method will return an empty list.
 *
 * @param   self        SC_UsersController instance handle
 * @return SC_UserList_h The list of user objects retrieved from the server.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_UserList_h SC_UsersController_GetUsers(SC_UsersController_h self);

/**
 * @brief Returns the value for the flag that indicates whether the search request should extend beyond the current game.
 *
 * This method can be used to check if the search request extends beyond the current game.
 * This method returns SC_TRUE when the search request extends beyond the current game otherwise SC_FALSE.
 *
 * @param   self        SC_UsersController instance handle
 * @return SC_Bool_t SC_FALSE, if the search is restricted to the current game only. SC_TRUE, if the search is set to users of any Scoreloop game.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_UsersController_GetSearchesGlobal(SC_UsersController_h self);

/**
 * @brief Sets the flag extending the search request beyond the current game.
 *
 * This method sets the flag to extend the search request beyond the current game.
 * Set the searchesGlobal parameter to SC_TRUE to retrieve users of any Scoreloop game.
 * Set the searchesGlobal parameter to SC_FALSE to retrieve users of the current game only.
 *
 * @param self          SC_UsersController instance handle
 * @param searchesGlobal   Set this flag to @c SC_TRUE to retrieve users of any Scoreloop game.
 *                   Set this flag to @c SC_FALSE to retrieve users of the current game only.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UsersController_SetSearchesGlobal(SC_UsersController_h self,
        SC_Bool_t searchesGlobal);

/**
 * @brief Requests user objects from the server for the user whose login matches the supplied string.
 *
 * Note that this is an asynchronous call and a callback will be triggered. After a successful server request, the
 * user objects that are retrieved can be accessed by calling SC_UsersController_GetUsers().
 * The total count of positive matches found on the server can be accessed by calling SC_UsersController_GetUsersCount().
 *
 * If the number of matched user objects exceeds the limit set by the developer, then the matched users will not be accessible.
 * This means that calling SC_UsersController_GetUsers() in this case will return an empty list. However, the count of
 * positive matches will still be accessible by using SC_UsersController_GetUsersCount().
 *
 * @param   self        SC_UsersController instance handle
 * @param   login       The search string.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UsersController_SearchByLogin(SC_UsersController_h self,
        const char *login);

/**
 * @brief Requests user objects from the server for the user whose email address matches the supplied string.
 *
 *  Note that this is an asynchronous call and a callback will be triggered. After a successful server request, the
 *  user objects that are retrieved can be accessed by calling SC_UsersController_GetUsers().
 *  The total count of positive matches found on the server can be accessed by
 *  calling SC_UsersController_GetUsersCount().
 *
 *  If the number of matched user objects exceeds the
 *  limit set by the developer, then the matched users
 *  will not be accessible.
 * This means that calling SC_UsersController_GetUsers() in this case will return an empty list. However, the count of
 * positive matches will still be accessible by using SC_UsersController_GetUsersCount().
 *
 * @param   self        SC_UsersController instance handle
 * @param   email       The search string.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UsersController_SearchByEmail(SC_UsersController_h self,
        const char *email);

/**
 * @brief Requests all Scoreloop users who
 * are friends or followers of the session user
 * on a particular social network.
 *
 * This method requests all Scoreloop users who
 * are also friends or followers of the session user
 * on a particular social network.
 * Note that the session user must be connected to a social
 * provider before calling this method.
 *
 *  Note that this is an asynchronous call and a callback will be triggered. After a successful server request, the
 *  user objects that are retrieved can be accessed by calling SC_UsersController_GetUsers().
 *  The total count of positive matches found on the server can be accessed by
 *  calling SC_UsersController_GetUsersCount().
 *
 *  If the number of matched user objects exceeds the
 *  limit set by the developer, then the matched users
 *  will not be accessible.
 * This means that calling SC_UsersController_GetUsers() in this case will return an empty list. However, the count of
 * positive matches will still be accessible using SC_UsersController_GetUsersCount().
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param   self            SC_UsersController instance handle
 * @param   socialProvider  The SocialProvider object that provides the search criteria.
 * @return SC_Error_t       A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UsersController_SearchBySocialProvider(
        SC_UsersController_h self, SC_SocialNetwork_t socialProvider);


/**
 * @brief Requests the buddy list of the user that is returned by SC_UsersController_GetUsers().
 *
 * If no user has been explicitly set, the buddy list of the session
 * user is requested instead.
 *
 * Note that this is an asynchronous call and a callback will be triggered. After a successful request, you can access the buddy list by calling
 * SC_UsersController_GetUsers().
 *
 * @param  self         SC_UserController instance handle
 * @param  user         The user whose buddy list is requested.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 * @sa User
 *
 * @since 10.0.0
  */
SC_PUBLISHED SC_Error_t SC_UsersController_LoadBuddies(SC_UsersController_h self, SC_User_h user);

/**
 * @brief Reports whether the search limit was exceeded or not.
 *
 * This method will return the value SC_TRUE if the number of
 * positive matches found on the server exceeds the value
 * set by SC_UsersController_SetSearchLimit(). Otherwise, it will have the value SC_FALSE.
 *
 * @param   self        SC_UsersController instance handle
 * @return SC_Bool_t True, when more search results were found than defined by using SC_UsersController_SetSearchLimit().
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Bool_t SC_UsersController_IsOverLimit(SC_UsersController_h self);

/**
 * @brief Returns the total number of users matched on the server.
 *
 * After a successful server request, this
 * property will store the total count of
 * positive user matches found on the server.
 *
 * @param   self        SC_UsersController instance handle
 * @return unsigned int, An int corresponding to the number of users matched. Has an upper limit of 999.
 *
 * @since 10.0.0
 */
SC_PUBLISHED unsigned int SC_UsersController_GetUsersCount(SC_UsersController_h self);

/**
 * @brief Cancel any ongoing request or operation initiated by this particular controller instance.
 *
 * This method cancels any ongoing request or operation initiated by this particular controller instance.
 *
 * @param self An opaque handle of the users controller instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UsersController_Cancel(SC_UsersController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_USERS_CONTROLLER_H__ */

/*! @} */

