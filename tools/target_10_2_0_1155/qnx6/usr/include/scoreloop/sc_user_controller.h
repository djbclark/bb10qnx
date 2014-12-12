/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @ingroup CoreSocial
 * @brief The data controller to query and change a user's details.
 * @file        sc_user_controller.h
 * @addtogroup  SC_UserController
 * @{
 * The \ref SC_UserController is used to retrieve information
 * about an arbitrary user from the server.
 *
 * It is also used to update the attributes and
 * buddy list of the current session user.
 *
 * Basic use:
 *
 * a) To retrieve information for the current
 * session user:
 * -# Create an instance of UserController, or re-use an existing instance.
 * -# Call SC_UserController_LoadUser().
 * -# Wait for notification of success via
 *    delegate callbacks.
 * -# After a successful request, access
 *    the attributes of the user by calling
 *    SC_UserController_GetUser().
 *
 * b) To retrieve information about an arbitrary user:
 * -# Create an instance of UserController, or re-use an existing one.
 * -# Request the user's information by passing
 *    the user's unique ID to SC_UserController_LoadUserFromHandle()
 * -# Wait for notification of success via delegate
 *    callbacks.
 * -# After a successful request, access the
 *    retrieved user by using SC_UserController_GetUser().
 *
 * Alternatively, 
 * -# Set the user property of the controller
 * equal to the user for whom the information is to be
 * requested by calling the SC_UserController_SetUser() method.
 * -# Call SC_UserController_LoadUser().
 * -# Wait for notification of success via delegate callbacks.
 * -# After a successful request, access the
 *    retrieved user by using SC_UserController_GetUser().
 *
 * c) To add a user to the buddy list of the session user:
 * -# Create an instance of UserController, or re-use an existing instance.
 * -# Set the user property of the controller equal to the
 * buddy to be added by calling the SC_UserController_SetUser() method.
 * -# Call SC_UserController_AddAsBuddy().
 * -# Wait for notification of success via delegate callbacks.
 *
 * d) To update the user profile
 * -# Create an instance of UserController, or re-use an existing instance.
 * -# Call SC_UserController_UpdateUser() to push updates of the current session user's attributes to the server.
 * -# if SC_UserController_UpdateUser() returns a failure with SC_INVALID_USER_DATA,
 *    call SC_UserController_GetValidationErrors() to check what went wrong.
 *
 * @note Do not modify a user object or one of its sub-objects while one of the following asynchronous methods is in progress, as this might cause undefined results:
 * - SC_UserController_LoadUser()
 * - SC_UserController_LoadUserContext()
 * - SC_UserController_LoadUserFromHandle()
 * - SC_UserController_UpdateUser()
 * - SC_UserController_UpdateUserContext()
 */

#ifndef __SC_USER_CONTROLLER_H__
#define __SC_USER_CONTROLLER_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_session.h>
#include <scoreloop/sc_user.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_completion_callback.h>
#include <scoreloop/sc_user_handle.h>
#include <scoreloop/sc_string_list.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_UserController object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_UserController_tag* SC_UserController_h;

