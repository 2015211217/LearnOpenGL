/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/version.h
 * \brief This file defines the function to get the version of the library.
 */

#include <stddef.h>
#include <stdint.h>

#include "megcommon-c/macro.h"

MGF_CAPI_BEGIN

/*! \brief Get the version of the library.
 * \param[out] result The start address of the version string in the format of
 * "vx.y.z".
 *
 * Valid version strings are like: "v2.0.3", "v2.2.0-beta3" and "v2.3.0-rc4".
 */
MGF_CAPI void MGF_get_version(const char** result);

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
