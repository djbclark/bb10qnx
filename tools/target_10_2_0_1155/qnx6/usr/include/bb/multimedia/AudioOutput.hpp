/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_AUDIOOUTPUT_HPP
#define BB_MULTIMEDIA_AUDIOOUTPUT_HPP

#include <bb/multimedia/Global>

#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile AudioOutput.hpp <bb/multimedia/AudioOutput>
 *
 *
 * @brief Represents the audio output options for a media player.
 * 
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT AudioOutput
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the audio output options for a media player.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type
    {
        /*!
         * @brief Represents no audio output.
         *
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief Represents the preferred audio output.
         *
         * @since BlackBerry 10.0.0
         */
        Default = 1,
    };

private:
    /*! @cond PRIVATE */
    AudioOutput();
    ~AudioOutput();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

#endif /* BB_MULTIMEDIA_AUDIOOUTPUT_HPP */
