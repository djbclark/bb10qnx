#ifndef _AUDIO_MANAGER_DEVICE_H_INCLUDED
#define _AUDIO_MANAGER_DEVICE_H_INCLUDED
#include <sys/platform.h>
#include <stdbool.h>
#include <limits.h>

/**
 * @mainpage Audio Manager Library Overview
 *
 * The audio manager library allows applications to set up and process events
 * from audio devices supported on the target. This library provides a C/C++
 * friendly interface to audio devices. Using this library, you can get and set
 * properties for audio device status, volume, routing, and concurrency. You can
 * also add and remove audio device events to notify clients that are using
 * audio devices.
 *
 */
 
 /**
 * @file audio_manager_device.h
 *
 * @brief Definitions for supported audio devices and their properties
 * 
 * The audio manager maintains a list of supported devices on the target and
 * their properties. This file defines device properties and provides get and
 * set functions for them.
 * 
 */
 
#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

/**
 * @brief Names for supported audio devices.
 */
#define AUDIO_DEVICE_NAMES  \
{                           \
    "speaker",              \
    "headset",              \
    "headphone",            \
    "a2dp",                 \
    "handset",              \
    "hac",                  \
    "btsco",                \
    "hdmi",                 \
    "toslink",              \
    "tty",                  \
    "lineout",              \
    "usb",                  \
    "tones",                \
    "voice",                \
    "miracast",             \
    "mirrorlink",           \
    "audioshare",           \
}

/**
 * @brief Names for audio channels.
 */
#define AUDIO_CHANNEL_NAMES \
{                           \
    "",                     \
    "FL",                   \
    "FC",                   \
    "FR",                   \
    "RL",                   \
    "RR",                   \
    "LFE",                  \
}

/**
 * @brief Names for volume control types.
 */
#define AUDIO_VOLUME_CONTROL_NAMES  \
{                                   \
    "unavailable",                  \
    "simple",                       \
    "percentage",                   \
}

/**
 * @brief Names for headset buttons.
 */
#define AUDIO_HEADSET_BUTTON_NAMES  \
{                                   \
    "button_play_pause",            \
    "button_vol_up",                \
    "button_vol_down",              \
    "button_forward",               \
    "button_back",                  \
}

/**
 * @brief Names for headset button states.
 */
#define AUDIO_HEADSET_BUTTON_STATE_NAMES    \
{                                           \
    "pressed",                              \
    "released",                             \
}

/**
 * @brief Supported audio devices.
 * 
 * This enumeration defines the types of audio devices 
 * supported.
 */
typedef enum {
    /**
     * The main speaker(s).
     */
    AUDIO_DEVICE_SPEAKER,
    /**
     * The mono/stereo headset with microphone.
     */
    AUDIO_DEVICE_HEADSET,
    /**
     * The mono/stereo output only headphone.
     */
    AUDIO_DEVICE_HEADPHONE,
    /**
     * The Bluetooth A2DP streaming service.
     */
    AUDIO_DEVICE_A2DP,
    /**
     * The phone receiver.
     */
    AUDIO_DEVICE_HANDSET,
    /**
     * The hearing aid compatibility device.
     */
    AUDIO_DEVICE_HAC,
    /**
     * The Bluetooth hands-free profile service for voice calls.
     */
    AUDIO_DEVICE_BT_SCO,
    /**
     * The HDMI connection.
     */
    AUDIO_DEVICE_HDMI,
    /**
     * The TOSLINK connection.
     */
    AUDIO_DEVICE_TOSLINK,
    /**
     * The telecommunications device for the hearing challenged.
     */
    AUDIO_DEVICE_TTY,
    /**
     * The lineout connection through the headset jack.
     */
    AUDIO_DEVICE_LINEOUT,
    /**
     * The USB connection.
     */
    AUDIO_DEVICE_USB,
    /**
     * The virtual tones port that is used for system tones.
     */
    AUDIO_DEVICE_TONES,
    /**
     * The virtual voice port that is used for voice stream processing such as
     * VoIP.
     */
    AUDIO_DEVICE_VOICE,
    /**
     * The audio device exposed by the Wi-Fi display connection.
     */
    AUDIO_DEVICE_WIFI_DISPLAY,
    /**
     * The audio device exposed by the MirrorLink connection.
     */
    AUDIO_DEVICE_MIRRORLINK,
    /**
     * The virtual audio device exposed by video share.
     */
    AUDIO_DEVICE_AUDIO_SHARE,
    /**
     * The total number of devices supported.
     */
    AUDIO_DEVICE_COUNT,
    /**
     * The current active output device that audio is playing out of.
     */
    AUDIO_DEVICE_DEFAULT = 0xFF,
    /**
     * The audio device is unchanged if the given value is specified.
     */
    AUDIO_DEVICE_UNCHANGED = INT_MAX,
} audio_manager_device_t;

