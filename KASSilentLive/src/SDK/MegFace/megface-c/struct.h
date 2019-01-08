/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/struct.h
 * \brief This file defines the structures and enumerations that is widely used
 * in the library.
 */

#include "megcommon-c/struct.h"

/*! \brief The pose information of a face, represented in Euler angles.
 * \ingroup dtype
 *
 * There are many kinds of Euler angles. Here the applied is the intrinsic
 * Tait-Bryan angles, also known as the nautical angles.
 *
 * See https://en.wikipedia.org/wiki/Euler_angles#Tait.E2.80.93Bryan_angles for
 * more information.
 */
typedef struct MGFPose {
    float roll;  /*!< Radius around nose */
    float pitch; /*!< Radius up and down */
    float yaw;   /*!< Radius left and right */
} MGFPose;

/*! \brief Genders.
 * \ingroup dtype
 */
typedef enum MGFGender {
    MGF_MALE = 0,
    MGF_FEMALE,
    MGF_GENDER_COUNT,
} MGFGender;

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
