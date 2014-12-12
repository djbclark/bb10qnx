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


#if !defined(MM_RENDERER_H_INCLUDED)
#define MM_RENDERER_H_INCLUDED

/** @file renderer.h
 *  mm-renderer API functions
 *  @ingroup ClientAPI Client API
 */

#if defined(MM_RENDERER_PLUGIN_HEADERS_INCLUDED)
#error "Please don't mix plugin headers with <mm/renderer.h>"
#endif

#if !defined(MM_RENDERER_TYPES_H_INCLUDED)
#include <mm/renderer/types.h>
#endif

__BEGIN_DECLS

/** 
 * @addtogroup ClientAPI Client API
 */
/*@{*/

/**
 *  @brief The mm-renderer connection handle type.
 */
typedef struct mmr_connection mmr_connection_t;

/**
 *  @brief The mm-renderer context handle type.
 */
typedef struct mmr_context mmr_context_t;

/**
 *  @brief Connect to mm-renderer.
 *
 *  @details Connect to mm-renderer.
 *
 *  @param name The name of the mm-renderer service to connect to (use NULL for the default service)
 *  @return a connection handle, or NULL on error (errno is set)
 */
mmr_connection_t *mmr_connect( const char *name );

/**
 *  @brief Disconnect from mm-renderer.
 *
 *  @details Disconnect from mm-renderer.
 *  Closes any existings context handles, as if by calling
 *  either mmr_context_destroy() or mmr_context_close(),
 *  depending on whether the handle was created
 *  by mmr_context_create() or mmr_context_open().
 *
 *  @param connection An mm-renderer connection handle
 */
void mmr_disconnect( mmr_connection_t *connection );

/**
 *  @brief Open an existing context.
 *
 *  @details Open an existing context and return its handle.
 *
 *  @param connection An mm-renderer connection handle
 *  @param name The context name
 *  @return A handle on success, or a null pointer on failure (check errno)
 */
mmr_context_t *mmr_context_open( mmr_connection_t *connection, const char *name );

/**
 *  @brief Create a context.
 *
 *  @details Create a context and return its handle.
 *  Fails if a context with that name already exists.
 *  The name must be a valid filename and will show up in the pathname
 *  space, with its file mode flags set as specified by the mode argument. 
 *
 *  @param connection An mm-renderer connection handle
 *  @param name The name of the context.  This must be a valid filename
 *              and will show up in the pathname space as a directory.
 *  @param flags Must be zero.  No flags are defined for now.
 *  @param mode File permission flags for the new context directory
 *  @return A handle on success, or a null pointer on failure (check errno)
 */
mmr_context_t *mmr_context_create( mmr_connection_t *connection, const char *name, unsigned flags, mode_t mode );


/**
 *  @brief Destroy a context.
 *
 *  @details Destroy the context the handle refers to and close the handle.
 *  Implicitly stops any playback and detaches any inputs or outputs.
 *  If any other handles to this context still exist,
 *  attempts to use them to attach any inputs or outputs will fail.
 *
 *  @param ctxt A context handle
 *  @return Zero on success, -1 on failure (check errno).
 *          The handle becomes invalid either way.
 */
int mmr_context_destroy( mmr_context_t *ctxt );

/**
 *  @brief Close a context.
 *
 *  @details Close and invalidate the context handle.
 *  Depending on the configuration, the context the handle refers to 
 *  might also be destroyed.
 *
 *  @param ctxt A context handle
 *  @return Zero on success, -1 on failure (check errno).
 *          The handle becomes invalid either way.
 *  @retval EPERM -- the server destroyed your context
 *                   because it is configured to disallow "orphaned" contexts
 *                   and this handle was created using mmr_context_create().
 */
int mmr_context_close( mmr_context_t *ctxt );

/**
 *  @brief Get the context path.
 *
 *  @details Get the context path.
 *  Builds the full path to the context PPS directory.
 *  If the function fails or the buffer is too small,
 *  and len is nonzero, buf is set to an empty string.
 *
 *  @param ctxt A context handle
 *  @param buf The buffer to store the path in (not used if len==0)
 *  @param len The length of the buffer
 *  @return The full length of the path (not counting the null terminator),
 *          or -1 on on failure (use mmr_error_info())
 */
