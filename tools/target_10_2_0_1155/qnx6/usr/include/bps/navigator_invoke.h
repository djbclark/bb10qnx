/*
 * Research In Motion Limited. Copyright (C) 2012-2013.
 * Research In Motion Limited. All rights reserved.
 */

/**
 * @file navigator_invoke.h
 *
 * @brief Functions and structures to create, configure, and send application or
 *        card invocations and queries
 *
 * The Navigator Invoke API defines the invocation framework service, which
 * allows you to send and receive application or card invocations, to send
 * queries to the invocation framework, and to send data between a parent
 * application and the corresponding card.
 *
 * This has a number of uses, including:
 *
 * Creating, customizing, and sending a handler invocation using the action and
 * the type, and passing necessary data directly to the handler:
 * @code
 *   // create handler invocation
 *   navigator_invoke_invocation_t *invoke = NULL;
 *   navigator_invoke_invocation_create(&invoke);
 *
 *   // set invocation action and type
 *   navigator_invoke_invocation_set_action(invoke,
 *       "com.example.action.SET_SCREEN_COLOR");
 *   navigator_invoke_invocation_set_type(invoke,
 *       "application/com.example.type");
 *
 *   // pass arbitrary data (in this example, set screen color value to yellow)
 *   int screen_color = 0xffffff00;
 *   navigator_invoke_invocation_set_data(invoke, &screen_color, sizeof(int));
 *
 *   // invoke the target
 *   navigator_invoke_invocation_send(invoke);
 *
 *   // clean up resources
 *   navigator_invoke_invocation_destroy(invoke);
 * @endcode
 *
 * Decoding an invocation request from a BPS event on the target handler's side:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_TARGET: {
 *       const navigator_invoke_invocation_t *invoke =
 *           navigator_invoke_event_get_invocation(event);
 *       // an invocation has been received
 *       if(invoke) {
 *         // retrieve invocation action
 *         const char *action = navigator_invoke_invocation_get_action(invoke);
 *
 *         // if invocation includes data, retrieve data
 *         if(navigator_invoke_invocation_get_data_length(invoke) > 0) {
 *           // set color to value passed by invocation
 *           const int *p;
 *           p = navigator_invoke_invocation_get_data(invoke);
 *           change_color(*p);
 *         }
 *       }
 *     }
 *     break;
 *   }
 * @endcode
 *
 * Decoding the invocation target response's ID and the error from a BPS event:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_TARGET_RESULT: {
 *       const char *id = navigator_event_get_id(event);
 *       const char *err = navigator_event_get_err(event);
 *     }
 *     break;
 *   }
 * @endcode
 *
 * Creating, customizing, and sending a handler invocation using the action and
 * the type, and passing the URI location of the data to be passed to the
 * handler:
 * @code
 *   // create handler invocation
 *   navigator_invoke_invocation_t *invoke = NULL;
 *   navigator_invoke_invocation_create(&invoke);
 *
 *   // set action and type (in this example, view a jpeg image)
 *   navigator_invoke_invocation_set_action(invoke, "com.example.action.VIEW");
 *   navigator_invoke_invocation_set_type(invoke, "image/jpeg");
 *
 *   // pass URI pointing the the data (in this example, the image to view)
 *   navigator_invoke_invocation_set_uri(invoke, "file:///accounts/1000/appdata/com.example.application.123456789123456789123456789/data/image%201.jpg");
 *
 *   // invoke the target
 *   navigator_invoke_invocation_send(invoke);
 *
 *   // clean up resources
 *   navigator_invoke_invocation_destroy(invoke);
 * @endcode
 *
 * Decoding the URI path to the invocation data from a BPS event on the target
 * handler's side:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_TARGET: {
 *       const navigator_invoke_invocation_t *invoke =
 *           navigator_invoke_event_get_invocation(event);
 *       // an invocation has been received
 *       if(invoke) {
 *         // retrieve action, MIME type, and URI of the image from the
 *         // invocation
 *         const char *action = navigator_invoke_invocation_get_action(invoke);
 *         const char *mime_type = navigator_invoke_invocation_get_type(invoke);
 *         const char *image_uri = navigator_invoke_invocation_get_uri(invoke);
 *         // view image located at the defined URI
 *         view_image(image_uri);
 *       }
 *     }
 *     break;
 *   }
 * @endcode
 *
 * Invoking a handler with a known target ID:
 * @code
 *   // create handler invocation
 *   navigator_invoke_invocation_t *invoke = NULL;
 *   navigator_invoke_invocation_create(&invoke);
 *
 *   // set action
 *   navigator_invoke_invocation_set_action(invoke,
 *       "com.example.action.SET_SCREEN_COLOR");
 *   // set handler ID
 *   navigator_invoke_invocation_set_target(invoke,
 *       "com.example.DefaultHandler");
 *
 *   // invoke the target
 *   navigator_invoke_invocation_send(invoke);
 *
 *   // clean up resources
 *   navigator_invoke_invocation_destroy(invoke);
 * @endcode
 *
 * Sending a query for a find a specific action and type:
 * @code
 *   // create query
 *   navigator_invoke_query_t *query = NULL;
 *   navigator_invoke_query_create(&query);
 *
 *   // set query ID
 *   navigator_invoke_query_set_id(query, "123");
 *   // set action and type to query for
 *   navigator_invoke_query_set_action(query, "bb.action.SHARE");
 *   navigator_invoke_query_set_type(query, "image/png");
 *
 *   // send query
 *   navigator_invoke_query_send(query);
 * @endcode
 *
 * Handling a query response:
 * @code
 *   switch (bps_event_get_code(event)) {
 *     case NAVIGATOR_INVOKE_QUERY_RESULT: {
 *       const char *id = navigator_event_get_id(event);
 *
 *       // create integer holding the number of actions returned by the query
 *       int action_count =
 *           navigator_invoke_event_get_query_result_action_count(event);
 *       int i=0;
 *       // loop listing all actions returned by the query
 *       for (; i < action_count; i++) {
 *         const navigator_invoke_query_result_action_t *action =
 *             navigator_invoke_event_get_query_result_action(event, i);
 *
 *         // retrieve action attributes
 *         const char *name =
 *             navigator_invoke_query_result_action_get_name(action);
 *         const char *icon =
 *             navigator_invoke_query_result_action_get_icon(action);
 *         const char *label =
 *             navigator_invoke_query_result_action_get_label(action);
 *
 *         // create integer holding the number of targets in the action
 *         int target_count =
 *             navigator_invoke_query_result_action_get_target_count(action);
 *
 *         int j=0;
 *         // loop listing all targets in the action
 *         for (; j < target_size; j++) {
 *           const navigator_invoke_query_result_target_t *target =
 *               navigator_invoke_query_result_action_get_target(action, j);
 *
 *           // retrieve target attributes
 *           const char *target_key =
 *               navigator_invoke_query_result_target_get_key(target);
 *           const char *target_icon =
 *               navigator_invoke_query_result_target_get_icon(target);
 *           const char *target_splash =
 *               navigator_invoke_query_result_target_get_splash(target);
 *           const char *target_label =
 *               navigator_invoke_query_result_target_get_label(target);
 *           navigator_invoke_target_type_t target_type =
 *               navigator_invoke_query_result_target_get_type(target);
 *           navigator_invoke_perimeter_type_t perimeter =
 *               navigator_invoke_query_result_target_get_perimeter(target);
 *         }
 *       }
 *     }
 *   }
 * @endcode
 *
 * @since BlackBerry 10.0.0
 */

#ifndef _BPS_NAVIGATOR_INVOKE_H_INCLUDED
#define _BPS_NAVIGATOR_INVOKE_H_INCLUDED

#include <stdbool.h>
#include <unistd.h>
#include "bps/bps.h"

__BEGIN_DECLS

