/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 * Proprietary and confidential.
 */

#ifndef cascades_abstractshortcut_h
#define cascades_abstractshortcut_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/UIObject>

namespace bb {
    namespace cascades {
        
        class AbstractShortcutPrivate;

         /*!
         * @brief The base class for all shortcut subclasses.
         *
         * All subclasses can be added to a @c AbstractPane, @c Control, and @c AbstractActionItem
         *
         * @xmlonly
         *     <apigrouping group="User interface/Application structure"/>
         * @endxmlonly
          *
          * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT AbstractShortcut : public UIObject {
            Q_OBJECT

            /*!
             * @brief Describes whether the current shortcut is enabled or disabled.
             *
             * By default a shortcut is enabled.
             *
             * @since BlackBerry 10.1.0
             */
            
            Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled RESET resetEnabled NOTIFY enabledChanged FINAL)
        public:
            virtual ~AbstractShortcut();
                      
            /*!
             * @brief Sets the @c enabled state of the shortcut.
             *
             * After the operation is completed and the @c enabled state is changed,
             * the @c enabledChanged() signal is emitted.
             *
             * @param enabled If @c true the shortcut is enabled, and if @c false the shortcut is disabled.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void setEnabled(bool enabled);
            
            /*!
             * @brief Resets the @c #enabled state of the shortcut to @c true.
             *
             * After the operation is completed and the @c enabled state
             * is changed, the @c enabledChanged() signal is emitted.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void resetEnabled();                      
            
            /*!
             * @brief Gets the @c #enabled state of the shortcut.
             *
             * @return @c true if this shortcut is enabled and @c false otherwise.
             *
             * @since BlackBerry 10.1.0
             */
            bool isEnabled() const;
            
        Q_SIGNALS:                      
            
            /*!
             * @brief Emitted when the @c #enabled property on the shortcut changes.
             *
             * @param enabled If @c true the shortcut is enabled, if @c false the shortcut is disabled.
             *
             * @since BlackBerry 10.1.0
             */
            void enabledChanged(bool enabled);
            
            /*!
             * @brief Emitted when the @c %AbstractShortcut is triggered by the user.
             *
             * @since BlackBerry 10.1.0
             */
            void triggered();

        /*! @cond PRIVATE */
        protected:          
            AbstractShortcut(AbstractShortcutPrivate &_d_ptr, UIObject *parent = 0);
        /*! @endcond */

        private:            
            Q_DECLARE_PRIVATE(AbstractShortcut)       
            Q_DISABLE_COPY(AbstractShortcut)

        public:
            /*! @cond PRIVATE */
            typedef AbstractShortcut ThisClass;
            typedef BaseObject BaseClass;
            /*! @endcond */
            
            /*!
             * @brief A builder template for constructing an @c %AbstractShortcut. To retrieve the builder, call
             * @c Shortcut::create().
             *
             * @since BlackBerry 10.1.0
             */
            template <typename BuilderType, typename BuiltType>
            class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
            {
            protected:
                TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
                {
                }
            public:                               
                /*!
                 * @brief Enable or disable @c %AbstractShortcut.
                 *
                 * Using this convenience function in the builder pattern is the equivalent of the
                 * following:
                 * @code
                 * myShortcut->setEnabled(false);
                 * @endcode
                 *
                 * @param enabled Describes whether this @c %AbstractShortcut should be activated when
                 *                 a corresponding shortcut event is available for handling.
                 *
                 * @since BlackBerry 10.1.0
                 */
                BuilderType& enable(bool enabled)
                {
                    this->instance().setEnabled(enabled);
                    return this->builder();
                }
                
                /*!
                 * @brief A convenience method for connecting passed receiver's slot to
                 * the @c triggered() signal with the default connection type
                 * @c Qt::AutoConnection.
                 *
                 * Example:
                 * @code
                 * Shortcut *shortcut = Shortcut::create()
                 *     .key("a")
                 *     .onTriggered(this, SLOT(onShortcutTriggeredHandler()));
                 * @endcode
                 *
                 * @param receiver A receiver object that is not @c null.
                 * @param method A name for the slot that can be connected in the receiver object.
                 *                 This parameter cannot be @c null.
                 *
                 * @see BaseObject::TBuilder::connect()
                 *
                 * @since BlackBerry 10.1.0
                 */
                BuilderType& onTriggered(const QObject* receiver, const char *method) {
                    this->connect(SIGNAL(triggered()), receiver, method);
                    return this->builder();
                }
            };                
        };
    } // namespace Cascades
}


QML_DECLARE_TYPE(bb::cascades::AbstractShortcut)


#endif // cascades_abstractshortcut_h
