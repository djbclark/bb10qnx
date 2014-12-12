/*-------------------------------------------------------------------------------------*
* Copyright (C) 2012 Scoreloop AG. All rights reserved.
*-------------------------------------------------------------------------------------*/

/**
* @file        sc_init.h
* @brief       QNX Platform-specific initialization data
*
* @addtogroup  SC_Init
* @{
* 
* Initialization of Platform Specific Data (QNX Platform-specific initialization data)
*/

#ifndef __SC_INIT_H__
#define __SC_INIT_H__

/*-------------------------------------------------------------------------------------*
* Includes
*-------------------------------------------------------------------------------------*/

#include <scoreloop/sc_types.h>
#include <bps/event.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------------------------*
 * Constants
 *-------------------------------------------------------------------------------------*/

/** Definition of the 1.0 version 
 *
 * @since 10.0.0
 */
#define SC_INIT_VERSION_1_0        0x100

/** Constant describing current version of the Scoreloop CoreSocial and the library itself. 
 *
 * @since 10.0.0
 */
#define SC_INIT_CURRENT_VERSION    SC_INIT_VERSION_1_0

/*-------------------------------------------------------------------------------------*
 * Data Types
 *-------------------------------------------------------------------------------------*/

/**
 * The method type for log writers.
 * @sa SC_InitData_t, SC_InitData_t.logWriter
 *
 * @since 10.0.0
 */
typedef void (*SC_LogWriter_t)(const char* message);

/**
 * The type of event notifiers.
 * @sa SC_InitData_t, SC_InitData_t.eventNotifier
 *
 * @since 10.0.0
 */
typedef void (*SC_EventNotifier_t)(void *eventNotifierContext);

/**
 * The type of possible runloop kinds.
 * @sa SC_InitData_t, SC_InitData_t.runLoopType
 *
 * @since 10.0.0
 */
typedef enum SC_RunLoopType_tag
{
    SC_RUN_LOOP_TYPE_BPS = 0,
    SC_RUN_LOOP_TYPE_CUSTOM
} SC_RunLoopType_t;

/**
 * Platform Abstraction Layer initialization data.
 * Please make sure sizeof( SC_InitData_t ) gets initialized to \0
 * e.g. with memset or calloc - or call SC_InitData_Init instead.
 *
 * Note that initializing SC_InitData_t this way is new and required on the QNX platform.
 * If you port a Scoreloop enabled game from another platform you have take these changes into
 * account.
 *
 * @since 10.0.0
 */
typedef struct SC_InitData_tag
{
    /* Begin of SC_INIT_VERSION_1_0 fields */
    
    /**
     *  This required field must be set to SC_INIT_CURRENT_VERSION when initializing.
     *  On return of the client initialization, it will be set to the maximum version the library supported
     */
    int currentVersion;

    /**
     *  This required field must be set to the minimum version containing all fields absolutely required
     *  to run the application, e.g. SC_INIT_VERSION_1_0. If the library does not support that version,
     *  SC_Client_New will fail
     */ 
    int minimumRequiredVersion;
    
    /**
     * Set the method used to write out log messages
     *
     * By default, log messages are written to stdout. If you want to write the log messages
     * to some other place, set this field to a method with the correct signature instead.
     */
    SC_LogWriter_t logWriter;

    /**
     * This required field must be set to either SC_RUN_LOOP_TYPE_BPS, when you use BPS
     * or SC_RUN_LOOP_TYPE_CUSTOM, when you use a custom run loop.
     * Note that the thread where your run loop is hosted is the thread all API
     * calls will have to be issued as well as all callbacks will take place.
     */
    SC_RunLoopType_t runLoopType;

    /**
     * If you use the run loop type SC_RUN_LOOP_TYPE_BPS, you assign the event domain to be used
     * by Scoreloop via this field.
     * If you set this field to 0, Scoreloop will pick a domain for you. After the creation of a SC_Client
     * object this field will then contain the domain picked by Scoreloop. You can use the utility method
     * SC_GetBPSEventDomain() instead to query this field.
     * @sa SC_GetBPSEventDomain
     */
    unsigned int eventDomain;
    
    /**
     * If you use the run loop type SC_RUN_LOOP_TYPE_CUSTOM, you can specify a method here which
     * gets called to indicate that you should call SC_HandleCustomEvent soon.
     * Note that this method gets called on a different thread than the scoreloop thread on which you have to
     * call SC_HandleCustomEvent. This is an advanced feature and should only be used if you understand
     * the threading implications.
     */
    SC_EventNotifier_t eventNotifier;

    /**
     * Internal. Should be left @c NULL.
     */
    struct PAL_DispatchQueue_tag *mainDispatchQueue;

    /**
     * Type of the client's application (optional). @c NULL for a game.
     */
    const char *clientType;

    /**
     * Some arbitrary void pointer that gets passed to invocations of the event notifier. You have to take care
     * of memory management of this pointer by yourself. This context is undefined if not set explicitly.
     */
    void *eventNotifierContext;

    /* End of SC_INIT_VERSION_1_0 fields */
    
} SC_InitData_t;