/**
 * @brief The opaque invocation argument type
 *
 * This type defines the @c #navigator_invoke_invocation_t structure used by
 * several functions in the invocation framework. Use this to create and control
 * invocations. The @c #navigator_invoke_invocation_t structure is opaque, but
 * includes the following members:
 *     - @b ID: the ID used to identify the invocation
 *              (@c navigator_invoke_invocation_set_id())
 *     - @b Target: the target to which the invocation is sent
 *              (@c navigator_invoke_invocation_set_target())
 *     - @b Source: the location where response messages to the invocation
 *              should be sent (@c navigator_invoke_invocation_set_source())
 *     - @b Action: the action the invoked target should perform
 *              (@c navigator_invoke_invocation_set_action())
 *     - @b Type: the MIME type of the data the invoked target should act on
 *              (@c navigator_invoke_invocation_set_type())
 *     - @b URI: the URI to the data the invoked target should act on
 *              (@c navigator_invoke_invocation_set_uri())
 *     - @b Transfer @b mode: the transfer mode for the URI file
 *              (@c navigator_invoke_invocation_set_file_transfer_mode())
 *     - @b Data: the data the invoked target should act on
 *              (@c navigator_invoke_invocation_set_data())
 *     - @b Data @b length: the length of the data the invoked target should act
 *              on (@c navigator_invoke_invocation_set_data())
 *     - @b Perimeter: the perimeter the target should be invoked in
 *              (@c navigator_invoke_invocation_set_perimeter())
 *     - @b List @b ID: the id of the list the invocation is associated with
 *              (@c navigator_invoke_invocation_set_list_id())
 *
 * To perform an invocation, you must:
 *     1. Instantiate a @c #navigator_invoke_invocation_t structure with the @c
 *        navigator_invoke_invocation_create() function.
 *     2. Set all desired members with the @c
 *        navigator_invoke_invocation_set_*() functions to match the purpose of
 *        the @c invocation. A minimum of either a @c target, @c action, or @c
 *        type member is required for the @c invocation to be recognised by the
 *        framework (though further members may be required for more specific
 *        invocations, such as including a @c uri or @c data member for
 *        invocations that require input data to be successfully performed.)
 *     3. Send the @c invocation with the @c navigator_invoke_invocation_send()
 *        function. Depending on the members you set to the @c
 *        #navigator_invoke_invocation_t structure, the invocation is sent
 *        either directly to a target handler or the brokering system to
 *        determine which target to use based on the provided information.
 *     4. Retrieve the data from an @c invocation in an event handler by using
 *        the navigator_invoke_invocation_get_*() functions.
 *     5. Deallocate the memory reserved for the @c
 *        #navigator_invoke_invocation_t structure with the @c
 *        navigator_invoke_invocation_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_invocation_t navigator_invoke_invocation_t;

/**
 * @brief The opaque query argument type
 *
 * This type defines the @c #navigator_invoke_query_t structure used by several
 * functions in the invocation framework. Use this to create and control
 * queries. The @c #navigator_invoke_query_t structure is opaque, but includes
 * the following members:
 *     - @b ID: the ID used to identify the query
 *              (@c navigator_invoke_query_set_id())
 *     - @b Action: the action query results should be able to perform
 *              (@c navigator_invoke_query_set_action())
 *     - @b Type: the MIME type the query results should be able to act on
 *              (@c navigator_invoke_query_set_type())
 *     - @b File @b URI: the URI to the type interface the query results should
 *              be able to act on (@c navigator_invoke_query_get_file_uri())
 *     - @b Target @b type: the type of targets the query should filter for
 *              (@c navigator_invoke_query_set_target_type_mask())
 *     - @b Action @b type: the type of actions the query should filter for
 *              (@c navigator_invoke_query_set_action_type())
 *     - @b Perimeter: the perimeter the query results should be invoked in
 *              (@c navigator_invoke_query_set_perimeter())
 *
 * To perform an invocation query, you must:
 *     1. Instantiate a @c #navigator_invoke_query_t structure with the @c
 *        navigator_invoke_query_create() function.
 *     2. Set all desired members with the @c navigator_invoke_query_set_*()
 *        functions to match the purpose of the @c query.
 *     3. Send the @c query with the @c navigator_invoke_query_send()
 *        function. The query is sent to the brokering system, which returns a
 *        set of results that correspond to the @c #navigator_invoke_query_t
 *        structure parameters.
 *     4. Deallocate the memory reserved for the @c #navigator_invoke_query_t
 *        structure with the @c navigator_invoke_query_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_query_t navigator_invoke_query_t;

/**
 * @brief The opaque query result action argument type
 *
 * This type defines the @c #navigator_invoke_query_result_action_t structure
 * used by several functions in the invocation framework. Use this to retrieve
 * actions returned from invocation query results. The @c
 * #navigator_invoke_query_result_action_t structure is opaque, but includes the
 * following members:
 *     - @b Name: the name of the action
 *                (@c navigator_invoke_query_result_action_get_name())
 *     - @b Icon: an image associated with the action
 *                (@c navigator_invoke_query_result_action_get_icon())
 *     - @b Label: the label or name associated with the action
 *                (@c navigator_invoke_query_result_action_get_label())
 *     - @b Default @b target: the target that will provide this action by
 *                default
 *                (@c navigator_invoke_query_result_action_get_default_target())
 *     - @b Target @b count: the number of viable targets that can perform the
 *                action (@c navigator_invoke_query_result_action_get_target())
 *     - @b Targets: an array of all viable targets that can perform the
 *                action (@c navigator_invoke_query_result_action_get_target())
 *
 * The @c #navigator_invoke_query_result_action_t structure is returned by an
 * invocation query. Extract values from this structure using the @c
 * navigator_invoke_query_result_action_get_*() functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_query_result_action_t navigator_invoke_query_result_action_t;

/**
 * @brief The opaque query result target argument type
 *
 * This type defines the @c #navigator_invoke_query_result_target_t structure
 * used by several functions in the invocation framework. Use this to retrieve
 * targets returned from invocation query results, and contained within @c
 * #navigator_invoke_query_result_action_t structures. The @c
 * #navigator_invoke_query_result_target_t structure is opaque, but includes the
 * following members:
 *     - @b Key: the name of the target
 *               (@c navigator_invoke_query_result_target_get_key())
 *     - @b Icon: an image associated with the target
 *               (@c navigator_invoke_query_result_target_get_icon())
 *     - @b Splash: an image to be displayed by a target when loading
 *               (@c navigator_invoke_query_result_target_get_splash())
 *     - @b Label: the label or name associated with the target
 *               (@c navigator_invoke_query_result_target_get_label())
 *     - @b Type: the target's type
 *               (@c navigator_invoke_query_result_target_get_type())
 *     - @b Perimeter: the perimeter in which the target should reside
 *               (@c navigator_invoke_query_result_target_get_perimeter())
 *
 * The @c #navigator_invoke_query_result_target_t structures are contained
 * within @c #navigator_invoke_query_result_action_t structures that are
 * returned by an invocation query. Extract values from this structure using the
 * @c navigator_invoke_query_result_target_get_*() functions.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_query_result_target_t navigator_invoke_query_result_target_t;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * This type defines the @c #navigator_invoke_viewer_t structure used by several
 * functions in the invocation framework. Use this to create and control
 * viewers. The @c #navigator_invoke_viewer_t structure is opaque, but includes
 * the following members:
 *     - @b Invocation: the invocation associated with the viewer
 *                 (@c navigator_invoke_viewer_create())
 *     - @b Window @b ID: the ID used to identify the viewer
 *                 (@c navigator_invoke_viewer_set_window_id())
 *     - @b Width: the width of the viewer
 *                 (@c navigator_invoke_viewer_set_width())
 *     - @b Height: the height of the viewer
 *                 (@c navigator_invoke_viewer_set_height())
 *
 * To create an invocation viewer, you must:
 *     1. Instantiate a @c #navigator_invoke_viewer_t structure with the @c
 *        navigator_invoke_viewer_create() function.
 *     2. Set all desired members with the @c navigator_invoke_viewer_set_*()
 *        functions to match the purpose of the @c viewer.
 *     3. Send the @c viewer with the @c navigator_invoke_viewer_send()
 *        function. The invocation is sent to an event handler, triggering the
 *        NAVIGATOR_INVOKE_VIEWER event.
 *     4. Retrieve the data from a @c viewer in an event handler by using
 *        the navigator_invoke_viewer_get_*() functions, within this, further
 *        data from the invocation can be retrieved through the @c
 *        #navigator_invoke_invocation_t structure using the @c
 *        navigator_invoke_viewer_get_invocation() function followed by the @c
 *        navigator_invoke_invocation_get_*() functions.
 *     5. Deallocate the memory reserved for the @c #navigator_invoke_viewer_t
 *        with the @c navigator_invoke_viewer_destroy() function.
 *
 * @since BlackBerry 10.0.0
 */
typedef struct navigator_invoke_viewer_t navigator_invoke_viewer_t;

/**
 * @brief The possible invocation target types
 *
 * This enumeration defines the possible types of targets to query for with the
 * @c #navigator_invoke_query_t structure. This is used by the brokering system
 * to filter for targets that are of the given type.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the target type is unspecified.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED = 0x00,
    /**
     * Indicates that the target is an application. Applications are software
     * designed to perform specific tasks.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION = 0x01,
    /**
    * Indicates that the target is a card. Cards are compact windows that allow
    * an application to expose functionality so that it can be imported in to
    * the flow of another application. Cards may be stacked multiple layers
    * when one card uses another. However, each layer of the stack can stack
    * only one child card at a time. For example, the Universal Inbox list may
    * stack a card to preview an email message. The message card may in turn
    * stack a card to preview an image attachment. The attachment card may
    * then also stack a card to share the image, and so on. The peeking
    * feature exclusive to cards allows users to "peek" back behind the current
    * card to reveal its parent's content using a swipe gesture. Peeking is
    * handled in the Navigator API.
     *
     * @since BlackBerry 10.0.0
    */
   NAVIGATOR_INVOKE_TARGET_TYPE_CARD         = 0x02,
   /**
    * @deprecated The use of viewers has been deprecated - use applications or
    *             cards as invocation targets instead.
    *
    * Indicates that the target is a viewer. Viewers are embedded applications
    * that can render a certain content type (images for example). They appear
    * as part of the root application rather than as a separate application.
    *
    * @since BlackBerry 10.0.0
    */
    NAVIGATOR_INVOKE_TARGET_TYPE_VIEWER      = 0x04,
    /**
     * Indicates that the target is a service. The meaning of a service value is
     * reserved for future use.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE     = 0x08,
    /**
     * Indicates that the matched targets belonging to the current application
     * should be returned in the query result.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_TARGET_TYPE_SELF        = 0x10
} navigator_invoke_target_type_t;


/**
 * @brief The possible invocation query action type values
 *
 * This enumeration defines the possible types of actions to query for with the
 * @c #navigator_invoke_query_t structure. This is used by the brokering system
 * to filter for targets that use the given action type.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the query action type is unspecified.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_UNSPECIFIED = 0,
    /**
     * Indicates that the query results are filtered to only include those
     * that support menu actions. Menu actions have a defined icon and label
     * associated with them.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_MENU        = 1,
    /**
     * Indicates that the query results include all viable targets regardless of
     * their action type(s).
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_ALL         = 2
} navigator_invoke_query_action_type_t;

/**
 * The possible application perimeter type values
 *
 * This enumeration defines the possible types of perimeters in which a targeted
 * or queried application can reside. This is used to determine where a target
 * application should invoke, primarily in cases where the application is a
 * "hybrid" that can run in both enterprise and personal perimeters.
 *
 * Your app should not explicitly set the perimeter, as the Invocation Framework
 * will automatically take care of this across all device configurations (e.g.
 * Personal-only, Balance, Corporate Liable, etc.). If your app sets the
 * perimeter, it may not be able to invoke applications in particular device
 * configurations.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the perimeter type is unspecified.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_PERIMETER_TYPE_UNSPECIFIED = 0,
    /**
     * Indicates that the application should run in the personal perimeter.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL    = 1,
    /**
     * Indicates that the application should run in the enterprise perimeter.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE  = 2
} navigator_invoke_perimeter_type_t;

/**
 * @brief The possible transfer modes for files specified in invocation requests
 *
 * This enumeration defines the supported modes for handling file transfer when
 * a file URI is provided that does not point to a file in the shared area.
 * Unless @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK is specified, file
 * transfer handling will transfer the file via the target's private inbox.
 *
 * @since BlackBerry 10.0.0
 */
typedef enum {
    /**
     * Indicates that the file transfer mode has not been specified and the
     * default logic should apply
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_UNSPECIFIED = 0,
    /**
     * Indicates that the file transfer handling should be skipped and the
     * specified file URI should be passed to the target as-is
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_PRESERVE    = 1,
    /**
     * Indicates that the file should be transfered as a read only copy of the
     * file specified in the URI attribute
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RO     = 2,
    /**
     * Indicates that the file should be transfered as a read/write copy of the
     * file specified in the URI attribute.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_COPY_RW     = 3,
    /**
     * Indicates that the file should be transfered as a link to the file
     * specified in the URI attribute. Note that link mode requires that the
     * original file support o+r. In addition, if the file has o+w then the
     * sender must be the owner of the file.
     *
     * @since BlackBerry 10.0.0
     */
    NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK        = 4
} navigator_invoke_file_transfer_mode_t;

/**
 * The possible directions of movement for an invoke list cursor
 *
 * This enumeration defines the possible directions in which an invoke
 * list cursor may move relative to the current selection.
 *
 * @since BlackBerry 10.2.0
 */
typedef enum {
    /**
     * Indicates that the cursor's direction is determined by the application.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_UNSPECIFIED    = 0,

    /**
     * Indicates that the cursor's direction is towards the next list item.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_NEXT           = 1,
    /**
     * Indicates that the cursor's direction is towards the previous list item.
     *
     * @since BlackBerry 10.2.0
     */
    NAVIGATOR_INVOKE_LIST_CURSOR_PREVIOUS       = 2
} navigator_invoke_list_cursor_direction_t;


