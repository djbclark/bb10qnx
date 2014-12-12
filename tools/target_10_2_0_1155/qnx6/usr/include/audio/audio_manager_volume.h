#ifndef _AUDIO_MANAGER_VOLUME_H_INCLUDED
#define _AUDIO_MANAGER_VOLUME_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <stdint.h>
#include <audio/audio_manager_device.h>

/**
 * @file audio_manager_volume.h
 *
 * @brief Definitions for supported audio volume controls.
 *
 * The audio manager maintains the volume control interfaces for all supported
 * devices. This file defines audio volume control properties and provides 
 * functions for them.
 */

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @internal
 * @brief Statistic entry name used with @c audio_manager_get_stat_counter() for
 * EU headphone volume regulations.
 *
 * This counter tracks the total time the user has spent in the EU
 * unsafe volume zone with headphones.
 */
#define UNSAFEZONE_TIMEOUT_ID "Audio.EU.headphone.boost.timer"
/**
 * @internal
 * @brief The default threshold in percentage for entering the EU unsafe 
 * volume zone for headphones.
 */
#define UNSAFEZONE_DEFAULT_EU_UNSAFE_LEVEL   75
/**
 * @internal
 * @brief The default timeout of the EU unsafe volume zone for headphones.
 * 
 * Once the timer reaches this threshold, the user is required to acknowledge 
 * the EU regulations again to use headphones with volume level above 
 * the @c UNSAFEZONE_DEFAULT_EU_UNSAFE_LEVEL. 
 */
#define UNSAFEZONE_DEFAULT_EU_UNSAFE_TIMEOUT 72000000


/**
 * @brief Headphone volume override status.
 *
 * This structure defines the status of the configuration of a given headphone
 * volume override feature.
 */
typedef struct {
    /**
     * True, if the extra volume override is supported by the device or
     * region; false, otherwise.
     */
    bool supported;
    /**
     * True, if the extra volume range is allowed; false, otherwise.
     */
    bool enabled;
    /**
     * The output level in percentage (0-100) that the headphone volume is 
     * limited to if the override is false.
     */
    int level;
} audio_manager_headphone_volume_override_status_t;


/**
 * @internal
 * @brief The audio headphone output volume regulation status.
 * 
 * This structure defines the status of whether and at which level the headphone 
 * output volume is regulated.
 */
typedef struct {
    /**
     * The current status of whether the headphone volume is regulated.
     */
    bool regulated;
    /**
     * The output level in percentage that the headphone volume is regulated at.
     */
    double level;
} audio_manager_headphone_output_regulation_t;

