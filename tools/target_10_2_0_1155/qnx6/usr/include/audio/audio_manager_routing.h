#ifndef _AUDIO_MANAGER_ROUTING_H_INCLUDED
#define _AUDIO_MANAGER_ROUTING_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <limits.h>
#if SND_LIB_MAJOR == 1
#include <alsa/asoundlib.h>
#else
#include <sys/asoundlib.h>
#endif
#include <audio/audio_manager_device.h>

/**
 * @file audio_manager_routing.h
 *
 * @brief Definitions for supporting audio routing configurations.
 *
 * The audio manager maintains the audio routing logic based on registered audio
 * sources. This file defines routing properties and provides functions for
 * them.
 *
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief Names for audio types.
 */
#ifndef AUDIO_TYPE_NAMES_EXTENDED
#define AUDIO_TYPE_NAMES_EXTENDED
#endif

/**
 * @brief Audio type names.
 */
#define AUDIO_TYPE_NAMES        \
{                               \
    "voice",                    \
    "ringtone",                 \
    "voicerecognition",         \
    "texttospeech",             \
    "videochat",                \
    "voicerecording",           \
    "multimedia",               \
    "inputfeedback",            \
    "default",                  \
    "alert",                    \
    "voicetones",               \
    "soundeffect",              \
    "pushtotalk",               \
    "reserved_0",               \
    "cmas",                     \
    "alarm",                    \
    "screenreader",             \
    AUDIO_TYPE_NAMES_EXTENDED   \
}

/**
 * @brief Supported audio types.
 *
 * This enumeration defines the supported audio types.
 */
typedef enum {
    /**
     * The audio type used by voice audio sources.
     */
    AUDIO_TYPE_VOICE,
    /**
     * The audio type used by ringtone audio sources.
     */
    AUDIO_TYPE_RINGTONE,
    /**
     * The audio type used by voice recognition audio sources.
     */
    AUDIO_TYPE_VOICE_RECOGNITION,
    /**
     * The audio type used by text-to-speech audio sources.
     */
    AUDIO_TYPE_TEXT_TO_SPEECH,
    /**
     * The audio type used by video chat audio sources.
     */
    AUDIO_TYPE_VIDEO_CHAT,
    /**
     * The audio type used by voice recording audio sources.
     */
    AUDIO_TYPE_VOICE_RECORDING,
    /**
     * The audio type used by multimedia audio sources.
     */
    AUDIO_TYPE_MULTIMEDIA,
    /**
     * The audio type used by user input feedback.
     */
    AUDIO_TYPE_INPUT_FEEDBACK,
    /**
     * The audio type used by default audio sources.
     */
    AUDIO_TYPE_DEFAULT,
    /**
     * The audio type used by alert audio sources.
     */
    AUDIO_TYPE_ALERT,
    /**
     * The audio type used by voice tone audio sources.
     */
    AUDIO_TYPE_VOICE_TONES,
    /**
     * The audio type used by high priority sound effect.
     */
    AUDIO_TYPE_SOUND_EFFECT,
    /**
     * The audio type used by push-to-talk.
     */
    AUDIO_TYPE_PUSH_TO_TALK,
    /**
     * The reserved audio type 0.
     */
    AUDIO_TYPE_RESERVED_0,
    /**
     * The audio type used by CMAS emergency broadcast systems.
     */
    AUDIO_TYPE_CMAS,
    /**
     * The audio type used by alarms.
     */
    AUDIO_TYPE_ALARM,
    /**
     * The audio type used by screen reader for accessibility.
     */
    AUDIO_TYPE_SCREEN_READER,
    /**
     * The total number of all audio types.
     */
    AUDIO_TYPE_COUNT,
    /**
     * The audio type is unchanged if the given value is specified.
     */
    AUDIO_TYPE_UNCHANGED = INT_MAX,
} audio_manager_audio_type_t;

/**
 * @brief Audio runtime names.
 */
#define AUDIO_RUNTIME_NAMES     \
{                               \
    "native",                   \
    "android"                   \
}


