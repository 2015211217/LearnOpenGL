#pragma once

/* \file include/megcommon-c/blurness_context.h
 * \brief This file defines the functions to predict blurness.
 */

#include "landmark.h"

/*! \brief Get the landmark name string given a landmark tag.
 */
inline const char* MGF_landmark_name(MGFLandmarkTag tag) {
#define L(x) \
    case x:  \
        return #x
    switch (tag) {
        L(MGF_LEFTEYEBROW_LEFTCORNER);
        L(MGF_LEFTEYEBROW_RIGHTCORNER);
        L(MGF_LEFTEYEBROW_UPPERLEFTQUARTER);
        L(MGF_LEFTEYEBROW_UPPERMIDDLE);
        L(MGF_LEFTEYEBROW_UPPERRIGHTQUARTER);
        L(MGF_LEFTEYEBROW_LOWERLEFTQUARTER);
        L(MGF_LEFTEYEBROW_LOWERMIDDLE);
        L(MGF_LEFTEYEBROW_LOWERRIGHTQUARTER);
        L(MGF_RIGHTEYEBROW_LEFTCORNER);
        L(MGF_RIGHTEYEBROW_RIGHTCORNER);
        L(MGF_RIGHTEYEBROW_UPPERLEFTQUARTER);
        L(MGF_RIGHTEYEBROW_UPPERMIDDLE);
        L(MGF_RIGHTEYEBROW_UPPERRIGHTQUARTER);
        L(MGF_RIGHTEYEBROW_LOWERLEFTQUARTER);
        L(MGF_RIGHTEYEBROW_LOWERMIDDLE);
        L(MGF_RIGHTEYEBROW_LOWERRIGHTQUARTER);
        L(MGF_LEFTEYE_LEFTCORNER);
        L(MGF_LEFTEYE_RIGHTCORNER);
        L(MGF_LEFTEYE_TOP);
        L(MGF_LEFTEYE_BOTTOM);
        L(MGF_LEFTEYE_CENTER);
        L(MGF_LEFTEYE_PUPIL);
        L(MGF_LEFTEYE_UPPERLEFTQUARTER);
        L(MGF_LEFTEYE_UPPERRIGHTQUARTER);
        L(MGF_LEFTEYE_LOWERLEFTQUARTER);
        L(MGF_LEFTEYE_LOWERRIGHTQUARTER);
        L(MGF_RIGHTEYE_LEFTCORNER);
        L(MGF_RIGHTEYE_RIGHTCORNER);
        L(MGF_RIGHTEYE_TOP);
        L(MGF_RIGHTEYE_BOTTOM);
        L(MGF_RIGHTEYE_CENTER);
        L(MGF_RIGHTEYE_PUPIL);
        L(MGF_RIGHTEYE_UPPERLEFTQUARTER);
        L(MGF_RIGHTEYE_UPPERRIGHTQUARTER);
        L(MGF_RIGHTEYE_LOWERLEFTQUARTER);
        L(MGF_RIGHTEYE_LOWERRIGHTQUARTER);
        L(MGF_NOSE_LEFT);
        L(MGF_NOSE_RIGHT);
        L(MGF_NOSE_TIP);
        L(MGF_NOSE_CONTOURLOWERMIDDLE);
        L(MGF_NOSE_CONTOURLEFT1);
        L(MGF_NOSE_CONTOURLEFT2);
        L(MGF_NOSE_CONTOURLEFT3);
        L(MGF_NOSE_CONTOURRIGHT1);
        L(MGF_NOSE_CONTOURRIGHT2);
        L(MGF_NOSE_CONTOURRIGHT3);
        L(MGF_MOUTH_LEFTCORNER);
        L(MGF_MOUTH_RIGHTCORNER);
        L(MGF_MOUTH_UPPERLIPTOP);
        L(MGF_MOUTH_UPPERLIPBOTTOM);
        L(MGF_MOUTH_LOWERLIPTOP);
        L(MGF_MOUTH_LOWERLIPBOTTOM);
        L(MGF_MOUTH_UPPERLIPLEFTCONTOUR1);
        L(MGF_MOUTH_UPPERLIPLEFTCONTOUR2);
        L(MGF_MOUTH_UPPERLIPLEFTCONTOUR3);
        L(MGF_MOUTH_UPPERLIPRIGHTCONTOUR1);
        L(MGF_MOUTH_UPPERLIPRIGHTCONTOUR2);
        L(MGF_MOUTH_UPPERLIPRIGHTCONTOUR3);
        L(MGF_MOUTH_LOWERLIPLEFTCONTOUR1);
        L(MGF_MOUTH_LOWERLIPLEFTCONTOUR2);
        L(MGF_MOUTH_LOWERLIPLEFTCONTOUR3);
        L(MGF_MOUTH_LOWERLIPRIGHTCONTOUR1);
        L(MGF_MOUTH_LOWERLIPRIGHTCONTOUR2);
        L(MGF_MOUTH_LOWERLIPRIGHTCONTOUR3);
        L(MGF_MOUTH_MIDDLE);
        L(MGF_CONTOUR_CHIN);
        L(MGF_CONTOUR_LEFT1);
        L(MGF_CONTOUR_LEFT2);
        L(MGF_CONTOUR_LEFT3);
        L(MGF_CONTOUR_LEFT4);
        L(MGF_CONTOUR_LEFT5);
        L(MGF_CONTOUR_LEFT6);
        L(MGF_CONTOUR_LEFT7);
        L(MGF_CONTOUR_LEFT8);
        L(MGF_CONTOUR_LEFT9);
        L(MGF_CONTOUR_RIGHT1);
        L(MGF_CONTOUR_RIGHT2);
        L(MGF_CONTOUR_RIGHT3);
        L(MGF_CONTOUR_RIGHT4);
        L(MGF_CONTOUR_RIGHT5);
        L(MGF_CONTOUR_RIGHT6);
        L(MGF_CONTOUR_RIGHT7);
        L(MGF_CONTOUR_RIGHT8);
        L(MGF_CONTOUR_RIGHT9);
        default:
            return "(unknown landmark)";
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