/**
 * @brief Create an invocation structure and allocate all necessary memory
 *
 * The @c navigator_invoke_invocation_create() function creates an instance of a
 * @c #navigator_invoke_invocation_t structure called @c invocation to be used
 * by the invocation framework. Destroy all invocation instances created through
 * this function once they are no longer needed by using the @c
 * navigator_invoke_invocation_destroy() function to prevent memory leaks.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to
 *        populate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_create(navigator_invoke_invocation_t **invocation);

/**
 * @brief Deallocate the memory used by an invocation structure
 *
 * The @c navigator_invoke_invocation_destroy() function deallocates any memory
 * set to a given @c invocation. Use this function to deallocate memory used by
 * a @c #navigator_invoke_invocation_t structure (created by the @c
 * navigator_invoke_invocation_create() function) that's no longer in use.
 * Failing to do so will result in a memory leak.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to
 *                   deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_destroy(
        navigator_invoke_invocation_t *invocation);

/**
 * @brief Set the ID of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_id() function sets the invocation ID
 * of a given @c #navigator_invoke_invocation_t structure. Assign an @c id
 * member to any invocation for which you would like to receive a delivery
 * receipt response. The @c id member you assign through a sender appears in its
 * corresponding delivery receipt. The receipt is returned once the invocation
 * is dispatched to a target, but does not imply that the target has processed
 * the invocation. If the sender terminates before receiving a receipt response
 * then it is forfeit.
 *
 * Assigning an @c id member to an invocation is not mandatory, but if you do
 * not assign one there is no way to determine the result of the invocation
 * request. Don't assign an invocation ID if you don't want to receive a
 * delivery receipt response.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c id you want to set.
 *
 * @param id The invocation ID you want to display on the delivery receipt
 *           response. This value must be in numerical format. For example, a
 *           valid @c id would be "42".
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_id(
        navigator_invoke_invocation_t *invocation, const char* id);

/**
 * @brief Set the target of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_target() function sets the target of a
 * given @c #navigator_invoke_invocation_t structure. The @c target member is an
 * identifier to the target (as stated in its BAR manifest) handler to which the
 * invocation is sent.
 *
 * If you assign a @c target member to an invocation then brokering is bypassed
 * and an attempt is made to invoke the specified target. If you don't call this
 * function, the invocation framework uses brokering along with the @c action
 * and/or @c type member (assigned with the @c
 * navigator_invoke_invocation_set_action() and @c
 * navigator_invoke_invocation_set_type() functions respectively) to find the
 * corresponding handler(s).
 *
 * The format of a @c target member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Target: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.invoke.target"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c target you want to set.
 *
 * @param target The target you want the invocation to be sent to. The value
 *               must conform to the "[Domain][Sub-domain]" format (see
 *               description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_target(
        navigator_invoke_invocation_t *invocation, const char* target);

/**
 * @brief Set the source of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_source() function sets the source of a
 * given @c #navigator_invoke_invocation_t structure. The @c source member is an
 * identifier to a target (as stated in its BAR manifest) to which the results
 * of an invocation are sent. If you assign a @c source member to an invocation
 * then the receiving target may send a response with the corresponding results.
 *
 * Assigning a @c source member to an invocation is not mandatory, but if you do
 * not assign one then the invoked target won't be able to communicate with
 * the caller. Don't assign an invocation source if the sender doesn't support
 * results.
 *
 * The format of a @c target member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Source: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.result.target"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c source you want to set.
 *
 * @param source The target you want the invocation target to be send results
 *               to. The value must conform to the "[Domain][Sub-domain]" format
 *               (see description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_source(
        navigator_invoke_invocation_t *invocation, const char* source);

/**
 * @brief Set the action of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_action() function sets the action of a
 * given @c #navigator_invoke_invocation_t structure. The @c action member
 * identifies the action to be performed by the invocation target.
 *
 * If you assign an @c action member to an invocation but don't assign a @c
 * target (using the @c navigator_invoke_invocation_set_target() function), the
 * brokering system uses the @c action value to filter for target handlers that
 * support that action. If a @c type member is also assigned (using the @c
 * navigator_invoke_invocation_set_type() function), the brokering system uses
 * that information to filter for handler(s) that support both the given
 * action and type. If only a @c type member is assigned, the brokering system
 * doesn't filter for any specific action.
 *
 * The format of an @c action member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Action: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "bb.action.SHARE"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c action member you want to set.
 *
 * @param action The action you want the invocation target to perform. The value
 *               must conform to the "[Domain][Sub-domain]" format (see
 *               description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_action(
        navigator_invoke_invocation_t *invocation, const char* action);

/**
 * @brief Set the type of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_type() function sets the @c type
 * member of a given @c #navigator_invoke_invocation_t structure. The @c type
 * member identifies the MIME type of the data the invoked handler is to perform
 * an action on.
 *
 * If you assign a @c type member to an invocation but don't assign a @c target
 * (using the @c navigator_invoke_invocation_set_target() function), the
 * brokering system uses the @c type value to filter for target handlers that
 * support that MIME type. If an @c action member is also assigned (using the @c
 * navigator_invoke_invocation_set_action() function), the brokering system uses
 * that information to filter for handler(s) that support both the given type
 * and action. If only an @c action member is assigned, the brokering system
 * doesn't filter for any specific MIME type.
 *
 * The format of a @c type member must conform to the following guidelines:
 *      - MIME type: Type Subtype
 *      - Type: [a-zA-Z0-9-_\.]+
 *      - Subtype: NUL | / Type Subtype
 *
 * Example: "image/png"
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c type member you want to set.
 *
 * @param type The MIME type of the data being sent to the invocation handler.
 *               The value must conform to the "Type Subtype" format (see
 *               description for further information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_type(
        navigator_invoke_invocation_t *invocation, const char* type);

/**
 * @brief Set the URI of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_uri() function sets the URI pointing
 * to the data of a given @c #navigator_invoke_invocation_t structure. The @c
 * uri member identifies the location of the data the invoked handler is to
 * perform an action on.
 *
 * If you don't call this function, the URI is assumed to be "data://local",
 * indicating that the invocation data is provided through the @c data member
 * (using the @c navigator_invoke_invocation_set_data() function).
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c uri member you want to set.
 *
 * @param uri The URI to the data being sent to the invocation handler. The
 *            value of this member should be a percent-encoded URI. For example,
 *            file:///accounts/1000/appdata/com.example.application.123456789123456789123456789/data/image%201.jpg
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_uri(
        navigator_invoke_invocation_t *invocation, const char* uri);

/**
 * @brief Set the file transfer mode of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_file_transfer_mode() function sets the
 * file transfer mode.
 *
 * The transfer_mode identifies how the file transfer should be handled. By
 * default, private file transfer will be applied if the URI is a file URI that 
 * points to a file that is not in the shared area. The file will be transfered 
 * by creating a read-only copy in the target's private inbox.
 *
 * Setting the @c transfer_mode allows the sender to control the transfer by
 * specifying that no handling should be applied, or that the file should be
 * copied read/write, or should be hard-linked.
 *
 * If @c NAVIGATOR_INVOKE_FILE_TRANSFER_MODE_LINK is specified the file must
 * have o+r permissions. In addition, if the file is o+w then the sender must be
 * the owner of the file.
 *
 * @param invoke A pointer to the @c #navigator_invoke_invocation_t structure
 *                   whose @c transfer_mode member you want to set.
 *
 * @param transfer_mode The mode that should control the transfer of the data if
 *            the URI is a file URI that does not refer to a file in the shared
 *            area.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_file_transfer_mode(
        navigator_invoke_invocation_t *invoke,
        navigator_invoke_file_transfer_mode_t transfer_mode);

/**
 * @brief Set the arbitrary data of an @c invocation
 *
 * The @c navigator_invoke_invocation_set_data() function sets the @c data and
 * @c data_length of a given @c #navigator_invoke_invocation_t structure. The @c
 * data member is the data the invoked handler is to perform an action on. Upon
 * sending the invocation, the data is delivered to the target in its unchanged
 * form.
 *
 * If you don't call this function, the action and/or type information (which
 * can be set using the @c navigator_invoke_invocation_set_action() and @c
 * navigator_invoke_invocation_set_type() functions respectively) must be
 * sufficient to carry out the invocation.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c data you want to set.
 *
 * @param data The arbitrary data being sent to the invocation handler. The
 *            value of this member can take the form of any binary data.
 *
 * @param data_length The size of the @c data member in bytes.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_data(
        navigator_invoke_invocation_t *invocation, const void* data,
        int data_length);

/**
 * @cond internal
 */

/**
 * @brief Set the perimeter of an @c invocation
 *
 * This function should not be used by third-party developers. The Invocation
 * Framework will automatically take care of setting the perimeter across all
 * device configurations (e.g. Personal-only, Balance, Corporate Liable, etc.).
 * If you use this function to set the perimeter, your app may not be able to
 * invoke applications in particular device configurations.
 *
 * The @c navigator_invoke_invocation_set_perimeter() function sets the @c
 * perimeter member of a given @c #navigator_invoke_invocation_t structure. The
 * @c perimeter member identifies the perimeter (either personal or enterprise)
 * in which the application should be invoked. Use this function in instances
 * where the target application is a "hybrid" that can run in both enterprise
 * and personal perimeters. In all cases, the perimeter is mandated to be the
 * same as the sender.
 *
 * If you don't call this function for a hybrid application, then the invocation
 * will be rejected and an error will be returned.
 *
 * The possible values that you can set to this member are:
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * See the @c #navigator_invoke_perimeter_type_t enumeration for details.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c perimeter member you want to set.
 *
 * @param perimeter The perimeter in which you want the application to be
 *                  invoked. This value must correspond to an entry in the @c
 *                  #navigator_invoke_perimeter_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_perimeter(
        navigator_invoke_invocation_t *invocation,
        navigator_invoke_perimeter_type_t perimeter);

/**
 * @endcond
 */

