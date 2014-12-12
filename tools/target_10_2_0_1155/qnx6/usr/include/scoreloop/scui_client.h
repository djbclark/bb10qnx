/*-------------------------------------------------------------------------------------*
 * Copyright (C) 2012-2013 Scoreloop AG. All rights reserved.
 *-------------------------------------------------------------------------------------*/

/**
 * @file        scui_client.h
 * @brief       API to manage the Scoreloop Default UI.
 *
 * @addtogroup  SCUI_Client
 * @{
 * Use instances of this \ref SCUI_Client class to setup and manage the Scoreloop Default UI.
 * This Default UI consists of ready-made cards e.g. for leaderboards, achievements and
 * challenges to be easily used from within your game.
 */

#ifndef __SCUI_CLIENT_H__
#define __SCUI_CLIENT_H__

/*-------------------------------------------------------------------------------------*
 * Includes
 *-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_client.h>
#include <scoreloop/sc_completion_callback.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Defines
 *-------------------------------------------------------------------------------------*/

/** Defines deprecated attribute */
#ifndef SC_DEPRECATED
#   define SC_DEPRECATED       __attribute__((deprecated))   SC_PUBLISHED
#endif

/*-------------------------------------------------------------------------------------*
 * Types
 *-------------------------------------------------------------------------------------*/
    
/** Opaque SCUI_Client object handle 
 *
 * @since 10.1.0
 */
typedef struct SCUI_Client_tag* SCUI_Client_h;


/** @cond PRIVATE */
/** Type descriptors for SCUI_Client.
 *
 * @since 10.1.0
 */
SC_TYPEINFO(SCUI_Client);
/** @endcond */

/** Result of the card execution
 *
 * @since 10.1.0
 */
typedef enum SCUI_Result_tag
{
    SCUI_RESULT_OK = 0,                                 /**< The UI was closed without any specific action. */
    SCUI_RESULT_ERROR = 2,                              /**< An error occurred that caused the view not to be shown. */
    SCUI_RESULT_START_CHALLENGE                         /**< User started a challenge - you game should now start a game-play and submit the challenge at end. */

} SCUI_Result_t;

/** Result callback for UI notifications. Executed when the view has been closed. */
typedef void (*SCUI_ViewResultCallback_t) (void *cookie, SCUI_Result_t viewResult, const void *data);
    
/** List of scores selected at startup for Leaderboard view. 
 *
 * @since 10.2.0
 */
typedef enum SCUI_LeaderboardType_tag
{
    SCUI_LEADERBOARD_TYPE_GLOBAL = 0,                   /**< Select global leaderboard view. */
    SCUI_LEADERBOARD_TYPE_FRIENDS,                      /**< Select friends' leaderboard view. */
    SCUI_LEADERBOARD_TYPE_24H                           /**< Select 24 h leaderboard view. */

} SCUI_LeaderboardType_t;

/** Ways to customize the Leaderboard view. 
 *
 * @since 10.2.0
 */
typedef enum SCUI_LeaderboardFlags_tag
{
    SCUI_LEADERBOARD_FLAGS_DEFAULT = 0x00,              /**< Default appearance - dynamically determined by implementation. */

    SCUI_LEADERBOARD_FLAGS_SHOW_LIST_AUTOMATIC = 0x01,  /**< Loads scores either from top of around user, depending on whether a score is submitted or not. */
    SCUI_LEADERBOARD_FLAGS_SHOW_LIST_FROM_TOP = 0x02,   /**< Loads scores starting with the best score. */
    SCUI_LEADERBOARD_FLAGS_SHOW_LIST_AROUND_USER = 0x03,/**< Loads scores around user at start up, instead of top of the leaderboard. */
    SCUI_LEADERBOARD_FLAGS_SHOW_LIST_MASK = 0x0F        /**< Mask for show list part of flags. */

} SCUI_LeaderboardFlags_t;

    
/** Extra flags for customizing behavior on Achievements view. 
 *
 * @since 10.2.0
 */
