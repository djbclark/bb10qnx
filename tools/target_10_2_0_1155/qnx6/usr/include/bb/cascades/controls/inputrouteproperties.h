#ifndef bb_cascades_inputrouteproperties_h
#define bb_cascades_inputrouteproperties_h

#include <bb/cascades/UIObject>

namespace bb {
    namespace cascades {
        class InputRoutePropertiesPrivate;

        /*!
         * @brief Optional group of properties that can be set on controls to define their role in the propagation of input events
         * and influence the default routing logic.
         *
         * This is typically used to indicate that the control is the default target of some type of input event when
         * a target cannot be determined by the another propagation mechanism.
         * E.g. if there is no focused control, setting @c inputRoute.primaryKeyTarget to @c true on a control will make it the target
         * of key events.
         *
         * @xmlonly
         * <apigrouping group="User interface/Core controls"/>
         * @endxmlonly
         *
         * @since BlackBerry 10.1.0
         */
        class BBCASCADES_EXPORT InputRouteProperties : public UIObject {
            Q_OBJECT

            /*!
             * @brief Indicates that the owner of these properties should be treated as primary key target.
             *
             * This property is read by the event system when a key event is about to be propagated and
             * there is no focused control. The event system scans the content of the current page, and
             * when a page or control with this property set to true is found, it will be used as the
             * target for the key event. The event then bubbles up to the root according to standard
             * key event propagation rules.
             *
             * The intent is to enable the developer to set a primary key target per page. If the primary
             * key target needs to change for some reason, it is up to the developer to reset and set this
             * property where needed. The scan will always pick the first occuring primary key target, in
             * a pre-order depth first search from the page (meaning parents have precedence over children).
             *
             * @note Focus set explicitly with @c Control::requestFocus() overrides the effect of this property. 
             * I.e. once focus has been set on a control, this property has no effect.
             *
             * @note There is no visual hint to indicate which control or page is the effective main key
             * target. It can be confusing for a user if it changes within the same screen.
             *
             * The default value for this property is @c false.
             *
             * QML usage:
             * @snippet tad/examples/controls/control/assets/main.qml control_qml2
             *
             * C++ usage:
             * @snippet tad/examples/controls/control/src/ControlExamples.cpp control2
             *
             * C++ usage (with builder):
             * @snippet tad/examples/controls/control/src/ControlExamples.cpp control1
             *
             * @see Page::inputRoute, Control::inputRoute
             *
             * @since BlackBerry 10.1.0
             */
            Q_PROPERTY(bool primaryKeyTarget READ isPrimaryKeyTarget WRITE setPrimaryKeyTarget RESET resetPrimaryKeyTarget NOTIFY primaryKeyTargetChanged FINAL)

        public:
            /*!
             * @brief Constructs an @c InputRouteProperties object with a parent @c UIObject.
             *
             * The ownership of the @c InputRouteProperties object is transferred to the parent,
             * if a parent is specified.
             *
             * @param parent The parent UIObject, or @c 0. This parameter is optional.
             * The default is @c 0 if you don't specify a parent.
             *
             * @since BlackBerry 10.1.0
             */
            explicit InputRouteProperties(UIObject *parent = 0);
            virtual ~InputRouteProperties();

            /*!
             * @brief Returns the @c #primaryKeyTarget state of the control.
             *
             * @return @c true if the control is set to be primary key target, @c false otherwise.
             *
             * @since BlackBerry 10.1.0
             */
            bool isPrimaryKeyTarget() const;

            /*!
             * @brief Sets the @c #primaryKeyTarget state of the control.
             *
             * @param primaryKeyTarget If @c true the control is a primary key target and if @c false
             * the control is not a primary key target.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void setPrimaryKeyTarget(bool primaryKeyTarget);

            /*!
             * @brief Resets the @c #primaryKeyTarget state of the control to @c false.
             *
             * @since BlackBerry 10.1.0
             */
            Q_SLOT void resetPrimaryKeyTarget();

Q_SIGNALS:
            /*!
             * @brief Emitted when the @c #primaryKeyTarget property changes.
             *
             * @param primaryKeyTarget The new value of @c #primaryKeyTarget.
             *
             * @since BlackBerry 10.1.0
             */
            void primaryKeyTargetChanged(bool primaryKeyTarget);

        private:
            /*! @cond PRIVATE */
            Q_DECLARE_PRIVATE(InputRouteProperties)
            Q_DISABLE_COPY(InputRouteProperties)
            /*! @endcond */


        };
    }
}

QML_DECLARE_TYPE(bb::cascades::InputRouteProperties)

#endif    // bb_cascades_inputrouteproperties_h
