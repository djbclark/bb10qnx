/* Copyright (C) 2011-2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_webpage_h
#define cascades_webpage_h

#include <bb/cascades/bbcascades_global.h>
#include <stdint.h>
#include <QObject>
#include <QUrl>
#include <QVariantMap>

#include <bb/cascades/core/displaydirection.h>
#include <bb/cascades/web/javascriptworld.h>
#include <bb/cascades/web/webfindflag.h>
#include <bb/cascades/web/webnavigationrequest.h>

namespace bb {
    namespace cascades {

    class WebDownloadRequest;
    class WebPagePrivate;
    class WebPageEvent;
    class WebResourceRequestFilter;
    class WebSettings;
    class WebStorage;
    class WebViewPrivate;

    /*!
     * @brief A webpage that can be used when the app needs to interact with web content but not display it.
     *
     * This class can also be used together with a @c WebPageCompositor in order to render web content to a custom OpenGL scene.
     *
     * If user input events need to be forwarded to the webpage, or simulated, a @c WebPageEventHandler can be used
     * together with this class.
     *
     * @note The @c WebPage class must only be used on the main thread. It's not reentrant, unlike @c WebPageCompositor and
     *       @c WebPageEventHandler. The compositor and event handler can be created on another thread and connected to the
     *       webpage if given its @c uniqueId. Since the @c uniqueId is a string, it can be marshalled to the thread where
     *       the compositor or event handler was created. See @c WebPageCompositor for sample code.
     *
     * @c WebPage is normally used from C++, but here is an example of using @c WebPage in QML:
     *
     * @snippet tad/examples/controls/webpage/assets/main.qml webpage_qml1
     *
     * Add the following lines to the C++ main program to register @c WebPage with QML:
     *
     * @snippet tad/examples/controls/webpage/src/webpage.cpp webpage1
	 *
     * @xmlonly
     * <apigrouping group="User interface/Web"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT WebPage : public QObject
    {
        Q_OBJECT

        /*!
         * @brief The unique ID of this webpage.
         *
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString uniqueId READ uniqueId CONSTANT)

        /*!
         * @brief Settings for this webpage.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::WebSettings* settings READ settings CONSTANT)

        /*!
         * @brief Access to the web storage interface used to clear databases and access cookies.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bb::cascades::WebStorage* storage READ storage CONSTANT)

        /*!
         * @brief The title of the currently loaded webpage.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QString title READ title NOTIFY titleChanged FINAL)

        /*!
         * @brief The currently loaded URL.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged FINAL)

        /*!
         * @brief The favicon of the currently loaded webpage.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(QUrl icon READ icon NOTIFY iconChanged FINAL)

        /*!
         * @brief True if the navigation history contains a previous page.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool canGoBack READ canGoBack NOTIFY navigationHistoryChanged FINAL)

        /*!
         * @brief True if the navigation history contains a next page.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool canGoForward READ canGoForward NOTIFY navigationHistoryChanged FINAL)

        /*!
         * @brief True if the web view is currently loading a webpage, false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged FINAL)

        /*!
         * @brief The progress of loading the current webpage.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(int loadProgress READ loadProgress NOTIFY loadProgressChanged)

        /*!
         * @brief Suggested maximum content scale factor for pinch zoom.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float maxContentScale READ maxContentScale NOTIFY maxContentScaleChanged FINAL)

        /*!
         * @brief Suggested minimum content scale factor for pinch zoom.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(float minContentScale READ minContentScale NOTIFY minContentScaleChanged FINAL)

        /*!
         * @brief The webpage to use for displaying modal dialog content.
         *
         * Interaction with the webpage, particularly form controls, can trigger various modal dialogs. These are
         * themselves built from web content, and should be displayed in a separate @c WebPage object.
         *
         * The initial value of this property is 0. The modal dialog functionality is optional, and is disabled when
         * the value of the @c dialogWebPage property is 0.
         *
         * If a separate @c WebPage to be used for modal dialogs is provided by setting this property to a non-0 value,
         * the app must handle the @c dialogShowRequested() signal to display that webpage to the user, and allow
         * interaction with that webpage. @c WebPageCompositor and @c :WebPageEventHandler can
         * be used for this purpose. The app must also handle the @c dialogHideRequested() signal to hide that webpage.
         *
         * @note If the @c dialogWebPage is non-0 but is not displayed and/or not interactive after prompted by
         *       @c dialogShowRequested(), the modal dialog sequence will not be executed properly, and
         *       @c dialogHideRequested() will never be emitted. It's therefore not recommended to change the value of
         *       this property unless the app is prepared to handle the @c dialogShowRequested() signal properly.
         *
         * @see @c WebPageCompositor, @c WebPageEventHandler.
         *
         * @since BlackBerry 10.0.0
         */
        Q_PROPERTY(WebPage* dialogWebPage READ dialogWebPage WRITE setDialogWebPage RESET resetDialogWebPage NOTIFY dialogWebPageChanged FINAL)

    public:
        /*!
         * @brief Constructs a @c WebPage.
         *
         * @param parent Optional parent for this object.
         *
         * @since BlackBerry 10.0.0
         */
        explicit WebPage(QObject *parent = 0);
        virtual ~WebPage();

        /*!
         * @brief Gets the unique ID of the underlying WebKit webpage instance.
         *
         * This is used with @c WebPageCompositor::connectToWebPage() and @c WebPageEventHandler::connectToWebPage().
         *
         * @since BlackBerry 10.0.0
         */
        QString uniqueId() const;

        //! @copydoc WebView::settings()
        bb::cascades::WebSettings *settings() const;

        //! @copydoc WebView::storage()
        bb::cascades::WebStorage *storage();

        //! @copydoc WebView::title()
        QString title() const;

        /*!
         * @brief The currently loaded URL.
         *
         * @return The currently loaded URL.
         *
         * @since BlackBerry 10.0.0
         */
        QUrl url() const;

        //! @copydoc WebView::icon()
        QUrl icon() const;

        //! @copydoc WebView::setUrl()
        void setUrl(const QUrl& url);

        //! @copydoc WebView::loadData()
        void loadData(const QByteArray& data, const QString& mimeType, const QUrl& baseUrl);

        /*!
         * @brief Loads a file from the local file system.
         *
         * @param fileUrl Must be a file:/// URL, typically constructed using @c QUrl::fromLocalFile.
         * @param mimeType The mime type of the file contents.
         *
         * @since BlackBerry 10.0.0
         */
        void loadFile(const QUrl& fileUrl, const QString& mimeType);

        //! @copydoc WebView::canGoBack()
        bool canGoBack() const;

        //! @copydoc WebView::canGoForward()
        bool canGoForward() const;

        //! @copydoc WebView::loading()
        bool loading() const;

        //! @copydoc WebView::loadProgress()
        int loadProgress() const;

        //! @copydoc WebView::evaluateJavaScript()
        int evaluateJavaScript(const QString& script, JavaScriptWorld::Type world);

        //! @copydoc WebView::setResourceRequestFilter()
        void setResourceRequestFilter(WebResourceRequestFilter* filter);

        //! @copydoc WebView::findText()
        void findText(const QString& subString, WebFindFlag::Types options = 0);

        //! @copydoc WebView::minContentScale()
        float minContentScale() const;

        //! @copydoc WebView::maxContentScale()
        float maxContentScale() const;

        //! @return The WebPage to use for modal dialogs.
        bb::cascades::WebPage* dialogWebPage() const;

        /*! @brief Downloads a file to the local file system.
         *
         * The provided @c WebDownloadRequest object indicates what to download, and where. It also emits
         * various signals during the downloading process to indicate how the operation progresses.
         *
         * @param request An instance of @c WebDownloadRequest indicating what to download, and where.
         *
         * @since BlackBerry 10.0.0
         */
        void download(WebDownloadRequest* request);

    Q_SIGNALS:
        /*!
         * @brief Emitted when the page is initialized and ready to go.
         *
         * @since BlackBerry 10.0.0
         */
        void initialized(const QString& uniqueId);

        //! @copydoc WebView::loadingChanged()
        void loadingChanged(bb::cascades::WebLoadRequest* loadRequest);

        //! @copydoc WebView::loadProgressChanged()
        void loadProgressChanged(int loadProgress);

        //! @copydoc WebView::titleChanged()
        void titleChanged(const QString& title);

        //! @copydoc WebView::navigationHistoryChanged()
        void navigationHistoryChanged();

        //! @copydoc WebView::urlChanged()
        void urlChanged(const QUrl& url);

        //! @copydoc WebView::iconChanged()
        void iconChanged(const QUrl& icon);

        //! @copydoc WebView::navigationRequested()
        void navigationRequested(bb::cascades::WebNavigationRequest* request);

        //! @copydoc WebView::javaScriptResult()
        void javaScriptResult(int resultId, const QVariant& result);

        //! @copydoc WebView::javaScriptInterrupted()
        void javaScriptInterrupted();

        //! @copydoc WebView::messageReceived()
        void messageReceived(const QVariantMap& message);

        //! @copydoc WebView::microFocusChanged()
        void microFocusChanged();

        //! @copydoc WebView::minContentScaleChanged()
        void minContentScaleChanged(float minContentScale);

        //! @copydoc WebView::maxContentScaleChanged()
        void maxContentScaleChanged(float maxContentScale);

        /*!
         * @brief Emitted when interaction with the webpage causes it to want to display a context menu.
         *
         * @param actionSet The @c ActionSet to display in the context menu.
         *
         * @since BlackBerry 10.0.0
         */
        void contextMenuShowRequested(bb::cascades::ActionSet* actionSet);

        /*!
         * @brief Emitted when interaction with the webpage causes it to want to hide the context menu.
         *
         * @since BlackBerry 10.0.0
         */
        void contextMenuHideRequested();

        /*!
         * @brief Emitted when interaction with the webpage causes it to want to display another page in a modal dialog.
         *
         * The page that should be displayed is the one returned by @c dialogWebPage().
         *
         * @since BlackBerry 10.0.0
         */
        void dialogShowRequested();

        /*!
         * @brief Emitted when interaction with the webpage causes it to want to hide a previously requested modal dialog.
         *
         * @since BlackBerry 10.0.0
         */
        void dialogHideRequested();

        /*!
         * @brief Emitted when the @c dialogWebPage property changes.
         *
         * @since BlackBerry 10.0.0
         */
        void dialogWebPageChanged(bb::cascades::WebPage* newDialogWebPage);

        /*!
         * @brief Emitted when the webpage wants to enter full screen mode.
         *
         * The web content may request the webpage to be shown in full screen mode. If appropriate, the embedder can listen
         * to this signal and start rendering the webpage full screen until prompted by the @c exitFullScreenRequested() signal.
         */
        void enterFullScreenRequested();

        /*!
         * @brief Emitted when the webpage wants to exit full screen mode.

         */
        void exitFullScreenRequested();

    public Q_SLOTS:
        //! @copydoc WebView::goBack()
        void goBack();

        //! @copydoc WebView::goForward()
        void goForward();

        //! @copydoc WebView::stop()
        void stop();

        //! @copydoc WebView::reload()
        void reload();

        //! @copydoc WebView::postMessage()
        void postMessage(const QString& message);

        /*!
         * @brief Sets the selection of the webpage to a range starting at (x1, y1) in webpage content coordinates,
         * extending to (x2, y2).
         *
         * @param x1 X coordinate of the start point for the range to select, in content coordinates.
         * @param y1 Y coordinate of the start point for the range to select, in content coordinates.
         * @param x2 X coordinate of the end point for the range to select, in content coordinates.
         * @param y2 Y coordinate of the end point for the range to select, in content coordinates.
         *
         * @since BlackBerry 10.0.0
         */
        void setSelection(float x1, float y1, float x2, float y2);

        /*!
         * @brief Sets the webpage to use for displaying modal dialog content.
         *
         * @since BlackBerry 10.0.0
         */
        void setDialogWebPage(bb::cascades::WebPage* page);

        /*!
         * @brief Resets the webpage to use for displaying modal dialog content to 0, effectively disabling the modal dialog feature for this @c WebPage.
         *
         * @since BlackBerry 10.0.0
         */
        void resetDialogWebPage();

    private:
       /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(WebPage)
        Q_DISABLE_COPY(WebPage)

        WebPagePrivate * const d_ptr;
       /*! @endcond */
    }; // class WebPage

    } // namespace cascades
} // namespace bb

#endif	/* cascades_webpage_h */
