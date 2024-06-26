//
//  MLCDefines.h
//  MLCompute
//
//  Copyright © 2019 Apple. All rights reserved.
//

#ifndef MLComputeDefines_h
#define MLComputeDefines_h

/*
 *  Identify compiler capabilities
 *  clang will define these. Other compilers maybe not.
 */

#ifndef __has_attribute
#    define __has_attribute(a)   0
#endif
#ifndef __has_feature
#    define __has_feature(f)     0
#endif
#ifndef __has_extension
#    define __has_extension(e)   0
#endif

/*
 *  Macros to describe MLCompute functionality availability by operating system revision.
 */

#ifdef MLCOMPUTE_HIDE_AVAILABILITY
#    define MLCOMPUTE_ENUM_AVAILABLE_STARTING(...)
#    define MLCOMPUTE_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED(...)
#    define MLCOMPUTE_CLASS_AVAILABLE_STARTING(...)
#    define MLCOMPUTE_PROTOCOL_AVAILABLE_STARTING(...)
#    define MLCOMPUTE_AVAILABLE_STARTING(...)
#    define MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED(...)
#    define MLCOMPUTE_UNAVAILABLE(...)
#    define MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(MACOS, IOS, TVOS, ...) 
#else
#    define MLCOMPUTE_ENUM_AVAILABLE_STARTING(...)                    __API_AVAILABLE(__VA_ARGS__)
#    define MLCOMPUTE_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED(...)     __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#    define MLCOMPUTE_CLASS_AVAILABLE_STARTING(...)                   __API_AVAILABLE(__VA_ARGS__)
#    define MLCOMPUTE_PROTOCOL_AVAILABLE_STARTING(...)                __API_AVAILABLE(__VA_ARGS__)
#    define MLCOMPUTE_AVAILABLE_STARTING(...)                         __API_AVAILABLE(__VA_ARGS__)
#    define MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED(...)          __API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#    define MLCOMPUTE_UNAVAILABLE(...)                                __API_UNAVAILABLE(__VA_ARGS__)
#    define MLCOMPUTE_AVAILABLE_STARTING_BUT_DEPRECATED_MACOS14(ARG1, ARG2, ARG3, ...) \
       MLCOMPUTE_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED("Use Metal Performance Shaders Graph or BNNS instead.", macos(ARG1, 14.3)) \
       MLCOMPUTE_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED("Use Metal Performance Shaders Graph or BNNS instead.", ios(ARG2, 17.4)) \
       MLCOMPUTE_ENUM_AVAILABLE_STARTING_BUT_DEPRECATED("Use Metal Performance Shaders Graph or BNNS instead.", tvos(ARG3, 17.4))
#endif

#endif /* MLComputeDefines_h */