typedef enum SCUI_AchievementFlags_tag
{
    SCUI_ACHIEVEMENT_FLAGS_DEFAULT = 0x00,              /**< Default appearance - dynamically determined by implementation. */

    SCUI_ACHIEVEMENT_FLAGS_REWARDS_HIDE = 0x01,         /**< Displayed award's description will not be populated with a reward amount. */
    SCUI_ACHIEVEMENT_FLAGS_REWARDS_SHOW = 0x02,         /**< Displayed award's description will also be populated with a reward amount. */
    SCUI_ACHIEVEMENT_FLAGS_REWARDS_MASK = 0x0F,         /**< Mask for rewards part of flags. */

    SCUI_ACHIEVEMENT_FLAGS_LAYOUT_LIST = 0x10,          /**< Present achievements as a list. */
    SCUI_ACHIEVEMENT_FLAGS_LAYOUT_GRID_ICONS = 0x20,    /**< Present achievements as a grid with touchable icons only. */
    SCUI_ACHIEVEMENT_FLAGS_LAYOUT_GRID_ICONS_TITLE = 0x30,  /**< Present achievements as a grid, where each item has a title below. */
    SCUI_ACHIEVEMENT_FLAGS_LAYOUT_MASK = 0xF0           /**< Mask for layout part of flags. */

} SCUI_AchievementFlags_t;

/** Extra flags for customizing challenge views. 
 *
 * @since 10.2.0
 */
typedef enum SCUI_ChallengeFlags_tag
{
    SCUI_CHALLENGE_FLAGS_DEFAULT = 0x00,                /**< Default appearance - dynamically determined by implementation. */

    SCUI_CHALLENGE_FLAGS_STAKE_ANY = 0x01,              /**< UI will allow any stake selection including zero stakes. */
    SCUI_CHALLENGE_FLAGS_STAKE_NONZERO = 0x02,          /**< UI will not allow to select zero stakes. */
    SCUI_CHALLENGE_FLAGS_STAKE_NONE = 0x03,             /**< UI will not allow any stake selection. All created challenges will be zero stake challenges. */
    SCUI_CHALLENGE_FLAGS_STAKE_MASK = 0x0F              /**< Mask for layout part of flags. */

} SCUI_ChallengeFlags_t;

/*-------------------------------------------------------------------------------------*
 * Construction Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Creates an instance of SCUI_Client.
 *
 * This method creates the \ref SCUI_Client instance and initializes it.
 * The \ref SCUI_Client is a wrapper class around regular \ref SC_Client.
 * It only allows displaying of the UI views and requires separate BPS event forwarding.
 *
 * @note Default UI is completely supported in 10.2 and above. On BlackBerry World, select OS version 10.2 and above for your game with Default UI.
 *
 * @param pSelf A pointer to the SCUI_Client struct.
 * @param client An opaque handle for the current SC_Client instance used to regular communication with Scoreloop.
 * @param callback Callback for UI dismiss notification.
 * @param cookie The cookie passed to the callback.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_NewWithCallback(SCUI_Client_h* pSelf, SC_Client_h client, SCUI_ViewResultCallback_t callback, void *cookie);

/**
 * @brief Increments object's reference count
 *
 * This method increments the reference count of the \ref SCUI_Client instance.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return void
 *
 * @since 10.1.0
 */
SC_PUBLISHED void SCUI_Client_Retain(SCUI_Client_h self);

/**
 * @brief Decrements object's reference count, deletes the object if counter reaches 0.
 *
 * This method decrements the objects reference count.
 * The object will be automatically deleted if the reference count reaches 0.
 *
 * Note that this method is @c NULL pointer safe, i.e. @c NULL as an argument will
 * not cause an exception.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return void
 *
 * @since 10.1.0
 */
SC_PUBLISHED void SCUI_Client_Release(SCUI_Client_h self);

/*-------------------------------------------------------------------------------------*
 * Event Handling Methods
 *-------------------------------------------------------------------------------------*/
    