/**
 * @brief Supported audio runtimes.
 *
 * This enumeration defines the supported audio runtimes.
 */
typedef enum {
    /**
     * The audio type used by clients designed for QNX directly.
     */
    AUDIO_RUNTIME_NATIVE,
    /**
     * The audio type used by clients designed for Android.
     */
    AUDIO_RUNTIME_ANDROID,
    /**
     * The total number of supported runtimes.
     */
    AUDIO_RUNTIME_COUNT,
} audio_manager_runtime_t;


/**
 * @brief Supported reset conditions of the routing preference settings.
 *
 * This enumeration defines the supported reset conditions of the routing
 * preferences set by @c audio_manager_set_handle_type().
 */
typedef enum {
    /**
     * The preferences are never reset.
     */
    SETTINGS_NEVER_RESET                                    = 0,
    /**
     * The preferences are reset when any device disconnects.
     */
    SETTINGS_RESET_ON_DEVICE_DISCONNECTION                  = 1,
    /**
     * The preferences are reset when any device connects.
     */
    SETTINGS_RESET_ON_DEVICE_CONNECTION                     = (1<<1),
    /**
     * The preferences are reset when the preferred device disconnects.
     */
    SETTINGS_RESET_ON_PREFERRED_DEVICE_DISCONNECTION        = (1<<2),
    /**
     * The preferences are reset when the higher priority device connects.
     */
    SETTINGS_RESET_ON_HIGHER_PRIORITY_DEVICE_CONNECTION     = (1<<3),
} audio_manager_settings_reset_condition_t;

/**
 * @brief Get the audio handle runtime given the name of the runtime
 *
 * The @c audio_manager_get_runtime_from_name() function returns the audio
 * manager handle runtime given the name of the runtime.
 *
 * @param runtime_name The name of the runtime to query.
 *
 * @return The audio manager handle runtime.
 */
audio_manager_runtime_t audio_manager_get_runtime_from_name( const char * runtime_name );

/**
 * @brief Get the name of an audio manager runtime
 *
 * The @c audio_manager_get_name_from_runtime() function returns the name of
 * an audio manager runtime.
 *
 * @param runtime The audio manager runtime to query.
 *
 * @return The name of the audio manager runtime from @c AUDIO_RUNTIME_NAMES.
 */
const char* audio_manager_get_name_from_runtime( audio_manager_runtime_t runtime );

/**
 * @brief Get the audio handle type given the name of the type
 *
 * The @c audio_manager_get_type_from_name() function returns the audio
 * manager handle type given the name of the type.
 *
 * @param type_name The name of the type to query.
 *
 * @return The audio manager handle type.
 */
audio_manager_audio_type_t audio_manager_get_type_from_name( const char * type_name );

/**
 * @brief Get the name of an audio manager type
 *
 * The @c audio_manager_get_name_from_type() function returns the name of
 * an audio manager type.
 *
 * @param type The audio manager type to query.
 *
 * @return The name of the audio manager type from @c AUDIO_TYPE_NAMES.
 */
const char* audio_manager_get_name_from_type( audio_manager_audio_type_t type );

