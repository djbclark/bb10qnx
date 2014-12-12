/* Copyright (C) 2012-2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_webstorage_h
#define cascades_webstorage_h

#include <bb/cascades/bbcascades_global.h>

#include <QtCore/QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
  namespace cascades {

    class WebCookieJar;
    class WebStoragePrivate;

   /*!
    * @brief Utilities for accessing the storage for a @c WebView control.
    *
    * Each @c WebView instance has an associated @c WebStorage
    * which can be referenced by reading the @c WebView @c storage property.
    * You should never have any reason to create an instance of this class yourself.
    *
    * Note: Some storage is process wide and not tied an individual @c WebView.
    * For example, clearing cookies on one @c WebView will clear the cookies for all
    * other @c WebViews running inside the same process.
    *
    * @xmlonly
    * <apigrouping group="User interface/Web"/>
    * @endxmlonly
    *
    * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT WebStorage : public QObject
    {
        Q_OBJECT

        /*!
         * @brief A jar (database) containing web cookies.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::WebCookieJar* cookieJar READ cookieJar CONSTANT)

    public:
        /*!
         * @brief Returns the cookie jar.
         *
         * @see @c WebCookieJar.
         *
         * @since BlackBerry 10.0.0
         */
        bb::cascades::WebCookieJar* cookieJar() const;

    public Q_SLOTS:

        /*!
         * @brief Clears all data stored by this @c WebView.
         *
         * This is analogous to calling @c clearAutofillData(), @c clearCache(),
         * @c clearCookies(), @c clearCredentials(), @c clearLocalStorage() and
         * @c clearWebFileSystem().
         *
         * @since BlackBerry 10.0.0
         */
        void clear();

        /*!
         * @brief Clears the form AutoFill data accumulated in this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearAutofillData();

        /*!
         * @brief Clears the cache accumulated by this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearCache();

        /*!
         * @brief Clears the cookie database stored for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearCookies();

        /*!
         * @brief Clears the login credentials accumulated in this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearCredentials();

        /*!
         * @brief Clears any databases kept by this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearDatabases();

        /*!
         * @brief Clears the local storage for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearLocalStorage();

        /*!
         * @brief Clears the web file system for this @c WebView.
         *
         * @since BlackBerry 10.0.0
         */
        void clearWebFileSystem();

    public:

        /*! @cond PRIVATE */
        WebStorage(WebStoragePrivate &dd);
        virtual ~WebStorage();
       /*! @endcond */

    private:
       /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebStorage)
        Q_DISABLE_COPY(WebStorage)

        WebStoragePrivate* const d_ptr;
       /*! @endcond */
    };

}
}

QML_DECLARE_TYPE(bb::cascades::WebStorage)

#endif	/* cascades_webstorage_h */
