/**
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */
#ifndef BB_CASCADES_MAPS_RENDER_ENGINE_INFO_HPP
#define BB_CASCADES_MAPS_RENDER_ENGINE_INFO_HPP

#include <bb/platform/geo/Global>
#include <QSharedDataPointer>

namespace bb {
namespace cascades {
namespace maps {

class RenderEngineInfoPrivate;

/**
 * @headerfile RenderEngineInfo.hpp <bb/cascades/maps/RenderEngineInfo>
 *
 * @brief The characteristics of a render engine.
 *
 * @xmlonly
 * <apigrouping group="Location/Maps"/>
 * <library name="bbcascadesmaps"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_PLATFORM_GEO_EXPORT RenderEngineInfo {
    public:
        /**
         * @brief Basic constructor.
         *
         * @since BlackBerry 10.0.0
         */
        RenderEngineInfo();

        /**
         * @brief Copy constructor.
         *
         * @param src The object from which to copy information.
         *
         * @since BlackBerry 10.0.0
         */
        RenderEngineInfo( const RenderEngineInfo& src );

        /**
         * @brief Destructor.
         *
         * @since BlackBerry 10.0.0
         */
        ~RenderEngineInfo();

        /**
         * @brief Assignment operator.
         *
         * @param src The object from which to copy information.
         *
         * @since BlackBerry 10.0.0
         */
        RenderEngineInfo& operator=( const RenderEngineInfo& src );

        /**
         * @brief Gets the minimum supported altitude.
         *
         * Defaults to 1 meter.
         *
         * @return The minimum altitude.
         *
         * @since BlackBerry 10.0.0
         */
        int minimumAltitude() const;

        /**
         * @brief Sets the minimum supported altitude.
         *
         * @param minimumAltitude The new minimum altitude.
         *
         * @since BlackBerry 10.0.0
         */
        void setMinimumAltitude( int minimumAltitude );

        /**
         * @brief Gets the maximum supported altitude.
         *
         * Defaults to 23 000 000 meters.
         *
         * @return The maximum altitude.
         *
         * @since BlackBerry 10.0.0
         */
        int maximumAltitude() const;

        /**
         * @brief Sets the maximum supported altitude.
         *
         * @param maximumAltitude The new maximum altitude.
         *
         * @since BlackBerry 10.0.0
         */
        void setMaximumAltitude( int maximumAltitude );

        /**
         * @brief Indicates whether the @c RenderEngine supports map
         * "tilt" by gesture.
         *
         * @since BlackBerry 10.0.0
         */
        bool tiltByGestureSupported() const;

        /**
         * @brief Sets the flag if @c RenderEngine supports map "tilt"
         * by gesture.
         *
         * @param supported @c true if tilt is supported.
         *
         * @since BlackBerry 10.0.0
         */
        void setTiltByGestureSupported( bool supported );

        /**
         * @brief Indicates whether the @c RenderEngine supports map
         * "rotate" by gesture.
         *
         * @since BlackBerry 10.0.0
         */
        bool rotateByGestureSupported() const;

        /**
         * @brief Sets the flag if @c RenderEngine supports map "rotate"
         * by gesture.
         *
         * @param supported @c true if rotate is supported.
         *
         * @since BlackBerry 10.0.0
         */
        void setRotateByGestureSupported( bool supported );

        /**
         * @brief Indicates whether the @c RenderEngine supports
         * displaying traffic conditions within the map.
         *
         * @return @c true if the @c RenderEngine supports displaying
         * inline traffic conditions, @c false otherwise.
         * @since BlackBerry 10.2.0
         */
        bool isInlineTrafficSupported();

        /**
         * @brief Sets the flag for indicating whether the @c RenderEngine
         * supports displaying traffic conditions within the map.
         *
         * If unset, the value is @c false.
         *
         * @param supported @c true if the @c RenderEngine supports displaying
         * inline traffic conditions, @c false otherwise.
         * @since BlackBerry 10.2.0
         */
        void setInlineTrafficSupported( bool supported );

    private:
        QSharedDataPointer<RenderEngineInfoPrivate> p;
};

} /* namespace maps */
} /* namespace cascades */
} /* namespace bb */

#endif /* BB_CASCADES_MAPS_RENDER_ENGINE_INFO_HPP */