/**
 * @brief Set the metadata with which the application should be invoked
 *
 * The @c navigator_invoke_invocation_set_metadata() function sets the
 * metadata with which the application should be invoked.
 *
 * @param invocation The invocation to update.
 * @param metadata The JSON string carrying optional metadata.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_metadata(
        navigator_invoke_invocation_t *invocation, const char* metadata);

/**
 * @brief Set the target type mask of an invocation
 *
 * The @c navigator_invoke_invocation_set_target_type_mask() function sets the
 * target type mask of a given @c #navigator_invoke_invocation_t structure.
 * The @c target_type_mask member is a bitwise-OR value that indicates which
 * targets the invocation selection should include: applications, cards
 * and/or services.
 *
 * The invoke target type values you can use to set this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - a bitwise @c OR of any combination of the above values.
 *
 * See the @c #navigator_invoke_target_type_t enumeration for details.
 *
 * If you don't assign a @c target_type_mask member, or you assign
 * @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED to an @c invocation, then all of
 * the target types will be considered in the brokering system.
 *
 * @param invoke A pointer to the @c #navigator_invoke_invocation_t structure
 *               whose @c target_type_mask member you want to set.
 *
 * @param target_type_mask  A target type corresponding to an entry in the @c
 *                          #navigator_invoke_target_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_set_target_type_mask(
        navigator_invoke_invocation_t *invoke,
        int target_type_mask);

/**
 * @brief Set the list id to associate with the invocation
 *
 * The @c navigator_invoke_invocation_set_list_id() function sets the
 * list id of the list that @c invoke should be associated with.
 * If @c list_id is 0, @c invoke is disassociated from any lists.
 *
 * @param invoke  The invocation to update.
 * @param list_id The id of the list to associate the invocation with.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_invocation_set_list_id(
        navigator_invoke_invocation_t *invoke,
        int list_id);

/**
 * @brief Get the ID from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_id() function extracts the invocation
 * ID of a given @c #navigator_invoke_invocation_t structure. The @c id member
 * is used by the invocation handler to create delivery receipt responses to be
 * returned when an invocation is sent (see the @c
 * navigator_invoke_invocation_set_id() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c id member you want to retrieve.
 *
 * @return The invocation ID if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_id(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the target from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_target() function extracts the target
 * of a given @c #navigator_invoke_invocation_t structure. The @c target member
 * is used by the invocation framework to identify the target application or
 * card meant to perform an action based on the invocation (see the @c
 * navigator_invoke_invocation_set_target() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c target member you want to retrieve.
 *
 * @return The invocation target if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_target(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the source from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_source() function extracts the source
 * of a given @c #navigator_invoke_invocation_t structure. The @c source member
 * is used by the invoked handler to direct resopnse messages to the invocator
 * (see the @c navigator_invoke_invocation_set_source() function for further
 * details). This function doesn't copy members and the returned values are
 * released once the @c #navigator_invoke_invocation_t structure is destroyed
 * with the @c navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c source member you want to retrieve.
 *
 * @return The invocation source if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_source(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the action from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_action() function extracts the @c
 * action member of a given @c #navigator_invoke_invocation_t structure. The @c
 * action member is used by the brokering system and invocation framework to
 * identify what action an invoked handler is meant to perform (see the @c
 * navigator_invoke_invocation_set_action() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c action member you want to retrieve.
 *
 * @return The invocation action if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_action(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the type from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_type() function extracts the MIME type
 * of a given @c #navigator_invoke_invocation_t structure. The @c type member is
 * used by the brokering system and invocation framework to identify the MIME
 * type of the data an invoked handler is meant to perform an action on (see the
 * @c navigator_invoke_invocation_set_type() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c type member you want to retrieve.
 *
 * @return The invocation type if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_type(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the URI from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_uri() function extracts the URI
 * pointing the data of a given @c #navigator_invoke_invocation_t structure. The
 * @c uri member is used by the invocation handler to identify the location of
 * the data the invoked handler is to perform an action on (see the @c
 * navigator_invoke_invocation_set_uri() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c uri member you want to retrieve.
 *
 * @return The URI pointing to invocation data if one was provided by the
 *         sender, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_uri(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the file transfer mode of an @c invocation
 *
 * The @c navigator_invoke_invocation_get_file_transfer_mode() function extracts
 * the @c #navigator_invoke_file_transfer_mode_t file transfer mode of a given
 * @c #navigator_invoke_invocation_t structure.
 *
 * The @c transfer mode member is used to control how files are passed between
 * sender and target (see the @c
 * navigator_invoke_invocation_set_file_transfer_mode() function for further
 * details).
 *
 * @param invoke A pointer to the @c #navigator_invoke_invocation_t structure
 *                   whose transfer mode member you want to retrieve.
 *
 * @return The file transfer mode that describes how the file will be transfered
 *         in the case that it points to a file URI that is not in the shared
 *         area, or @c BPS_FAILURE with @c errno set if an error occurs.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_get_file_transfer_mode(
        const navigator_invoke_invocation_t * invoke);

/**
 * @brief Get the data length from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_data_length() function extracts the
 * length in bytes of the data of a given @c #navigator_invoke_invocation_t
 * structure. The @c data_length member is used by the invocation handler to
 * identify the size of the data the invoked handler is to perform an action on
 * (see the @c navigator_invoke_invocation_set_data() function for further
 * details). This function doesn't copy members and the returned values are
 * released once the @c #navigator_invoke_invocation_t structure is destroyed
 * with the @c navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c data_length member you want to retrieve.
 *
 * @return The size in bytes of the invocation data if one was provided by the
 *         sender, -1 otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_get_data_length(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the data from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_data() function extracts the binary
 * data of a given @c #navigator_invoke_invocation_t structure. The @c data
 * member is used by the invocation handler to perform an action (see the @c
 * navigator_invoke_invocation_set_data() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_invocation_t structure is destroyed with the @c
 * navigator_invoke_invocation_destroy() function.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c data member you want to retrieve.
 *
 * @return The invocation data if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const void* navigator_invoke_invocation_get_data(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the perimeter from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_perimeter() function extracts the @c
 * perimeter member of a given @c #navigator_invoke_invocation_t structure. The
 * @c perimeter member is used by the invocation framework to identify what
 * perimeter the target application is to be invoked (see the @c
 * navigator_invoke_invocation_set_perimeter() function for further details).
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c perimeter member you want to retrieve.
 *
 * @return The invocation perimeter if one was provided by the sender.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_perimeter_type_t navigator_invoke_invocation_get_perimeter(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the metadata with which the application should be invoked
 *
 * The @c navigator_invoke_invocation_get_metadata() function gets the
 * metadata with which the application should be invoked.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c metadata member you want to retrieve.
 *
 * @return The metadata if it was provided by sender.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_invocation_get_metadata(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Get the list ID with which the invocation should be associated with
 *
 * The @c navigator_invoke_invocation_get_list_id() function gets the
 * list ID with which @c invoke is associated.
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose list ID you want to retrieve.
 *
 * @return The id of the list this invocation should be associated with,
 *         or 0 if no such association exists.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_invocation_get_list_id(
        const navigator_invoke_invocation_t *invocation);


/**
 * @brief Get the target type mask from an @c invocation
 *
 * The @c navigator_invoke_invocation_get_target_type_mask() function extracts
 * the target type mask of a given @c #navigator_invoke_invocation_t structure.
 * The @c target_type_mask member indicates which target types should be
 * included by the invocation selection (see
 * @c navigator_invoke_invocation_set_target_type_mask() and
 * @c #navigator_invoke_target_type_t for further details).
 *
 * @param invocation A pointer to the @c #navigator_invoke_invocation_t
 *                   structure whose @c target_type_mask member you want to
 *                   retrieve.
 *
 * @return The invocation target type mask.
 *         @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is returned when the
 *         @c target_type_mask is not specified, which implies
 *         that all the target types are considered by the brokering system.
 *         @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is returned with @c errno
 *         set upon error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_get_target_type_mask(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Retrieve the invocation structure pointer from the BPS event
 *
 * The @c navigator_invoke_event_get_invocation() function extracts the
 * invocation properties from a @c #navigator_invoke_invocation_t structure sent
 * with the @c navigator_invoke_invocation_send() function. You should call this
 * function upon receiving the @c NAVIGATOR_INVOKE_TARGET event from the event
 * handler to perform the task defined by the invocation.
 *
 * We recommend that you use the @c navigator_event_get_err() function after
 * calling this function in case of an error in processing. The possible errors
 * for an invocation are:
 *      - @c INVOKE_NO_TARGET_ERROR: There is no target identified by the
 *                                   invocation.
 *      - @c INVOKE_BAD_REQUEST_ERROR: The invocation request specifications do
 *                                     not conform to the permitted parameters
 *                                     of the handler. For example, an image
 *                                     sharing invocation being sent to a
 *                                     target application that cannot share
 *                                     images would result in this error.
 *      - @c INVOKE_INTERNAL_ERROR: A generic error occured in the internal
 *                                  framework while attempting to retrieve the
 *                                  @c #navigator_invoke_invocation_t structure.
 *      - @c INVOKE_TARGET_ERROR: A generic error occured with the target
 *                                handler.
 *
 * "Ownership" of an event is not transferred to a handler upon its invocation.
 * A handler must not call the @c navigator_invoke_invocation_destroy() function
 * on invocation pointers that are retrieved using the @c
 * navigator_invoke_event_get_invocation() function.  The pointer to the
 * @c #navigator_invoke_invocation_t structure is valid until the @c
 * bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET event to extract the invocation
 * from.
 *
 * @return A pointer to the @c #navigator_invoke_invocation_t structure on
 *         success, NULL on failure with @c errno set.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_invocation_t* navigator_invoke_event_get_invocation(
        bps_event_t *event);

/**
 * @brief Request an @c invocation to a target
 *
 * The @c navigator_invoke_invocation_send() function invokes a target handler
 * that is specified by the given @c #navigator_invoke_invocation_t structure.
 * The target of an invocation can be determined in the following manners:
 *      - If you specified a @c target member (using the @c
 *        navigator_invoke_invocation_set_target() function, the target is
 *        invoked directly using the given information.
 *      - If you didn't specify a @c target member, the brokering system infers
 *        a target handler using the information from the @c action and/or @c
 *        type members, set with the @c navigator_invoke_invocation_set_action()
 *        and @c navigator_invoke_invocation_set_type() functions respectively.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_invocation_send(
        const navigator_invoke_invocation_t *invocation);

/**
 * @brief Create an invoke query structure and allocate all necessary memory
 *
 * The @c navigator_invoke_query_create() function creates an instance of a @c
 * #navigator_invoke_query_t structure called @c query to be used by the
 * invocation framework. Destroy all invocation query instances created through
 * this function once they are no longer needed by using the @c
 * navigator_invoke_query_destroy() function to prevent memory leaks.
 *
 * @param query The @c #navigator_invoke_query_t structure to populate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_create(navigator_invoke_query_t **query);

/**
 * @brief Deallocate the memory used by an invoke query structure
 *
 * The @c navigator_invoke_invocation_destroy() function deallocates any memory
 * set to a given @c query. Use this function to deallocate memory used by
 * a @c #navigator_invoke_query_t structure (created by the @c
 * navigator_invoke_query_create() function) that's no longer in use.
 * Failing to do so will result in a memory leak.
 *
 * @param query The @c #navigator_invoke_query_t structure to deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_destroy(navigator_invoke_query_t *query);

/**
 * @brief Set the ID of a @c query
 *
 * The @c navigator_invoke_query_set_id() function sets the invocation query ID
 * of a given @c #navigator_invoke_query_t structure. Assign an @c id member to
 * an invocation query to receive a delivery receipt response. The @c id member
 * you assign through a sender appears in its corresponding delivery receipt.
 *
 * Assigning an @c id member to an invocation is mandatory. If you don't assign
 * an @c id, there is no way to determine the result of the invocation query
 * request.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              id you want to set.
 *
 * @param id The invocation query ID you want to display on the delivery receipt
 *           response. This value must be in numerical format. For example, a
 *           valid @c id would be "42".
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.

 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_id(navigator_invoke_query_t *query,
        const char* id);

/**
 * @brief Set the action of a @c query
 *
 * The @c navigator_invoke_query_set_action() function sets the @c action member
 * of a given @c #navigator_invoke_query_t structure. The @c action member
 * identifies the action the invocation query results must be able to perform.
 *
 * If you don't assign an @c action member to an invocation query, the
 * brokering system doesn't filter for any specific action.
 *
 * The format of an @c action member must conform to the following guidelines:
 *      - Maximum 50 characters
 *      - Action: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "bb.action.SHARE"
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action member you want to set.
 *
 * @param action The action you want to query for. The value must conform to the
 *               "[Domain][Sub-domain]" format (see description for further
 *               information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_action(navigator_invoke_query_t *query,
        const char* action);

/**
 * @brief Set the type of a @c query
 *
 * The @c navigator_invoke_query_set_type() function sets the MIME type of a
 * given @c #navigator_invoke_query_t structure. The @c type member identifies
 * the MIME type the invocation query results must be able to parform an action
 * on.
 *
 * If you don't assign a @c type member to an invocation query, the brokering
 * system doesn't filter for any specific MIME type. You must assign this
 * member if you don't assign the @c file_uri member (using the @c
 * navigator_invoke_query_set_file_uri() function).
 *
 * The format of a @c type member must conform to the following guidelines:
 *      - MIME type: Type Subtype
 *      - Type: [a-zA-Z0-9-_\.]+
 *      - Subtype: NUL | / Type Subtype
 *
 * Example: "image/png"
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              type member you want to set.
 *
 * @param type The MIME type you want to query for. The value must conform to
 *             the "Type Subtype" format (see description for further
 *             information).
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_type(navigator_invoke_query_t *query,
        const char* type);

/**
 * @brief Set the URI of a @c query
 *
 * The @c navigator_invoke_query_set_file_uri() function sets the URI of a given
 * @c #navigator_invoke_query_t structure. The @c file_uri member identifies the
 * type interface the invocation query results must be able to perform an action
 * on.
 *
 * You must assign this member if the @c type member (assinged wih the @c
 * navigator_invoke_query_set_type() function) is not provided.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              file_uri member you want to set.
 *
 * @param file_uri The URI to the type interface you want to query for. The
 *            value of this member should be a percent-encoded URI. For example,
 *            file:///accounts/1000/appdata/com.example.application.123456789123456789123456789/data/image%201.jpg
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_file_uri(navigator_invoke_query_t *query,
        const char* file_uri);

/**
 * @brief Set the target type mask of a @c query
 *
 * The @c navigator_invoke_query_set_target_type_mask() function sets the target
 * type mask of a given @c #navigator_invoke_query_t structure. The
 * @c target_type_mask member is a bitwise @c OR value that determines which
 * targets the invocation query should include in its results.
 *
 * The invoke target type values you can use to set this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - @c a bitwise @c OR of any combination of the above values.
 *
 * If you don't assign a @c target_type_mask member or assign
 * @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED to a query, then all the target
 * types will be considered in the query.
 *
 * See the @c #navigator_invoke_target_type_t enumeration for details.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              target_type_mask member you want to set.
 *
 * @param target_type_mask  A target type corresponding to an entry in the @c
 *                          #navigator_invoke_target_type_t enumeration. The @c
 *                          NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE value is
 *                          reserved for future use.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_target_type_mask(
        navigator_invoke_query_t *query,
        int target_type_mask);

/**
 * @brief Set the action type of a @c query
 *
 * The @c navigator_invoke_query_set_action_type() function sets the action type
 * of a given @c #navigator_invoke_query_t structure. The @c action_type member
 * indicates whether the invocation query returns only menu actions (actions
 * that have an icon and label) or both brokered and menu actions (which may not
 * all have an icon and label).
 *
 * If you don't assign an @c action_type member to an invocation query, the
 * brokering system doesn't filter for any specific action type.
 *
 * The possible values that you can set to this member are:
 *     - @c NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_MENU
 *     - @c NAVIGATOR_INVOKE_QUERY_ACTION_TYPE_ALL
 *
 * See the @c #navigator_invoke_query_action_type_t enumeration for details.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action_type member you want to set.
 *
 * @param action_type An action type corresponding to an entry in the @c
 *                    #navigator_invoke_query_action_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_action_type(
        navigator_invoke_query_t *query,
        navigator_invoke_query_action_type_t action_type);

/**
 * @cond internal
 */

