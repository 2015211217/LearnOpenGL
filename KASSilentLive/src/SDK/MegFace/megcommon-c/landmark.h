/* -*- mode:c -*- */
#pragma once

/* \file include/meggface-c/landmark.h
 * \brief This file defines the landmark tags and related structures.
 */

#include <stddef.h>
#include <stdint.h>

#include "megcommon-c/struct.h"
/*! \brief Landmark tags.
 * \ingroup dtype
 */
typedef enum MGFLandmarkTag {
    MGF_LEFTEYEBROW_LEFTCORNER = 0,
    MGF_LEFTEYEBROW_RIGHTCORNER,
    MGF_LEFTEYEBROW_UPPERLEFTQUARTER,
    MGF_LEFTEYEBROW_UPPERMIDDLE,
    MGF_LEFTEYEBROW_UPPERRIGHTQUARTER,
    MGF_LEFTEYEBROW_LOWERLEFTQUARTER,
    MGF_LEFTEYEBROW_LOWERMIDDLE,
    MGF_LEFTEYEBROW_LOWERRIGHTQUARTER,
    MGF_RIGHTEYEBROW_LEFTCORNER = 16,
    MGF_RIGHTEYEBROW_RIGHTCORNER,
    MGF_RIGHTEYEBROW_UPPERLEFTQUARTER,
    MGF_RIGHTEYEBROW_UPPERMIDDLE,
    MGF_RIGHTEYEBROW_UPPERRIGHTQUARTER,
    MGF_RIGHTEYEBROW_LOWERLEFTQUARTER,
    MGF_RIGHTEYEBROW_LOWERMIDDLE,
    MGF_RIGHTEYEBROW_LOWERRIGHTQUARTER,
    MGF_LEFTEYE_LEFTCORNER = 32,
    MGF_LEFTEYE_RIGHTCORNER,
    MGF_LEFTEYE_TOP,
    MGF_LEFTEYE_BOTTOM,
    MGF_LEFTEYE_CENTER,
    MGF_LEFTEYE_PUPIL,
    MGF_LEFTEYE_UPPERLEFTQUARTER,
    MGF_LEFTEYE_UPPERRIGHTQUARTER,
    MGF_LEFTEYE_LOWERLEFTQUARTER,
    MGF_LEFTEYE_LOWERRIGHTQUARTER,
    MGF_RIGHTEYE_LEFTCORNER = 48,
    MGF_RIGHTEYE_RIGHTCORNER,
    MGF_RIGHTEYE_TOP,
    MGF_RIGHTEYE_BOTTOM,
    MGF_RIGHTEYE_CENTER,
    MGF_RIGHTEYE_PUPIL,
    MGF_RIGHTEYE_UPPERLEFTQUARTER,
    MGF_RIGHTEYE_UPPERRIGHTQUARTER,
    MGF_RIGHTEYE_LOWERLEFTQUARTER,
    MGF_RIGHTEYE_LOWERRIGHTQUARTER,
    MGF_NOSE_LEFT = 64,
    MGF_NOSE_RIGHT,
    MGF_NOSE_TIP,
    MGF_NOSE_CONTOURLOWERMIDDLE,
    MGF_NOSE_CONTOURLEFT1,
    MGF_NOSE_CONTOURLEFT2,
    MGF_NOSE_CONTOURLEFT3,
    MGF_NOSE_CONTOURRIGHT1,
    MGF_NOSE_CONTOURRIGHT2,
    MGF_NOSE_CONTOURRIGHT3,
    MGF_MOUTH_LEFTCORNER = 80,
    MGF_MOUTH_RIGHTCORNER,
    MGF_MOUTH_UPPERLIPTOP,
    MGF_MOUTH_UPPERLIPBOTTOM,
    MGF_MOUTH_LOWERLIPTOP,
    MGF_MOUTH_LOWERLIPBOTTOM,
    MGF_MOUTH_UPPERLIPLEFTCONTOUR1,
    MGF_MOUTH_UPPERLIPLEFTCONTOUR2,
    MGF_MOUTH_UPPERLIPLEFTCONTOUR3,
    MGF_MOUTH_UPPERLIPRIGHTCONTOUR1,
    MGF_MOUTH_UPPERLIPRIGHTCONTOUR2,
    MGF_MOUTH_UPPERLIPRIGHTCONTOUR3,
    MGF_MOUTH_LOWERLIPLEFTCONTOUR1,
    MGF_MOUTH_LOWERLIPLEFTCONTOUR2,
    MGF_MOUTH_LOWERLIPLEFTCONTOUR3,
    MGF_MOUTH_LOWERLIPRIGHTCONTOUR1,
    MGF_MOUTH_LOWERLIPRIGHTCONTOUR2,
    MGF_MOUTH_LOWERLIPRIGHTCONTOUR3,
    MGF_MOUTH_MIDDLE,
    MGF_CONTOUR_CHIN = 112,
    MGF_CONTOUR_LEFT1 = 113,
    MGF_CONTOUR_LEFT2,
    MGF_CONTOUR_LEFT3,
    MGF_CONTOUR_LEFT4,
    MGF_CONTOUR_LEFT5,
    MGF_CONTOUR_LEFT6,
    MGF_CONTOUR_LEFT7,
    MGF_CONTOUR_LEFT8,
    MGF_CONTOUR_LEFT9,
    MGF_CONTOUR_RIGHT1 = 145,
    MGF_CONTOUR_RIGHT2,
    MGF_CONTOUR_RIGHT3,
    MGF_CONTOUR_RIGHT4,
    MGF_CONTOUR_RIGHT5,
    MGF_CONTOUR_RIGHT6,
    MGF_CONTOUR_RIGHT7,
    MGF_CONTOUR_RIGHT8,
    MGF_CONTOUR_RIGHT9,

    MGF_LANDMARK_84P_TAG_COUNT,

    MGF_LEFTCHEEK = 200,
    MGF_RIGHTCHEEK,
    MGF_LEFTEYEBROW_RIGHTCORNER1,
    MGF_LEFTEYEBROW_RIGHTCORNER2,
    MGF_RIGHTEYEBROW_LEFTCORNER1,
    MGF_RIGHTEYEBROW_LEFTCORNER2,
    MGF_NOSE_LEFT2,
    MGF_NOSE_RIGHT2,
    MGF_NOSE_RIGHT1,
    MGF_NOSE_CENTER1,
    MGF_NOSE_CENTER2,
    MGF_NOSE_CENTER3,
    MGF_CONTOUR_DENSE_LEFT1,
    MGF_CONTOUR_DENSE_LEFT2,
    MGF_CONTOUR_DENSE_LEFT3,
    MGF_CONTOUR_DENSE_LEFT4,
    MGF_CONTOUR_DENSE_LEFT5,
    MGF_CONTOUR_DENSE_LEFT6,
    MGF_CONTOUR_DENSE_LEFT7,
    MGF_CONTOUR_DENSE_LEFT8,
    MGF_CONTOUR_DENSE_LEFT9,
    MGF_CONTOUR_DENSE_RIGHT9,
    MGF_CONTOUR_DENSE_RIGHT8,
    MGF_CONTOUR_DENSE_RIGHT7,
    MGF_CONTOUR_DENSE_RIGHT6,
    MGF_CONTOUR_DENSE_RIGHT5,
    MGF_CONTOUR_DENSE_RIGHT4,
    MGF_CONTOUR_DENSE_RIGHT3,
    MGF_CONTOUR_DENSE_RIGHT2,
    MGF_CONTOUR_DENSE_RIGHT1,
    MGF_LEFTEYEBROW_DENSE_UP1,
    MGF_LEFTEYEBROW_DENSE_UP2,
    MGF_LEFTEYEBROW_DENSE_UP3,
    MGF_LEFTEYEBROW_DENSE_UP4,
    MGF_LEFTEYEBROW_DENSE_DOWN4,
    MGF_LEFTEYEBROW_DENSE_DOWN3,
    MGF_LEFTEYEBROW_DENSE_DOWN2,
    MGF_LEFTEYEBROW_DENSE_DOWN1,
    MGF_RIGHTEYEBROW_DENSE_UP1,
    MGF_RIGHTEYEBROW_DENSE_UP2,
    MGF_RIGHTEYEBROW_DENSE_UP3,
    MGF_RIGHTEYEBROW_DENSE_UP4,
    MGF_RIGHTEYEBROW_DENSE_DOWN4,
    MGF_RIGHTEYEBROW_DENSE_DOWN3,
    MGF_RIGHTEYEBROW_DENSE_DOWN2,
    MGF_RIGHTEYEBROW_DENSE_DOWN1,
    MGF_LEFTEYE_ADD_LEFTCORNER,
    MGF_LEFTEYE_ADD_UP1,
    MGF_LEFTEYE_ADD_UP2,
    MGF_LEFTEYE_ADD_UP3,
    MGF_LEFTEYE_ADD_RIGHTCORNER,
    MGF_LEFTEYE_ADD_DOWN3,
    MGF_LEFTEYE_ADD_DOWN2,
    MGF_LEFTEYE_ADD_DOWN1,
    MGF_LEFTEYE_ADD_PUPIL,
    MGF_LEFTEYE_ADDDENSE_UP11,
    MGF_LEFTEYE_ADDDENSE_UP12,
    MGF_LEFTEYE_ADDDENSE_UP13,
    MGF_LEFTEYE_ADDDENSE_UP21,
    MGF_LEFTEYE_ADDDENSE_UP22,
    MGF_LEFTEYE_ADDDENSE_UP23,
    MGF_LEFTEYE_ADDDENSE_UP31,
    MGF_LEFTEYE_ADDDENSE_UP32,
    MGF_LEFTEYE_ADDDENSE_UP33,
    MGF_LEFTEYE_ADDDENSE_UP41,
    MGF_LEFTEYE_ADDDENSE_UP42,
    MGF_LEFTEYE_ADDDENSE_UP43,
    MGF_LEFTEYE_ADDDENSE_DOWN43,
    MGF_LEFTEYE_ADDDENSE_DOWN42,
    MGF_LEFTEYE_ADDDENSE_DOWN41,
    MGF_LEFTEYE_ADDDENSE_DOWN33,
    MGF_LEFTEYE_ADDDENSE_DOWN32,
    MGF_LEFTEYE_ADDDENSE_DOWN31,
    MGF_LEFTEYE_ADDDENSE_DOWN23,
    MGF_LEFTEYE_ADDDENSE_DOWN22,
    MGF_LEFTEYE_ADDDENSE_DOWN21,
    MGF_LEFTEYE_ADDDENSE_DOWN13,
    MGF_LEFTEYE_ADDDENSE_DOWN12,
    MGF_LEFTEYE_ADDDENSE_DOWN11,
    MGF_RIGHTEYE_ADD_RIGHTCORNER,
    MGF_RIGHTEYE_ADD_UP1,
    MGF_RIGHTEYE_ADD_UP2,
    MGF_RIGHTEYE_ADD_UP3,
    MGF_RIGHTEYE_ADD_LEFTCORNER,
    MGF_RIGHTEYE_ADD_DOWN3,
    MGF_RIGHTEYE_ADD_DOWN2,
    MGF_RIGHTEYE_ADD_DOWN1,
    MGF_RIGHTEYE_ADD_PUPIL,
    MGF_RIGHTEYE_ADDDENSE_UP11,
    MGF_RIGHTEYE_ADDDENSE_UP12,
    MGF_RIGHTEYE_ADDDENSE_UP13,
    MGF_RIGHTEYE_ADDDENSE_UP21,
    MGF_RIGHTEYE_ADDDENSE_UP22,
    MGF_RIGHTEYE_ADDDENSE_UP23,
    MGF_RIGHTEYE_ADDDENSE_UP31,
    MGF_RIGHTEYE_ADDDENSE_UP32,
    MGF_RIGHTEYE_ADDDENSE_UP33,
    MGF_RIGHTEYE_ADDDENSE_UP41,
    MGF_RIGHTEYE_ADDDENSE_UP42,
    MGF_RIGHTEYE_ADDDENSE_UP43,
    MGF_RIGHTEYE_ADDDENSE_DOWN43,
    MGF_RIGHTEYE_ADDDENSE_DOWN42,
    MGF_RIGHTEYE_ADDDENSE_DOWN41,
    MGF_RIGHTEYE_ADDDENSE_DOWN33,
    MGF_RIGHTEYE_ADDDENSE_DOWN32,
    MGF_RIGHTEYE_ADDDENSE_DOWN31,
    MGF_RIGHTEYE_ADDDENSE_DOWN23,
    MGF_RIGHTEYE_ADDDENSE_DOWN22,
    MGF_RIGHTEYE_ADDDENSE_DOWN21,
    MGF_RIGHTEYE_ADDDENSE_DOWN13,
    MGF_RIGHTEYE_ADDDENSE_DOWN12,
    MGF_RIGHTEYE_ADDDENSE_DOWN11,
    MGF_MOUTH_ADD_LEFTCORNER,
    MGF_MOUTH_ADD_UP1,
    MGF_MOUTH_ADD_UP2,
    MGF_MOUTH_ADD_UP3,
    MGF_MOUTH_ADD_UP4,
    MGF_MOUTH_ADD_UP5,
    MGF_MOUTH_ADD_RIGHTCORNER,
    MGF_MOUTH_ADD_DOWN5,
    MGF_MOUTH_ADD_DOWN4,
    MGF_MOUTH_ADD_DOWN3,
    MGF_MOUTH_ADD_DOWN2,
    MGF_MOUTH_ADD_DOWN1,
    MGF_MOUTH_ADD_UPLIP1,
    MGF_MOUTH_ADD_UPLIP2,
    MGF_MOUTH_ADD_UPLIP3,
    MGF_MOUTH_ADD_DOWNLIP3,
    MGF_MOUTH_ADD_DOWNLIP2,
    MGF_MOUTH_ADD_DOWNLIP1,
    MGF_MOUTH_ADDDENSE_UP11,
    MGF_MOUTH_ADDDENSE_UP12,
    MGF_MOUTH_ADDDENSE_UP13,
    MGF_MOUTH_ADDDENSE_UP21,
    MGF_MOUTH_ADDDENSE_UP22,
    MGF_MOUTH_ADDDENSE_UP23,
    MGF_MOUTH_ADDDENSE_UP31,
    MGF_MOUTH_ADDDENSE_UP41,
    MGF_MOUTH_ADDDENSE_UP51,
    MGF_MOUTH_ADDDENSE_UP52,
    MGF_MOUTH_ADDDENSE_UP53,
    MGF_MOUTH_ADDDENSE_UP61,
    MGF_MOUTH_ADDDENSE_UP62,
    MGF_MOUTH_ADDDENSE_UP63,
    MGF_MOUTH_ADDDENSE_DOWN63,
    MGF_MOUTH_ADDDENSE_DOWN62,
    MGF_MOUTH_ADDDENSE_DOWN61,
    MGF_MOUTH_ADDDENSE_DOWN53,
    MGF_MOUTH_ADDDENSE_DOWN52,
    MGF_MOUTH_ADDDENSE_DOWN51,
    MGF_MOUTH_ADDDENSE_DOWN43,
    MGF_MOUTH_ADDDENSE_DOWN42,
    MGF_MOUTH_ADDDENSE_DOWN41,
    MGF_MOUTH_ADDDENSE_DOWN33,
    MGF_MOUTH_ADDDENSE_DOWN32,
    MGF_MOUTH_ADDDENSE_DOWN31,
    MGF_MOUTH_ADDDENSE_DOWN23,
    MGF_MOUTH_ADDDENSE_DOWN22,
    MGF_MOUTH_ADDDENSE_DOWN21,
    MGF_MOUTH_ADDDENSE_DOWN13,
    MGF_MOUTH_ADDDENSE_DOWN12,
    MGF_MOUTH_ADDDENSE_DOWN11,
    MGF_MOUTH_ADDDENSE_UPLIP11,
    MGF_MOUTH_ADDDENSE_UPLIP12,
    MGF_MOUTH_ADDDENSE_UPLIP13,
    MGF_MOUTH_ADDDENSE_UPLIP21,
    MGF_MOUTH_ADDDENSE_UPLIP22,
    MGF_MOUTH_ADDDENSE_UPLIP23,
    MGF_MOUTH_ADDDENSE_UPLIP31,
    MGF_MOUTH_ADDDENSE_UPLIP32,
    MGF_MOUTH_ADDDENSE_UPLIP33,
    MGF_MOUTH_ADDDENSE_UPLIP41,
    MGF_MOUTH_ADDDENSE_UPLIP42,
    MGF_MOUTH_ADDDENSE_UPLIP43,
    MGF_MOUTH_ADDDENSE_DOWNLIP43,
    MGF_MOUTH_ADDDENSE_DOWNLIP42,
    MGF_MOUTH_ADDDENSE_DOWNLIP41,
    MGF_MOUTH_ADDDENSE_DOWNLIP33,
    MGF_MOUTH_ADDDENSE_DOWNLIP32,
    MGF_MOUTH_ADDDENSE_DOWNLIP31,
    MGF_MOUTH_ADDDENSE_DOWNLIP23,
    MGF_MOUTH_ADDDENSE_DOWNLIP22,
    MGF_MOUTH_ADDDENSE_DOWNLIP21,
    MGF_MOUTH_ADDDENSE_DOWNLIP13,
    MGF_MOUTH_ADDDENSE_DOWNLIP12,
    MGF_MOUTH_ADDDENSE_DOWNLIP11,

    MGF_LANDMARK_TAG_COUNT
} MGFLandmarkTag;

/*! \brief A group of landmarks indicating a face.
 *
 * The landmarks are stored in tag-point pairs.
 * The tags and points are stored correspondingly in the tag and point array.
 * The score is the confidence of face recognition.
 */
typedef struct MGFLandmarkMap {
    MGFLandmarkTag tags[MGF_LANDMARK_TAG_COUNT];
    MGFPoint2f points[MGF_LANDMARK_TAG_COUNT];
    size_t size;
    float score;
} MGFLandmarkMap;

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
