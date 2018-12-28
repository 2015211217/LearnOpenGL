/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/keypoint.h
 * \brief This file defines the keypoint tags and related structures.
 */

#include <stddef.h>
#include <stdint.h>

#include "megcommon-c/struct.h"
/*! \brief keypoint tags.
 * \ingroup dtype
 */

typedef enum MGHKeypointTag {
    MGH_WRIST = 0,
    MGH_TMCP,
    MGH_TPIP,
    MGH_TDIP,
    MGH_TTIP,
    MGH_IMCP,
    MGH_IPIP,
    MGH_IDIP,
    MGH_ITIP,
    MGH_MMCP,
    MGH_MPIP,
    MGH_MDIP,
    MGH_MTIP,
    MGH_RMCP,
    MGH_RPIP,
    MGH_RDIP,
    MGH_RTIP,
    MGH_PMCP,
    MGH_PPIP,
    MGH_PDIP,
    MGH_PTIP,
            
    MGH_KEYPOINT_TAG_COUNT
} MGHKeypointTag;

/*! \brief A group of keypoints indicating a hand.
 *
 * The keypoints are stored in tag-point pairs.
 * The tags and points are stored correspondingly in the tag and point array.
 * The score is the confidence of hand recognition.
 */
typedef struct MGHKeypointMap {
    MGHKeypointTag tags[MGH_KEYPOINT_TAG_COUNT];
    MGFPoint2f points[MGH_KEYPOINT_TAG_COUNT];
    size_t size;
} MGHKeypointMap;
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