/**
 * @brief Checks if the event is Scoreloop related event
 * 
 * This method checks for Scoreloop related events from all the BPS events. 
 * Call this method in the main loop and pass the bps_events to the handler.
 * Your event loop could look similar to the following:
 *
 * @code
 * bps_event_t *event;
 *
 * // get an event
 * bps_get_event(&event, -1); // blocking
 *
 * if (bps_event_get_domain(event) == SC_GetBPSEventDomain(&initData))
 * {
 *      // pass events to SC_Client as before
 *      // should already exist in your code, if not refer Initialization section
 *      SC_HandleBPSEvent(palInitData, event);
 * }
 * // pass events to the SCUI_Client
 * SCUI_Client_HandleEvent(uiClient, event);
 * @endcode
 *
 * @param self An opaque handle for the current SCUI_client instance.
 * @param event The BPS event to handle
 * @return SC_Bool_t SC_TRUE if it was a Scoreloop-related event, SC_FALSE otherwise
 *
 * @since 10.1.0
 */
SC_PUBLISHED SC_Bool_t SCUI_Client_HandleEvent(SCUI_Client_h self, bps_event_t *event);

/**
 * @brief Function to set optional event callback.
 *
 * This function set the optional event callback. The Default UI calls the callback only once, just before showing the view.
 * This callback can be used hide spinners or handle any Scoreloop-related errors that might occur. Errors might be a part of some precondition checks e.g., a valid network connectivity, Scoreloop authentication, etc.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @param callback Callback for view event notifications.
 * @param cookie The cookie passed to the callback.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.1.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_SetViewEventCallback(SCUI_Client_h self, SC_RequestControllerCompletionCallback_t callback, void *cookie);

/*-------------------------------------------------------------------------------------*
 * Query Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Checks if any UI view is currently displayed.
 *
 * This method checks if any view is displayed.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return SC_Bool_t Returns SC_TRUE if view is displayed. SC_FALSE otherwise.
 *
 * @since 10.1.0
 */
SC_PUBLISHED SC_Bool_t SCUI_Client_IsShowingView(SCUI_Client_h self);

/**
 * @brief Maps the result to a string
 *
 * This method maps the result \ref SCUI_Result_t values into an appropriate message in string format.
 *
 * @param result Way of closing the UI by user.
 * @return char An appropriate String message.
 *
 * @since 10.1.0
 */
SC_PUBLISHED const char *SCUI_MapResultCodeToStr(SCUI_Result_t result);

/*-------------------------------------------------------------------------------------*
 * Show UI Methods
 *-------------------------------------------------------------------------------------*/
    