/**
 * @brief Get the audio manager handle for a given audio type
 *
 * The @c audio_manager_get_handle() function returns the audio
 * manager handle of a given type with a flag indicating whether
 * the handle is immediately activated or not.
 *
 * @param type The type of the audio manager handle to query.
 * @param caller_pid The ID of the process that the audio manager handle
 * is allocated for (0 = the current process ID).
 * @param start_suspended True, if the audio manager handle is suspended
 * after allocation; false, otherwise.
 * @param audioman_handle The audio manager handle allocated.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_handle( audio_manager_audio_type_t type,
                              pid_t caller_pid,
                              bool start_suspended,
                              unsigned int * audioman_handle );

/**
 * @brief Get the audio manager handle for a given audio type
 *
 * The @c audio_manager_get_handle_runtime() function returns the audio
 * manager handle of a given type with a flag indicating whether
 * the handle is immediately activated or not.
 * 
 * This function should be used only by different runtimes which implement
 * their own ducking rules. Applications should not use this function directly.
 *
 * @param type The type of the audio manager handle to query.
 * @param caller_pid The ID of the process that the audio manager handle
 * is allocated for (0 = the current process ID).
 * @param start_suspended True, if the audio manager handle is suspended
 * after allocation; false, otherwise.
 * @param audioman_handle The audio manager handle allocated.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_handle_for_runtime(
                                audio_manager_runtime_t runtime,
                                audio_manager_audio_type_t type,
                                pid_t caller_pid,
                                bool start_suspended,
                                unsigned int * audioman_handle );

/**
 * @brief Get an audio manager handle that is an alias of
 * another audio manager handle
 *
 * The @c audio_manager_get_alias_handle() function returns the
 * alias of a given audio manager handle. An alias audio manager
 * handle has no audio policy effect.
 *
 * @param target_audioman_handle The target audio manager handle that
 * the alias is created from.
 * @param audioman_handle The audio manager handle allocated.
 *
 * @return @c EOK upon success, negative @c errno upon failure
 */
int audio_manager_get_alias_handle( unsigned int target_audioman_handle,
                                    unsigned int * audioman_handle );