/**
 * @brief Set the perimeter of a @c query
 *
 * This function should not be used by third-party developers. The Invocation
 * Framework will automatically take care of setting the perimeter across all
 * device configurations (e.g. Personal-only, Balance, Corporate Liable, etc.).
 * If you use this function to set the perimeter, your app may not be able to
 * invoke applications in particular device configurations.
 *
 * The @c navigator_invoke_query_set_perimeter() function sets the @c perimeter
 * member of a given @c #navigator_invoke_query_t structure. The @c perimeter
 * member indicates in which perimeter the resulting targets should reside. Use
 * this function in instances where the query results include "hybrid"
 * applications that can run in both enterprise and personal perimeters. In all
 * cases, the perimeter is mandated to be the same as the sender.
 *
 * If you don't call this function for a hybrid application, then the query will
 * be rejected and an error will be returned.
 *
 * The possible values that you can set to this member are:
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * See the @c #navigator_invoke_perimeter_type_t enumeration for details.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              perimeter member you want to set.
 *
 * @param perimeter The perimeter in which you want the application to be
 *                  invoked. This value must correspond to an entry in the @c
 *                  #navigator_invoke_perimeter_type_t enumeration.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_set_perimeter(
        navigator_invoke_query_t *query,
        navigator_invoke_perimeter_type_t perimeter);

/**
 * @endcond
 */