/**
 * @brief Set the audio output level of a given audio device
 *
 * The @c audio_manager_set_output_level() function sets
 * the audio output level of a given audio device.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The new output level in percentage, 0.00 - 100.0 (e.g. 90.00 =
 * 90%).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_output_level( audio_manager_device_t dev, double level );

/**
 * @brief Get the audio output level of a given audio device
 *
 * The @c audio_manager_get_output_level() function returns
 * the audio output level of a given audio device.
 *
 * @param dev The audio device to query.
 * @param level The output level being returned in percentage, 0.00 - 100.0
 * (e.g. 90.00 = 90%).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_output_level( audio_manager_device_t dev, double * level );

/**
 * @brief Adjust the audio output level of a given audio device
 *
 * The @c audio_manager_adjust_output_level() function adjusts
 * the audio output level of a given audio device.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The change in level of the audio output in
 * percentage (e.g. 10.00 = 10% increase, -10.00 = 10% decrease).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_adjust_output_level( audio_manager_device_t dev, double level );

/**
 * @brief Increase the audio output level of a given audio device
 *
 * The @c audio_manager_increase_output_level() function increases
 * the audio output level of a given audio device. The step of the
 * output level increase is defined by the particular audio device.
 *
 * @param dev The audio device that the increase is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_increase_output_level( audio_manager_device_t dev );

/**
 * @brief Decrease the audio output level of a given audio device
 *
 * The @c audio_manager_decrease_output_level() function decreases
 * the audio output level of a given audio device. The step of the
 * output level decrease is defined by the particular audio device.
 *
 * @param dev The audio device that the decrease is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_decrease_output_level( audio_manager_device_t dev );

/**
 * @brief Get the number of available output volume steps
 *
 * The @c audio_manager_get_output_volume_steps() function returns the
 * number of available volume steps.
 *
 * @param dev The audio device to query.
 * @param steps The available volume steps returned.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_output_volume_steps( audio_manager_device_t dev, int * steps );

/**
 * @brief Mute the audio output of a given audio device
 *
 * The @c audio_manager_set_output_mute() function mutes
 * the audio output of a given audio device.
 *
 * @param dev The audio device to mute output.
 * @param mute True, if the output of the audio device should be muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_output_mute( audio_manager_device_t dev, bool mute );

/**
 * @brief Get the mute status of the audio output of a given audio device
 *
 * The @c audio_manager_get_output_mute() function returns the
 * mute status of the audio output of a given audio device.
 *
 * @param dev The audio device to query.
 * @param mute True, if the output of the audio device is being muted; false, 
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_output_mute( audio_manager_device_t dev, bool * mute );

/**
 * @brief Toggle the audio output mute status of a given audio device
 *
 * The @c audio_manager_toggle_output_mute() function toggles the
 * mute status of the audio output of a given audio device.
 *
 * @param dev The audio device that the toggle is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_toggle_output_mute( audio_manager_device_t dev );

/**
 * @brief Set the audio input level of a given audio device
 *
 * The @c audio_manager_set_input_level() function sets
 * the audio input level of a given audio device.
 *
 * @param dev The audio device that the new input level is applied to.
 * @param level The new input level in percentage, 0.00 - 100.00 (e.g. 90.00 =
 * 90%).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_input_level( audio_manager_device_t dev, double level );

/**
 * @brief Get the audio input level of a given audio device
 *
 * The @c audio_manager_get_input_level() function returns
 * the audio input level of a given audio device.
 *
 * @param dev The audio device to query.
 * @param level The input level being returned in percentage, 0.00 - 100.0
 * (e.g. 90.00 = 90%).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_input_level( audio_manager_device_t dev, double * level );

/**
 * @brief Adjust the audio input level of a given audio device
 *
 * The @c audio_manager_adjust_input_level() function adjusts
 * the audio input level of a given audio device.
 *
 * @param dev The audio device the new input level is applied to.
 * @param level The change in level of the audio input in
 * percentage (e.g. 10.00 = 10% increase, -10.00 = 10% decrease).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_adjust_input_level( audio_manager_device_t dev, double level );

/**
 * @brief Mute the audio input of a given audio device
 *
 * The @c audio_manager_set_input_mute() function mutes
 * the audio input of a given audio device.
 *
 * @param dev The audio device to mute input.
 * @param mute True, if the input of the audio device should be muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_input_mute( audio_manager_device_t dev, bool mute );

/**
 * @brief Get the mute status of the audio input of a given audio device
 *
 * The @c audio_manager_get_input_mute() function returns the
 * mute status of the audio input of a given audio device.
 *
 * @param dev The audio device to query.
 * @param mute True, if the input of the audio device is being muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_input_mute( audio_manager_device_t dev, bool * mute );

/**
 * @brief Toggle the audio input mute status of a given audio device
 *
 * The @c audio_manager_toggle_output_mute() function toggles the
 * mute status of the audio input of a given audio device.
 *
 * @param dev The audio device that the toggle is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_toggle_input_mute( audio_manager_device_t dev );

/**
 * @brief Get the headphone override status
 * @deprecated This function is deprecated.
 *
 * The @c audio_manager_get_headphone_override() function returns
 * the headphone volume override status. The override allows extra volume boost
 * to the headphone output.
 *
 * @param override True, if the extra volume boost is allowed; false, otherwise.
 * @param level The output level in percentage (0-100) that the headphone
 * volume is allowed.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int __attribute__((deprecated)) audio_manager_get_headphone_override( bool * override, int * level );

/**
 * @brief Get the headphone volume boost status
 *
 * The @c audio_manager_get_headphone_boost_status() function returns
 * the headphone volume boost status. The override allows extra volume boost
 * to the headphone output.
 *
 * @param status The status of the volume boost as
 * @c audio_manager_headphone_volume_override_status_t.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_headphone_boost_status( audio_manager_headphone_volume_override_status_t * status );

/**
 * @brief Get the headphone volume unsafe zone status
 *
 * The @c audio_manager_get_headphone_unsafezone_status() function returns
 * the headphone volume unsafe zone status.
 *
 * @param status The status of the volume unsafe zone as
 * @c audio_manager_headphone_volume_override_status_t.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_headphone_unsafe_zone_status( audio_manager_headphone_volume_override_status_t * status );

/**
 * @internal
 * @brief Get whether the current headphone output level is restricted due to
 * regulations
 *
 * The @c audio_manager_get_headphone_level_regulated() function returns whether
 * the level of the current headphone output level is regulated to a lower
 * level than the user or application might have set.
 *
 * @param regulated True, if the output of the audio device is being regulated; 
 * false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_headphone_output_level_regulation_status( audio_manager_headphone_output_regulation_t * status );


// privileged calls

/**
 * @brief [Privileged]Set the audio output level of a given audio
 * device during voice calls
 *
 * The @c audio_manager_set_voice_output_level() function sets
 * the audio output level of a given audio device during voice calls.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The new output level in percentage, 0.00 - 100.0 (e.g. 90.00 =
 * 90%).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_voice_output_level( audio_manager_device_t dev, double level );

/**
 * @brief [Privileged]Get the audio output level of a given audio
 * device during voice calls
 *
 * The @c audio_manager_get_voice_output_level() function returns
 * the audio output level of a given audio device during voice
 * calls.
 *
 * @param dev The audio device to query.
 * @param level The output level being returned in percentage, 0.00 - 100.0
 * (e.g. 90.00 = 90%).
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_output_level( audio_manager_device_t dev, double * level );

/**
 * @brief [Privileged]Adjust the audio output level of a given audio
 * device during voice calls
 *
 * The @c audio_manager_adjust_voice_output_level() function adjusts
 * the audio output level of a given audio device during voice calls.
 *
 * @param dev The audio device that the new output level is applied to.
 * @param level The change in level of the audio output in
 * percentage, 0.00 - 100.0. (e.g. 10.00 = 10% increase, -10.00 = 10% decrease)
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_adjust_voice_output_level( audio_manager_device_t dev, double level );

/**
 * @brief [Privileged]Increase the audio output level of a given audio
 * device during voice calls
 *
 * The @c audio_manager_increase_voice_output_level() function increases
 * the audio output level of a given audio device during voice calls.
 * The step of the output level increase is defined by the particular
 * audio device.
 *
 * @param dev The audio device that the increase is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_increase_voice_output_level( audio_manager_device_t dev );

/**
 * @brief [Privileged]Decrease the audio output level of a given audio
 * device during voice calls
 *
 * The @c audio_manager_decrease_voice_output_level() function decreases
 * the audio output level of a given audio device during voice calls.
 * The step of the output level decrease is defined by the particular
 * audio device.
 *
 * @param dev The audio device that the decrease is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_decrease_voice_output_level( audio_manager_device_t dev );

/**
 * @brief Get the number of available voice output volume steps
 *
 * The @c audio_manager_get_voice_output_volume_steps() function returns the
 * number of available volume steps for voice calls.
 *
 * @param dev The audio device to query.
 * @param steps The available volume steps returned.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_output_volume_steps( audio_manager_device_t dev, int * steps );


/**
 * @brief Get the statistic counter of a given statistic entry name
 *
 * The @c audio_manager_get_stat_counter() function returns the counter of
 * the given statistic entry.
 *
 * @param name The name of the statistic entry.
 * @param counter The counter of the selected entry returned.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_stat_counter( const char * name, uint64_t * counter );

/**
 * @brief [Priveleged]Clear the statistic counter of a given statistic entry
 * name
 *
 * The @c audio_manager_set_stat_counter() function clears the counter of
 * the given statistic entry.
 *
 * @param name The name of the statistic entry to clear.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_clear_stat_counter( const char * name );

/**
 * @brief [Privileged]Mute the audio output of a given audio device
 * during voice calls
 *
 * The @c audio_manager_set_voice_output_mute() function mutes
 * the audio output of a given audio device during voice calls.
 *
 * @param dev The audio device to mute output.
 * @param mute True, if the output of the audio device should be muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_voice_output_mute( audio_manager_device_t dev, bool mute );

/**
 * @brief [Privileged]Get the mute status of the audio output of a
 * given audio device during voice calls
 *
 * The @c audio_manager_get_voice_output_mute() function returns the
 * mute status of the audio output of a given audio device during
 * voice calls.
 *
 * @param dev The audio device to query.
 * @param mute True, if the output of the audio device is being muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_output_mute( audio_manager_device_t dev, bool * mute );

/**
 * @brief [Privileged]Mute the audio output of the modem
 *
 * The @c audio_manager_set_modem_output_mute() function mutes
 * the audio output of the modem.
 *
 * @param mute True, if the output of the modem should be muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_modem_output_mute( bool mute );

/**
 * @brief [Privileged]Get the mute status of the audio output of the
 * modem
 *
 * The @c audio_manager_get_modem_output_mute() function returns the
 * mute status of the audio output of the modem.
 *
 * @param mute True, if the output of the modem is muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_modem_output_mute( bool * mute );

/**
 * @brief [Privileged]Toggle the audio output mute status of a given
 * audio device during voice calls
 *
 * The @c audio_manager_toggle_voice_output_mute() function toggles the
 * mute status of the audio output of a given audio device during voice
 * calls.
 *
 * @param dev The audio device that the toggle is applied to.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_toggle_voice_output_mute( audio_manager_device_t dev );

/**
 * @brief [Privileged]Mute the audio input (to the far end) of the current
 * voice call
 *
 * The @c audio_manager_set_voice_input_mute() function mutes
 * the audio input (to the far end) of the current voice call.
 *
 * @param mute True, if the input of the current voice call should be muted;
 * false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_voice_input_mute( bool mute );

/**
 * @brief [Privileged]Get the mute status of the audio input (to the far end) of
 * the current voice call
 *
 * The @c audio_manager_get_voice_input_mute() function returns the mute status
 * of the audio input (to the far end) of the current voice call.
 *
 * @param mute True, if the input of the voice call is being muted; false,
 * otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_voice_input_mute( bool *mute );

/**
 * @brief [Privileged] Set the override status of the headphone output level
 * @deprecated This function is deprecated.
 *
 * The @c audio_manager_set_headphone_override() function sets the
 * override status of the headphone output level to allow an extra volume
 * boost to the headphone output.
 *
 * @param override True, if the extra volume boost is allowed; false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int  __attribute__((deprecated)) audio_manager_set_headphone_override( bool override );

/**
 * @brief [Privileged]Set the use of the headphone output volume boost
 *
 * The @c audio_manager_set_headphone_volume_boost() function sets the
 * enable status of the headphone output level to allow an extra volume
 * boost to the headphone output.
 *
 * @param enable True, if the extra volume boost is allowed; false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_headphone_volume_boost( bool enable );

/**
 * @brief [Privileged]Set the use of the unsafe range of the headphone
 * output volume
 *
 * The @c audio_manager_set_headphone_volume_unsafezone() function sets the
 * enable status of the unsafe volume range of the headphone output to allow
 * an extra volume range to the headphone output.
 *
 * @param enable True, if the extra volume range is allowed; false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_headphone_volume_unsafe_zone( bool enable );




#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_VOLUME_H_INCLUDED


__SRCVERSION( "$URL$ $Rev$" )
