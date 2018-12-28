/* -*- mode:c -*- */
#pragma once

/*! \file include/megcommon-c/macro.h
 * \brief This file defines API-related macros.
 */

/*! \def MGF_CAPI_BEGIN
 * \brief The start of API declaration.
 */

/*! \def MGF_CAPI_END
 * \brief The end of API declaration.
 */

/*! \def MGF_CAPI
 * \brief The API function decorator.
 */

/*! \def MGF_DEPRECATED
 * \brief The API is deprecated.
 */

/* clang-format off */
#ifdef __cplusplus
    #define MGF_CAPI_BEGIN extern "C" {
    #define MGF_CAPI_END }
#else
    #define MGF_CAPI_BEGIN
    #define MGF_CAPI_END
#endif

#if MGF_SHARED_LIBRARY
    #if defined(_WIN32)
        #if MGF_EXPORT
            #define MGF_CAPI __declspec(dllexport)
        #else
            #define MGF_CAPI __declspec(dllimport)
        #endif
    #else
        #if MGF_EXPORT
            #define MGF_CAPI __attribute__((visibility("default")))
        #else
            #define MGF_CAPI
        #endif
    #endif
#else
    #define MGF_CAPI
#endif

#ifdef __GNUC__
    #define MGF_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
    #define MGF_DEPRECATED __declspec(deprecated)
#else
    #define MGF_DEPRECATED
#endif

/* clang-format on */

#ifndef MGF_MEGFACE_HEADER_CHECKER_v2_7_7_r1_build_789
#define MGF_MEGFACE_HEADER_CHECKER_v2_7_7_r1_build_789

MGF_CAPI_BEGIN
void MGF_megface_header_checker_v2_7_7_r1_build_789() __attribute__((weak));
MGF_CAPI void MGF_megface_v2_7_7_r1_build_789();
MGF_CAPI_END

void MGF_megface_header_checker_v2_7_7_r1_build_789() {
  (void) MGF_megface_v2_7_7_r1_build_789();
}

#endif
