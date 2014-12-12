#ifndef _AUDIO_MANAGER_VOICE_SERVICE_H_INCLUDED
#define _AUDIO_MANAGER_VOICE_SERVICE_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <audio/audio_manager_device.h>

/**
 * @file audio_manager_voice_service.h
 *
 * @brief Definitions for supported voice services.
 * 
 * The audio manager maintains the voice services status for devices. This file
 * defines voice services status properties and provides functions for them.
 * 
 */
 
#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief Audio voice service names.
 */
#define AUDIO_VOICE_SERVICE_NAMES   \
{                                   \
    "cellular",                     \
    "voip",                         \
}

/**
 * @brief Audio voice status names.
 */
#define AUDIO_VOICE_STATUS_NAMES    \
{                                   \
    "off",                          \
    "ringer",                       \
    "on",                           \
}

/**
 * @brief Audio voice option names.
 */
#define AUDIO_VOICE_OPTION_NAMES    \
{                                   \
    "normal",                       \
    "boost_treble",                 \
    "boost_bass",                   \
}

/**
 * @brief Audio voice codec names.
 */
#define AUDIO_VOICE_CODEC_NAMES     \
{                                   \
    "narrowband",                   \
    "wideband",                     \
}

/**
 * @brief The supported status of the voice services.
 * 
 * This enumeration defines the supported status of the voice services.
 */
typedef enum {
    /**
     * The voice service is shut down.
     */
    AUDIO_VOICE_OFF,
    /**
     * The voice service is playing a ringtone.
     */
    AUDIO_VOICE_RINGTONE,
    /**
     * The voice service is turned on.
     */
    AUDIO_VOICE_ON,
    /**
     * The total number of status types.
     */
    AUDIO_VOICE_STATUS_COUNT,
} audio_manager_voice_service_status_t;

/**
 * @brief The supported voice service types.
 * 
 * This enumeration defines the supported voice service types.
 */
typedef enum {
    /**
     * The cellular voice service.
     */
    AUDIO_VOICE_CELLULAR,
    /**
     * The Voice over IP (VoIP) service.
     */
    AUDIO_VOICE_VOIP,
    /**
     * The total of voice services supported.
     */
    AUDIO_VOICE_SERVICE_COUNT,
} audio_manager_voice_service_t;

/**
 * @brief Supported audio options of the voice services.
 * 
 * This enumeration defines the supported audio options of the
 * voice services.
 */
typedef enum {
    /**
     * The audio option for no particular audio tuning.
     */
    AUDIO_VOICE_OPTION_NORMAL,
    /**
     * The audio option for treble audio tuning.
     */
    AUDIO_VOICE_OPTION_TREBLE,
    /**
     * The audio option for bass audio tuning.
     */
    AUDIO_VOICE_OPTION_BASS,
    /**
     * The total number of audio options.
     */
    AUDIO_VOICE_OPTION_COUNT,
} audio_manager_voice_option_t;

/**
 * @brief Supported voice codecs.
 * 
 * This enumeration defines the supported voice codecs.
 */
typedef enum {
    /**
     * The voice codec is narrowband (8 KHz).
     */
    AUDIO_VOICE_CODEC_NARROWBAND,
    /**
     * The voice codec is wideband (>=16 KHz).
     */
    AUDIO_VOICE_CODEC_WIDEBAND,
    /**
     * The total number of voice codecs.
     */
    AUDIO_VOICE_CODEC_COUNT,
} audio_manager_voice_codec_t;

/**
 * @brief Get the audio voice service name given the type of the service
 * 
 * The @c audio_manager_get_voice_service_name() function returns the audio
 * voice service name given the type of the service.
 * 
 * @param service The type of the service to query.
 * 
 * @return The audio voice service name.
 */
const char * audio_manager_get_voice_service_name( audio_manager_voice_service_t service );

/**
 * @brief Get the audio voice service given the name of the service
 * 
 * The @c audio_manager_get_voice_service_from_name() function returns the audio
 * voice service given the name of the service.
 * 
 * @param name The name of the service to query.
 * 
 * @return The audio voice service identifier.
 */
audio_manager_voice_service_t audio_manager_get_voice_service_from_name( const char * name );

/**
 * @brief Get the audio voice service status name given the type of the status
 * 
 * The @c audio_manager_get_voice_service_status_name() function returns the
 * audio voice service status name given the type of the status.
 * 
 * @param status The type of the status to query.
 * 
 * @return The service status name.
 */
const char * audio_manager_get_voice_service_status_name( audio_manager_voice_service_status_t status );

