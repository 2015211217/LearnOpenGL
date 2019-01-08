#pragma once

/* \file include/megcommon-c/logging.h
 * \brief This file defines the function to control the verboseness of the logs.
 */

#include "macro.h"

/*! \brief The log level.
 * \ingroup dtype
 *
 * Logging is enabled only in the development version of the library. All the
 * logging including the error messages are removed in the release version.
 */
typedef enum MGFLogLevel {
    MGF_LOG_DEBUG = 0, /*!< The most verbose level, printing debugging info */
    MGF_LOG_PROFILER,  /*!< Printing profiler results */
    MGF_LOG_INFO,      /*!< The default level */
    MGF_LOG_WARN,      /*!< Printing warnings */
    MGF_LOG_ERROR      /*!< The least verbose level, printing errors only */
} MGFLogLevel;

MGF_CAPI_BEGIN

/*! \brief Set the log level.
 * \param[in] level The level to set to
 */
MGF_CAPI void MGF_set_log_level(MGFLogLevel level);

/*! \brief Get the log level.
 * \param[out] level The current level
 */
MGF_CAPI void MGF_get_log_level(MGFLogLevel* level);

MGF_CAPI_END

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
