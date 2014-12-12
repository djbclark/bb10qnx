/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * Proprietary and confidential.
*/

#ifndef cascades_themesupport_h
#define cascades_themesupport_h

#include <bb/cascades/bbcascades_global.h>

#include <QObject>
#include <QtDeclarative/QtDeclarative>


namespace bb {
    namespace cascades {
    class Theme;
    class ThemeSupportPrivate;

    /*!
     * @brief A class containing theme related functionality.
     *
     * This class offers functionality to obtain the current theme and listen
     * for theme related changes. At this point in time, no support exists for
     * setting the theme at run time.
     *
     * Each theme has a @c VisualStyle that determines the colors used for
     * controls and the default container background. The two visual
     * styles are @c VisualStyle::Bright and @c VisualStyle::Dark, the default
     * being @c Bright.
     *
     * @image html theme_examples.png
     *
     * To change the application's theme to Dark specify the following configuration value
     * in the application's bar-descriptor.xml file.
     *
     * @code
     * <env var="CASCADES_THEME" value="dark"/>
     * @endcode
     *
     * Here are some examples for how to check the @c VisualStyle of the currently
     * set theme for the application:
     *
     * C++:
     * @code
     * void ThemeTest()
     * {
     *     Label* pLabel = Label::create();
     *
     *     ThemeSupport* pThemeSupport = Application::instance()->themeSupport();
     *     Theme* pTheme = pThemeSupport->theme();
     *     ColorTheme* pColTheme = pTheme->colorTheme();
     *
     *     switch(pColTheme->style()) {
     *         case VisualStyle::Bright:
     *             pLabel->setText("Theme: Bright");
     *             break;
     *
     *         case VisualStyle::Dark:
     *             pLabel->setText("Theme: Dark");
     *             break;
     *
     *         default:
     *             pLabel->setText("Theme: Unknown");
     *             break;
     *     }
     * }
     * @endcode
     *
     * QML:
     * @code
     * Container {
     *     id: cont1
     *
     *     function themeStyleToString(style){
     *         switch(style) {
     *             case VisualStyle.Bright:    return "Theme: Bright"
     *             case VisualStyle.Dark:      return "Theme: Dark"
     *         }
     *         return "Theme: UNKNOWN :("
     *     }
     *
     *     Label {
     *         id: themeLabel;
     *         text: cont1.themeStyleToString(Application.themeSupport.theme.colorTheme.style)
     *     }
     * }
     * @endcode
     *
     * @see @c Application, @c Theme, @c VisualStyle
     *
     * @xmlonly
     *     <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT ThemeSupport : public QObject
    {
    private:
        Q_OBJECT

        /*!
         * @brief Provides access to the current theme used in the application.
         *
         * Typically connected from @c %Application:
         * @code
         *     QObject::connect((Application*)Application::instance()->themeSupport(),
         *                      SIGNAL(themeChanged(const bb::cascades::Theme*)),
         *                      this,
         *                      SLOT(onThemeChanged(const bb::cascades::Theme*)));
         * @endcode
         *
         * @see Theme
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::Theme* theme READ theme NOTIFY themeChanged FINAL);

    public:

        /*!
         * @brief Retrieves the current theme.
         *
         * Ownership of the returned object is not transferred.
         *
         * @return The application's theme.
         * @see Theme
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::Theme* theme() const;

    Q_SIGNALS:

        /*!
         * @brief Emitted when the theme for this application has changed.
         *
         * @param theme a new theme or @c 0 if there was an error
         *
         * @since BlackBerry 10.0.0
         */
        void themeChanged(const bb::cascades::Theme* theme);

    private:
        /*! @cond PRIVATE */
        ThemeSupportPrivate* const d_ptr;
        explicit ThemeSupport(QObject *parent = 0);
        virtual ~ThemeSupport();
        Q_DECLARE_PRIVATE(ThemeSupport)
        Q_DISABLE_COPY(ThemeSupport)
        /*! @endcond */
    };
}
}

QML_DECLARE_TYPE(bb::cascades::ThemeSupport)

#endif // cascades_themesupport_h