/**
 * @brief Supported audio channels.
 * 
 * This enumeration defines the supported types of 
 * audio channels (2.0/5.1).
 */
typedef enum {
    /**
     * No output channel is supported.
     */
    AUDIO_CHANNEL_UNAVAILABLE,
    /**
     * Front left channel.
     */
    AUDIO_CHANNEL_FRONT_LEFT,
    /**
     * Front center channel.
     */
    AUDIO_CHANNEL_FRONT_CENTER,
    /**
     * Front right channel.
     */
    AUDIO_CHANNEL_FRONT_RIGHT,
    /**
     * Rear left channel.
     */
    AUDIO_CHANNEL_REAR_LEFT,
    /**
     * Rear right channel.
     */
    AUDIO_CHANNEL_REAR_RIGHT,
    /**
     * Low frequency effects channel (subwoofer).
     */
    AUDIO_CHANNEL_LOW_FREQ_EFFECTS,
    /**
     * The total number of audio channels supported.
     */
    AUDIO_CHANNEL_COUNT,
} audio_manager_channel_t;

/**
 * @brief Supported audio volume control types.
 * 
 * This enumeration defines the supported types of the audio 
 * volume control types.
 */
typedef enum {
    /**
     * Volume control is not supported.
     */
    AUDIO_VOLUME_CONTROL_UNAVAILABLE,
    /**
     * The simple (up/down) volume control is supported.
     */
    AUDIO_VOLUME_CONTROL_SIMPLE,
    /**
     * The precise volume control in percentage is supported.
     */
    AUDIO_VOLUME_CONTROL_PERCENT,
    /**
     * The total number of volume control types supported.
     */
    AUDIO_VOLUME_CONTROL_COUNT,
} audio_manager_device_volume_control_t;

/**
 * @brief Supported audio device configurations.
 * 
 * This enumeration defines bit masks for supported audio device configurations.
 */
typedef enum {
    /**
     * The audio device supports stereo channels.
     */
    AUDIO_CHANNEL_CONFIG_STEREO = (1u<<0),
    /**
     * The audio device supports 5.1 surround sound.
     */
    AUDIO_CHANNEL_CONFIG_5_1    = (1u<<1),
} audio_manager_channel_config_t;

/**
 * @brief Supported audio device I/O.
 * 
 * This enumeration defines bit masks for the supported audio device I/O.
 */
typedef enum {
    /**
     * The audio device supports output (playback).
     */
    AUDIO_OUTPUT                = (1u<<0),
    /**
     * The audio device supports input (recording).
     */
    AUDIO_INPUT                 = (1u<<1),
} audio_manager_device_capability_t;

/**
 * @brief Audio configuration settings for a given audio device.
 * 
 * This structure defines the audio configuration of a given audio 
 * device.
 */
typedef struct {
    /**
     * The number of output channels supported.
     */
    int num_out_channels;
    /**
     * The number of input channels supported.
     */
    int num_in_channels;
    /**
     * The output channels of the audio device, listed in setup order.
     */
    audio_manager_channel_t channel_order[AUDIO_CHANNEL_COUNT];
    /**
     * The audio device configuration of the audio device.
     */
    audio_manager_channel_config_t channel_config_mask;
} audio_manager_device_audio_config_t;

/**
 * @brief Supported audio headset button types.
 * 
 * This enumeration defines the supported types of the audio headset buttons.
 */
typedef enum {
    /**
     * The play/pause button or the mute/unmute button.
     */
    AUDIO_HEADSET_PLAY_PAUSE,
    /**
     * The volume up button.
     */
    AUDIO_HEADSET_VOLUME_UP,
    /**
     * The volume down button.
     */
    AUDIO_HEADSET_VOLUME_DOWN,
    /**
     * The track forward button.
     */
    AUDIO_HEADSET_FORWARD,
    /**
     * The track backward button.
     */
    AUDIO_HEADSET_BACKWARD,
    /**
     * The total of headset button types supported.
     */
    AUDIO_HEADSET_BUTTON_COUNT,
} audio_manager_device_headset_button_t;

