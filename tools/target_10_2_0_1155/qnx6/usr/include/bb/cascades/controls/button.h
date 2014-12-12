/* Copyright (C) 2011-2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_button_h
#define cascades_button_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/abstractbutton.h>
#include <bb/cascades/resources/image.h>

namespace bb {
    namespace cascades {

    class ButtonPrivate;
    class Container;

    /*!
     *
     * @brief A clickable button with a fixed height and an optional image and text.
     *
     * A button is used to intercept touch events on the screen in order to affect application
     * behavior and emit a @c Button::clicked() signal that can be 
     * used to affect application behavior, 
     * for example by connecting the @c clicked() signal to the slot of another object,
     * or using the @c onClicked signal handler in QML to respond to the button click.
     * 
     * The @c %Button class provides methods for setting or resetting its text and image (the default state
     * is no text and no image). When the text or image
     * is changed, corresponding signals are emitted (@c Button::textChanged() and @c Button::imageChanged()).
     * 
     * The visual appearance of the button is predefined and cannot be changed. The button text has predefined font, font size, and color. The
     * aspect ratio of the button's image scales to fit inside the button. A button with text but
     * no image, or an image with no text, will show the text or
     * image centered on the button, whereas a button with both text and image will be
     * left-aligned, as can be seen in the examples below. 
     *
     * A button with text:
     * @image html button_txt.png
     *
     * A button with an image and text:
     * @image html button_str_img.png
     *
     * A button with only an image:
     * @image html button_img.png
     *
     * The size of the button behaves as follows:
     * - By default, the width of the button has a device-dependent built-in value, but it is increased
     * automatically to fit an image and text if necessary.
     * - The width is adjustable using the Control::preferredWidth, Control::minWidth, and Control::maxWidth properties. 
     * - Setting the preferred width does not affect the size of the button if the preferred width is smaller
     * than is necessary to fit an image and text. 
     * - Setting the maximum width allows the width of the button to be smaller than the width required
     * to show the whole button text (and image, if it is also
     *   visible), causing the text to be truncated. However, the maximum width cannot be set
     * small enough to cause the image to be truncated.
     * - The height of the button is fixed, so the properties Control::preferredHeight, Control::minHeight, and Control::maxHeight are not used.
     *
     * Creating a Button with some text and an image, using the builder pattern:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button1
     *
     * Creating a default button and then setting the text and image properties:
     *
     * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button2
     *
     * Creating a %Button with some text and an image, in QML:
     *
     * @snippet tad/examples/controls/button/assets/main.qml button_qml
     *
     * @xmlonly
     * <apigrouping group="User interface/Core controls"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Button : public AbstractButton {
    private:
        Q_OBJECT

        /*!
         * @brief A text string to display on the button.
         *
         * The default value is @c QString::Null, indicating that no text is set.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString text READ text WRITE setText
                  RESET resetText NOTIFY textChanged FINAL)

        /*!
         * @brief An image to display on the button.
         *
         * The default value is an empty image, indicating that no image is set.
         *
         * @xmlonly
         * <qml>
         * <variant type="bb::cascades::Image"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QVariant image READ imageQml WRITE setImageQml
                  RESET resetImage NOTIFY imageChanged FINAL)

       /*!
        * @brief The location of an image to display on the button.
        *
        * If no image is set, an invalid QUrl is returned.
        * When the image source changes, the @c imageSourceChanged() signal is emitted.
        *
        * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource
                  RESET resetImageSource NOTIFY imageSourceChanged FINAL)

    public:
        /*!
         * @brief Constructs a clickable button and assigns a parent container.
         *
         * The ownership of the button is transferred to the parent if a parent is specified.
         *
         * @param parent The parent container, or @c 0. This parameter is optional. The default is @c 0 if you don't specify a parent.
         *
         * @since BlackBerry 10.0.0
         */
        explicit Button(Container * parent = 0);

        /*!
         * @brief Destructs the button.
         *
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Button();

        /*!
         * @brief Returns the text that is displayed on this button.
         *
         * @return A string that represents the text on the button, or @c QString::Null if no text is set.
         *
         * @since BlackBerry 10.0.0
         */
        const QString text() const;

        /*!
         * @brief Sets the text to display on this button.
         *
         * The button will attempt to resize itself to accommodate the text, if necessary.
         * The button may not be able to resize depending on the @c Control::maxWidth property
         * and other layout restrictions (e.g. not enough space amongst other controls).
         * In this case, the text is cropped.
         *
         * @param text A text string to set as the text on the button, or QString::Null to display no text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setText(const QString & text);

        /*!
         * @brief Resets the text for this button to @c QString::Null.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetText();

        /*!
         * @brief Returns the image that is displayed on this button.
         *
         * @return The @c Image that is displayed on the button, or an empty image if no image is set.
         *
         * @since BlackBerry 10.0.0
         */
        Image image() const;

        /*!
         * @brief Sets the image to display on this button.
         *
         * Once completed, the @c imageChanged() signal is emitted if the @c image parameter specifies an image
         * that is different than the image that was previously set for this button.
         *
         * @param image The @c Image to display on this button, or an empty image to display no image.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setImage(const bb::cascades::Image& image);

        /*!
         * @brief Resets the image for this button to an empty image.
         *
         * Once completed, the imageChanged() signal is emitted if the image for this button was not already set
         * to an empty image.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetImage();


         /*!
          * @brief Returns the image source.
          *
          * @return The source of the displayed image.
          *
          * @since BlackBerry 10.0.0
          */
        QUrl imageSource() const;

        /*!
          * @brief Sets the image for the button.
          *
          * This function emits an @c imageSourceChanged() signal if the currently set image source changes.
          *
          * An invalid @c QUrl indicates no image.
          *
          * @param source The image url.
         *
         * @since BlackBerry 10.0.0
          */
        Q_SLOT void setImageSource(const QUrl &source);

        /*!
          * @brief Resets the @c Image in the button to its default, meaning that no image is set.
          *
          * Once completed, the @c imageSourceChanged() signal is emitted if the currently set image source changes.
         *
         * @since BlackBerry 10.0.0
          */
        Q_SLOT void resetImageSource();


    Q_SIGNALS:
        /*!
         * @brief Emitted when the text on the button changes.
         *
         * @param text The new text string for this button, or @c QString::Null if no text is set.
         *
         * @since BlackBerry 10.0.0
         */
        void textChanged(QString text);

        /*!
         * @brief Emitted when the image for this button changes.
         *
         * @param image The new image for this button, or an empty image if no image is set.
         *
         * @xmlonly
         * <qml>
         * <param name="image" type="QVariant"/>
         * </qml>
         * @endxmlonly
         *
         * @since BlackBerry 10.0.0
         */
        void imageChanged(const bb::cascades::Image& image);

        /*!
         * @brief Emitted when the image source changes.
         *
         * @since BlackBerry 10.0.0
         */
        void imageSourceChanged(const QUrl& image);

        /*! @cond PRIVATE */
        /*!
         * Emitted when the image for the button changes. This is used for QML.
         */
        void imageChanged(const QVariant& image);
        /*! @endcond */

    private:
        /*! @cond PRIVATE */

        /*!
         * @brief Returns the image for the button.
         *
         * This is a private function needed by the QML. The returned QVariant is always an Image.
         * \warning The client must not call this function, instead image() should be called.
         *
         * \return A QVariant container the Image for the button or an empty image if no image was set (or was reset).
         */
        QVariant imageQml() const;

       /*!
        * @brief Sets the image for the button.
        *
        * The QVariant image can either be of type Image or a QString name. This is a private function
        * encapsulating setImage() needed by the QML.
        * \warning The client must not call this function, instead setImage() should be called.
        *
        * \param image A QVariant container either the Image or QString name of the image to set for
        * the button.
        */
        Q_SLOT void setImageQml(const QVariant & image);

        /*! \endcond */

        Q_DECLARE_PRIVATE(Button)
        Q_DISABLE_COPY(Button)

        /*! \cond PRIVATE */
        typedef Button ThisClass;  // The class in which scope we're currently inside
        typedef AbstractButton BaseClass; // References the class which ThisClass derives from
        /*! \endcond */

   public:
        /*!
         * @brief A builder template for constructing a button.
         *
         * To retrieve the builder, call Button::create().
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType> {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node) {}
        public:

            /*!
             * @brief Sets the text for this button.
             *
             * @param text The text string to set for the button, or @c QString::Null to display no text on the button.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& text(const QString &text) {
                this->instance().setText(text);
                return this->builder();
            }

            /*!
             * @brief Sets the image for this button.
             *
             * The button does not take ownership of the image once it's set.
             *
             * @param image The image to set, or an empty image to display no image.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& image(const Image& image) {
                this->instance().setImage(image);
                return this->builder();
            }

            /*!
             * @brief Sets the image for this button, identified by its name.
             *
             * @param url The name of the image to set for this button.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& imageSource(const QUrl &url) {
                return image(Image(url));
            }

            /*!
             * A convenience method for connecting passed receiver's slot to
             * the clicked() signal with the default connection type
             * Qt::AutoConnection.
             *
             * Example:
             * @code
             * Button *button = Button::create()
             *     .onClicked(this, SLOT(onClicked()));
             * @endcode
             *
             * @param receiver a non-@c null receiver object
             * @param method a non-null name of the slot in the receiver object to connect to
             *
             * @see BaseObject::TBuilder::connect()
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& onClicked(const QObject* receiver, const char *method) {
                this->connect(SIGNAL(clicked()), receiver, method);
                return this->builder();
            }
        };

        /*!
         * @brief A builder that constructs a button.
         *
         * To retrieve the builder, call @c Button::create().
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, Button> {
        public:
            explicit Builder() : TBuilder<Builder, Button>(new Button()) {}
        };

        /*!
         * @brief Creates and returns a builder for constructing a button.
         *
         * Using the builder to create a @c %Button:
         *
         * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button1
         *
         * @return A Builder used for constructing a button.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create() {
            return Builder();
        }

        /*!
         * @brief Creates and returns a builder for constructing a button with text.
         *
         * Using the builder to create a @c %Button:
         *
         * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button3
         *
         * This builder is a convenience constructor for creating a %Button with text. This
         * is equivalent to the following:
         * 
         * @snippet tad/examples/controls/button/src/ButtonExamples.cpp button4
         *
         * @param text A text string that represents the text to display on the button, or QString::Null to
         * display no text on the button.
         * @return A Builder used to create a button with text.
         *
         * @since BlackBerry 10.0.0
         */
        static Builder create(const QString & text) {
            return Builder().text(text);
        }
      };
}
}

QML_DECLARE_TYPE(bb::cascades::Button)

#endif
