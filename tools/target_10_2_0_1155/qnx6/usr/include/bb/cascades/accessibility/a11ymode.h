/* Copyright (C) 2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_a11ymode_h
#define cascades_a11ymode_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
  namespace cascades {

    /*!
     * @brief A set of modes used to specify how a control and it's subtree is exposed to assistive technologies.
     *
     * @xmlonly
     * <apigrouping group="User interface/Accessibility"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT A11yMode
    {
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
         * @brief Specifies the different accessibility modes for a control.
         *
         * @since BlackBerry 10.2.0
         */
        enum Type
        {
            /*! @brief Accessibility mode is automateded ny framework.
             *
             * Framework automates accessibility mode based on accessible
             * information and context. Typically accessibility information
             * is assumed to be available, unless any parent is configured
             * with accessibilityMode = Collapsed
             *
             * @since BlackBerry 10.2.0
             */
            Default,
            /*! @brief Accessibility is hidden for the control and it's subtree.
             *
             * @since BlackBerry 10.2.0
             */
            Collapsed
        };

    private:
        /*! @cond PRIVATE */
        A11yMode();
        ~A11yMode();
        /*! @endcond */
    };
  }
}

#endif // cascades_a11ymode_h

