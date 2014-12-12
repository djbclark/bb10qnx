/*
 * $QNXLicenseC:
 * Copyright 2009, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */


#if !defined(MM_RENDERER__EVENTS_H_INCLUDED)
#define MM_RENDERER_EVENTS_H_INCLUDED

/** @file events.h
 *  mm-renderer event API functions
 *  @ingroup EventAPI Event API
 */

#if !defined(MM_RENDERER_H_INCLUDED)
#include <mm/renderer.h>
#endif

__BEGIN_DECLS

/**
 * @addtogroup EventAPI Event API
 */
/*@{*/

/**
 *  The event type.
 */
typedef enum mmr_event_type {
		MMR_EVENT_NONE,     ///< No pending events.
		MMR_EVENT_ERROR,    ///< Playback has stopped due to an error or EOF.
		MMR_EVENT_STATE,    ///< State or speed change, other than an error or EOF.
		MMR_EVENT_OVERFLOW, ///< Some state changes lost; the event contains most the recent state.
		MMR_EVENT_WARNING,  ///< Warning event.
		MMR_EVENT_STATUS,   ///< Status update (position, buffer level, etc).
		MMR_EVENT_METADATA, ///< Metadata update for the attached input, or one track referenced by the attached input
				    ///< (such as a playlist entry).
		MMR_EVENT_PLAYLIST, ///< Playlist window update.
		MMR_EVENT_INPUT,    ///< An input has been attached or detached, or input parameters changed.
		MMR_EVENT_OUTPUT,   ///< An output has been attached or detached, or output parameters changed.
		MMR_EVENT_CTXTPAR,  ///< Context parameters have changed.
		MMR_EVENT_TRKPAR,   ///< Track parameters for an individual track or a playlist entry have changed.
		MMR_EVENT_OTHER,    ///< None of the above, but something has changed. You can typically ignore this event type.
} mmr_event_type_t;

/**
 *  The context state
 */
typedef enum mmr_state {
    MMR_STATE_DESTROYED,  ///< The context has been destroyed.
    MMR_STATE_IDLE,       ///< The context has no input.
    MMR_STATE_STOPPED,    ///< The context has an input but is not playing.
    MMR_STATE_PLAYING,    ///< The context is playing or paused.
} mmr_state_t;

/**
 *  The event structure.
 */
typedef struct mmr_event {
	mmr_event_type_t    type;         ///< The event type
	mmr_state_t         state;        ///< The context state (valid even when type is MMR_EVENT_NONE)
	int                 speed;        ///< The playback speed (0 means paused)

	union mmr_event_details {
		struct mmr_event_state {
			mmr_state_t oldstate;     ///< The state before the event
			int oldspeed;             ///< The speed before the event
		}               state;        ///< When type is STATE
		struct mmr_event_error {
			mmr_error_info_t info;    ///< The error information
		}               error;        ///< When type is ERROR
		struct mmr_event_warning {
			const char *str;          ///< The warning string, as a C string
			const strm_string_t *obj; ///< The warning string, as a strm_string_t (dictionary string)
		}               warning;      ///< When type is WARNING
		struct mmr_event_metadata {
			unsigned index;           ///< The playlist index for playlist-related events; otherwise, zero
		}               metadata;     ///< When type is METADATA
		struct mmr_event_trkparam {
			unsigned index;           ///< The playlist index
		}               trkparam;     ///< When type is TRKPAR
		struct mmr_event_playlist {
			unsigned start;           ///< The index of the first item in the playlist window
			unsigned end;             ///< The index of the last item in the playlist window
			unsigned length;          ///< The playlist length
		}               playlist;     ///< When type is PLAYLIST
		struct mmr_event_output {
			unsigned id;              ///< Output ID
		}               output;       ///< When type is OUTPUT
	} details;

	const strm_string_t *pos_obj;     ///< The playback position when the event occurred, stored as a shareable string,
					  ///< for STATUS, ERROR, and WARNING events; otherwise NULL.
	const char          *pos_str;     ///< The playback position when the event occurred, stored as a string,
					  ///< for STATUS, ERROR, and WARNING events; otherwise NULL.
	const strm_dict_t   *data;        ///< The full set of mm-renderer properties reported by the event, stored in a
					  ///< dictionary object. When this field is NULL, the set of properties no longer
					  ///< exists; for example, the input parameters, URL, and type are deleted when
					  ///< the input is detached.
	const char          *objname;     ///< The name of the internal mm-renderer object that updated the dictionary in
                                      ///< response to user activity or a playback state change.
	void                *usrdata;     ///< The user data associated with the object that manages the dictionary
                                      ///< referenced in the event information.
} mmr_event_t;

/**
 *  Get the next available event.
 *
 *  @param ctxt A context handle
 *  @return A pointer to an event, or NULL on error (check errno)
 */
const mmr_event_t *mmr_event_get( mmr_context_t *ctxt );

/**
 *  Set a pointer to the user data to associate with the dictionary returned with events that affect this context.
 *
 *  @param ctxt A context handle
 *  @param usrdata The pointer to associate with the object returned in the last event.
 *  @return 0 on success, or -1 if the event was a MMR_EVENT_NONE or a deletion.
 */
int mmr_event_data_set( mmr_context_t *ctxt, void *usrdata );


/**
 *  Wait until an event is available.
 *
 *  @param ctxt A context handle
 *  @return 0 on success, or -1 on error (check errno).
 */
int mmr_event_wait( mmr_context_t *ctxt );

/**
 *  Arm a sigevent to be delivered when a new event becomes available.
 *
 *  @param ctxt A context handle
 *  @param sev A sigevent to send; set to NULL to disarm
 *  @return >0 if already available (sigevent is not armed),
 *           0 on success, or -1 on error (check errno).
 */
int mmr_event_arm( mmr_context_t *ctxt, struct sigevent const *sev );


/*@}*/

__END_DECLS

#endif

__SRCVERSION("$URL$ $Rev$")