ssize_t mmr_context_path( mmr_context_t *ctxt, char buf[], size_t len );

/**
 *  @brief Get error information.
 *
 *  @details Get error information.
 *  Returns a pointer to an internal buffer containing error information
 *  about the most recent API call using the same context handle.
 *  The pointer and the error information it points to are only valid
 *  until another API call is made.
 *
 *  @param ctxt A context handle
 *  @return Pointer to error information,
 *          or a null pointer if the most recent API call succeeded
 */
const mmr_error_info_t *mmr_error_info( mmr_context_t *ctxt );

/**
 *  @brief Set context parameters.
 *
 *  @details Set parameters associated with the context.
 *  These might be implementation-specific.
 *
 *  @param ctxt A context handle
 *  @param parms A dictionary object containing the parameters to set
 *               (handle gets consumed by this call, even on failure)
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_context_parameters( mmr_context_t *ctxt, strm_dict_t *parms );

/**
 *  @brief Attach an input.
 *
 *  @details Attach an input file, device, or playlist.
 *  If the context already has an input, it is detached first.
 *
 *  @param ctxt A context handle
 *  @param url The URL of the new input
 *  @param type The type of the input ("playlist", "track", "dvd", etc)
 *             or null for auto-detect (may not be supported for all URL types)
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_input_attach( mmr_context_t *ctxt, const char *url, const char *type );

/**
 *  @brief Detach an input.
 *
 *  @details Detach an input.
 *  If the context is playing, it is stopped first.
 *  If there is no input already, this is a no-op.
 *
 *  @param ctxt A context handle
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_input_detach( mmr_context_t *ctxt );

/**
 *  @brief Set input parameters.
 *
 *  @details Set parameters associated with the attached input media.
 *  This is generally input-dependent and may include things like
 *  a repeat or random mode for devices, perhaps parental control level for DVDs, etc.
 *  These are not inherited when a new input is attached.
 *  (Note that an individual playlist item is not considered an "input"
 *  -- the playlist as a whole is.)
 *
 *  @param ctxt A context handle
 *  @param parms A dictionary object containing the parameters to set
 *               (handle gets consumed by this call, even on failure)
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_input_parameters( mmr_context_t *ctxt, strm_dict_t *parms );

/**
 *  @brief Attach an output.
 *
 *  @details Attach an output and return its output ID
 *  (a small non-negative integer, unique for this context).
 *  An output can be an audio or video device,
 *  a combined audio/video device (such as a DSP directly
 *  connected to output hardware), or a file.
 *  The types of outputs attached to a context may affect
 *  the set of operations that the context will allow.
 *  For instance, when "playing" to a file (i.e. ripping),
 *  seeking or trick play may not be supported.
 *
 *  Note that even though the API allows requesting multiple outputs of the same type,
 *  this may not be supported by all player module implementations.
 *  Attaching or detaching outputs while the context has an input may not be supported, either.
 *
 *  @param ctxt A context handle
 *  @param url The URL of the new output
 *  @param type The output type ("audio", "video", etc.)
 *  @return A non-negative output ID on success, -1 on failure (use mmr_error_info())
 */
int mmr_output_attach( mmr_context_t *ctxt, const char *url, const char *type );

