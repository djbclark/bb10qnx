/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_GLOBAL_HPP
#define BB_MULTIMEDIA_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(BB_STATIC_MULTIMEDIA_LIB)
#   define BB_MULTIMEDIA_EXPORT
#else
#   if defined(BB_BUILD_MULTIMEDIA_LIB)
#       define BB_MULTIMEDIA_EXPORT    Q_DECL_EXPORT
#   else
#       define BB_MULTIMEDIA_EXPORT    Q_DECL_IMPORT
#   endif
#endif

// Deprecation warning macro - only supported by GCC
#if defined(__GNUC__)
#   define BB_DEVICE_DEPRECATED    __attribute__ ((deprecated))
#else
#   define BB_DEVICE_DEPRECATED
#endif

#endif // BB_MULTIMEDIA_GLOBAL_HPP