/**
 * @brief Get the ID from a @c query
 *
 * The @c navigator_invoke_query_get_id() function extracts the invocation query
 * ID of a given @c #navigator_invoke_query_t structure. The @c id member is
 * used by the query handler to create delivery receipt responses to be returned
 * when an invocation query is sent (see the @c navigator_invoke_query_set_id()
 * function for further details). This function doesn't copy members and the
 * returned values are released once the @c #navigator_invoke_query_t structure
 * is destroyed with the @c navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              id member you want to retrieve.
 *
 * @return The invocation query ID if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_id(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the action from a @c query
 *
 * The @c navigator_invoke_query_get_action() function extracts the @c action
 * member of a given @c #navigator_invoke_query_t structure. The @c action
 * member is used by the brokering system to identify what action the invocation
 * query results must be able to perform (see the @c
 * navigator_invoke_query_set_action() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_query_t structure is destroyed with the @c
 * navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action member you want to retrieve.
 *
 * @return The action to query for if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_action(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the type from a @c query
 *
 * The @c navigator_invoke_query_get_type() function extracts the MIME type
 * of a given @c #navigator_invoke_query_t structure. The @c type member is used
 * by the brokering system to identify what MIME type the invocation query
 * results must be able to perform an action on (see the @c
 * navigator_invoke_query_set_type() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_query_t structure is destroyed with the @c
 * navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              type member you want to retrieve.
 *
 * @return The MIME type to query for if one was provided by the sender, @c NULL
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_type(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the URI from a @c query
 *
 * The @c navigator_invoke_query_get_file_uri() function extracts the URI of a
 * given @c #navigator_invoke_query_t structure. The @c file_uri member is used
 * by the brokering system to identify what type interface the invocation query
 * results must be able to perform an action on (see the @c
 * navigator_invoke_query_set_file_uri() function for further details). This
 * function doesn't copy members and the returned values are released once the
 * @c #navigator_invoke_query_t structure is destroyed with the @c
 * navigator_invoke_query_destroy() function.
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              file_uri member you want to retrieve.
 *
 * @return The URI to the type interface to query for if one was provided by the
 *         sender, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_get_file_uri(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the target type mask from a @c query
 *
 * The @c navigator_invoke_query_get_target_type_mask() function extracts the
 * target type of a given @c #navigator_invoke_query_t structure. The
 * @c target_type_mask member is a bitwise @c OR value that determines which
 * targets the invocation query should include in its results.
 * (see @c navigator_invoke_query_set_target_type_mask() and
 * @c #navigator_invoke_target_type_t for further details).
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              target_type_mask member you want to retrieve.
 *
 * @return The invocation query target type mask to query for if one was provided
 *         by the sender.  @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is
 *         returned when the @c target_type_mask is not specified, which implies
 *         that all possible target types are considered in the query.
 *         @c NAVIGATOR_INVOKE_TARGET_TYPE_UNSPECIFIED is returned with @c errno
 *         set upon error.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_get_target_type_mask(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the action type from a @c query
 *
 * The @c navigator_invoke_query_get_action_type() function extracts the action
 * type of a given @c #navigator_invoke_query_t structure. The @c action_type
 * member is used by the brokering system to identify whether the invocation
 * query should return only menu actions or both brokered and menu actions (see
 * the @c navigator_invoke_query_set_action_type() function and the @c
 * #navigator_invoke_query_action_type_t enumeration for further details).
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              action_type member you want to retrieve.
 *
 * @return The invocation query target type to query for if one was provided
 *         by the sender.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_query_action_type_t navigator_invoke_query_get_action_type(
        const navigator_invoke_query_t *query);

/**
 * @brief Get the perimeter from a @c query
 *
 * The @c navigator_invoke_query_get_perimeter() function extracts the @c
 * perimeter member of a given @c #navigator_invoke_query_t structure. The @c
 * perimeter member is used by the invocation framework to identify in which
 * perimeter the resulting targets should reside (see the @c
 * navigator_invoke_query_set_perimeter() function and the @c
 * #navigator_invoke_perimeter_type_t enumeration for further details).
 *
 * @param query A pointer to the @c #navigator_invoke_query_t structure whose @c
 *              perimeter member you want to retrieve.
 *
 * @return The perimeter in which the query target should be invoked if one was
 *         provided by the sender, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_perimeter_type_t navigator_invoke_query_get_perimeter(
        const navigator_invoke_query_t *query);

/**
 * @brief Send a @c query request to the invocation framework
 *
 * The @c navigator_invoke_query_send() function deploys an invocation query
 * that is specified by the given @c #navigator_invoke_query_t structure. Viable
 * candidates conforming to the specifications set through the various members
 * of the @c #navigator_invoke_query_t structure (using the @c
 * navigator_invoke_query_set_*() functions) are returned as results of the
 * query.
 *
 * @param query The @c #navigator_invoke_query_t structure to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_send(const navigator_invoke_query_t *query);

/**
 * @brief Get the number of @c action values in an invocation query result
 *
 * The @c navigator_invoke_event_get_query_result_action_count() function
 * extracts the number of @c #navigator_invoke_query_result_action_t structure
 * results that are returned from an invocation query. The @c
 * #navigator_invoke_query_result_action_t action structures returned are
 * considered viable actions based on the information supplied through the @c
 * #navigator_invoke_query_t structure that invoked the query. Call this
 * function from an event handler upon receiving the @c
 * NAVIGATOR_INVOKE_QUERY_RESULT event to determine how many viable actions were
 * returned. You can use this value to create a loop of the returned values.
 *
 * If you encounter an error in processing the query, we recommend that you call
 * the @c navigator_event_get_err() function to determine the nature of the
 * error. The possible errors are:
 *     - @c invalid_argument
 *     - @c response_too_large
 *     - @c server_error
 *
 * @param event The @c NAVIGATOR_INVOKE_QUERY_RESULT event targeted by the query
 *              result.
 *
 * @return The number of actions inside the invocation query result, -1
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_event_get_query_result_action_count(
        bps_event_t *event);

/**
 * @brief Get an @c action from an invocation query result
 *
 * The @c navigator_invoke_event_get_query_result_action() function extracts one
 * of the @c #navigator_invoke_query_result_action_t structure results returned
 * from an invocation query, identified by a given @c index value. The @c
 * #navigator_invoke_query_result_action_t action structures returned are
 * considered viable actions based on the information supplied through the @c
 * #navigator_invoke_query_t structure that invoked the query. This function
 * doesn't copy members and the returned values are released once the @c
 * bps_get_event() function is called again.
 *
 * Note that "ownership" of the event is not passed to the handler. For this
 * reason, don't call the free function on invocation query result action
 * pointers that are retrieved using this function.
 *
 * @param event The @c NAVIGATOR_INVOKE_QUERY_RESULT event targeted by the query
 *              result.
 *
 * @param index The numerical index value of the @c
 *              #navigator_invoke_query_result_action_t structure inside the
 *              invocation query result.
 *
 * @return The pointer to the returned action, @c NULL if the query result is
 *         @c NULL or the @c index is out of bounds.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_query_result_action_t* navigator_invoke_event_get_query_result_action(
        bps_event_t *event, int index);

/**
 * @brief Get the name of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_name() function extracts the
 * action name of a given @c #navigator_invoke_query_result_action_t structure.
 * The @c name member is used by the query result handler to identify a given @c
 * action that is supported for the specified query. This function doesn't copy
 * members and the returned values are released once the @c bps_get_event()
 * function is called again. You must call this function to display the returned
 * @c action value(s).
 *
 * Each @c action @c name conforms to the following guidelines:
 *      - Maximum 50 characters
 *      - Action: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "bb.action.SHARE"
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c name member you want to retrieve.
 *
 * @return The name of the given action, in the "[Domain][Sub-domain]" format
 *         (see description for further information), @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_name(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the icon of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_icon() function extracts the
 * URI to an icon of a given @c #navigator_invoke_query_result_action_t
 * structure. The @c icon member is a path to an icon to be identified with the
 * corresponding action. This function doesn't copy members and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c icon member you want to retrieve.
 *
 * @return The icon URI of the given @c action, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_icon(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the label of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_label() function extracts the
 * label to an icon of a given @c #navigator_invoke_query_result_action_t
 * structure. The @c label member allows the action to be identified with a
 * localized label name in UTF-8 format. For example, a suitable label for the
 * "bb.action.SHARE" action would be "Share". This function doesn't copy members
 * and the returned values are released once the @c bps_get_event() function is
 * called again.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c label member you want to retrieve.
 *
 * @return The label of the given @c action, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_label(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the default target of an @c action from an invocation query result
 *
 * The @c navigator_invoke_query_result_action_get_default_target() function
 * extracts the default target of a given @c
 * #navigator_invoke_query_result_action_t structure. The @c default_target
 * member is the name of a target handler that is considered as the default
 * provider for the given @c action. This function doesn't copy members and the
 * returned values are released once the @c bps_get_event() function is called
 * again.
 *
 * Each @c action @c default_target conforms to the following guidelines:
 *      - Maximum 50 characters
 *      - Target: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.target"
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure whose
 *               @c default_target member you want to retrieve.
 *
 * @return The default target of the given @c action, in the
 *         "[Domain][Sub-domain]" format (see description for further
 *         information), @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_action_get_default_target(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get the number of @c target values in an @c action
 *
 * The @c invoke_get_query_result_target_count() function extracts the number of
 * @c #navigator_invoke_query_result_target_t structures contained within a @c
 * #navigator_invoke_query_result_action_t structure. The @c
 * #navigator_invoke_query_result_target_t target structures contained are
 * considered viable targets to perform the given action.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure
 *               holding the @c target values.
 *
 * @return The number of targets inside the @c action, -1 otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_query_result_action_get_target_count(
        const navigator_invoke_query_result_action_t *action);

/**
 * @brief Get a @c target from an @c action
 *
 * The @c navigator_invoke_query_result_action_get_target() function extracts
 * one of the @c #navigator_invoke_query_result_target_t structures inside of a
 * @c #navigator_invoke_query_result_action_t structure, identified by a given
 * @c index value. The @c #navigator_invoke_query_result_target_t target
 * structures contained are considered viable targets to perform the given
 * action. This function doesn't copy members and the returned values are
 * released once the @c bps_get_event() function is called again.
 *
 * @param action The @c #navigator_invoke_query_result_action_t structure
 *               holding the @c target values.
 *
 * @param index The numerical index value of the @c
 *              #navigator_invoke_query_result_target_t structure inside the
 *              given @c #navigator_invoke_query_result_action_t structure.
 *
 * @return The pointer to the returned target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_query_result_target_t* navigator_invoke_query_result_action_get_target(
        const navigator_invoke_query_result_action_t *action, int index);

/**
 * @brief Get the key of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_key() function extracts the
 * target key of a given @c #navigator_invoke_query_result_target_t structure.
 * The @c key member is an identifier to a target (as stated in its BAR
 * manifest) that is capable of performing the specified action. This function
 * doesn't copy members and the returned values are released once the @c
 * bps_get_event() function is called again. You must call this function to
 * display returned @c target value(s).
 *
 * Each @c target @c key conforms to the following guidelines:
 *      - Maximum 50 characters
 *      - Target: [Domain][Sub-domain]
 *      - Sub-domain:  NUL | .[Domain][Sub-domain]
 *      - Domain: [a-zA-Z]([a-zA-Z0-9_])*
 *
 * Example: "com.example.invoke.target"
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c key member you want to retrieve.
 *
 * @return The location key of the given target, in the "[Domain][Sub-domain]"
 *         format (see description for further information), @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_key(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief Get the icon of an @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_icon() function extracts the
 * URI to an icon of a given @c #navigator_invoke_query_result_target_t
 * structure. The @c icon member is a path to an icon to be identified with the
 * corresponding target. This function doesn't copy members and the returned
 * values are released once the @c bps_get_event() function is called again. You
 * must call this function to display returned @c target value(s).
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c icon member you want to retrieve.
 *
 * @return The icon URI of the given @c target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_icon(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_query_result_target_get_splash() function extracts
 * the URI to a splash icon of a given @c
 * #navigator_invoke_query_result_target_t structure. The @c splash member is a
 * path to an icon to be displayed to represent the given target while loading.
 * This function doesn't copy members and the returned values are released once
 * the @c bps_get_event() function is called again.
 *
 * You must call this function if the @c target @c type is a viewer. To test
 * this, call the @c navigator_invoke_query_result_target_get_type() function.
 * If the function returns @c NAVIGATOR_INVOKE_TARGET_TYPE_VIEWER, the given
 * target is a viewer).
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c splash member you want to retrieve.
 *
 * @return The splash icon URI of the given @c target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_splash(
        const navigator_invoke_query_result_target_t *target) BPS_DEPRECATED;

/**
 * @brief Get the label of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_label() function extracts the
 * label to an icon of a given @c #navigator_invoke_query_result_target_t
 * structure. The @c label member allows the target to be identified with a
 * localized label name in UTF-8 format. For example, "Example Target" would be
 * a suitable label for a target. This function doesn't copy members and the
 * returned values are released once the @c bps_get_event() function is called
 * again. You must call this function to display returned @c target value(s).
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c label member you want to retrieve.
 *
 * @return The label of the given @c target, @c NULL otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_query_result_target_get_label(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief Get the type of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_type() function extracts the
 * target type of a given @c #navigator_invoke_query_result_target_t structure.
 * The @c type member allows the target to be identified as an
 * application, service, or card. You must call this function to display returned
 * @c target value(s).
 *
 * The possible values that you can receive from this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c type member you want to retrieve.
 *
 * @return The type of the given @c target.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_target_type_t navigator_invoke_query_result_target_get_type(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief Get the perimeter of a @c target for an @c action
 *
 * The @c navigator_invoke_query_result_target_get_perimeter() function extracts
 * the @c perimeter member of a given @c #navigator_invoke_query_result_target_t
 * structure. The @c perimeter member indicates in which perimeter the given
 * target should reside. You must call this function to display returned @c
 * target value(s).
 *
 * The possible values that you can receive from this member are:
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_PERSONAL
 *     - @c NAVIGATOR_INVOKE_PERIMETER_TYPE_ENTERPRISE
 *
 * @param target The @c #navigator_invoke_query_result_target_t structure whose
 *               @c perimeter member you want to retrieve.
 *
 * @return The perimeter in which the given @c target should reside.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API navigator_invoke_perimeter_type_t navigator_invoke_query_result_target_get_perimeter(
        const navigator_invoke_query_result_target_t *target);

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_create() function creates an instance of a @c
 * #navigator_invoke_viewer_t structure called @c viewer to be used by the
 * invocation framework, and associates it to a @c
 * #navigator_invoke_invocation_t invocation structure. Destroy all viewer
 * instances created through this function once they are no longer needed by
 * using the @c navigator_invoke_viewer_destroy() function to prevent memory
 * leaks.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to populate.
 *
 * @param invocation The @c #navigator_invoke_invocation_t structure to
 *                   associate with the given @c viewer. The @c invocation
 *                   member cannot be @c NULL. When you call this function,
 *                   ownership of the @c #navigator_invoke_invocation_t
 *                   structure is passed to the @c #navigator_invoke_viewer_t
 *                   structure, and is destroyed once you call the @c
 *                   navigator_invoke_viewer_destroy() function. For this
 *                   reason, don't call the @c
 *                   navigator_invoke_invocation_destroy() function once you
 *                   call the @c navigator_invoke_viewer_create() function.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_create(navigator_invoke_viewer_t **viewer,
        navigator_invoke_invocation_t *invocation) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_destroy() function deallocates any memory set
 * to a given @c viewer. Use this function to deallocate memory used by a @c
 * #navigator_invoke_viewer_t structure (created by the @c
 * navigator_invoke_viewer_create() function) that's no longer in use. Failing
 * to do so will result in a memory leak.
 *
 * Note that calling this function will also destroy the @c
 * #navigator_invoke_invocation_t structure associated with the given @c
 * #navigator_invoke_viewer_t structure. For this reason, don't call the @c
 * navigator_invoke_invocation_destroy() function on a @c
 * #navigator_invoke_invocation_t structure that has been associated with a
 * viewer using the @c navigator_invoke_viewer_create() function.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to deallocate.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_destroy(
        navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer() function extracts a pointer to the
 * @c #navigator_invoke_viewer_t structure that has been sent to the handler
 * calling this function. Call this function from the event handler upon
 * receiving the @c NAVIGATOR_INVOKE_VIEWER event to extract the invocation
 * viewer properties (see the @c navigator_invoke_viewer_*() functions for
 * further details about the @c #navigator_invoke_viewer_t structure). The
 * pointer to the @c #navigator_invoke_viewer_t structure is valid until the @c
 * bps_get_event() function is called again.
 *
 * If you encounter an error in processing the viewer invocation, we recommend
 * that you call the @c navigator_event_get_err() function to determine the
 * nature of the error. The possible errors are:
 *     - @c INVOKE_NO_TARGET_ERROR
 *     - @c INVOKE_BAD_REQUEST_ERROR
 *     - @c INVOKE_INTERNAL_ERROR
 *     - @c INVOKE_TARGET_ERROR
 *
 * Note that "ownership" of the event is not passed to the handler. For this
 * reason, don't call the @c navigator_invoke_viewer_destroy() function from the
 * handler on @c #navigator_invoke_viewer_t structures that are retrieved using
 * this function.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER event targeted by the @c viewer.
 *
 * @return A pointer to the @c #navigator_invoke_viewer_t structure upon
 *         success, @c NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_viewer_t* navigator_invoke_event_get_viewer(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_invocation() function extracts a pointer
 * to the @c #navigator_invoke_invocation_t structure that has been assigned to
 * the given @c #navigator_invoke_viewer_t structure. This can be used to
 * retrieve invocation members assigned to a given @c viewer. For example, call
 * this function from the event handler upon calling the @c
 * navigator_invoke_event_get_viewer() function to extract the invocation
 * properties of the viewer (see the @c navigator_invoke_invocation_set_*()
 * functions for further details about the @c #navigator_invoke_invocation_t
 * structure parameters).
 *
 * If you retrieved the given @c viewer using the @c
 * navigator_invoke_event_get_viewer() function, the pointer to the @c
 * #navigator_invoke_viewer_t structure remains valid until the @c
 * bps_get_event() function is called again. If you created the @c viewer using
 * @c navigator_invoke_viewer_create(), the pointer will be valid until the @c
 * navigator_invoke_viewer_destroy() function is called.
 *
 * Note that "ownership" of the invocation is not passed to the handler. For
 * this reason, don't call the @c navigator_invoke_invocation_destroy() function
 * on @c #navigator_invoke_invocation_t structures that are retrieved using this
 * function.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to extract the @c
 *               #navigator_invoke_invocation_t structure from.
 *
 * @return A pointer to the @c #navigator_invoke_invocation_t structure upon
 *         success, @c NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const navigator_invoke_invocation_t* navigator_invoke_viewer_get_invocation(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_set_window_id() function sets the window ID of
 * a given @c #navigator_invoke_viewer_t structure. The @c window_id member
 * identifies a window created by the viewer. You may use this for application
 * to viewer communication. You must set a @c window_id to all @c
 * #navigator_invoke_viewer_t structures.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c window_id you want to set.
 *
 * @param window_id The window ID you want to associate with a window created by
 *                  the viewer. The value can be any string of characters. For
 *                  example, "window#123" is an acceptable window ID.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_set_window_id(
        navigator_invoke_viewer_t *viewer, const char* window_id) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_set_width() function sets the window width of
 * a given @c #navigator_invoke_viewer_t structure. The @c width member
 * identifies the width of a window created by the viewer. You must set a @c
 * width to all @c #navigator_invoke_viewer_t structures.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c width you want to set.
 *
 * @param width The width in pixels you want to set to a window created by the
 *              viewer. The value must be an integer. For example, "100" is an
 *              acceptable width.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_set_width(
        navigator_invoke_viewer_t *viewer, int width) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_set_height() function sets the window height
 * of a given @c #navigator_invoke_viewer_t structure. The @c height member
 * identifies the height of a window created by the viewer. You must set a @c
 * height to all @c #navigator_invoke_viewer_t structures.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c height you want to set.
 *
 * @param height The height in pixels you want to set to a window created by the
 *               viewer. The value must be an integer. For example, "100" is an
 *               acceptable height.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_set_height(
        navigator_invoke_viewer_t *viewer, int height) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_window_id() function extracts the window
 * ID of a given @c #navigator_invoke_viewer_t structure. The @c window_id
 * member is used to identify the window created by a viewer invocation (see the
 * @c navigator_invoke_viewer_set_window_id() function for further details).
 * This function doesn't copy members and the returned values are released once
 * the @c #navigator_invoke_viewer_t structure is destroyed with the @c
 * navigator_invoke_viewer_destroy() function.
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c window_id member you want to retrieve.
 *
 * @return The invocation viewer window ID if was provided by the sender, @c
 *         NULL with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_viewer_get_window_id(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_width() function extracts the window width
 * of a given @c #navigator_invoke_viewer_t structure. The @c width member is
 * used to set the width of the window created by a viewer invocation (see the
 * @c navigator_invoke_viewer_set_width() function for further details).
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c width member you want to retrieve.
 *
 * @return The invocation viewer width if was provided by the sender, -1 with @c
 *         errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_get_width(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_get_height() function extracts the window
 * height of a given @c #navigator_invoke_viewer_t structure. The @c height
 * member is used to set the height of the window created by a viewer invocation
 * (see the @c navigator_invoke_viewer_set_height() function for further
 * details).
 *
 * @param viewer A pointer to the @c #navigator_invoke_viewer_t structure whose
 *               @c height member you want to retrieve.
 *
 * @return The invocation viewer height if was provided by the sender, -1 with
 *         @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_get_height(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_send() function invokes a target handler
 * that is specified by the given @c #navigator_invoke_invocation_t structure
 * within the @c #navigator_invoke_viewer_t structure (see the @c
 * navigator_invoke_invocation_send() function for more details regarding how
 * a target for an invocation is determined). The handler uses the information
 * provided in the the @c #navigator_invoke_viewer_t structure to invoke an
 * instance of a viewer with the given parameters.
 *
 * @param viewer The @c #navigator_invoke_viewer_t structure to send.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_send(
        const navigator_invoke_viewer_t *viewer) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_close_viewer() function closes the viewer window of a
 * given @c #navigator_invoke_viewer_t structure that was started with the
 * @c navigator_invoke_viewer_send() function.
 *
 * @param window_id The window ID associated with the viewer window you want to
 *        close. The @c window_id member cannot be @c NULL.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_close_viewer(const char *window_id) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_viewer_relay() function enables two way communication
 * between the parent application and the viewer in the form of request/response
 * messages. Both the viewer and the parent application use this function to
 * send the data to each other.
 *
 * If you call this function, the target application or viewer receives the @c
 * NAVIGATOR_INVOKE_VIEWER_RELAY request event, and can retrieve the sent data.
 * The sender gets a @c NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT response event as a
 * response to the sent message.
 *
 * If you encounter an error in processing the message delivery, we recommend
 * that you call the @c navigator_event_get_err() function to determine the
 * nature of the error. The possible errors are:
 *     - @c INVALID_WINDOW_ID
 *     - @c INVALID_MESSAGE
 *
 * @param window_id The window ID associated with the viewer. The @c window_id
 *                  member must not be NULL.
 * @param message_name The name or title of the message you want to send. The @c
 *                     message_name member must not be NULL.
 * @param data The data you want to send the viewer relay message target. The @c
 *             data member can be NULL.
 * @param id The ID of the message. This is used to correlate the request with
 *           the peer's response. If you don't set this member, the sender
 *           doesn't receive a response to the sent message. Use the @c
 *           navigator_event_get_id() function to retrieve the @c id from the
 *           @c NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT response event.
 * @param is_response The request/response type of the message. If this member
 *                    is @c false, the message type is a request, otherwise it's
 *                    a response. The request messages are received by peer
 *                    through @c NAVIGATOR_INVOKE_VIEWER_RELAY events. The
 *                    responses from the peer are received through @c
 *                    NAVIGATOR_INVOKE_VIEWER_RELAY_RESULT events.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_viewer_relay(const char *window_id,
        const char *message_name, const char *data, const char *id,
        bool is_response) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer_relay_window_id() function extracts
 * the window ID of a given viewer relay message (created and sent using the @c
 * navigator_invoke_viewer_relay() function). The @c window_id member is used by
 * the receiving target to identify the @c viewer that sent the message. Call
 * this function in the parent application upon receiving the @c
 * NAVIGATOR_INVOKE_VIEWER_RELAY event to identify the corresponding @c viewer.
 * This function doesn't copy data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_RELAY event targeted by the @c
 *              viewer.
 *
 * @return The window ID of the viewer that sent the relay data, @c NULL with @c
 *         errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_viewer_relay_window_id(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer_relay_message_name() function
 * extracts the name of a given viewer relay message (created and sent using the
 * @c navigator_invoke_viewer_relay() function). The @c name member is used by
 * the receiving target (either the viewer or parent application) to identify
 * the name of the message sent by the sender (if the receiver is the viewer,
 * then the sender is the parent application, and vice versa). Call this
 * function upon receiving the @c NAVIGATOR_INVOKE_VIEWER_RELAY event to
 * identify the message name. This function doesn't copy data and the returned
 * values are released once the @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_RELAY event targeted by the
 *              sender of the viewer relay message.
 *
 * @return The name of the message set by the viewer relay sender, @c NULL with
 *         @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_viewer_relay_message_name(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_viewer_relay_data() function extracts the
 * data of a given viewer relay message (created and sent using the @c
 * navigator_invoke_viewer_relay() function). The @c data member is used by
 * the receiving target (either the viewer or parent application) to identify
 * the data content of the message sent by the sender (if the receiver is the
 * viewer, then the sender is the parent application, and vice versa). Call this
 * function upon receiving the @c NAVIGATOR_INVOKE_VIEWER_RELAY event to
 * identify the data of the message. This function doesn't copy data and the
 * returned values are released once the @c bps_get_event() function is called
 * again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_RELAY event targeted by the
 *              sender of the viewer relay message.
 *
 * @return The data of the message set by the viewer relay sender, @c NULL with
 *         @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_viewer_relay_data(
        bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief The use of viewers has been deprecated - use applications or cards as
 *        invocation targets instead
 *
 * @deprecated The use of viewers has been deprecated - use applications or
 *             cards as invocation targets instead.
 *
 * The @c navigator_invoke_event_get_window_id() function extracts the window ID
 * of a given viewer that has been terminated. The @c window_id member is used
 * by the parent application to identify the @c viewer that was terminated. Call
 * this function in the parent application upon receiving a @c
 * NAVIGATOR_INVOKE_VIEWER_STOPPED event to identify the terminated @c viewer.
 * This function doesn't copy data and the returned values are released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_VIEWER_STOPPED event triggered by the
 *              terminated @c viewer.
 *
 * @return The window ID of the terminated @c viewer, @c NULL with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_window_id(bps_event_t *event) BPS_DEPRECATED;

/**
 * @brief Get the key of an invoked @c target from the BPS event
 *
 * The @c navigator_invoke_event_get_target() function extracts the target key
 * of an invoked target application. The target key is an identifier to a
 * target (as stated in its BAR manifest) that had been invoked. Call this
 * function in the application upon receiving a @c
 * NAVIGATOR_INVOKE_TARGET_RESULT event to identify the target that was invoked.
 * This function doesn't copy data and the returned value is released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET_RESULT event triggered by the
 *              invoked target.
 *
 * @return The key of the target that was invoked, NULL with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_target(bps_event_t *event);

/**
 * @brief Get the type of an invoked @c target from the BPS event
 *
 * The @c navigator_invoke_event_get_target() function extracts the target type
 * of an invoked target application. The @c type member allows the target to be
 * identified as an application, service, or card.
 *
 * The possible values that you can receive from this member are:
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_APPLICATION
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_CARD
 *     - @c NAVIGATOR_INVOKE_TARGET_TYPE_SERVICE
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET_RESULT event triggered by the
 *              invoked target.
 *
 * @return The type of the target that was invoked upon success, @c BPS_FAILURE
 *         with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_event_get_target_type(bps_event_t *event);

/**
 * @brief Get the group ID of an invocation source application from the BPS
 *        event
 *
 * The @c navigator_invoke_event_get_group_id() function extracts the group ID
 * of an
 * invocation source application. The group ID is an identifier to the client
 * application that sent the invocation. Call this function in the application
 * upon receiving a @c NAVIGATOR_INVOKE_TARGET event to identify the source
 * of the invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET event triggered by the
 *              source application.
 *
 * @return The group ID of the invocation source application upon success, @c
 *         BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int64_t navigator_invoke_event_get_group_id(bps_event_t *event);

/**
 * @brief Get the error code associated with an invoke request
 *
 * The @c navigator_invoke_event_get_error_code() function returns the
 * error code of invoke request responses. The error code is set when
 * @c navigator_event_get_err() is not @c NULL and @c bps_event_get_code()
 * is one of:
 *  - @c NAVIGATOR_INVOKE_TARGET_RESULT
 *  - @c NAVIGATOR_INVOKE_SET_FILTERS_RESULT
 *  - @c NAVIGATOR_INVOKE_QUERY_RESULT
 *  - @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT
 *
 * @param event The event associated with the invoke request whose
 *              result has an error code set.
 *
 * @return The error code of the request upon success,
 *         @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_error_code(bps_event_t *event);

/**
 * @brief Get the dname of an invocation source application from the BPS event
 *
 * The @c navigator_invoke_event_get_dname() function extracts the dname of an
 * invocation source application. The dname is an identifier to a package, and
 * contains the package name and package ID attributes. Call this function in
 * the application upon receiving a @c NAVIGATOR_INVOKE_TARGET event to
 * identify the source of the invocation.
 * This function doesn't copy data and the returned value is released once the
 * @c bps_get_event() function is called again.
 *
 * @param event The @c NAVIGATOR_INVOKE_TARGET event triggered by
 *              the source application.
 *
 * @return The dname of the invocation source application.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_dname(bps_event_t *event);

/**
 * @brief Sends the set target filters request to the invocation framework.
 *
 * The @c navigator_invoke_set_filters() function sends the set target filters
 * request to the invocation framework.
 *
 * @param id The ID you want to display on the delivery receipt response. This
 *           value must be in numerical format. For example, a valid @c id
 *           would be "42".
 *
 * @param target The target key of the target whose filters are to be set.
 *
 * @param filters The array of filters to be set.
 *
 * @param filters_count The size of the filters array.
 *
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_set_filters(const char *id, const char *target,
        const char *filters[], size_t filters_count);

/**
 * @brief Sends the get target filters invocation request to the invocation
 * framework.
 *
 * The @c navigator_invoke_get_filters() function sends the get target filters
 * invocation request to the invocation framework.
 *
 * @param id The ID you want to display on the delivery receipt response. This
 *           value must be in numerical format. For example, a valid @c id
 *           would be "42".
 *
 * @param target The target key of the target whose filters are to be retrieved.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 * otherwise.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_get_filters(const char *id, const char *target);

/**
 * @brief Get the target of the get target filters invocation result
 *
 * The function doesn't copy the data and the returned value will be released
 * once the @c bps_get_event() function is called again.
 *
 * The @c navigator_invoke_event_get_filters_target()
 * function should be called by the application upon receiving the
 * @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event to extract the
 * target of the get target filters invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event.
 *
 * @return The the target of the get target filters invocation result.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_filters_target(
        bps_event_t *event);

/**
 * @brief Get the filters count of the get target filters invocation result
 *
 * The function doesn't copy the data and the returned value will be released
 * once the @c bps_get_event() function is called again.
 *
 * The
 * @c navigator_invoke_event_get_filters_count()
 * function should be called by the application upon receiving the
 * @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event to extract the
 * filters count of the get target filters invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT
 * event.
 *
 * @return The the filters count of the get target filters invocation result.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API int navigator_invoke_event_get_filters_count(bps_event_t *event);

/**
 * @brief Get the filter of the get target filters invocation result
 *
 * The function doesn't copy the data and the returned value will be released
 * once the @c bps_get_event() function is called again.
 *
 * The @c navigator_invoke_event_get_filter()
 * function should be called by the application upon receiving the
 * @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event to extract the
 * filter of the get target filters invocation.
 *
 * @param event The @c NAVIGATOR_INVOKE_GET_FILTERS_RESULT event.
 *
 * @param index The index of the filter in the filters array
 *
 * @return The filter at the index from the get target filters invocation result.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API const char* navigator_invoke_event_get_filter(bps_event_t *event,
        int index);

/**
 * @brief Request that the list item specified by @c selection is invoked to
 * replace the current list item that this application belongs to
 *
 * The @c navigator_invoke_select_list_item() function sends a request to the
 * Navigator to invoke the list item @c selection from the list that this
 * application belongs to.
 *
 * The requesting application must be launched as an invoke list item. Success
 * is determined by whether the request has been sent.
 *
 * @param selection  The list item to invoke. This is either @c
 *                   NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_NEXT to invoke the
 *                   next list item or @c
 *                   NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_PREVIOUS to invoke
 *                   the previous list item. @c
 *                   NAVIGATOR_INVOKE_LIST_CURSOR_DIRECTION_UNSPECIFIED is
 *                   unsupported.
 *
 * @return @c BPS_SUCCESS upon success, @c BPS_FAILURE with @c errno set
 *         otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_select_list_item(
        navigator_invoke_list_cursor_direction_t selection);

/**
 * @brief Get the list id of @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED and
 * @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED events
 *
 * The @c navigator_invoke_event_get_list_id() function returns the list ID
 * of the list that the event corresponds to.
 *
 * @param event The @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED or
 *              @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED event.
 *
 * @return list ID upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_list_id(bps_event_t *event);

/**
 * @brief Get the direction of movement from
 * @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED events
 *
 * The @c navigator_invoke_event_get_list_cursor_direction() function returns
 * the direction in which the list item cursor should move.
 *
 * @param event The @c NAVIGATOR_INVOKE_LIST_CURSOR_MOVED event.
 *
 * @return The direction of movement in the list upon success,
 *         @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_list_cursor_direction(bps_event_t *event);

/**
 * @brief Get which list item to select from
 * @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED events
 *
 * The @c navigator_invoke_event_get_list_item_selection() function returns
 * which list item to select.
 *
 * @param event The @c NAVIGATOR_INVOKE_LIST_ITEM_SELECTED event.
 *
 * @return The @c #navigator_invoke_list_cursor_direction_t of the list item to
 *         select upon success, @c BPS_FAILURE with @c errno set otherwise.
 *
 * @since BlackBerry 10.2.0
 */