/** Type descriptors for SC_UserController. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_UserController);

/*-------------------------------------------------------------------------------------*
 * Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Increments the object's reference count.
 *
 * This method increments the reference count of the
 * current instance by 1.
 *
 * @param   self        SC_UserController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UserController_Retain(SC_UserController_h self);

/**
 * @brief Decrements the object's reference count, and deletes the object if the counter reaches 0.
 *
 * This method decrements the reference count for the
 * current instance by 1. The current controller instance will
 * be automatically deleted when the reference count equals 0.
 *
 * Please note that this method is NULL pointer safe. That is, NULL as an argument will
 * not cause an exception.
 *
 * @param   self        SC_UserController instance handle
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_UserController_Release(SC_UserController_h self);

/**
 * @brief Returns the user currently set for the controller.
 *
 * If the user is not explicitly set,
 * the controller will
 * deal with the current session user instead.
 *
 * @param   self        SC_UserController instance handle
 * @return SC_User_h     The user currently set for the controller.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_User_h SC_UserController_GetUser(SC_UserController_h self);

/**
 * @brief Sets the user object that the controller should deal with.
 *
 * If the user is not explicitly set,the controller will
 * deal with the current session user instead.
 *
 * @param   self        SC_UserController instance handle
 * @param   user        The SC_User object that the controller will deal with.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_SetUser(SC_UserController_h self,
        SC_User_h user);

/**
 * @brief Requests attribute information for the user. User is given as handle.
 *
 * If no user has been provided, attributes for the current
 * session user will be requested instead. 
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you can access the retrieved user by calling SC_UserController_GetUser().
 *
 * @param  self       SC_UserController instance handle
 * @param  userHandle User handle to load info for.
 * @return SC_Error_t A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_LoadUserFromHandle(
        SC_UserController_h self, SC_UserHandle_h userHandle);

/**
 * @brief Requests attribute information for the user.
 *
 * If no user has been explicitly set, attributes for the current
 * session user will be requested instead. 
 *
 * Note that this is an asynchronous call and a callback will be triggered, after which you can access the retrieved user by calling SC_UserController_GetUser().
 *
 * @param   self        SC_UserController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_LoadUser(SC_UserController_h self);

/**
 * @brief Pushes updates of the current session user's attributes to the server.
 *
 * This method updates a user's attributes on the Scoreloop server. Only the session user can be updated in this way.
 *
 * Note that this is an asynchronous call and a callback will be triggered upon success or failure.
 *
 * @param   self        SC_UserController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * If the error code returned indicates SC_INVALID_USER_DATA, you must call SC_UserController_GetValidationErrors()
 * to figure out the exact causes of the failure, for example, SC_EMAIL_ALREADY_TAKEN, SC_EMAIL_FORMAT_INVALID, SC_USERNAME_ALREADY_TAKEN,
 * or SC_USERNAME_FORMAT_INVALID. It may also return SC_EMAIL_ALREADY_TAKEN + SC_USERNAME_FORMAT_INVALID.
 * In case of SC_EMAIL_ALREADY_TAKEN, an E-mail is sent to the given E-mail address with a link to manage the accounts(merge/transfer device). 
 * Please see SC_UserController_GetValidationErrors() for more details.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_UpdateUser(SC_UserController_h self);

/**
 * @brief Adds the user returned by SC_UserController_GetUser() to the buddy list of the session user.
 *
 * This method adds the user that is returned by SC_UserController_GetUser()
 * to the buddy list of the current session user.
 * It also verifies if the current session user tries to become a buddy of self.
 *
 * Note that this is an asynchronous call and a callback will be triggered upon success or failure.
 *
 * @param   self        SC_UserController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 * @sa removeAsBuddy
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_AddAsBuddy(SC_UserController_h self);

/**
 * @brief Removes the user that is returned by SC_UserController_GetUser()
 * from the buddy list of the current session user.
 * It also verifies, if current session user, tries to remove itself from the buddylist.
 *
 * Note that this is an asynchronous call and a callback will be triggered upon success or failure.
 *
 * @param   self        SC_UserController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_RemoveAsBuddy(SC_UserController_h self);

/**
 * @brief Returns the bitmask of validation errors that occurred while updating the user data.
 *
 * This method returns the bitmask of validation errors that occurred while updating the user data. The errors
 * that could occur include SC_EMAIL_ALREADY_TAKEN, SC_EMAIL_FORMAT_INVALID, SC_USERNAME_ALREADY_TAKEN,
 * or SC_USERNAME_FORMAT_INVALID
 *
 * @param   self        SC_UserController instance handle
 * @return SC_UserValidationError_t Lists all possible reasons for user update failure.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_UserValidationError_t SC_UserController_GetValidationErrors(
        SC_UserController_h self);

/**
 * @brief Returns the proposed available user logins.
 *
 * This method returns the list of available user names the user can chose from. This method should
 * be called if a call to SC_UserController_GetValidationErrors() indicates SC_USERNAME_ALREADY_TAKEN.
 *
 * @param   self        SC_UserController instance handle
 * @return SC_StringList_h  Lists of proposed user names.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_StringList_h SC_UserController_GetProposedUserNames(
        SC_UserController_h self);

/**
 * @brief Cancels any ongoing request or operation initiated by this particular controller instance.
 *
 * This method cancels any ongoing request or operation that is initiated by this particular controller instance.
 *
 * @param self An opaque handle of the user controller instance.
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_Cancel(SC_UserController_h self);

/**
 * @brief Requests the context of the user.
 *
 * If no user has been explicitly set, the context for the session user will be requested instead.
 * After a successful request, you can access the context by calling SC_User's SC_User_GetContext().
 *
 * Note that this is an asynchronous call and a callback will be triggered.
 *
 * @param  self        SC_UserController instance handle
 * @return SC_Error_t  A return code (a value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_User
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_LoadUserContext(SC_UserController_h self);

/**
 * @brief Pushes the updated user's context to the server.
 *
 * Any user can be updated in this way.
 *
 * Note: Only the most recent context, requested by SC_UserController_LoadUserContext, can be updated.
 * If some other client updated the context in the meantime, a delegate callback will be called with
 * SC_CONTEXT_VERSION_MISMATCH. SC_User_GetContext will then contain the most recent server context and
 * SC_User_GetOldContext will contain the context that was sent with the last SC_UserController_UpdateUserContext.
 *
 * Note that this is an asynchronous call and a callback will be triggered upon success or failure.
 *
 * @param   self        SC_UserController instance handle
 * @return SC_Error_t   A return code (a value of SC_OK indicates success, any other value indicates an error).
 * @sa SC_User
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_UserController_UpdateUserContext(SC_UserController_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_USER_CONTROLLER_H__ */

/*! @} */