/**
 * @brief This method requests display of favorite games view.
 *
 * This method displays the favorite games view. The view is shown asynchronously
 * and will automatically capture all user interactions over the whole screen.
 * It allows adding currently played as top favorite for session user.
 *
 * When the screen is dismissed, the callback will be called with the result \ref SCUI_RESULT_OK.
 * 
 * Before showing the UI, establishing a valid session with Scoreloop is performed, if not yet done.
 * This might introduce a random delay between call to this method and actual view display.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowFavoritingView(SCUI_Client_h self);

/**
 * @brief This method requests display of leaderboard view.
 *
 * This method displays the leaderboard view. The view is shown asynchronously
 * and will automatically capture all user interactions over the whole screen.
 * It displays a navigable list of scores of 3 leaderboards (Global, Friends, 24h).
 * There are also some optional parameters available helping in customization of displayed data,
 * however all the rest information (like: score-formatter definition, user logins and images) are downloaded from Scoreloop server dynamically.
 * It is possible to define:
 *  - active mode and score list at startup
 *  - and submit a score
 *
 * When the screen is dismissed, the callback will inform about it with \ref SCUI_RESULT_OK.
 *
 * Before showing the UI, establishing a valid session with Scoreloop is performed, if not yet done.
 * This might introduce a random delay between call to this method and actual view display.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @param modeSelected The mode to show up at start.
 * @param listSelected Type of leaderboard selected to display at start (global/friends'/24h).
 * @param optionalScore The score object that is submitted before showing the view.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowLeaderboardView(SCUI_Client_h self, unsigned int modeSelected, SCUI_LeaderboardType_t listSelected, SC_Score_h optionalScore);
    
/**
 * @brief This method requests display of achievements view.
 *
 * This method displays the achievements view. The view is shown asynchronously and will automatically capture all user interactions over the whole screen.
 * This view displays the list of awards in achieved and unachieved state.
 *
 * When the screen is dismissed, the callback will be called with a respective \ref SCUI_RESULT_OK result.
 *
 * Before showing the UI, establish a valid session with Scoreloop, if not already done.
 * This might introduce a random delay between call to this method and actual view display.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowAchievementsView(SCUI_Client_h self);

/**
 * @brief This method requests display of the user profile view.
 *
 * This method displays the user profile view. The view is shown asynchronously and will automatically capture all user interactions over the whole screen. It allows the user to edit his details and submit the changes.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowUserProfileView(SCUI_Client_h self);

/**
 * @brief This method requests the display of the challenges view.
 *
 * This method will display the challenges view that allows the user to select an open challenge, view his past challenges or create a new challenge.
 *
 * The view is shown asynchronously and will automatically capture all user interactions over the whole screen.
 * When the user starts a challenge, the view-result-callback will be called with a result value of SCUI_RESULT_START_CHALLENGE. 
 *
 * In this case, the data argument of the view-result-callback is of type \ref SC_Challenge_h (you will have to cast it to this type). 
 * You have to start a gameplay with the configuration of the challenge and once the game play is done, call \ref SCUI_Client_ShowChallengeSubmitView 
 * providing the same \ref SC_Challenge_h object together with the score the user gained during the game play.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowChallengesView(SCUI_Client_h self);

/**
 * @brief This method requests the display of the create challenge view.
 *
 * This method will display a view that lets the user create a new challenge.
 *
 * The view is shown asynchronously and will automatically capture all user interactions over the whole screen.
 * When the user starts a challenge, the view-result-callback will be called with a result value of SCUI_RESULT_START_CHALLENGE.
 *
 * In this case, the data argument of the view-result-callback is of type \ref SC_Challenge_h (you will have to cast it to this type).
 * You have to start a gameplay with the configuration of the challenge and once the game play is done, call \ref SCUI_Client_ShowChallengeSubmitView
 * providing the same \ref SC_Challenge_h object together with the score the user gained during the game play.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowChallengeCreateView(SCUI_Client_h self);

/**
 * @brief This method submits the results of a challenge play and requests the display of it to the user.
 *
 * After a challenge started with \ref SCUI_Client_ShowChallengesView or \ref SCUI_Client_ShowChallengeCreateView you have to call this method to upload the play result 
 * to the server. It then requests the display of the challenge result.
 *
 * The view is shown asynchronously and will automatically capture all user interactions over the whole screen.
 * When the user chooses to start a rematch, the view-result-callback will be called with a result value of SCUI_RESULT_START_CHALLENGE.
 *
 * In this case, the data argument of the view-result-callback is of type \ref SC_Challenge_h (you will have to cast it to this type).
 * You have to start a gameplay with the configuration of the challenge and once the game play is done, call \ref SCUI_Client_ShowChallengeSubmitView again
 * providing the correct \ref SC_Challenge_h object together with the score the user gained during the game play.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @param challenge The SC_Challenge_h you retrieved in the data argument of a previous view-result-callback.
 * @param score The SC_Score_h object describing the result of the game-play.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
SC_PUBLISHED SC_Error_t SCUI_Client_ShowChallengeSubmitView(SCUI_Client_h self, SC_Challenge_h challenge, SC_Score_h score);

/*-------------------------------------------------------------------------------------*
 * Configuration Methods
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Sets the money format to use in the UI.
 *
 * Use this configuration method to set a simple format string to be used for the display of money in the UI. E.g. the stake of a
 * challenge will be formatted by this string.
 * The format string has to conform to the standard printf specification with the money provided as a float value (%f). The float
 * value is derived from the money amount by dividing it by 100 - e.g. amount = 150 -> float-value = 1.5.
 * With this simple money format, no formatting dependent on the cardinality is possible - you might thus want to use a string like this:
 * "%.2f Coin(s)".
 *
 * If no format is specified explicitly, money will formatted as the number of amount (e.g. 150).
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @param formatString An UTF-8 encoded format string conforming to the printf specification. The value will be copied internally.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.2.0
 */
 SC_PUBLISHED SC_Error_t SCUI_Client_SetSimpleMoneyFormat(SCUI_Client_h self, const char *formatString);

 /**
  * @brief Sets the leaderboard flags.
  *
  * Use this to change the way leaderboards should be presented.
  *
  * @param self An opaque handle for the current SCUI_Client instance.
  * @param flags The flags to set.
  * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
  *
  * @since 10.2.0
  */
 SC_PUBLISHED SC_Error_t SCUI_Client_SetLeadearboardFlags(SCUI_Client_h self, SCUI_LeaderboardFlags_t flags);

 /**
  * @brief Sets the achievements flags.
  *
  * Use this to change the way achievements should be presented.
  *
  * @param self An opaque handle for the current SCUI_Client instance.
  * @param flags The flags to set.
  * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
  *
  * @since 10.2.0
  */
 SC_PUBLISHED SC_Error_t SCUI_Client_SetAchievementFlags(SCUI_Client_h self, SCUI_AchievementFlags_t flags);

 /**
  * @brief Sets the challenge flags.
  *
  * Use this method to change the way challenges should be presented.
  *
  * @param self An opaque handle for the current SCUI_Client instance.
  * @param flags The flags to set.
  * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
  *
  * @since 10.2.0
  */
 SC_PUBLISHED SC_Error_t SCUI_Client_SetChallengeFlags(SCUI_Client_h self, SCUI_ChallengeFlags_t flags);