/*-------------------------------------------------------------------------------------*
 * Funcion prototypes
 *-------------------------------------------------------------------------------------*/

/**
 * @brief Initializes the SC_InitData_t structure with default values.
 *
 * This macro will set all fields to to a sensible default value:
 *
 *  - currentVersion =          SC_INIT_CURRENT_VERSION
 *  - minimumRequiredVersion =  SC_INIT_VERSION_1_0
 *  - logWriter =               'log to stdout'
 *  - runLoopType =             SC_RUN_LOOP_TYPE_BPS
 *  - eventDomain =             0 (means Scoreloop will choose a domain by itself)
 *  - eventDomainContext =      NULL
 *
 * You should nevertheless inspect the fields and change them to your special needs
 * after calling this method.
 *
 * @param initData  A Pointer to the init data to be initialized
 *
 * @since 10.0.0
 */
#define SC_InitData_Init(initData) (SC_InitData_InitWithSizeAndVersion(initData, sizeof(SC_InitData_t), SC_INIT_CURRENT_VERSION))

/**
 * @brief Method used by SC_InitData_Init to do the initialization properly.
 *
 * This method is used internally by the method SC_InitData_Init to do the initialization properly.
 * It initializes the data size and currentversion too.
 *
 * @param *initData pointer to SC_InitData_t
 * @param initDataSize int representing the size of the SC_InitData
 * @param currentVersion int representing the current version of SC_InitData
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_InitData_InitWithSizeAndVersion(SC_InitData_t *initData, unsigned int initDataSize, int currentVersion);

/**
 * @brief Continue processing of Scoreloop code when using SC_RUN_LOOP_TYPE_BPS
 *
 * You have to call this method at the beginning of your BPS event loop, so that Scoreloop
 * can continue its processing of asynchronous message receives from the servers.
 * Your event loop should look like this:
 *
 * @code 
 * for (;;) {
 *      // Get next event
 *      bps_event_t *event;
 *      bps_get_event(&event, -1);
 *
 *      if (bps_event_get_domain(event) == SC_GetBPSEventDomain(&initData)) {
 *          SC_HandleBPSEvent(&initData, event);
 *      }
 *      ...
 * }
 * @endcode
 *
 * @param initData      A pointer to the init data
 * @param event         The BPS event to handle
 * @return BPS_SUCCESS if it was a Scoreloop event, BPS_FAILURE otherwise
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_HandleBPSEvent(SC_InitData_t *initData, bps_event_t *event);

/**
 * @brief Returns the event domain used by Scoreloop
 *
 * Use this method to query the event domain used by Scoreloop in order to correctly dispatch BPS events.
 * The event domain will only be correctly set after a \ref SC_Client instance was created.
 *
 * @param initData      A pointer to the init data
 * @return The BPS event domain used by Scoreloop
 * @sa SC_InitData_t.eventDomain
 *
 * @since 10.0.0
 */
SC_PUBLISHED int SC_GetBPSEventDomain(SC_InitData_t *initData);

/**
 * @brief Continue processing of Scoreloop code when using SC_RUN_LOOP_TYPE_CUSTOM
 *
 * You have to call this method regularly in your own run loop so that Scoreloop
 * callbacks can be invoked when asynchronous replies come in from the servers.
 * Your event loop should look like this:
 *
 * @code
 * for (;;) {
 *      // Scoreloop event handling
 *      SC_HandleCustomEvent(&initData, SC_FALSE); // SC_FALSE will not block here, SC_TRUE will
 *
 *      // Other event handling here
 *      ...
 * }
 * @endcode
 *
 * @param initData      A pointer to the init data
 * @param blockIfNeeded Either SC_TRUE if you want this method to block or SC_FALSE otherwise
 *
 * @since 10.0.0
 */
SC_PUBLISHED void SC_HandleCustomEvent(SC_InitData_t *initData, SC_Bool_t blockIfNeeded);

#ifdef __cplusplus
}
#endif

#endif /* __SC_INIT_H__ */

/*! @} */

