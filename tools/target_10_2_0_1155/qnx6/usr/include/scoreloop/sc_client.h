 /*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        sc_client.h
 * @brief       Instances of the Client class set up the underlying infrastructure necessary for using Scoreloop in a game.
 *
 * @addtogroup  SC_Client
 * @{
 *
 * Instances of the \ref SC_Client set up the underlying infrastructure necessary for using Scoreloop in a game. 
 * The first step to integrating Scoreloop is to create a \ref SC_Client. Typically only a single instance of \ref SC_Client should be created, which should persist for the entire lifetime of the game.
 *
 * Developers must register their games on https://developer.scoreloop.com in order to obtain an identifier and secret for the game application. In addition
 * to the game identifier and secret, you also obtain the game-specific currency code on registering your game. The game-specific currency code (and the game-id and secret)
 * are required as part of the initialization of \ref SC_Client.
 * 
 * The \ref SC_Session and \ref SC_Game instances can be accessed from \ref SC_Client.
 * \ref SC_Client is also used to create instances of other controllers like:
 * - \ref SC_AchievementsController,
 * - \ref SC_ChallengeController,
 * - \ref SC_ChallengesController,
 * - \ref SC_GamesController,
 * - \ref SC_LocalAchievementsController,
 * - \ref SC_RankingController,
 * - \ref SC_ScoresController, 
 * - \ref SC_ScoreController, 
 * - \ref SC_UserController,
 * - \ref SC_UsersController.
 *
 * \ref SC_Client is also used to create instances of model objects like:
 * - \ref SC_Challenge
 * - \ref SC_Money
 * - \ref SC_Score
 */
 
#ifndef __SC_CLIENT_H__
#define __SC_CLIENT_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_init.h>
#include <scoreloop/sc_errors.h>
#include <scoreloop/sc_game.h>
#include <scoreloop/sc_session.h>
#include <scoreloop/sc_scores_controller.h>
#include <scoreloop/sc_score_controller.h>
#include <scoreloop/sc_score_formatter.h>
#include <scoreloop/sc_ranking_controller.h>
#include <scoreloop/sc_user_controller.h>
#include <scoreloop/sc_users_controller.h>
#include <scoreloop/sc_achievements_controller.h>
#include <scoreloop/sc_local_achievements_controller.h>
#include <scoreloop/sc_games_controller.h>
#include <scoreloop/sc_game_item_controller.h>
#include <scoreloop/sc_game_items_controller.h>
#include <scoreloop/sc_challenge_controller.h>
#include <scoreloop/sc_challenges_controller.h>
#include <scoreloop/sc_activities_controller.h>
#include <scoreloop/sc_message_controller.h>
#include <scoreloop/sc_social_controller.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/** Opaque SC_Client object handle 
 *
 * @since 10.0.0
 */
typedef struct SC_Client_tag* SC_Client_h;

/** Type descriptors for SC_Client. 
 *
 * @since 10.0.0
 */
SC_TYPEINFO(SC_Client);


