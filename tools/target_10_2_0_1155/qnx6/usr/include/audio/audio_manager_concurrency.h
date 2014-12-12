#ifndef _AUDIO_MANAGER_CONCURRENCY_H_INCLUDED
#define _AUDIO_MANAGER_CONCURRENCY_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <audio/audio_manager_device.h>
#include <audio/audio_manager_routing.h>

/**
 * @file audio_manager_concurrency.h
 *
 * @brief Definitions for supported audio concurrency policies.
 * 
 * The audio manager maintains the audio concurrency policies for the supported
 * audio types. This file defines concurrency properties and provides functions
 * for them.
 * 
 */
 
#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @internal
 * @brief Supported audio attenuation types.
 *
 * This enumeration defines the supported audio attenuation types.
 */
typedef enum {
    AUDIO_ATTENUATION_MUTE          = -1,
    AUDIO_ATTENUATION_NO_EFFECT     = 100,
    AUDIO_ATTENUATION_DEFAULT       = INT_MAX,
    /**
     * The total number of all audio types.
     */
} audio_manager_attenuation_type_t;

/**
 * @internal
 * @brief Supported audio voice attenuation types.
 *
 * This enumeration defines the supported audio voice attenuation types.
 */
typedef enum {
    ATTENUATION_VOICE_UPLINK   = (1u<<0),
    ATTENUATION_VOICE_DOWNLINK = (1u<<1),
} audio_manager_attenuation_extra_option_t;

/**
 * @internal
 * @brief Supported audio attenuation parameters.
 *
 * This structure defines the parameters for setting the attenuation effect
 * of an audio manager handle.
 */
typedef struct {
    /**
     * @brief Attenuation value from 0-100 and enum
     * @c audio_manager_attenuation_type_t.
     */
    int attenuation;
    /**
     * @brief Extra attenuation options, represented by a bitmask of
     * @c audio_manager_attenuation_extra_option_t.
     */
    int attenuation_extra_options;
} audio_manager_attenuation_params_t;

/**
 * @brief Audio concurrency settings.
 * 
 * This structure defines the audio concurrency settings.
 */
typedef struct {
    /**
     * True, if the audio type is currently being attenuated; false, otherwise.
     */
    bool attenuated;
    /**
     * True, if the audio type is currently being fully muted; false, otherwise.
     */
    bool muted;
    /**
     * The audio type causing the mute policy to be applied.
     */
    audio_manager_audio_type_t muted_by;
    /**
     * The ID of the process causing the mute policy to be applied.
     */
    pid_t muted_by_pid;
} audio_manager_concurrency_t;

/**
 * @brief Get the audio concurrency status of a given audio type
 * 
 * The @c audio_manager_get_audio_type_concurrency_status() function returns
 * the audio concurrency status @c audio_manager_concurrency_t of a given
 * audio type.
 * 
 * @param type The audio type to query.
 * @param status The audio concurrency status.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_audio_type_concurrency_status( audio_manager_audio_type_t type, 
                                     audio_manager_concurrency_t * status );
/**
 * @brief Get the audio concurrency status of a given audio manager 
 * handle
 * 
 * The @c audio_manager_get_current_audio_handle_concurrency_status()
 * function returns the current audio concurrency status 
 * @c audio_manager_concurrency_t of a given audio manager handle.
 * 
 * @param audioman_handle The audio mananger handle to query.
 * @param status The audio concurrency status.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_current_audio_handle_concurrency_status( unsigned int audioman_handle, 
                                     audio_manager_concurrency_t * status );

/**
 * @internal
 * @brief Override the attenuation that's associated with the type of the given
 * audio manager handle
 *
 * The definition of this function is not considered stable; it may be changed
 * or removed in the future without warning. Do not call it without asking
 * BBOS - Audio team.
 *
 * The @c audio_manager_set_handle_attenuation() function overrides the
 * attenuation of the given audio manager handle applied to the lower ducking
 * priority audio sources.
 *
 * @param audioman_handle The audio manager handle returned by
 * @c audio_mananger_get_handle.
 * @param params The parameters for the handle attenuation to apply.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_handle_attenuation( unsigned int audioman_handle, audio_manager_attenuation_params_t params );

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_CONCURRENCY_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
