/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 * Proprietary and confidential.
*/

#ifndef cascades_developmentsupport_h
#define cascades_developmentsupport_h

#include <bb/cascades/BaseObject>

namespace bb {
    namespace cascades {

    class DevelopmentSupportPrivate;

    /*!
     *
     * @brief Provides a signal for receiving live QML updates from the QNX Momentics IDE.
     *
     * This class provides a signal for receiving live QML updates from Momentics. This
     * makes it faster to work with QML based UI since asset updates can be sent to the
     * running application, causing greatly increased development turn around time.
     *
     * By listening to the assetsChanged signal the application gets notified when assets
     * are changed and updated from Momentics and will be able to refresh the QML scene
     * graph. All updated files and folders in the application assets folder will be sent
     * to the device, this includes for example image assets and xml/json models.
     *
     * @note The assetsChanged signal will only be sent if the application is built in
     * debug and launched from Momentics.
     *
     * @warning Since there is currently no way to clear the image cache, image assets that
     * are already loaded into the image cache cannot be updated in a running application.
     *
     * Here is an example slot connected to the assetsChanged signal that will reload all
     * QML but keep the old data and context properties (notice however that all QML states
     * will get lost):
     *
     * @code
     * void ApplicationUI::reloadQML(QUrl mainFile) {
     *     // Get the context of the first scene root to keep the contextProperties
     *     QDeclarativeContext* context = QDeclarativeEngine::contextForObject(mRoot);
     *
     *     // Clear the QML cache
     *     QDeclarativeEngine* appEngine = context->engine();
     *     appEngine->clearComponentCache();
     *
     *     // Reload all QML
     *     QmlDocument* qml = QmlDocument::create(mainFile);
     *     AbstractPane *root = qml->createRootObject<AbstractPane>(context);
     *     qml->setParent(root);
     *     Application::instance()->setScene(root);
     * }
     * @endcode
     *
     * To set this up use the following code in the end of the application constructor:
     * (after the call setScene)
     *
     * @code
     * // mRoot declared in the application header file as:
     * // bb::cascades::AbstractPane* mRoot;
     *
     * mRoot = Application::instance()->scene();
     * mRoot->setParent(this);
     * DevelopmentSupport* devSupport = new DevelopmentSupport(this);
     * connect(devSupport, SIGNAL(assetsChanged(QUrl)), this, SLOT(reloadQML(QUrl)));
     * connect(Application::instance(),SIGNAL(aboutToQuit()),this,SLOT(cleanup()));
     * @endcode
     *
     * In the code above we make sure we save the scene root to be able to use its context
     * for the reloaded QML files. Below we declare the cleanup slot to clean up that scene
     * root.
     *
     * @code
     * void ApplicationUI::cleanup() {
     *     Application::instance()->setScene(0);
     *     mRoot->setParent(0);
     *     delete mRoot;
     * }
     * @endcode
     *
     * @xmlonly
     *     <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT DevelopmentSupport : public BaseObject {
        Q_OBJECT

    public:

        /*!
         * @brief Constructs a @c %DevelopmentSupport.
         *
         * @since BlackBerry 10.2.0
         */
        explicit DevelopmentSupport(QObject *parent=0);

        virtual ~DevelopmentSupport();

    Q_SIGNALS:

        /*!
         * @brief Emitted when updated assets have been uploaded from Momentics
         *
         * @param mainQmlFile The QML file set as main file from Momentics
         *
         * @since BlackBerry 10.2.0
         */
        void assetsChanged(const QUrl & mainQmlFile);

    private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(DevelopmentSupport)
        Q_DISABLE_COPY(DevelopmentSupport)
        /*! @endcond */

    };

    }
}

#endif /* cascades_developmentsupport_h */
