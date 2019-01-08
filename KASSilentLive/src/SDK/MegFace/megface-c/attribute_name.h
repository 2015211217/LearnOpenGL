#pragma once

#include "megface-c/landmark.h"

/*! \brief Get the attribute name string given a flag.
 */
inline const char* MGF_attribute_name(MGFLandmarkAttributeFlag flag) {
#define L(x) \
    case x:  \
        return #x
    switch (flag) {
        L(MGF_LMKATTR_LANDMARK_OCCLUSION);
        L(MGF_LMKATTR_EYE_CLOSED_STATUS);
        L(MGF_LMKATTR_FACE_POSE);
        L(MGF_LMKATTR_BLURRINESS);
        L(MGF_LMKATTR_GAZE);
        L(MGF_LMKATTR_AGE);
        L(MGF_LMKATTR_GENDER);
        L(MGF_LMKATTR_EYE_OCCLUSION);
        L(MGF_LMKATTR_MOUTH_OCCLUSION);
        L(MGF_LMKATTR_MOUTH_OPEN_STATUS);
        L(MGF_LMKATTR_PRED);
        L(MGF_LMKATTR_PROD);
        L(MGF_LMKATTR_ATTENTION);
        L(MGF_LMKATTR_NOSE_OCCLUSION);
        L(MGF_LMKATTR_MINORITY);
        L(MGF_LMKATTR_HEADWEAR);
        L(MGF_LMKATTR_BEARD);
        L(MGF_LMKATTR_RACE);
        L(MGF_LMKATTR_EXPRESSION);
        default:
            return "(unknown attribute)";
    }
#undef L
}

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