/*-------------------------------------------------------------------------------------*
 * Deprecated Methods
 *-------------------------------------------------------------------------------------*/

 /** User pressed 'Cancel' button.
  *
  * @since 10.1.0
  *
  * @deprecated 10.2.0
  */
#define SCUI_RESULT_CANCEL  (1)     

/**
 * @brief Creates an instance of SCUI_Client.
 *
 * This method creates the \ref SCUI_Client instance and initializes it.
 * The \ref SCUI_Client is a wrapper class around regular \ref SC_Client.
 * It only allows displaying of the UI views and requires separate BPS event forwarding.
 *
 * @param pSelf A pointer to the SCUI_Client handle.
 * @param client An opaque handle for the current SC_Client instance used to regular communication with Scoreloop.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.1.0
 *
 * @deprecated 10.2.0 Use \ref SCUI_Client_NewWithCallback instead.
 */
SC_DEPRECATED SC_Error_t SCUI_Client_New(SCUI_Client_h* pSelf, SC_Client_h client);

/**
 * @brief This method requests display of favorite games view.
 *
 * This method displays the favorite games view. The view is shown asynchronously
 * and will automatically capture all user interactions over the whole screen.
 * It allows adding currently played as top favorite for session user.
 *
 * When the screen is dismissed, the callback will be called with a respective result (i.e. \ref SCUI_RESULT_OK or \ref SCUI_RESULT_CANCEL by user).
 *
 * Before showing the UI, establishing a valid session with Scoreloop is performed, if not yet done.
 * This might introduce a random delay between call to this method and actual view display.
 *
 * @param self An opaque handle for the current SCUI_Client instance.
 * @param callback Callback for UI dismiss notification.
 * @param cookie The cookie passed to the callback.
 * @return SC_Error_t A return code (SC_OK indicates success, any other value indicates an error).
 *
 * @since 10.1.0
 *
 * @deprecated 10.2.0 Use \ref SCUI_Client_ShowFavoritingView instead.
 */
SC_DEPRECATED SC_Error_t SCUI_Client_ShowFavoriteGamesView(SCUI_Client_h self, SCUI_ViewResultCallback_t callback, void *cookie);

#ifdef __cplusplus
}
#endif

#endif /* __SC_CLIENT_H__ */

/*! @} */
