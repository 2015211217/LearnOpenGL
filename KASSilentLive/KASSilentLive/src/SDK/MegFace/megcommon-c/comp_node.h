/* -*- mode:c -*- */
#pragma once

/* \file include/megcommon-c/comp_node.h
 * \brief This file defines the functions to operate computing node in MegBrain
 * directly.
 */

#include <stddef.h>
#include <stdint.h>

#include "macro.h"
#include "struct.h"

MGF_CAPI_BEGIN

/*! \brief Basic function pointer
 *
 * receive a void pointer as parameter
 */
typedef void (*MGFFunction)(void*);

/*! \brief Dispatch a function to a specific computing node.
 *
 * \param[in] device_option The computing node to run on
 * \param[in] function The function to be dispatched
 * \param[in] data The data to be sent as the argument to function
 */
MGF_CAPI MGFErrorCode MGF_dispatch_func_to_comp_node(
        MGFDeviceOption device_option, MGFFunction function, void* data);

/*! \brief Set CPU resource usage level when performing synchronization
 * \param level CPU waiting level:
 *      0. condition var (the default)
 *      1. busy wait with yield
 *      2. busy wait
 */
MGF_CAPI MGFErrorCode MGF_set_cpu_sync_level(int level);

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
