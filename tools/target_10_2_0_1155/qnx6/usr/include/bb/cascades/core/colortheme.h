/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * Proprietary and confidential.
 */

#ifndef cascades_colortheme_h
#define cascades_colortheme_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>

#include <bb/cascades/VisualStyle>

namespace bb {
    namespace cascades {
    class ColorThemePrivate;

    /*! 
     * @brief A class representing the color configurations of the theme.
     *
     * The @c style property specifies the @c VisualStyle that represents the
     * color of the theme. You can read the @c ColorTheme for an app using the
     * @c Application::themeSupport property.
     *
     * @see @c Theme, @c VisualStyle
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ColorTheme : public QObject
    {
    private:
        Q_OBJECT

        /*!
         * @brief Specifies the current @c VisualStyle used in the @c %ColorTheme.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::VisualStyle::Type style READ style CONSTANT FINAL);

    public:

        /*!
         * @brief Retrieves the @c %VisualStyle for the theme.
         *
         * @return The application's @c VisualStyle.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::VisualStyle::Type style() const;

    private:
        /*! @cond PRIVATE */
        ColorThemePrivate* const d_ptr;
        explicit ColorTheme(const VisualStyle::Type visualStyle, QObject *parent = 0);
        virtual ~ColorTheme();
        Q_DECLARE_PRIVATE(ColorTheme)
        Q_DISABLE_COPY(ColorTheme)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ColorTheme)

#endif // cascades_colortheme_h