/**
 *  @brief Detach an output.
 *
 *  @details Detach an output.
 *
 *  @param ctxt A context handle
 *  @param output_id An output ID
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_output_detach( mmr_context_t *ctxt, unsigned output_id );

/**
 *  @brief Set output parameters.
 *
 *  @details Set various parameters for the specified output device.
 *      * For audio outputs: volume, audio stream selection.
 *      * For video outputs: audio and subtitle stream selection, scaling, etc.
 *      * For file outputs: the encoding, metadata to be saved to the file.
 *      * For a timeshifting buffer: its size, encoding, and probably a lot of other details.
 *
 *  Note that even though the API allows requesting the playback of different streams
 *  to different outputs of the same type, this may not be supported by all player module 
 *  implementations.
 *
 *  @param ctxt A context handle
 *  @param output_id An output ID
 *  @param parms A dictionary object containing the parameters to set
 *               (handle gets consumed by this call, even on failure)
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_output_parameters( mmr_context_t *ctxt, unsigned output_id, strm_dict_t *parms );

/**
 *  @brief Start playing.
 *
 *  @details Start playing. A no-op if already playing.
 *
 *  @param ctxt A context handle
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_play( mmr_context_t *ctxt );

/**
 *  @brief Stop playing.
 *
 *  @details Stop playing. A no-op if already stopped.
 *  Depending on the input media, stopping the playback may cause the
 *  playing position to change or even become indeterminate. Unless you know
 *  the behaviour of the media being played, make sure to seek to a known
 *  position before restarting the playback.
 *
 *  @param ctxt A context handle
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_stop( mmr_context_t *ctxt );

/**
 *  @brief Seek to a position.
 *
 *  @details Seek to a position.
 *  The exact format of the position string depends on the input media.
 *  For playlists, the position can be specified as two decimal numbers
 *  separated by a colon (such as "2:1200"), where the first number
 *  specifies the playlist index and the second is the number of
 *  milliseconds from the beginning of the specified playlist item.
 *
 *  @param ctxt A context handle
 *  @param position The position to seek to, in a media-specific format
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_seek( mmr_context_t *ctxt, const char *position );

/**
 *  @brief Set the play speed, in units of 1/1000 of normal speed.
 *
 *  @details Set the play speed, in units of 1/1000 of normal speed.
 *  If the context is playing (including paused), the new speed is aplied
 *  immediately; otherwise it is stored in the context and applied the next
 *  time mmr_play() is called.
 *
 *  Depending on the input media, speeds other than the normal speed (1000)
 *  may be unsupported or forbidden, either completely or only for some
 *  portions of the media. (For instance: a playlist may contain some tracks
 *  that don't support trick play; some devices have only one fast-forward
 *  speed; and DVD forbids pausing or fast-forwarding through menus and some
 *  portions of titles.)
 *  
 *  If an mmr_speed_set() call requests a trick-play speed (negative, slower
 *  than normal, or faster than normal) and the exact value is completely
 *  unsupported by the current input, the speed may be rounded to a
 *  supported value in the same category (negative vs. slow vs. fast). If
 *  the entire category is unsupported, the call fails.
 *  
 *  If the call was made during playback, and the speed (after the rounding
 *  described above) is unsupported or forbidden at the current playing
 *  position, the speed changes to an allowed value, and the call succeeds.
 *  A similar speed change may occur in the mmr_play() call, based on the
 *  curent speed and position, and during playback, if a position is reached
 *  (by playing or by an explicit seek request) where the current play speed
 *  is unsupported or forbidden. The navigation rules for the input media
 *  may also specify other circumstances that cause the speed to change to
 *  normal during playback. In particular, when playing a simple track or a
 *  playlist, it is configurable whether the speed reverts to normal at
 *  track boundaries.
 *
 *  @param ctxt A context handle
 *  @param speed The new speed
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_speed_set( mmr_context_t *ctxt, int speed );

/**
 *  @brief Send a remote control command to the context.
 *
 *  @details Send a remote control command to the context.
 *  Some commands expect parameters, separated from the command name with a
 *  colon character.  
 *
 *  @param ctxt A context handle
 *  @param cmd The command
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_command_send( mmr_context_t *ctxt, const char *cmd );

/**
 *  @brief Set a new playlist.
 *
 *  @details Set a new playlist without interrupting playback.
 *  This function can only be used during playback of a playlist (including
 *  when it's paused, but not stopped).
 *  It requires that the new playlist contains the currently playing track
 *  at position n+delta, where n is its position on the old playlist.
 *
 *  @param ctxt A context handle
 *  @param url The URL of a new playlist
 *  @param delta The difference between the position of the current track on the two lists
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_list_change( mmr_context_t *ctxt, const char *url, int delta );

/**
 *  Set track parameters.
 *  This function can only be used when the input is a playlist.
 *
 *  @param ctxt A context handle
 *  @param index Zero to set the default parameters, or an index within the current playlist window
 *  @param parms The parameters, or NULL to reset to the default
 *               (handle gets consumed by this call, even on failure)
 *  @return Zero on success, -1 on failure (use mmr_error_info())
 */
int mmr_track_parameters( mmr_context_t *ctxt, unsigned index, strm_dict_t *parms );

/*@}*/

__END_DECLS

#endif

__SRCVERSION("$URL$ $Rev$")