/**
 * @brief The states of the headset buttons.
 * 
 * This structure defines the supported states of the audio headset buttons.
 */
typedef struct {
    /**
     * The state of the audio headset button.
     */
    bool button_state[AUDIO_HEADSET_BUTTON_COUNT];
} audio_manager_headset_button_state_t;

/**
 * @brief Audio capabilities that can be queried.
 * 
 * This enumeration defines the audio capabilities that can be queried.
 */
typedef enum {
    /**
     * The number of output channels supported; of type @c int.
     */
    AUDIO_DEVICE_PROPERTY_NUM_OUT_CHANNELS,
    /**
     * The number of input channels supported; of type @c int.
     */
    AUDIO_DEVICE_PROPERTY_NUM_IN_CHANNELS,
    /**
     * The output channels, listed in setup order; of type
     * @c audio_manager_channel_t[]. This parameter is only
     * permitted if @c AUDIO_DEVICE_PROPERTY_NUM_OUT_CHANNELS is requested as
     * well. If the number of channels is greater than the input value for
     * @c AUDIO_DEVICE_PROPERTY_NUM_OUT_CHANNELS then, at most, the input value
     * will be written. 
     */
    AUDIO_DEVICE_PROPERTY_CHANNEL_ORDER,
    /**
     * The audio device configuration of the audio device; of type 
     * @c audio_manager_channel_config_t. The value may be multiple
     * values from this enum OR'ed together.
     */
    AUDIO_DEVICE_PROPERTY_CHANNEL_CONFIG,
    /**
     * Whether the device is supported on this platform; of type @c bool.
     */
    AUDIO_DEVICE_PROPERTY_SUPPORTED,
    /**
     * Whether the device is currently connected; of type @c bool. For example,
     * in the case of headphones, indicates whether the headphones are plugged
     * in.
     */
    AUDIO_DEVICE_PROPERTY_CONNECTED,
    /**
     * Whether the device is suspended; of type @c bool.
     */
    AUDIO_DEVICE_PROPERTY_SUSPENDED,
    /**
     * The type of volume control supported by the device; of type 
     * @c audio_manager_device_volume_control_t.
     */
    AUDIO_DEVICE_PROPERTY_VOLUME_CONTROL,
    /**
     * Whether the device is public; of type @c bool. This means a device may be 
     * listened to by multiple listeners, such as a speaker, as opposed to a 
     * private device listened to by one person, such as headphones.
     */
    AUDIO_DEVICE_PROPERTY_PUBLIC,
    /**
    * The number of input channels supported by the device. This enumerator 
    * represents the true number of input channels that a device supports and
    * therefore differs from the @c AUDIO_DEVICE_PROPERTY_NUM_IN_CHANNELS
    * enumerator.
    */
    AUDIO_DEVICE_PROPERTY_NUM_HW_IN_CHANNELS,
    /**
    * The bitmask of voice capabilities in the format of
    * (1u<<@c audio_manager_voice_service_t) supported by the
    * given device; of type @c int
    */
    AUDIO_DEVICE_PROPERTY_VOICE_CAPABILITIES,
    /**
     * The total number of device properties supported.
     */
    AUDIO_DEVICE_PROPERTY_COUNT

} audio_manager_device_capabilities_t;

/**
 * @brief Get the audio device given the name of the device
 * 
 * The @c audio_manager_get_device_from_name() function returns the audio
 * manager device given the name of the device.
 * 
 * @param device_name The name of the device being returned.
 * 
 * @return The device identifier.
 */
audio_manager_device_t audio_manager_get_device_from_name( const char * device_name );

/**
 * @brief Get the audio device name given the type of the device
 * 
 * The @c audio_manager_get_device_name() function returns the audio
 * manager device name given the type of the device.
 * 
 * @param device The type of the device being returned.
 * 
 * @return The device name.
 */
const char * audio_manager_get_device_name( audio_manager_device_t device );

