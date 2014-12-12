/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_PIM_GLOBAL_HPP
#define BB_PIM_GLOBAL_HPP


#include <QtGlobal>

#if defined(BB_STATIC_PIM_LIB)
#   define BB_PIM_EXPORT
// Leave out until library is actually shared
#else
#   if defined(BB_BUILD_PIM_LIB)
#       define BB_PIM_EXPORT    Q_DECL_EXPORT
#   else
#       define BB_PIM_EXPORT    Q_DECL_IMPORT
#   endif
#endif

#endif // BB_PIM_GLOBAL_HPP
