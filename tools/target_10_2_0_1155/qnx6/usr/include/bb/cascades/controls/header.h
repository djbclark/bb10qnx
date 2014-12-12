/* Copyright (C) 2011-2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_header_h
#define cascades_header_h

#include <QtCore/QString>

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>

namespace bb {
    namespace cascades {
    
    class HeaderPrivate;

    /*!
     * 
     * @brief A header that is used for grouping, or clustering items within a list.
     *
     * @image html header.png
     *
     * For example, in an messaging application, you might want to group together "Today's emails"
     * and "Older emails" in separate visual groups.
     *
     * @c %Header has two labels (@c title and @c subtitle). The title text is displayed with
     * a bolder font.
     *
     * Here's a simple example demonstrating the use of a @c %Header, in QML:
     *
     * @snippet tad/examples/controls/header/assets/main.qml header1_qml
     *
     * The size of the @c %Header behaves as follows:
     * - By default, the width of the control is adjusted automatically to fill its parent container.
     * - The width is adjustable using the @c Control::preferredWidth, @c Control::minWidth and @c Control::maxWidth properties.
     * - The height is fixed, so the properties @c Control::preferredHeight, @c Control::minHeight and @c Control::maxHeight are not used.
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Header : public Control
    {
    private:
        Q_OBJECT

        /*!
         * @brief A title string set on this header list item.
         *
         * @c QString::NULL is the default value for title text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title WRITE setTitle
                   RESET resetTitle NOTIFY titleChanged FINAL)

        /*!
         * @brief A subtitle string set on this header list item (displayed with a smaller font).
         *
         * @c QString::NULL is the default value for subtitle text.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString subtitle READ subtitle WRITE setSubtitle
                   RESET resetSubtitle NOTIFY subtitleChanged FINAL)

    public:
        /*!
         * @brief Constructs a @c %Header.
         *
         * Caller is responsible for properly setting the parent of this @c %Header.
         *
         * @since BlackBerry 10.0.0
         */
        Header();

        /*!
         * @brief Destructs this @c %Header.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Header();

        /*!
         * @brief Returns the title text set on this header list item.
         *
         * @c QString::NULL is returned when title text was not set.
         *
         * @since BlackBerry 10.0.0
         */
        const QString title() const;

        /*!
         * @brief Sets title text to a passed in title text.
         *
         * Title text will be empty if set to @c QString::NULL.
         * The @c titleChanged() signal is emitted if the title text gets changed.
         *
         * @param title The new title text to be set on this header list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setTitle(const QString & title);

        /*!
         * @brief Resets title text to a default value of QString::NULL.
         *
         * The @c titleChanged() signal is emitted if the title text gets changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetTitle();

        /*!
         * @brief Returns the subtitle text set on this header list item.
         *
         * @c QString::NULL is returned when subtitle text was not set.
         *
         * @since BlackBerry 10.0.0
         */
        const QString subtitle() const;

        /*!
         * @brief Sets subtitle text to a passed in text.
         *
         * Subtitle text will be empty if set to @c QString::NULL.
         * The @c subtitleChanged() signal is emitted if the subtitle text gets changed.
         *
         * @param subtitle The new subtitle text to be set on this header list item.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void setSubtitle(const QString & subtitle);

        /*!
         * @brief Resets subtitle text to a default value of QString::NULL.
         *
         * The @c subtitleChanged() signal is emitted if the subtitle text gets changed.
         *
         * @since BlackBerry 10.0.0
         */
        Q_SLOT void resetSubtitle();

    Q_SIGNALS:

        /*!
         * @brief Emitted when the title text changes in this header list item.
         *
         * @param title The new title text or 
         *                     QString::NULL if changed to an empty title.
         *
         * @since BlackBerry 10.0.0
         */
        void titleChanged(QString title);


        /*!
         * @brief Emitted when the subtitle text changes in this header list item.
         *
         * @param subtitle The new subtitle text or 
         *        QString::NULL if changed to an empty subtitle.
         *
         * @since BlackBerry 10.0.0
         */
        void subtitleChanged(QString subtitle);

    private:
        Q_DECLARE_PRIVATE(Header)
        Q_DISABLE_COPY(Header)

    public:

        typedef Header ThisClass;
        typedef Control BaseClass;

        /*!
         * @brief A builder template for constructing a Header.
         *
         * See Header::create() for getting a concrete Builder for
         * constructing a Header.
         *
         * @since BlackBerry 10.0.0
         */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            explicit TBuilder(BuiltType* node) :
            BaseClass::TBuilder<BuilderType, BuiltType>(node)
            { }
        public:
            /*!
             * @brief Sets the title text on the Header that is being constructed.
             *
             * @param title The new title text to be set on this header list item.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& title(const QString &title)
            {
                this->instance().setTitle(title);
                return this->builder();
            }

            /*!
             * @brief Sets the subtitle text on the Header that is being constructed.
             *
             * @param subtitle The new subtitle text to be set on this header list item.
             *
             * @since BlackBerry 10.0.0
             */
            BuilderType& subtitle(const QString &subtitle)
            {
                this->instance().setSubtitle(subtitle);
                return this->builder();
            }
        };

        /*!
         * @brief A concrete builder class for constructing a Header.
         *
         * @since BlackBerry 10.0.0
         */
        class Builder : public TBuilder<Builder, Header>
        {
         public:
             Builder() : TBuilder<Builder, Header>(new Header())
             { }
        };

        /*!
         * @brief Creates a Header and wraps it into a builder that
         * allows for "builder pattern" initialization:
         *
         * @snippet tad/examples/controls/header/src/HeaderExamples.cpp header1
         *
         * @since BlackBerry 10.0.0
         * @since tag injection and copyright date fixes
         */
        static Builder create()
        {
            return Builder();
        }
    };
}
}

QML_DECLARE_TYPE(bb::cascades::Header)


#endif // cascades_header_h


