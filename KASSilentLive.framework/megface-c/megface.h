/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/megface.h
 * \brief This file includes other headers.
 */

#include "megface-c/age_gender_context.h"
#include "megface-c/blurness_context.h"
#include "megface-c/detector_context.h"
#include "megface-c/detector_rect_context.h"
#include "megface-c/eye_status_context.h"
#include "megface-c/feature_context.h"
#include "megface-c/image.h"
#include "megface-c/landmark.h"
#include "megface-c/landmark_context.h"
#include "megface-c/landmark_name.h"
#include "megface-c/landmark_refiner_context.h"
#include "megface-c/logging.h"
#include "megface-c/macro.h"
#include "megface-c/minority_context.h"
#include "megface-c/misc.h"
#include "megface-c/mouth_status_context.h"
#include "megface-c/pose_context.h"
#include "megface-c/quality_context.h"
#include "megface-c/struct.h"
#include "megface-c/tracker_context.h"
#include "megface-c/version.h"

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
