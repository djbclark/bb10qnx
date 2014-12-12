/* Copyright (C) 2012-2013 Research In Motion Limited. Proprietary and confidential. */
#ifndef BB_CASCADES_TEXTINPUTFLAG_H
#define BB_CASCADES_TEXTINPUTFLAG_H

#include <bb/cascades/bbcascades_global.h>
#include <QtDeclarative/QtDeclarative>

namespace bb {
    namespace cascades {

        /*!
        * @brief Flags for turning on and off different text features (for example, spell check).
        *
        * @xmlonly
        * <apigrouping group="User interface/Text"/>
        * @endxmlonly
         *
         * @since BlackBerry 10.0.0
        */
        class TextInputFlag
        {
            Q_GADGET
                Q_ENUMS(Type)
                Q_FLAGS(Types)

        public:
            /*!
            * @brief Text feature flags used to turn on and of text features.
            *
            * If both the on and off 
            * flag for a certain feature is set to @c 1 at the same time, the behavior is undefined. 
            * If both are set to @c 0, the default behavior for the given control and input mode
            * are used.
            *
            * @xmlonly
            * <qml>
            * <enum flagsType="bb::cascades::TextInputFlag::Types"/>
            * </qml>
            * @endxmlonly
             *
             * @since BlackBerry 10.0.0
            */
            enum Type {
                /*! @brief Default settings for all features will be used.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Default = 0x00,
                /*! @brief Turn on spell checking.
                 *
                 * @since BlackBerry 10.0.0
                 */
                SpellCheck = (1<<0),
                /*! @brief Turn off spell checking.
                 *
                 * @since BlackBerry 10.0.0
                 */
                SpellCheckOff = (1<<1),
                /*! @brief Turn on word predictions.
                 *
                 * @since BlackBerry 10.0.0
                 */
                Prediction = (1<<2),
                /*! @brief Turn off word predictions.
                 *
                 * @since BlackBerry 10.0.0
                 */
                PredictionOff = (1<<3),
                /*! @brief Turn on auto correction.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCorrection = (1<<4),
                /*! @brief Turn off auto correction.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCorrectionOff = (1<<5),
                /*! @brief Turn on auto capitalization.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCapitalization = (1<<6),
                /*! @brief Turn off auto capitaliztion.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoCapitalizationOff = (1<<7),
                /*! @brief Turn on auto period.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoPeriod = (1<<8),
                /*! @brief Turn off auto period.
                 *
                 * @since BlackBerry 10.0.0
                 */
                AutoPeriodOff = (1<<9),
                /*! @brief Turn on word substitution.
                 *
                 * @since BlackBerry 10.0.0
                 */
                WordSubstitution = (1<<10),
                /*! @brief Turn off word substitution.
                 *
                 * @since BlackBerry 10.0.0
                 */
                WordSubstitutionOff = (1<<11),
                /*! @brief Turn on virtual keyboard.
                 *
                 * @since BlackBerry 10.0.0
                 */
                VirtualKeyboard = (1<<12),
                /*! @brief Turn off virtual keyboard.
                 *
                 * @since BlackBerry 10.0.0
                 */
                VirtualKeyboardOff = (1<<13),
                /*! @brief Force the keyboard to Latin-1. This affects the VKB layout and 
                 *         language predictions but does not filter non keyboard input such
                 *         as paste or setting the text programmatically.
                 *
                 * @since BlackBerry 10.2.0
                 */
                LatinOnly = (1<<14),
                /*! @brief Turn off force Latin-1 keyboard.
                 *
                * @since BlackBerry 10.2.0
                 */
                LatinOnlyOff = (1<<15)

            };

            /*!
            * @brief Bitfield containing information of what features are enabled or disabled.
            *
            * Overrides the default beahior for the control.
            * @see bb::cascades::TextInputFlag::Type
            *
            * @since BlackBerry 10.0.0
            */
            Q_DECLARE_FLAGS(Types, Type)

        private:
            /*! @cond PRIVATE */
            TextInputFlag();
            virtual ~TextInputFlag();
            /*! @endcond */
        };

    }
}

/*! @cond PRIVATE */
QML_DECLARE_TYPE(bb::cascades::TextInputFlag::Types)
Q_DECLARE_OPERATORS_FOR_FLAGS(bb::cascades::TextInputFlag::Types)
/*! @endcond */


#endif // BB_CASCADES_TEXTINPUTFLAG_H