/**
 * @brief Get the audio voice status given the name of the status
 * 
 * The @c audio_manager_get_voice_service_status_from_name() function returns
 * the voice status given the name of the status.
 * 
 * @param name The name of the status to query.
 * 
 * @return The service status identifier.
 */
audio_manager_voice_service_status_t audio_manager_get_voice_service_status_from_name( const char * name );

/**
 * @brief Get the enhanced audio option name given the type of the option
 * 
 * The @c audio_manager_get_voice_service_option_name() function returns the
 * name of the enhanced audio option for the voice service given the type of the 
 * option.
 * 
 * @param option The type of the option to query.
 * 
 * @return The option name.
 */
const char * audio_manager_get_voice_service_option_name( audio_manager_voice_option_t option );

/**
 * @brief Get the audio voice option given the name of the option
 * 
 * The @c audio_manager_get_voice_service_option_from_name() function returns
 * the enhanced audio option of a voice service given the name of the option.
 * 
 * @param name The name of the option to query.
 * 
 * @return The option identifier.
 */
audio_manager_voice_option_t audio_manager_get_voice_service_option_from_name( const char * name );


/**
 * @brief Get the current status of a given voice service type
 * 
 * The @c audio_manager_get_voice_service_status() function returns 
 * the status of a given voice service type.
 * 
 * @param service The voice service type to query.
 * @param status The status returned.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_service_status( audio_manager_voice_service_t service, 
                                            audio_manager_voice_service_status_t * status );


/**
 * @internal
 * @brief Get the current status and the codec settings of a given voice
 * service type
 * 
 * The @c audio_manager_get_voice_service_status_with_codec_settings() function
 * returns the status and the codec settings of a given voice service type.
 * 
 * @param service The voice service type to query.
 * @param status The status returned.
 * @param codec_name_buf The buffer to store the name of the codec the service
 * provider uses; NULL if not needed.
 * @param buf_size The size of the @c codec_name_buf.
 * @param codec_rate The pointer to store the audio sample rate of the service
 * provider.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_service_status_with_codec_settings( 
                                            audio_manager_voice_service_t service, 
                                            audio_manager_voice_service_status_t * status,
                                            char * codec_name_buf, int buf_size, int * codec_rate);

/**
 * @brief Get the current audio option of a given voice service type
 * and a given audio device
 * 
 * The @c audio_manager_get_voice_service_option() function returns 
 * the audio option of a given voice service type and a given audio device.
 * 
 * @param service The voice service type to query.
 * @param dev The audio device to query.
 * @param option The audio option returned.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_service_option( audio_manager_voice_service_t service, 
                                            audio_manager_device_t dev,
                                            audio_manager_voice_option_t * option );

// priviledged call
/**
 * @internal
 * @brief [Privileged]Set the status of a given voice service type
 * 
 * The @c audio_manager_set_voice_service_status() function sets 
 * the status of a given voice service type.
 * 
 * @param service The voice service type that the new status is applied to.
 * @param status The status to be applied.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_voice_service_status( audio_manager_voice_service_t service, 
                                            audio_manager_voice_service_status_t status );

/**
 * @brief [Privileged]Set the status and the codec settings of a given voice
 * service type
 * 
 * The @c audio_manager_set_voice_service_status_with_codec_settings() function
 * sets the status and the codec settings of a given voice service type.
 * 
 * @param service The voice service type that the new status is applied to.
 * @param status The status to be applied.
 * @param codec_name The name of the codec the service provider uses.
 * @param codec_rate The audio sample rate the service provider uses.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_voice_service_status_with_codec_settings( 
                                            audio_manager_voice_service_t service, 
                                            audio_manager_voice_service_status_t status,
                                            const char * codec_name,
                                            int codec_rate);


/**
 * @brief [Privileged]Set the audio option of a given voice service type
 * and a given audio device
 * 
 * The @c audio_manager_set_voice_service_option() function sets 
 * the audio option of a given voice service type and a given audio device.
 * 
 * @param service The voice service type that the new audio option is applied
 * to.
 * @param dev_output The audio device that the new audio option is applied to.
 * @param option The new audio option to be applied.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_voice_service_option( audio_manager_voice_service_t service, 
                                            audio_manager_device_t dev_output,
                                            audio_manager_voice_option_t option );

/**
 * @internal
 * @brief [Privileged] Get the ID of redirector.
 * 
 * The @c audio_manager_get_redirector_id() function gets the ID of redirector.
 * 
 * @param redirector_id The ID of redirector.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */

int audio_manager_get_redirector_id( int *redirector_id );


#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_VOICE_SERVICE_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
