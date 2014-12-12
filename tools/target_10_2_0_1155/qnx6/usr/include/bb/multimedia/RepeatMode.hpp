/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_REPEATMODE_HPP
#define BB_MULTIMEDIA_REPEATMODE_HPP

#include <bb/multimedia/Global>

#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile BufferStatus.hpp <bb/multimedia/RepeatMode>
 *
 * @brief Represents the various repeat modes.
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
class BB_MULTIMEDIA_EXPORT RepeatMode
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents the various repeat modes.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief Indicates that no repetition is to take place, and that playback will stop at the end of media.
         * 
         * @since BlackBerry 10.0.0
         */
        None = 0,

        /*!
         * @brief Indicates that playback of the current track should be repeated once playback of it has completed.
         * 
         * @since BlackBerry 10.0.0
         */
        Track = 1,

        /*!
         * @brief Indicates that once playback has finished playback should begin from the start of the playlist.
         * 
         * @since BlackBerry 10.0.0
         */
        All = 2,
    };

private:
    /*! @cond PRIVATE */
    RepeatMode();
    ~RepeatMode();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

#endif /* BB_MULTIMEDIA_REPEATMODE_HPP */
