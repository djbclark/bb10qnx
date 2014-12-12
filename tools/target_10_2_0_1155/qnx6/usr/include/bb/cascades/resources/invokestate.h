/* Copyright (C) 2012-2013 Research In Motion Limited. Proprietary and confidential. */

#ifndef cascades_invokestate_h
#define cascades_invokestate_h

#include <bb/cascades/bbcascades_global.h>
#include <QObject>

namespace bb {
namespace cascades {

/*!
 * @brief The different states of an invocation.
 *
 * @xmlonly
 * <apigrouping group="User interface/Application structure"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BBCASCADES_EXPORT InvokeState {
    Q_GADGET
    Q_ENUMS(Type)

public:
    /*!
     * @brief The current state or the final result of an @c InvokeActionItem being processed.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {
        /*!
         * @brief The state is unknown.
         *
         * @since BlackBerry 10.0.0
         */
        Unknown = 0,
        /*!
         * @brief The query is in progress.
         *
         * @since BlackBerry 10.0.0
         */
        Querying = 1,
        // 2 is reserved for future use (Selecting)
        /*!
         * @brief The invocation is in progress.
         *
         * @since BlackBerry 10.0.0
         */
        Invoking = 3,
        /*!
         * @brief A finished state, indicating that the invocation is complete.
         *
         * @since BlackBerry 10.0.0
         */
        Invoked = 4,
        /*!
         * @brief A finished state, indicating that the invocation is cancelled.
         *
         * @since BlackBerry 10.0.0
         */
        Cancelled = 5,
        /*!
         * @brief A finished state, indicating that the invocation resulted in an error.
         *
         * @since BlackBerry 10.0.0
         */
        Error = 6
    };

private:
    /* @cond PRIVATE */
    InvokeState();
    ~InvokeState();
    /* @endcond */
};

} // namespace cascades
} // namespace bb

#endif // cascades_invokestate_h