/**
 * @brief Retrieve the audio type of a given audio manager handle
 *
 * The @c audio_manager_get_handle_type() function gets the
 * audio type of a given audio manager handle and the
 * overrides of the default audio type routing policy
 * for the preferred output and input audio devices.
 *
 * @param audioman_handle The audio manager handle that the new
 * type is applied to.
 * @param type The audio type that has been set on the given
 * audio manager handle.
 * @param pref_output The preferred output routing of the handle.
 * @param pref_input The preferred input routing of the handle.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_handle_type( unsigned int audioman_handle,
                                   audio_manager_audio_type_t *type,
                                   audio_manager_device_t *pref_output,
                                   audio_manager_device_t *pref_input );

/**
 * @brief Set the audio type of a given audio manager handle
 *
 * The @c audio_manager_set_handle_type() function sets the
 * audio type of a given audio manager handle and gives the
 * option to override the default audio type routing policy
 * by specifying the preferred output and input audio devices.
 *
 * @param audioman_handle The audio manager handle that the new
 * type is applied to.
 * @param type The new audio type to be set to the given
 * audio manager handle. If @c AUDIO_TYPE_UNCHANGED is specified,
 * the audio type is unchanged.
 * @param pref_output The preferred output routing of the new
 * audio type. If @c AUDIO_DEVICE_UNCHANGED is specified, the
 * preferred output device is unchanged.
 * @param pref_input The preferred input routing of the new
 * audio type. If @c AUDIO_DEVICE_UNCHANGED is specified, the
 * preferred input device is unchanged.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_handle_type( unsigned int audioman_handle,
                                   audio_manager_audio_type_t type,
                                   audio_manager_device_t pref_output,
                                   audio_manager_device_t pref_input );

/**
 * @brief Set the reset condition of the preferred input and output
 *
 * The @c audio_manager_set_handle_routing_conditions() function sets the
 * reset conditions of the preferred output and input routing path that are
 * specified with @c audio_manager_set_handle_type().
 *
 * @param audioman_handle The audio manager handle that the conditions apply to.
 * @param routing_preference_reset_conditions The bitmask of @c
 * audio_manager_settings_reset_condition_t that specifies the condition(s) that
 * the audio routing preference(s) gets set to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_handle_routing_conditions(
        unsigned int audioman_handle,
        int routing_preference_reset_conditions );


/**
 * @brief Set the keep-alive status for the handle
 *
 * The @c audio_manager_set_handle_keep_alive() function sets the
 * keep-alive status of the handle. When audio is being routed according to this
 * handle, the device being routed to will be kept ready, at a possible cost
 * in power, even when no audio is being played or recorded.
 *
 * @param audioman_handle The audio manager handle that the keep-alive status
 * applies to.
 * @param A bitmask of @c AUDIO_INPUT or @c AUDIO_OUTPUT to control keep-alive
 * direction. An empty bitmask will disable keep-alive.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_handle_keep_alive(
        unsigned int audioman_handle,
        int direction );


/**
 * @brief Get the status of the given audio manager handle
 *
 * The @c audio_manager_get_handle_status() function returns the
 * activation status and binding status of a given audio manager handle.
 *
 * @param audioman_handle The audio manager handle to query.
 * @param suspended True, if the audio manager handle is suspended; false,
 * otherwise.
 * @param bound True, if the audio manager handle is bound to a PCM handle;
 * false, otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_handle_status( unsigned int audioman_handle,
                                     bool * suspended,
                                     bool * bound );

/**
 * @brief Activate the given audio manager handle
 *
 * The @c audio_manager_activate_handle() function activates the
 * given audio manager handle if it is not already bound with a
 * PCM handle.
 *
 * @param audioman_handle The audio manager handle that is being
 * activated.

 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_activate_handle( unsigned int audioman_handle );


/**
 * @internal
 * @brief Activate the given audio manager handle and refresh audio
 * ducking settings
 *
 * The @c audio_manager_activate_bound_handle() function activates the
 * given audio manager handle if it is already bound with a PCM handle
 * by @c snd_pcm_set_audioman_handle.
 * 
 * @param audioman_handle The audio manager handle that is being
 * activated.
 * @param refresh_ducking True, if refresh ducking should be enabled;
 * false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_activate_bound_handle( unsigned int audioman_handle,
                                         bool refresh_ducking );


/**
 * @brief Suspend the given audio manager handle
 *
 * The @c audio_manager_suspend_handle() function suspends the
 * given audio manager handle if it is not already bound with a
 * PCM handle.
 *
 * @param audioman_handle The audio manager handle that is being
 * suspended.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_suspend_handle( unsigned int audioman_handle );

/**
 * @internal
 * @brief Activate the given audio manager handle and refresh audio
 * ducking settings
 *
 * The @c audio_manager_activate_bound_handle() function activates the
 * given audio manager handle if it is already bound with a PCM handle
 * by @c snd_pcm_set_audioman_handle.
 *
 * @param audioman_handle The audio manager handle that is being
 * activated.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_suspend_bound_handle( unsigned int audioman_handle );

/**
 * @brief Free the given audio manager handle
 *
 * The @c audio_manager_free_handle() function frees the
 * given audio manager handle.
 *
 * @param audioman_handle The audio manager handle that is being
 * freed.

 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_free_handle( unsigned int audioman_handle );

#if SND_LIB_MAJOR == 0
/**
 * @brief Open a preferred PCM channel with a given audio type
 *
 * The @c audio_manager_snd_pcm_open_preferred() function combines
 * the @c snd_pcm_open_preferred() and @c audio_manager_get_handle() functions
 * and allows the allocation of a specific audio type PCM channel in
 * one step.
 *
 * @param type The audio type of the PCM channel being allocated.
 * @param handle The handle of the PCM channel opened.
 * @param audioman_handle The audio manager handle allocated to the PCM channel.
 * @param rcard The audio card used to open the PCM channel.
 * @param rdevice The audio device used to open the PCM channel.
 * @param mode The PCM channel mode defined in @c asoundlib.h.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_snd_pcm_open_preferred(audio_manager_audio_type_t type, snd_pcm_t **handle, unsigned int *audioman_handle, int *rcard, int *rdevice, int mode);

/**
 * @brief Open a PCM channel with a given audio type, given
 * audio card, and device
 *
 * The @c audio_manager_snd_pcm_open() function combines
 * the @c snd_pcm_open() and @c audio_manager_get_handle() functions
 * and allows the allocation of a specific audio type PCM channel in
 * one step.
 *
 * @param type The audio type of the PCM channel being allocated.
 * @param handle The handle of the PCM channel opened
 * @param audioman_handle The audio manager handle allocated to the PCM channel.
 * @param card The audio card to be used to open the PCM channel.
 * @param device The audio device to be used to open the PCM channel.
 * @param mode The PCM channel mode defined in @c asoundlib.h.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_snd_pcm_open(audio_manager_audio_type_t type, snd_pcm_t **handle, unsigned int *audioman_handle, int card, int device, int mode);

/**
 * @brief Open a PCM channel with a given audio type and a given
 * name of the audio path
 *
 * The @c audio_manager_snd_pcm_open_name() function combines
 * the @c snd_pcm_open_name() and @c audio_manager_get_handle() functions
 * and allows the allocation a specific audio type PCM channel in
 * one step.
 *
 * @param type The audio type of the PCM channel being allocated.
 * @param handle The handle of the PCM channel opened.
 * @param audioman_handle The audio manager handle allocated to the PCM channel.
 * @param name The name of the audio path to be used to open the PCM
 * channel.
 * @param mode The PCM channel mode defined in @c asoundlib.h.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_snd_pcm_open_name(audio_manager_audio_type_t type, snd_pcm_t **handle, unsigned int *audioman_handle, char *name, int mode);
#endif

/**
 * @internal
 * @brief Check if a device switch should result in an autopause
 *
 * The definition of this function is not considered stable; it may be changed
 * or removed in the future without warning. Do not call it without asking
 * BBOS - Audio team.
 *
 * The @c audio_manager_check_autopause() function indicates whether it is
 * recommended that a client that has been forced to switch from one device
 * to another should autopause.
 *
 * @param audioman_handle The audio manager handle on which to check.
 * @param from The device that was active at the last point in time when
 * the associated PCM channel was prepared.
 * @param to The device that is now active.
 * @param result True, if the client should autopause; false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_check_autopause( unsigned int audioman_handle,
                                   audio_manager_device_t from, audio_manager_device_t to,
                                   bool* result );

/**
 * @internal
 * @brief Check if audio is active at the moment the function is called
 *
 * The definition of this function is not considered stable; it may be changed
 * or removed in the future without warning. Do not call it without asking
 * BBOS - Audio team.
 *
 * The @c audio_manager_get_audio_activities() function returns whether there
 * is active audio playback or recording.
 *
 * @param activities A bitmask of @c audio_manager_device_capability_t that
 * indicates activities.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_audio_activities( int * activities );

/**
 * @internal
 * @brief Compare the routing priority of 2 audio manager handles
 *
 * The definition of this function is not considered stable; it may be changed
 * or removed in the future without warning. Do not call it without asking
 * BBOS - Audio team.
 *
 * The @c audio_manager_compare_handle_routing_priority() function returns
 * the comparison result of the 2 given handles.
 *
 * @param handle1 The first audio manager handle returned by
 * @c audio_manager_get_handle.
 * @param handle2 The second audio manager handle returned by
 * @c audio_manager_get_handle.
 * @param result A pointer to the integer to store the comparison result. A
 * positive value means that @c handle1 has higher priority than @c handle2. A
 * negative value means that @c handle1 has lower priority than @c handle2.
 * Otherwise, both handles have the same priority.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_compare_handle_routing_priority( unsigned int handle1, unsigned int handle2, int * result );

/**
 * @internal
 * @brief Get the process IDs associated with the audio manager handle
 *
 * The definition of this function is not considered stable; it may be changed
 * or removed in the future without warning. Do not call it without asking
 * BBOS - Audio team.
 *
 * The @c audio_manager_get_handle_pids() function returns
 * the process IDs (PIDs) associated with the audio manager handle.
 *
 * @param audioman_handle The audio manager handle returned by
 * @c audio_mananger_get_handle.
 * @param caller_pid The PID of the caller process. If client A plays music
 * through mm-renderer and allows mm-renderer to allocate the audioman handle,
 * the caller_pid = pidof(mm-renderer).
 * @param client_pid The PID of the client process. If client A plays music
 * through mm-renderer and allows mm-renderer to allocate the audioman handle,
 * the caller_pid = pidof(clientA)
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_handle_pids( unsigned int audioman_handle, pid_t * caller_pid, pid_t * client_pid );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_ROUTING_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