/**
 * @brief Check whether a given audio device is supported by the system
 * 
 * The @c audio_manager_is_device_supported() function checks whether a
 * given audio device is currently supported by the system. Unsupported 
 * audio devices would result in errors when used against other audio manager
 * interfaces, such as volume, event, and concurrency.
 * 
 * @param dev The type of the audio device to check against.
 * @param supported True, if the specified audio device is supported; false, 
 * otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_is_device_supported( audio_manager_device_t dev, 
                                       bool * supported);

/**
 * @brief Check whether a given audio device is connected to the system
 * 
 * The @c audio_manager_is_device_connected() function checks whether a
 * given audio device is currently connected to the system. Disconnected 
 * audio devices are not picked by the audio manager as a valid routing 
 * destination/source.
 * 
 * @param dev The type of the audio device to check against.
 * @param connected True, if the specified audio device is connected; false,
 * otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_is_device_connected( audio_manager_device_t dev, 
                        bool * connected);

/**
 * @brief Check whether a given audio device is suspended by the system
 * 
 * The @c audio_manager_is_device_suspended() function checks whether a
 * given audio device is currently suspended by the system. Suspended 
 * audio devices are not picked by the audio manager as a valid routing 
 * destination/source.
 * 
 * @param dev The type of the audio device to check against.
 * @param suspended True, if the specified audio device is suspended; false,
 * otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_is_device_suspended( audio_manager_device_t dev, 
                        bool * suspended);

/**
 * @brief Check whether a given audio device is kept alive by the system
 * 
 * The @c audio_manager_is_device_kept_alive() function checks whether a
 * given audio device is currently kept alive by the system even when 
 * no audio streams are active. This is typically done to avoid excessive 
 * audio artifacts caused by hardware transitions.
 * 
 * @param dev The type of the audio device to check against.
 * @param keep_alive True, if the specified audio device is kept alive; false,
 * otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_is_device_kept_alive( audio_manager_device_t dev, 
                        bool * keep_alive);

/**
 * @brief Check whether the mirror mode of the HDMI settings is on
 * 
 * The @c audio_manager_is_hdmi_in_mirror_mode() function checks whether the
 * HDMI is currently set to mirror mode. 
 * 
 * @param mirror_mode True, if the HDMI is set to mirror mode; false, otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_is_hdmi_in_mirror_mode( bool * mirror_mode);

/**
 * @brief Get the audio configuration of a given audio device
 * 
 * The @c audio_manager_get_device_audio_config() function returns
 * the audio configuration of the given audio device, using
 * @c audio_manager_device_audio_config_t.
 *
 * @param dev The type of the audio device to query. If @c AUDIO_DEVICE_DEFAULT
 * is passed in, the @c num_in_channels returned represents the number of
 * input channels of the current default input device. The rest of the fields
 * represent the settings of the current default output device.
 * @param config The audio configuration.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_audio_config( audio_manager_device_t dev, 
                        audio_manager_device_audio_config_t * config);

/**
 * @brief Get the audio capabilities of a given audio device
 * 
 * The @c audio_manager_get_device_capabilities() function returns
 * the requested capabilities of the given audio device.
 *
 * @param dev The type of the audio device to query.
 * @param in A list of capabilities requested. 
 * @param out The output pointers must match the type required for each input.
 * @param count The number of elements in each of the @c in and @c out arrays.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_audio_capabilities( audio_manager_device_t dev, 
                        audio_manager_device_capabilities_t * in,
                        void **out,
                        int count);

/**
 * @brief Deprecated: Get the output audio path of a given audio device
 * 
 * The @c audio_manager_get_device_audio_path() function returns
 * the audio output path of a given audio device.
 * 
 * @deprecated This function is deprecated. This function should not be
 * used in new code. The path should simply be the name of the device.
 *
 * @param dev The type of the audio device to query.
 * @param path The audio path.
 * @param size The size of the path buffer. If not sufficient, the minimum 
 * size to store the path is returned.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int __attribute__((deprecated)) audio_manager_get_device_audio_path( audio_manager_device_t dev, 
                        char * path, int * size);



/**
 * @brief Get whether an audio output device is public
 * 
 * The @c audio_manager_get_device_audio_public() function returns
 * whether an audio output device is public, which means it can be heard by 
 * many people.
 *
 * @param dev The type of the audio device to query.
 * @param pub True, if the device is public; false, otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_audio_public( audio_manager_device_t dev, 
                        bool * pub);


/**
 * @brief Get the preferred system audio output path
 * 
 * The @c audio_manager_get_preferred_audio_output_path() function returns
 * the preferred system audio output path.
 *
 * @param path The audio path.
 * @param size The size of the path buffer. If not sufficient, the minimum 
 * size to store the path is returned.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_preferred_audio_output_path( char * path, int * size );

/**
 * @brief Get the preferred system audio input path
 * 
 * The @c audio_manager_get_default_audio_input_path() function returns
 * the preferred system audio input path.
 *
 * @param path The audio path.
 * @param size The size of the path buffer. If not sufficient, the minimum 
 * size to store the path is returned.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_preferred_audio_input_path( char * path, int * size );

/**
 * @brief Get the capabilities of a given audio device
 * 
 * The @c audio_manager_get_device_capability() function returns
 * the capabilities of a given audio device indicating whether
 * it is capable of output and/or input.
 *
 * @param dev The type of the audio device to query.
 * @param cap_mask The capabilities of the audio device, given as a mask of 
 * @c audio_manager_device_capability_t.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_capability( audio_manager_device_t dev, 
                        audio_manager_device_capability_t * cap_mask);

/**
 * @brief Get the type of volume control of a given audio device
 * 
 * The @c audio_manager_get_device_volume_control() function 
 * returns the type of the volume control of a given audio device. 
 *
 * @param dev The type of the audio device to query.
 * @param control The type of the volume control.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_volume_control( audio_manager_device_t dev, 
                        audio_manager_device_volume_control_t * control);

/**
 * @brief Get the dependency of a given audio device
 * 
 * The @c audio_manager_get_device_dependency() function 
 * returns the dependency of a given audio device. An audio 
 * device with an inactive (suspended/unsupported/disconnected) 
 * dependency is not picked by the audio manager as a 
 * valid routing destination/source.
 *
 * @param dev The type of the audio device to query.
 * @param dev_dependent The associated dependent audio device.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_dependency( audio_manager_device_t dev, 
                        audio_manager_device_t * dev_dependent);

/**
 * @brief Get the current default audio output device picked 
 * by audio manager
 * 
 * The @c audio_manager_get_default_device() function 
 * returns the type of the default audio output device 
 * picked by the audio manager.
 *
 * @param dev The default audio device.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_default_device( audio_manager_device_t * dev );

/**
 * @brief Get the current default audio input device picked 
 * by audio manager
 * 
 * The @c audio_manager_get_default_input_device() function 
 * returns the type of the default audio input device 
 * picked by the audio manager.
 *
 * @param dev The default audio input device.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_default_input_device( audio_manager_device_t * dev );

/**
 * @brief Get the current button states of a given output device
 * 
 * The @c audio_manager_get_device_button_states() function 
 * returns the states of all the supported buttons of a given device. Currently,
 * only headset is supported.
 *
 * @param dev The default audio device.
 * @param state The current button states.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_get_device_button_states( audio_manager_device_t dev, 
                        audio_manager_headset_button_state_t * state);


// privilege calls
/**
 * @brief [privilege] Deprecated: Wake up a given audio device and keep it awake 
 * 
 * The @c audio_manager_set_device_keep_alive() function 
 * puts the given audio device into non-sleep mode. In this mode,
 * the audio device never gets turned off, regardless of whether there
 * are any audio streams active or not.
 *
 * @deprecated This function is deprecated.
 *
 * @param dev The audio device.
 * @param keep_alive True, if the audio device is to be kept alive; false,
 * otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_device_keep_alive( audio_manager_device_t dev, bool keep_alive);

/**
 * @brief [privilege]Set HDMI audio in mirror mode
 * 
 * The @c audio_manager_set_hdmi_mirror_mode() function 
 * puts the HDMI audio in mirror mode, which routes audio
 * automatically to the HDMI.
 *
 * @param mirror_mode True, if the HDMI is to be put in mirror mode; false,
 * otherwise.
 * 
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_hdmi_mirror_mode( bool mirror_mode );

/**
 * @brief [privilege]Set any audio device as connected
 * 
 * The @c audio_manager_set_device_connected() function 
 * sets the connected status of a given audio device to 
 * help the audio manager allocate proper audio devices as 
 * default.
 *
 * @param dev The type of the audio device.
 * @param connected True, if the given audio device is to be marked as
 * connected; false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_device_connected( audio_manager_device_t dev, bool connected);

/**
 * @brief [privilege]Set a supported audio device as suspended
 * 
 * The @c audio_manager_set_device_suspended() function sets the suspended 
 * status of a given audio device to help the audio manager allocate proper 
 * audio devices as default.
 *
 * @param dev The type of audio device.
 * @param suspended True, if the given audio device is to be marked as
 * suspended; false, otherwise.
 *
 * @return @c EOK upon success, negative @c errno upon failure.
 */
int audio_manager_set_device_suspended( audio_manager_device_t dev, bool suspended);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif //_AUDIO_MANAGER_DEVICE_H_INCLUDED

__SRCVERSION( "$URL$ $Rev$" )