/*-------------------------------------------------------------------------------------*
 * Methods 
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Creates a new instance of SC_Client.
 *
 * This method creates the \ref SC_Client instance and initializes it.
 * It initializes the PAL Context and creates a session (with the new game object created).
 * The game object is created with the ID, secret and currency passed as input parameters to this method.
 *
 * @note
 * - The object is created with a reference count equal to 1.
 * - On BlackBerry,
 *      - this call will prompt for BBID credentials.
 *      - only local game play is possible in CORPORATE LIABLE MODE. Here, the device forbids the use of Scoreloop. A connection request returns error code SC_DISABLED_DUE_TO_CORPORATE_LIABLE_MODE that needs to be handled.
 *      - Before calling SC_Client_New you need to have posted a window. As SC_Client_New might block for an unbounded amount of time, your application could be slayed by the system when no window is posed before. Also, your game will not be brought automatically to the foreground if you forget to post a window first.
 *      Posting a window depends on the application environment you use – please check the documentation of these environments how to post a window.
 *      For example, with Core Native you would have to call screen_post_window() first, with Cascades you would have to wait for the posted() signal of Application::mainWindow().
 *
 * @param pSelf A pointer to the SC_Client struct.
 * @param initData A pointer to the SC_InitData struct. The initData variable has to have the same lifetime as the client variable.
 * @param gameIdentifier The unique game identifier assigned by Scoreloop when
 *  the game was registered on
 *  <a href="https://developer.scoreloop.com">https://developer.scoreloop.com</a>.
 * @param gameSecret The unique game secret assigned by Scoreloop
 * when the game was registered on 
 * <a href="https://developer.scoreloop.com">https://developer.scoreloop.com</a>.
 * @param gameVersion The version of the game in the format "<MajorVersion>.<MinorVersion>", e.g. "1.0".
 * In the case of a wrong format SC_INVALID_ARGUMENT is returned.
 * @param currency The unique game specific currency code assigned by Scoreloop when the game was registered on
 *  <a href="https://developer.scoreloop.com">https://developer.scoreloop.com</a>.
 * @param languages A comma-separated list of languages the game supports. e.g., for English, pass "en". This parameter is mandatory if the game supports localization of Awards.  
 * The current language on the device is intersected with the given list and all Scoreloop supported languages. If an intersection is found, the intersected language will be used. 
 * If there is no intersection the first language from the given list is used. English ("en") will be used if NULL is passed.
 * \n Example:\n
 * List of languages supported by game: ['en', 'en_US', 'de', 'pl'] 
 * <table>
 * <tr><td>Current Language of OS</td><td>Language used</td></tr>
 * <tr><td> 'en_US' </td><td>'en_US'</td></tr>
 * <tr><td> 'en_UK' </td><td>'en'</td></tr>
 * <tr><td> 'pl_PL' </td><td>'pl'</td></tr>
 * <tr><td> 'de' </td><td>'de'</td></tr>
 * <tr><td> 'it' </td><td>'en'</td></tr>
 * </table>
 * Note that the awards bundle needs to be localized to all given languages.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-New here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_New(SC_Client_h* pSelf, SC_InitData_t* initData,
        const char* gameIdentifier, const char* gameSecret, const char* gameVersion, const char *currency,
        const char* languages);

/**
 * @brief Increments object's reference count
 *
 * This method increments the reference count of the client instance.
 *
 * @param self An opaque handle for the current client instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Client_Retain(SC_Client_h self);

/**
 * @brief Decrements object's reference count, deletes the object if counter reaches 0.
 *
 * This method decrements the objects reference count.
 * The object will be automatically deleted if the reference
 * count reaches 0.
 * 
 * Please note that this method is @c NULL pointer safe, i.e. @c NULL as an argument will 
 * not cause an exception.
 *
 * @param self An opaque handle for the current client instance.
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_Client_Release(SC_Client_h self);

/**
 * @brief Get SC_Game object instance associated with the client.
 *
 * This method provides access to the current game instance.
 * There will be only one SC_Game instance throughout the
 * \ref SC_Client lifecycle.
 *
 * @param self An opaque handle for the current client instance.
 * @return SC_Game_h An opaque handle for the current game instance. There is no need to
 * retain the handle returned.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Game_h SC_Client_GetGame(SC_Client_h self);

/**
 * @brief Get SC_Session object instance associated with the client.
 *
 * This method provides access to the current Scoreloop session.
 * There is only one SC_Session instance throughout the SC_Client
 * lifecycle.
 *
 * @param self An opaque handle for the current client instance.
 * @return SC_Session_h An opaque handle for the current session instance.
 * There is no need to retain the handle returned.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Session_h SC_Client_GetSession(SC_Client_h self);

/**
 * @brief Creates a scores controller, which can be used to retrieve a high scores list
 * 
 * This method creates an instance of \ref SC_ScoresController. The controller
 * is used to retrieve lists of scores from the server.
 *
 * @param self Opaque handle for the current client instance.
 * @param pScoresController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateScoresController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateScoresController(SC_Client_h self,
        SC_ScoresController_h* pScoresController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a score controller, which can be used to submit a score achieved by the player.
 *
 * This method creates an instance of \ref SC_ScoreController. The controller
 * is used to submit scores to the server.
 *
 * @param self Opaque handle for the current client instance.
 * @param pScoreController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateScoreController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateScoreController(SC_Client_h self,
        SC_ScoreController_h* pScoreController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a ranking controller, which can be used to retrieve a rank.
 *
 * This method creates an instance of \ref SC_RankingController. The controller
 * is used to retrieve ranks from the server.
 *
 * @param self Opaque handle for the current client instance.
 * @param pRankingController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateRankingController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateRankingController(SC_Client_h self,
        SC_RankingController_h *pRankingController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a message controller, which can be used to post messages.
 *
 * This method creates an instance of \ref SC_MessageController. The controller
 * is used to post messages to receivers, including social networks.
 *
 * @param self Opaque handle for the current client instance.
 * @param pMessageController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateMessageController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateMessageController(SC_Client_h self,
        SC_MessageController_h *pMessageController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a challenge controller, which can be used to accept, reject or submit a challenge.
 *
 * This method creates an instance of \ref SC_ChallengeController. The controller
 * is used to accept, reject or submit a challenge.
 *
 * @param self Opaque handle for the current client instance.
 * @param pChallengeController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateChallengeController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateChallengeController(SC_Client_h self,
        SC_ChallengeController_h* pChallengeController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a challenges controller, which can be used to retrieve the lists of challenges 
 * on behalf of the current session user from the Scoreloop servers
 *
 * This method creates an instance of SC_ChallengesController. The controller
 * is used to retrieve the lists of challenges 
 * on behalf of the current session user from the Scoreloop servers
 *
 * @param self Opaque handle for the current client instance.
 * @param pChallengesController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateChallengesController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateChallengesController(SC_Client_h self,
        SC_ChallengesController_h* pChallengesController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a user controller, which can be used to retrieve 
 * information about an arbitrary user from the server
 *
 * This method creates an instance of \ref SC_UserController. The controller
 * is used to retrieve the information about an arbitrary user from the Scoreloop servers
 *
 * @param self Opaque handle for the current client instance.
 * @param pUserController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateUserController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateUserController(SC_Client_h self,
        SC_UserController_h *pUserController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates a users controller, which can be used to retrieve lists of User objects from the server
 *
 * This method creates an instance of \ref SC_UsersController. The controller
 * is used to lists of SC_User objects from the server based on various criteria.
 *
 * @param self Opaque handle for the current client instance.
 * @param pUsersController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateUsersController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateUsersController(SC_Client_h self,
        SC_UsersController_h *pUsersController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates an achievements controller, which is used to manage Achievements locally
 *
 * This method creates an instance of \ref SC_LocalAchievementsController. The controller
 * can be used to retrieve lists of achievements from the server
 * or to set an Award as being achieved for a user and to synchronize information stored locally with that on the server.
 *
 * @param self Opaque handle for the current client instance.
 * @param pAchievementsController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateLocalAchievementsController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateLocalAchievementsController(SC_Client_h self,
        SC_LocalAchievementsController_h *pAchievementsController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates an achievements controller, which is used to access users' Achievements.
 *
 * This method creates an instance of SC_AchievementsController. The controller
 * can be used to retrieve lists of achievements of selected user from the server.
 *
 * @param self Opaque handle for the current client instance.
 * @param pAchievementsController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateAchievementsController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateAchievementsController(SC_Client_h self,
        SC_AchievementsController_h *pAchievementsController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates an activities controller, which is used to manage Activities
 *
 * This method creates an instance of SC_ActivitiesController. The controller
 * can be used to retrieve lists of activities from the server.
 *
 * @param self Opaque handle for the current client instance.
 * @param pActivitiesController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateActivitiesController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateActivitiesController(SC_Client_h self,
        SC_ActivitiesController_h* pActivitiesController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates an instance of SC_GamesController
 * 
 * Method to create a new GamesController object.
 *
 * @param self Opaque handle for the current client instance.
 * @param pGamesController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateGamesController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateGamesController(SC_Client_h self,
        SC_GamesController_h *pGamesController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates an instance of SC_GameItemController
 *
 * Method to create a new GameItemController object.
 *
 * @param self Opaque handle for the current client instance.
 * @param pGameItemController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateGameItemController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateGameItemController (SC_Client_h self,
        SC_GameItemController_h *pGameItemController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

/**
 * @brief Creates an instance of SC_GameItemsController
 *
 * Method to create a new GameItemsController object.
 *
 * @param self Opaque handle for the current client instance.
 * @param pGameItemsController Opaque handle for the controller that will be created.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error. For more error codes see @link page-CreateGameItemsController here@endlink).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateGameItemsController (SC_Client_h self,
        SC_GameItemsController_h *pGameItemsController,
        SC_RequestControllerCompletionCallback_t callback, void* cookie);

#if SC_HAS_SOCIAL_PROVIDERS
/**
 * @brief Creates a social controller, which can be used to connect the user to one of the social networks
 *
 * This method creates an instance of SC_SocialController. Each instance handles one social
 * network (see aSocialNetwork parameter).
 *
 * NOTE: Currently not supported on BlackBerry.
 *
 * @param self Opaque handle for the current client instance.
 * @param pSocialController Opaque handle for the controller that will be created.
 * @param socialNetwork A social network for which to create the controller.
 * @param callback Handle to be registered for callback
 * @param cookie This will be passed back to the controller's callback and using this, users
 * can use the same callback for multiple controllers if they wish to.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateSocialController(SC_Client_h self,
        SC_SocialController_h *pSocialController, SC_SocialNetwork_t socialNetwork,
        SC_SocialControllerCompletionCallback_t callback, void* cookie);
#endif
    
/**
 * @brief Creates an instance of SC_Money
 *
 * Method to create a new Money object with a given amount of the game specific currency. The amount must be given in cents.
 *
 * @param self Opaque handle for the current client instance.
 * @param pMoney Opaque handle for the SC_Money object that will be created.
 * @param amount The amount of currency that the object will have. This must be in cents.
 * @return SC_Error_t A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateMoney(SC_Client_h self, SC_Money_h *pMoney,
        unsigned int amount);

/**
 *  @brief Creates a new challenge.
 *
 *  This method sets the session user as the challenge contender.
 *  The challenge contestant is the User object passed as a
 *  method argument. To create an open (non-assigned) challenge,
 *  pass a @c NULL value as the contestant argument. Challenges
 *  must be instantiated with a challenge stake chosen by the contender.
 *
 * @param self Opaque handle for the current client instance.
 * @param stake The challenge stake. Valid stakes can be retrieved from
 * the current session (use the current session user's SC_Session_GetBalance()). This value cannot be @c NULL.
 * @param contestant The challenge contestant. Passing a @c NULL value here creates an open challenge that
 * can be accepted by any player.
 * @param mode The mode for the challenge.
 * @param level The level for the challenge.
 * @param pChallenge Opaque handle for the SC_Challenge object that will be created.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateChallenge(
        SC_Client_h self, SC_Money_h stake, SC_User_h contestant,
        unsigned int mode, unsigned int level, SC_Challenge_h *pChallenge);

/**
 * @brief Creates an instance of SC_Score
 *
 * Creates a new \ref SC_Score object.
 *
 * @param self Opaque handle for the current client instance.
 * @param pScore Opaque handle for the SC_Score object that will be created.
 * @return SC_Error_t   A return code (A value of SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_Error_t SC_Client_CreateScore(SC_Client_h self, SC_Score_h *pScore);

/**
 * @brief Returns a score formatter instance.
 *
 * This call returns a score formatter instance.
 *
 * The score formatter is loaded during client creation if the configuration file is present.
 * If the configuration file couldn't be found this method will return NULL.
 *
 * @param self                 Opaque handle for the current client instance.
 * @return SC_ScoreFormatter_h Opaque handle for the loaded SC_ScoreFormatter object.
 *
 * @since 10.0.0
 */
SC_PUBLISHED SC_ScoreFormatter_h SC_Client_GetScoreFormatter(SC_Client_h self);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CLIENT_H__ */

/*! @} */