BPS_API int navigator_invoke_event_get_list_item_selection(bps_event_t *event);

/**
 * @brief Convert a percent-encoded file URI to a file path
 *
 * The @c navigator_invoke_uri_to_local_path() function can be called to convert
 * file URIs retrieved from invocation events to file paths. This function
 * expects @c uri to start with "file:///", and handles percent-encoded URIs.
 *
 * This function allocates memory that needs to be freed by the @c bps_free()
 * function.
 *
 * For example:
 * @code
 *   char *file_path =
 *        navigator_invoke_uri_to_local_path("file:///path/to/some%20file.txt");
 *
 *   // file_path is "/path/to/some file.txt"
 *
 *   bps_free(file_path);
 * @endcode
 *
 * @param uri The URI encoded file path.  It needs to start with "file:///".
 *
 * @return The local file path upon success; NULL with @c errno set upon
 *         failure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API char* navigator_invoke_uri_to_local_path(const char* uri);

/**
 * @brief Convert an absolute file path to a percent-encoded file URI
 *
 * The @c navigator_invoke_local_path_to_uri() function should be called by the
 * application to ensure that a file path is converted to a percent-encoded file
 * URI for use with invocation functions. 
 *
 * This function expects @c path to start with "/".
 *
 * The function allocates memory that needs to be freed by the @c bps_free()
 * function.
 *
 * For example:
 * @code
 *   char *file_uri =
 *                navigator_invoke_local_path_to_uri("/path/to/some file.txt");
 *
 *   // file_uri is "file:///path/to/some%20file.txt"
 *
 *   bps_free(file_uri);
 * @endcode
 *
 * @param path The absolute file path.  It needs to start with "/".
 *
 * @return A percent-encoded file URI that corresponds to @c path upon success;
 *         NULL with @c errno set upon failure.
 *
 * @since BlackBerry 10.0.0
 */
BPS_API char* navigator_invoke_local_path_to_uri(const char* path);

__END_DECLS

#endif // include guard
